#include <iostream>
#include <string>
#include <cstdio>
#include <array>

using namespace std;

//BASE CLASS
class Kamar {
    //ENKAPSULASI
    protected:
        bool ketersediaan;
        string fasilitas;
        double harga;
        string kapasitas;
        string tipeKamar;
        string noKamar;

    public:
        //CONSTRUCTOR 
        Kamar(bool kt, string f, double h, string k, string tipe, string no) {
            ketersediaan = kt;
            fasilitas = f;
            harga = h;
            kapasitas = k;
            tipeKamar = tipe;
            noKamar = no;
        }

        Kamar() {
            ketersediaan = false;
            fasilitas = kapasitas = tipeKamar = noKamar = "";
            harga = 0;
        }

        //SETTER & GETTER METHOD
        void setKetersediaan(bool k) {
            ketersediaan = k;
        }

        bool getKetersediaan() { return ketersediaan; }
        string getFasilitas()  { return fasilitas; }
        double getHarga()      { return harga; }
        string getKapasitas()  { return kapasitas; }
        string getTipeKamar()  { return tipeKamar; }
        string getNoKamar()    { return noKamar; } // GETTER untuk noKamar

        //VIRTUAL (UNTUK DI-OVERRIDE)
        virtual double hitungHarga(int lamaNginap) = 0;

        virtual void tampilkanInfo() {
            cout << "\n--------------------------------------------------";
            cout << "\nTipe Kamar    : " << tipeKamar
                 << "\nNo Kamar      : " << noKamar
                 << "\nKetersediaan  : " << (ketersediaan ? "Tersedia" : "Terisi")
                 << "\nFasilitas     : " << fasilitas
                 << "\nKapasitas     : " << kapasitas;
            printf("\nHarga/malam   : Rp %.0f", harga);
            cout << "\n--------------------------------------------------";
        }

        //VIRTUAL DESTRUCTOR
        virtual ~Kamar() {}
};

//CHILD CLASS 1
class Standard : public Kamar {
    public:
        Standard(string no, bool kt) : Kamar(kt, "AC, TV, Wi-Fi, 2 Bed, Kamar Mandi", 699000, "2 orang", "Standard", no) {}

        //OVERRIDE
        double hitungHarga(int lamaNginap) override {
            return (getHarga() * lamaNginap);
        }
};

//CHILD CLASS 2
class Deluxe : public Kamar {
    public:
        Deluxe(string no, bool kt) : Kamar(kt, "AC, TV, Wi-Fi, 2 Bed, Kamar Mandi, Mini Bar, Balcony, Breakfast", 1299000, "2-3 orang", "Deluxe", no) {}

        //OVERRIDE
        double hitungHarga(int lamaNginap) override {
            return (getHarga() * lamaNginap);
        }
};

//CHILD CLASS 3
class Suite : public Kamar {
    public:
        Suite(string no, bool kt) : Kamar(kt, "AC, TV, Wi-Fi, 4 Bed, Bathroom, Mini Bar, Balcony, Breakfast, Living Room, Kitchen, Swimming Pool & Spa", 3999000, "4-6 orang", "Suite", no) {}

        //OVERRIDE
        double hitungHarga(int lamaNginap) override {
            return (getHarga() * lamaNginap);
        }
};

class Reservasi {
    private:
        array<Kamar*, 20> daftarKamar;
        array<string, 20> daftarReservasi;
        array<double, 20> totalReservasi;
        int banyakReservasi;
        int jumlahKamar;

    public:
        Reservasi() {
            banyakReservasi = 0;
            jumlahKamar = 0;
            
            for (int i = 0; i < 20; i++) {
                daftarKamar[i] = nullptr;
            }
            
            inisialisasi();
        }

        void inisialisasi() {
            //Standard
            daftarKamar[0] = new Standard("201", true);
            daftarKamar[1] = new Standard("204", true);
            daftarKamar[2] = new Standard("207", true);
            daftarKamar[3] = new Standard("219", true);
            
            //Deluxe
            daftarKamar[4] = new Deluxe("403", true);
            daftarKamar[5] = new Deluxe("409", true);
            daftarKamar[6] = new Deluxe("412", true);
            daftarKamar[7] = new Deluxe("425", true);
            
            //Suite
            daftarKamar[8] = new Suite("702", true);
            daftarKamar[9] = new Suite("714", true);
            daftarKamar[10] = new Suite("720", true);
            daftarKamar[11] = new Suite("742", true);
            
            jumlahKamar = 12;
        }

