#ifndef PARKINGGARAGE_H
#define PARKINGGARAGE_H

#include "ParkingFloor.h"
#include "Vehicle.h"
#include <vector>
#include <string>
#include <utility>

class ParkingGarage {
    private:
        std::vector<ParkingFloor*> floors;
        std::vector<std::pair<std::string, Vehicle*>> parkedVehicles;
        std::vector<std::pair<std::string, ParkingSlot*>> ticketRecords;
        
        int ticketCounter;
        int paymentFailureCounter;
        
        std::string generateTicketId();
        void processPayment(double amount, const std::string& plate);
        
    public:
        ParkingGarage();
        
        void addFloor(ParkingFloor* floor);
        std::string parkVehicle(Vehicle* vehicle, int hour, int minute);
        std::pair<double, std::string> unparkVehicle(const std::string& ticketId, int hour, int minute);
        std::string reserveVIPSlot(const std::string& plate, int durationHours);
        void showCurrentOccupation() const;
        void generateDailyReport() const;
};

#endif //PARKINGGARAGE_H