//===========================================
//library yang digunakan
//===========================================
#include <iostream>    //untuk input/output ke console
#include <string>      //untuk tipe data string
#include <vector>      //untuk menyimpan kumpulan monster
#include <stdexcept>   //untuk exception handling (runtime_error, invalid_argument)

using namespace std;   //menggunakan namespace std agar tidak perlu menulis std:: setiap kali

//===========================================
//base class: monster (abstract class)
//===========================================
class Monster {
protected:
    string name;           //nama monster (dilindungi, hanya bisa diakses oleh class turunan)
    int health;            //health points (hp) monster
    int attackPower;       //attack power (atk) monster
    int resourcePoints;    //resource points (rp) untuk skill khusus

public:
    //constructor: menginisialisasi monster dengan nama, hp, atk, dan rp
    Monster(string n, int h, int ap, int rp) 
        : name(n), health(h), attackPower(ap), resourcePoints(rp) {}

    //virtual destructor: memastikan destructor class turunan dipanggil dengan benar
    virtual ~Monster() {}

    //==================== getters (encapsulation) ====================
    //fungsi untuk mendapatkan nama monster (membaca saja, tidak mengubah)
    string getName() const { return name; }
    
    //fungsi untuk mendapatkan hp monster
    int getHealth() const { return health; }
    
    //fungsi untuk mendapatkan attack power monster
    int getAttackPower() const { return attackPower; }
    
    //fungsi untuk mendapatkan rp monster
    int getResourcePoints() const { return resourcePoints; }

    //==================== methods utama ====================
    
    //fungsi untuk menerima damage (pengurangan hp)
    void takeDamage(int damage) {
        if (damage < 0) throw invalid_argument("Damage cannot be negative."); //validasi
        health -= damage;  //kurangi hp dengan damage yang diterima
        if (health < 0) health = 0;  //pastikan hp tidak negatif
    }

    //fungsi untuk healing (penambahan hp)
    void heal(int amount) {
        if (amount < 0) throw invalid_argument("Heal amount cannot be negative."); //validasi
        health += amount;  //tambah hp
    }

    //fungsi untuk menggunakan rp (resource points)
    void useRP(int cost) {
        if (cost > resourcePoints) throw runtime_error("Not enough RP!"); //validasi
        resourcePoints -= cost;  //kurangi rp sesuai cost skill
    }

    //fungsi untuk regenerasi rp
    void regenRP(int amount) {
        resourcePoints += amount;  //tambah rp
    }

    //==================== overloading ====================
    //versi 1: serangan dasar tanpa bonus
    void attack(Monster& target) {
        target.takeDamage(attackPower);  //panggil takedamage pada target
        cout << name << " attacks " << target.getName() << " for " << attackPower << " damage!" << endl;
    }

    //versi 2: serangan dengan bonus damage (overloading)
    void attack(Monster& target, int bonusDamage) {
        int total = attackPower + bonusDamage;  //hitung total damage
        target.takeDamage(total);  //terapkan damage ke target
        cout << name << " attacks " << target.getName() << " with bonus " << bonusDamage 
             << "! Total damage: " << total << endl;
    }

    //==================== pure virtual methods (polymorphism) ====================
    //fungsi virtual murni - harus di-override oleh class turunan
    virtual void basicAttack(Monster& target) = 0;  //serangan dasar (berbeda tiap monster)
    virtual void defend() = 0;                      //skill bertahan (berbeda tiap monster)
    virtual void ultimate(Monster& target) = 0;     //skill ultimate (berbeda tiap monster)

    //fungsi untuk menampilkan status monster
    virtual void displayStatus() const {
        cout << "[" << name << "] HP: " << health << " | RP: " << resourcePoints << endl;
    }
};

//===========================================
//derived class: firemonster (mewarisi monster)
//===========================================
class FireMonster : public Monster {
public:
    //constructor: inisialisasi firemonster dengan statistik spesifik
    FireMonster(string n) : Monster(n, 90, 25, 0) {}  //hp: 90, atk: 25, rp: 0