        //METHOD UNTUK MENAMPILKAN DAFTAR KAMAR PER TIPE
        void tampilkanDaftarKamar() {
            cout << "\n\n==================================================";
            cout << "\n                DAFTAR TIPE KAMAR                 ";
            cout << "\n==================================================";
            
            //TIPE KAMAR 1: STANDARD
            cout << "\nTIPE KAMAR 1: STANDARD";
            tampilkanKamarPerTipe("Standard");            
            
            //TIPE KAMAR 2: DELUXE
            cout << "\nTIPE KAMAR 2: DELUXE";
            tampilkanKamarPerTipe("Deluxe");
            
            //TIPE KAMAR 3: SUITE
            cout << "\nTIPE KAMAR 3: SUITE";
            tampilkanKamarPerTipe("Suite");
            cout << "\n";
        }

        //METHOD UNTUK MENAMPILKAN KAMAR PER TIPE
        void tampilkanKamarPerTipe(string tipe) {
            string kamarTersedia = "";
            int countTersedia = 0;
            string fasilitasTipe = "";
            string kapasitasTipe = "";
            double hargaTipe = 0;
            
            //Kumpulkan nomor kamar yang tersedia dan ambil data tipe
            for (int i = 0; i < jumlahKamar; i++) {
                if (daftarKamar[i] != nullptr && 
                    daftarKamar[i]->getTipeKamar() == tipe) {
                    
                    //Simpan fasilitas, kapasitas, harga dari kamar pertama
                    if (fasilitasTipe.empty()) {
                        fasilitasTipe = daftarKamar[i]->getFasilitas();
                        kapasitasTipe = daftarKamar[i]->getKapasitas();
                        hargaTipe = daftarKamar[i]->getHarga();
                    }
                    
                    if (daftarKamar[i]->getKetersediaan()) {
                        if (!kamarTersedia.empty()) kamarTersedia += ", ";
                        kamarTersedia += daftarKamar[i]->getNoKamar();
                        countTersedia++;
                    }
                }
            }
            
            //Tampilkan dalam 
            cout << "\nKetersediaan: " << (countTersedia > 0 ? "Ada" : "Penuh");
            
            if (countTersedia > 0) {
                cout << "\nNo Kamar: " << kamarTersedia;
                cout << "\nFasilitas     : " << fasilitasTipe;
                cout << "\nKapasitas     : " << kapasitasTipe;
                printf("\nHarga/malam   : Rp %.0f", hargaTipe);
            }
            cout << "\n--------------------------------------------------";
        }

        //METHOD UNTUK BUAT RESERVASI 
        void buatReservasi(string noKamar, int lamaNginap, string namaTamu) {
            Kamar* kamarDitemukan = nullptr;
            
            //Cari kamar berdasarkan nomor
            for (int i = 0; i < jumlahKamar; i++) {
                if (daftarKamar[i] != nullptr && 
                    daftarKamar[i]->getNoKamar() == noKamar) {
                    kamarDitemukan = daftarKamar[i];
                    break;
                }
            }
            
            if (kamarDitemukan == nullptr) {
                cout << "\nKamar " << noKamar << " tidak ditemukan!\n";
                return;
            }
            
            if (!kamarDitemukan->getKetersediaan()) {
                cout << "\nKamar " << noKamar << " sudah terisi!\n";
                return;
            }
            
            //Hitung total harga
            double total = kamarDitemukan->hitungHarga(lamaNginap);
            
            //Simpan reservasi
            daftarReservasi[banyakReservasi] = "Kamar " + noKamar + " - " + namaTamu;
            totalReservasi[banyakReservasi] = total;
            banyakReservasi++;
            
            //Update status kamar
            kamarDitemukan->setKetersediaan(false);
            
            cout << "\n\n=============== RESERVASI BERHASIL ===============";
            cout << "\nNama Tamu     : " << namaTamu;
            cout << "\nNo Kamar      : " << noKamar;
            cout << "\nTipe Kamar    : " << kamarDitemukan->getTipeKamar();
            cout << "\nLama Menginap : " << lamaNginap << " malam";
            printf("\nTotal Harga   : Rp %.0f", total);
            cout << "\n--------------------------------------------------\n";
        }

