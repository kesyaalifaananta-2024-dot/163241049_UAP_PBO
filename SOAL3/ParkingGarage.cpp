#include "ParkingGarage.h"
#include "Exceptions.h"
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

ParkingGarage::ParkingGarage() : ticketCounter(1), paymentFailureCounter(0) {}

string ParkingGarage::generateTicketId() {
    return "TICKET-" + to_string(ticketCounter++);
}

void ParkingGarage::processPayment(double amount, const string& plate) {
    // Simulasi sederhana: setiap pembayaran ke-3 gagal
    paymentFailureCounter++;
    if (paymentFailureCounter % 3 == 0) {
        throw PaymentException("Payment failed for vehicle " + plate + ". Please try again.");
    }
    
    // Simulasi: jika amount negatif atau nol
    if (amount <= 0) {
        throw PaymentException("Invalid payment amount: Rp " + to_string((int)amount));
    }
}

void ParkingGarage::addFloor(ParkingFloor* floor) {
    floors.push_back(floor);
}

string ParkingGarage::parkVehicle(Vehicle* vehicle, int hour, int minute) {
    ParkingSlot* availableSlot = nullptr;
    ParkingFloor* targetFloor = nullptr;
    
    for (auto floor : floors) {
        ParkingSlot* slot = floor->findAvailableSlot(*vehicle);
        if (slot) {
            availableSlot = slot;
            targetFloor = floor;
            break;
        }
    }
    
    if (!availableSlot) {
        throw NoAvailableSlotException();
    }
    
    string ticketId = generateTicketId();
    availableSlot->occupy(vehicle->getPlate());
    vehicle->setArrivalTime(hour, minute);
    
    parkedVehicles.push_back({ticketId, vehicle});
    ticketRecords.push_back({ticketId, availableSlot});
    
    cout << "Vehicle " << vehicle->getPlate() 
         << " parked in " << availableSlot->getTypeName() 
         << " slot " << availableSlot->getId() 
         << " on floor " << targetFloor->getFloorNumber() 
         << ". Ticket ID: " << ticketId << endl;
    
    return ticketId;
}

pair<double, string> ParkingGarage::unparkVehicle(const string& ticketId, int hour, int minute) {
    Vehicle* vehicle = nullptr;
    ParkingSlot* slot = nullptr;
    int vehicleIndex = -1;
    
    for (size_t i = 0; i < ticketRecords.size(); i++) {
        if (ticketRecords[i].first == ticketId) {
            slot = ticketRecords[i].second;
            vehicle = parkedVehicles[i].second;
            vehicleIndex = i;
            break;
        }
    }
    
    if (!vehicle || !slot) {
        throw InvalidTicketException();
    }
    
    ArrivalTime arrival = vehicle->getArrivalTime();
    int arrivalMinutes = arrival.hour * 60 + arrival.minute;
    int currentMinutes = hour * 60 + minute;
    int durationMinutes = currentMinutes - arrivalMinutes;
    int durationHours = (durationMinutes + 59) / 60;
    
    double baseRate = vehicle->calculateRate(durationHours);
    double finalRate = slot->calculateSurcharge(baseRate);
    
    // PROSES PEMBAYARAN dengan PaymentException
    try {
        processPayment(finalRate, vehicle->getPlate());
    } catch (const PaymentException& e) {
        // RETHROW: Demonstrasi rethrow exception
        cout << "Payment processing error, rethrowing..." << endl;
        throw; // Rethrow exception
    }
    
    slot->vacate();
    
    string plate = vehicle->getPlate();
    
    if (vehicleIndex != -1) {
        parkedVehicles.erase(parkedVehicles.begin() + vehicleIndex);
        ticketRecords.erase(ticketRecords.begin() + vehicleIndex);
    }
    
    cout << "\n--------------------------------------------------\n";
    cout << "Vehicle " << plate << " unparked. Duration: " 
         << durationHours << " hours. Total cost: Rp " << finalRate << endl;
    
    return {finalRate, plate};
}

string ParkingGarage::reserveVIPSlot(const string& plate, int durationHours) {
    for (auto floor : floors) {
        vector<ParkingSlot*> slots = floor->getAllSlots();
        for (auto slot : slots) {
            VIPSlot* vipSlot = dynamic_cast<VIPSlot*>(slot);
            if (vipSlot && !vipSlot->isOccupied()) {
                if (vipSlot->reserve(plate, durationHours)) {
                    cout << "\n--------------------------------------------------\n";
                    return "VIP slot reserved for " + plate + 
                           " for " + to_string(durationHours) + " hours";
                }
            }
        }
    }
    throw ReservationException();
}

void ParkingGarage::showCurrentOccupation() const {
    cout << "\n----------- CURRENT PARKING OCCUPATION -----------" << endl;
    for (const auto& floor : floors) {
        cout << "\nFloor " << floor->getFloorNumber() << ":" << endl;
        cout << "  Total slots: " << floor->getTotalSlots() 
             << ", Occupied: " << floor->getOccupiedSlots() 
             << ", Available: " << (floor->getTotalSlots() - floor->getOccupiedSlots()) << endl;
        
        vector<ParkingSlot*> slots = floor->getAllSlots();
        for (auto slot : slots) {
            cout << "    " << slot->getId() << " [" << slot->getTypeName() << "]: ";
            if (slot->isOccupied()) {
                cout << "Occupied by " << slot->getVehiclePlate();
            } else {
                cout << "Available";
                
                VIPSlot* vipSlot = dynamic_cast<VIPSlot*>(slot);
                if (vipSlot && vipSlot->isReserved()) {
                    cout << " (Reserved for " << vipSlot->getReservedFor() << ")";
                }
            }
            cout << endl;
        }
    }
}

void ParkingGarage::generateDailyReport() const {
    cout << "\n-------------- DAILY PARKING REPORT --------------" << endl;
    
    int totalVehicles = parkedVehicles.size();
    int totalSlots = 0;
    int totalOccupied = 0;
    
    int carCount = 0, motorcycleCount = 0, evCount = 0;
    for (const auto& record : parkedVehicles) {
        VehicleType type = record.second->getVehicleType();
        if (type == VehicleType::Car) carCount++;
        else if (type == VehicleType::Motorcycle) motorcycleCount++;
        else if (type == VehicleType::EV) evCount++;
    }
    
    cout << "\nFloor utilization:" << endl;
    for (const auto& floor : floors) {
        int floorSlots = floor->getTotalSlots();
        int floorOccupied = floor->getOccupiedSlots();
        double utilization = floor->getUtilization();
        totalSlots += floorSlots;
        totalOccupied += floorOccupied;
        
        cout << "  Floor " << floor->getFloorNumber() << ": " 
             << floorOccupied << "/" << floorSlots << endl;
    }
    
    cout << "\nTotal vehicles parked: " << totalVehicles << endl;
    cout << "  Cars: " << carCount << endl;
    cout << "  Motorcycles: " << motorcycleCount << endl;
    cout << "  EVs: " << evCount << endl;
    
    cout << "\nAvailable slots by type (per floor):" << endl;
    for (const auto& floor : floors) {
        cout << "Floor " << floor->getFloorNumber() << ": ";
        cout << "Regular: " << floor->getAvailableSlotsByType("Regular") << ", ";
        cout << "EV: " << floor->getAvailableSlotsByType("EV") << ", ";
        cout << "VIP: " << floor->getAvailableSlotsByType("VIP") << endl;
    }
}