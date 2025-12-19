#ifndef PARKINGFLOOR_H
#define PARKINGFLOOR_H

#include "ParkingSlot.h"
#include <vector>

class ParkingFloor {
    private:
        int floorNumber;
        std::vector<ParkingSlot*> slots;
        
    public:
        ParkingFloor(int floorNum);
        
        void addSlot(ParkingSlot* slot);
        ParkingSlot* findAvailableSlot(const Vehicle& vehicle);
        std::vector<ParkingSlot*> getAllSlots() const;
        
        int getFloorNumber() const;
        int getTotalSlots() const;
        int getOccupiedSlots() const;
        int getAvailableSlotsByType(const std::string& type) const;
        double getUtilization() const;
};

#endif //PARKINGFLOOR_H