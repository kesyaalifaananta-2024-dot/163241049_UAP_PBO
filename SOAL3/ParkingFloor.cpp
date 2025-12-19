#include "ParkingFloor.h"
#include <vector>

using namespace std;

ParkingFloor::ParkingFloor(int floorNum) : floorNumber(floorNum) {}

void ParkingFloor::addSlot(ParkingSlot* slot) {
    slots.push_back(slot);
}

ParkingSlot* ParkingFloor::findAvailableSlot(const Vehicle& vehicle) {
    for (auto slot : slots) {
        if (slot->canPark(vehicle)) {
            return slot;
        }
    }
    return nullptr;
}

vector<ParkingSlot*> ParkingFloor::getAllSlots() const {
    return slots;
}

int ParkingFloor::getFloorNumber() const { 
    return floorNumber; 
}

int ParkingFloor::getTotalSlots() const { 
    return slots.size(); 
}

int ParkingFloor::getOccupiedSlots() const {
    int count = 0;
    for (auto slot : slots) {
        if (slot->isOccupied()) count++;
    }
    return count;
}

int ParkingFloor::getAvailableSlotsByType(const string& type) const {
    int count = 0;
    for (auto slot : slots) {
        if (!slot->isOccupied() && slot->getTypeName() == type) {
            count++;
        }
    }
    return count;
}

double ParkingFloor::getUtilization() const {
    if (slots.size() == 0) return 0;
    return (static_cast<double>(getOccupiedSlots()) / slots.size()) * 100;
}