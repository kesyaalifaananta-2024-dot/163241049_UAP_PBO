#include <iostream>
#include "ParkingGarage.h"
#include "ParkingFloor.h"
#include "Vehicle.h"
#include "ParkingSlot.h"
#include "Exceptions.h"

using namespace std;

int main() {
    ParkingGarage garage;
    
    // Setup parking floors and slots
    ParkingFloor floor1(1);
    floor1.addSlot(new RegularSlot("R1-01", 1));
    floor1.addSlot(new RegularSlot("R1-02", 1));
    floor1.addSlot(new EVSlot("E1-01", 1));
    floor1.addSlot(new VIPSlot("V1-01", 1));
    
    ParkingFloor floor2(2);
    floor2.addSlot(new RegularSlot("R2-01", 2));
    floor2.addSlot(new EVSlot("E2-01", 2));
    floor2.addSlot(new VIPSlot("V2-01", 2));
    floor2.addSlot(new VIPSlot("V2-02", 2));
    
    garage.addFloor(&floor1);
    garage.addFloor(&floor2);
    
    int choice;
    do {
        cout << "\n--------------------------------------------------\n";
        cout << "             PARKING MANAGEMENT SYSTEM            \n";
        cout << "--------------------------------------------------\n";
        cout << "1. Register vehicle dan park" << endl;
        cout << "2. Unpark (masukkan ticket id)" << endl;
        cout << "3. Reserve VIP slot" << endl;
        cout << "4. Show current occupation" << endl;
        cout << "5. Generate daily report" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;
        cout << "--------------------------------------------------\n";
        
        try {
            switch(choice) {
                case 1: {
                    string plate, owner;
                    int vehicleType;
                    bool needCharging = false;
                    int hour, minute;
                    
                    cout << "Enter plate number: ";
                    cin >> plate;
                    cout << "Enter owner name: ";
                    cin >> owner;
                    
                    cout << "Enter arrival time (hour): ";
                    cin >> hour;
                    cout << "Enter arrival time (minute): ";
                    cin >> minute;
                    
                    cout << "Vehicle type (1 = Car, 2 = Motorcycle, 3 = EV): ";
                    cin >> vehicleType;
                    
                    Vehicle* vehicle = nullptr;
                    if (vehicleType == 1) {
                        vehicle = new Car(plate, owner);
                    } else if (vehicleType == 2) {
                        vehicle = new Motorcycle(plate, owner);
                    } else if (vehicleType == 3) {
                        char charging;
                        cout << "Need charging? (y/n): ";
                        cin >> charging;
                        needCharging = (charging == 'y' || charging == 'Y');
                        vehicle = new EV(plate, owner, needCharging);
                    } else {
                        cout << "Invalid vehicle type!" << endl;
                        break;
                    }
                    
                    string ticket = garage.parkVehicle(vehicle, hour, minute);
                    cout << "Ticket issued: " << ticket << endl;
                    break;
                }
                    
                case 2: {
                    string ticketId;
                    int hour, minute;
                    cout << "Enter ticket ID: ";
                    cin >> ticketId;
                    cout << "Enter current time (hour minute): ";
                    cin >> hour >> minute;
                    
                    try {
                        auto result = garage.unparkVehicle(ticketId, hour, minute);
                        cout << "Payment received: Rp " << result.first 
                             << " for vehicle " << result.second << endl;
                    } catch (const PaymentException& e) {
                        cout << "PAYMENT ERROR: " << e.what() << endl;
                        cout << "Please contact customer service." << endl;
                    }
                    break;
                }
                    
                case 3: {
                    string plate;
                    int hours;
                    cout << "Enter vehicle plate: ";
                    cin >> plate;
                    cout << "Enter reservation duration (hours): ";
                    cin >> hours;
                    
                    string result = garage.reserveVIPSlot(plate, hours);
                    cout << result << endl;
                    break;
                }
                    
                case 4:
                    garage.showCurrentOccupation();
                    break;
                    
                case 5:
                    garage.generateDailyReport();
                    break;
                    
                case 0:
                    cout << "Exiting..." << endl;
                    break;
                    
                default:
                    cout << "Invalid choice!" << endl;
            }
        } catch (const ParkingException& e) {
            cout << "PARKING ERROR: " << e.what() << endl;
        } catch (const exception& e) {
            cout << "Unexpected error: " << e.what() << endl;
        }
        
    } while (choice != 0);
    
    return 0;
}