    //override method basicattack dari class monster
    void basicAttack(Monster& target) override {
        cout << name << " uses Basic Attack!" << endl;
        attack(target);  //panggil fungsi attack dasar dari class monster
    }

    //override method defend dari class monster
    void defend() override {
        int cost = 8;  //biaya rp untuk skill flame aura
        if (resourcePoints < cost) {
            throw runtime_error("Not enough RP for Flame Aura!");
        }
        useRP(cost);  //kurangi rp sesuai biaya
        cout << name << " activates Flame Aura! Damage reduced by 50% and reflects 5 damage when attacked." << endl;
        //catatan: implementasi damage reduction perlu logic tambahan di game loop
    }

    //override method ultimate dari class monster
    void ultimate(Monster& target) override {
        int cost = 30;  //biaya rp untuk skill firestorm
        if (resourcePoints < cost) {
            throw runtime_error("Not enough RP for FireStorm!");
        }
        useRP(cost);  //kurangi rp sesuai biaya
        int damage = attackPower * 4;  //damage = 4x atk
        target.takeDamage(damage);  //terapkan damage ke target
        cout << name << " casts FireStorm! Deals " << damage 
             << " damage + 5 DOT for 2 turns!" << endl;
        //catatan: implementasi dot (damage over time) perlu logic tambahan
    }
};

//===========================================
//derived class: icemonster (mewarisi monster)
//===========================================
class IceMonster : public Monster {
public:
    //constructor: inisialisasi icemonster dengan statistik spesifik
    IceMonster(string n) : Monster(n, 130, 12, 0) {}  //hp: 130, atk: 12, rp: 0

    //override method basicattack dari class monster
    void basicAttack(Monster& target) override {
        cout << name << " uses Basic Attack!" << endl;
        attack(target);  //panggil fungsi attack dasar
    }

    //override method defend dari class monster
    void defend() override {
        int cost = 15;  //biaya rp untuk skill ice barrier
        if (resourcePoints < cost) {
            throw runtime_error("Not enough RP for Ice Barrier!");
        }
        useRP(cost);  //kurangi rp sesuai biaya
        heal(10);  //icemonster healing 10 hp saat defend
        cout << name << " activates Ice Barrier! Blocks 100% damage this turn and heals 10 HP." << endl;
        //catatan: implementasi block 100% perlu logic tambahan di game loop
    }

    //override method ultimate dari class monster
    void ultimate(Monster& target) override {
        int cost = 20;  //biaya rp untuk skill absolute zero
        if (resourcePoints < cost) {
            throw runtime_error("Not enough RP for Absolute Zero!");
        }
        useRP(cost);  //kurangi rp sesuai biaya
        int damage = attackPower * 2;  //damage = 2x atk
        target.takeDamage(damage);  //terapkan damage ke target
        heal(15);  //icemonster healing 15 hp saat ultimate
        cout << name << " casts Absolute Zero! Deals " << damage 
             << " damage, removes DOT, and heals 15 HP." << endl;
        //catatan: implementasi dot removal perlu logic tambahan
    }
};

//===========================================
//derived class: earthmonster (mewarisi monster)
//===========================================
class EarthMonster : public Monster {
public:
    //constructor: inisialisasi earthmonster dengan statistik spesifik
    EarthMonster(string n) : Monster(n, 100, 18, 0) {}  //hp: 100, atk: 18, rp: 0

    //override method basicattack dari class monster
    void basicAttack(Monster& target) override {
        cout << name << " uses Basic Attack!" << endl;
        attack(target);  //panggil fungsi attack dasar
        regenRP(10);  //earthmonster regenerasi 10 rp setiap basic attack
        cout << name << " regenerates 10 RP!" << endl;
    }

    //override method defend dari class monster
    void defend() override {
        int cost = 10;  //biaya rp untuk skill rock solid
        if (resourcePoints < cost) {
            throw runtime_error("Not enough RP for Rock Solid!");
        }
        useRP(cost);  //kurangi rp sesuai biaya
        cout << name << " activates Rock Solid! Reduces 30% incoming damage and drains 5 RP from opponent." << endl;
        //catatan: implementasi damage reduction dan rp drain perlu logic tambahan
    }