        //METHOD UNTUK MENAMPILKAN TOTAL TRANSAKSI
        void tampilkanTotalTransaksi() {
            cout << "\n\n============= TOTAL TRANSAKSI HOTEL ==============";
            
            if (banyakReservasi == 0) {
                cout << "\nBelum ada transaksi.";
            } else {
                double totalPendapatan = 0;
                
                for (int i = 0; i < banyakReservasi; i++) {
                    cout << "\n" << (i + 1) << ". " << daftarReservasi[i];
                    printf(" - Rp %.0f", totalReservasi[i]);
                    totalPendapatan += totalReservasi[i];
                }
                
                cout << "\n--------------------------------------------------";
                printf("\nTotal Pendapatan: Rp %.0f", totalPendapatan);
            }
            cout << "\n==================================================\n";
        }

        //METHOD UNTUK TAMPILKAN STATISTIK
        void tampilkanKetersediaanKamar() {
            int total[3] = {0}; // [0]=Standard, [1]=Deluxe, [2]=Suite
            int tersedia[3] = {0};
            
            for (int i = 0; i < jumlahKamar; i++) {
                if (daftarKamar[i] != nullptr) {
                    string tipe = daftarKamar[i]->getTipeKamar();
                    
                    if (tipe == "Standard") {
                        total[0]++;
                        if (daftarKamar[i]->getKetersediaan()) tersedia[0]++;
                    }
                    else if (tipe == "Deluxe") {
                        total[1]++;
                        if (daftarKamar[i]->getKetersediaan()) tersedia[1]++;
                    }
                    else if (tipe == "Suite") {
                        total[2]++;
                        if (daftarKamar[i]->getKetersediaan()) tersedia[2]++;
                    }
                }
            }
            
            cout << "\n\n=== STATISTIK KAMAR ===";
            cout << "\nSTANDARD: " << tersedia[0] << "/" << total[0] << " tersedia";
            cout << "\nDELUXE  : " << tersedia[1] << "/" << total[1] << " tersedia";
            cout << "\nSUITE   : " << tersedia[2] << "/" << total[2] << " tersedia";
            cout << "\n=======================\n";
        }

        void tampilkanMenu() {
            int pilihan;

            do {
                cout << "\n==================================================";
                cout << "\n                   HOTEL KESYA                    ";
                cout << "\n==================================================";

                cout << "\n1. Tampilkan Tipe Kamar Tersedia";
                cout << "\n2. Reservasi Kamar";
                cout << "\n3. Total Transaksi Hotel";
                cout << "\n4. Ketersediaan Kamar";
                cout << "\n5. Keluar";
                cout << "\nPilih menu (1-5): ";

                cin >> pilihan;

                switch (pilihan) {
                    case 1:
                        tampilkanDaftarKamar();
                        break;

                    case 2: {
                        string noKamar, namaTamu;
                        int lamaNginap;

                        cout << "\nSilahkan lengkapi informasi berikut:";
                        cout << "\nNama                  : ";
                        cin.ignore();
                        getline(cin, namaTamu);
                        cout << "Lama Menginap (malam) : ";
                        cin >> lamaNginap;
                        cout << "Nomor Kamar           : ";
                        cin >> noKamar;

                        buatReservasi(noKamar, lamaNginap, namaTamu);
                        break;
                    }                    

                    case 3:
                        tampilkanTotalTransaksi();
                        break;

                    case 4:
                        tampilkanKetersediaanKamar();
                        break;

                    case 5:
                        cout << "\nTerima kasih telah mampir di Hotel Kesya :D\n";
                        return;
                        
                    default:
                        cout << "\nPilihan tidak valid! Silakan pilih 1-5.\n";
                }
            } while (pilihan != 5);        
        }

        //DESTRUCTOR untuk membersihkan memori
        ~Reservasi() {
            for (int i = 0; i < jumlahKamar; i++) {
                if (daftarKamar[i] != nullptr) {
                    delete daftarKamar[i];
                }
            }
        }
};

int main() {
    Reservasi hotel;
    
    hotel.tampilkanMenu();
    
    return 0;
}