    //override method ultimate dari class monster
    void ultimate(Monster& target) override {
        int cost = 25;  //biaya rp untuk skill tectonic shift
        if (resourcePoints < cost) {
            throw runtime_error("Not enough RP for Tectonic Shift!");
        }
        useRP(cost);  //kurangi rp sesuai biaya
        int damage = attackPower * 2;  //damage = 2x atk
        target.takeDamage(damage);  //terapkan damage ke target
        cout << name << " casts Tectonic Shift! Deals " << damage 
             << " damage and STUNS target (skips next turn)!" << endl;
        //catatan: implementasi stun perlu logic tambahan di game loop
    }
};

//===========================================
//game manager class
//===========================================
class Game {
private:
    vector<Monster*> players;  //vector untuk menyimpan pointer ke monster pemain
    int currentPlayer = 0;     //indeks pemain yang sedang giliran (0 atau 1)

public:
    //destructor: membersihkan memory yang dialokasikan
    ~Game() {
        for (auto player : players) {
            delete player;  //hapus monster dari memory
        }
    }

    //==================== setup game ====================
    void setup() {
        cout << "=========================================\n";
        cout << "     MONSTER BATTLE ARENA - GAME START\n";
        cout << "=========================================\n\n";
        
        //loop untuk 2 pemain
        for (int i = 1; i <= 2; i++) {
            cout << "PLAYER " << i << ", CHOOSE YOUR MONSTER:\n";
            cout << "=========================================\n";
            cout << "1. FireMonster    - High Damage, Low HP\n";
            cout << "   - HP: 90, ATK: 25, RP Regen: 10/turn\n";
            cout << "   - Ultimate: FireStorm (4x ATK + DOT)\n\n";
            
            cout << "2. IceMonster     - High HP, Low Damage\n";
            cout << "   - HP: 130, ATK: 12, RP Regen: 8/turn\n";
            cout << "   - Ultimate: Absolute Zero (2x ATK + Heal)\n\n";
            
            cout << "3. EarthMonster   - Balanced, Fast RP Regen\n";
            cout << "   - HP: 100, ATK: 18, RP Regen: 15/turn\n";
            cout << "   - Ultimate: Tectonic Shift (2x ATK + Stun)\n";
            cout << "=========================================\n";
            
            cout << "Enter choice (1-3): ";
            int choice;
            cin >> choice;

            string name;
            cout << "Enter your monster's name: ";
            cin >> name;

            //buat monster berdasarkan pilihan pemain
            switch (choice) {
                case 1: 
                    players.push_back(new FireMonster(name)); 
                    cout << "\n[+] " << name << " (FireMonster) has joined the battle!\n";
                    break;
                case 2: 
                    players.push_back(new IceMonster(name)); 
                    cout << "\n[+] " << name << " (IceMonster) has joined the battle!\n";
                    break;
                case 3: 
                    players.push_back(new EarthMonster(name)); 
                    cout << "\n[+] " << name << " (EarthMonster) has joined the battle!\n";
                    break;
                default: 
                    cout << "Invalid choice! Defaulting to FireMonster.\n";
                    players.push_back(new FireMonster(name));
            }
            cout << "-----------------------------------------\n";
        }
    }

    //==================== play a turn ====================
    void playTurn() {
        //dapatkan monster pemain yang sedang giliran dan lawannya
        Monster* attacker = players[currentPlayer];
        Monster* defender = players[(currentPlayer + 1) % 2];
        
        cout << "\n=========================================\n";
        cout << "           " << attacker->getName() << "'S TURN\n";
        cout << "=========================================\n";
        
        //tampilkan status kedua monster
        cout << "\nCURRENT STATUS:\n";
        cout << "-------------------------------\n";
        cout << "Attacker: ";
        attacker->displayStatus();
        cout << "Defender: ";
        defender->displayStatus();
        cout << "-------------------------------\n";
        
        //tampilkan menu aksi
        cout << "\nAVAILABLE ACTIONS:\n";
        cout << "1. BASIC ATTACK    - Deal normal damage (0 RP cost)\n";
        cout << "2. DEFEND          - Use defensive skill (varies by monster)\n";
        cout << "3. ULTIMATE        - Use powerful ultimate skill (high RP cost)\n";
        cout << "4. SKIP TURN       - Do nothing, regenerate 10 RP\n";
        
        cout << "\nEnter action (1-4): ";
        int action;
        cin >> action;
        
        //exception handling untuk aksi yang invalid
        try {
            switch (action) {
                case 1:
                    cout << "\n>>> " << attacker->getName() << " chooses BASIC ATTACK!\n";
                    attacker->basicAttack(*defender);
                    break;
                case 2:
                    cout << "\n>>> " << attacker->getName() << " chooses DEFEND!\n";
                    attacker->defend();
                    break;
                case 3:
                    cout << "\n>>> " << attacker->getName() << " chooses ULTIMATE!\n";
                    attacker->ultimate(*defender);
                    break;
                case 4:
                    cout << "\n>>> " << attacker->getName() << " SKIPS turn to regenerate RP.\n";
                    break;
                default:
                    cout << "\n⚠ Invalid action! Turn skipped.\n";
            }
        } catch (const exception& e) {
            cout << "\nERROR: " << e.what() << " Turn skipped.\n";
        }
        
        //regenerasi rp otomatis setiap giliran
        attacker->regenRP(10);
        cout << "\n" << attacker->getName() << " regenerates 10 RP automatically.\n";
        
        //cek apakah defender sudah kalah
        if (defender->getHealth() <= 0) {
            cout << "\n" << defender->getName() << " has been defeated!\n";
        }
        
        //ganti giliran ke pemain berikutnya
        currentPlayer = (currentPlayer + 1) % 2;
        
        cout << "\n=========================================\n";
        cout << "Press Enter to continue to next turn...";
        cin.ignore();  //clear input buffer
        cin.get();     //tunggu user menekan enter
    }

    //==================== check game over ====================
    bool isGameOver() const {
        //game berakhir jika hp salah satu monster <= 0
        for (const auto& player : players) {
            if (player->getHealth() <= 0) return true;
        }
        return false;
    }

    //==================== declare winner ====================
    void declareWinner() const {
        cout << "\n\n";
        cout << "-------------------------------------------\n";
        cout << "             GAME OVER - RESULT            \n";
        cout << "-------------------------------------------\n\n";
        
        //tampilkan status akhir kedua monster
        cout << "FINAL STATUS:\n";
        cout << "-----------------------------------------\n";
        players[0]->displayStatus();
        players[1]->displayStatus();
        cout << "-----------------------------------------\n\n";
        
        //tentukan pemenang
        if (players[0]->getHealth() <= 0 && players[1]->getHealth() <= 0) {
            cout << "DRAW! Both monsters are defeated!\n";
        } else if (players[0]->getHealth() <= 0) {
            cout << "VICTORY! " << players[1]->getName() << " wins the battle!\n";
        } else {
            cout << "VICTORY! " << players[0]->getName() << " wins the battle!\n";
        }
        
        cout << "\n-------------------------------------------\n";
        cout << "     THANK YOU FOR PLAYING!\n";
        cout << "-------------------------------------------\n";
    }

    //==================== run game ====================
    void run() {
        setup();  //setup game: pilih monster
        
        int turnCount = 1;
        //main loop: terus bermain sampai game over
        while (!isGameOver()) {
            cout << "\n\n";
            cout << "-------------------------------------------\n";
            cout << "              TURN " << turnCount << "\n";
            cout << "-------------------------------------------\n";
            
            playTurn();  //mainkan satu giliran
            turnCount++; //naikkan counter turn
        }
        
        declareWinner();  //tampilkan hasil akhir
    }
};

//===========================================
//main function - entry point program
//===========================================
int main() {
       
    //exception handling tingkat atas
    try {
        Game game;  //buat objek game
        game.run(); //jalankan game
    } catch (const exception& e) {
        //tangani exception fatal
        cout << "\nFATAL ERROR: " << e.what() << endl;
        cout << "Game terminated unexpectedly.\n";
        return 1;  //return error code
    }
    
    return 0;  //program selesai dengan sukses
}