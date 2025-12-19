#include "ParkingSlot.h"
#include "Exceptions.h"
#include <string>

using namespace std;

// ParkingSlot Implementation
ParkingSlot::ParkingSlot(const string& slotId, int lvl) 
    : id(slotId), level(lvl), occupied(false), vehiclePlate("") {}

ParkingSlot::~ParkingSlot() {}

string ParkingSlot::getId() const { return id; }
int ParkingSlot::getLevel() const { return level; }
bool ParkingSlot::isOccupied() const { return occupied; }
string ParkingSlot::getVehiclePlate() const { return vehiclePlate; }

void ParkingSlot::occupy(const string& plate) {
    if (occupied) throw ParkingException("Slot already occupied");
    occupied = true;
    vehiclePlate = plate;
}

void ParkingSlot::vacate() {
    occupied = false;
    vehiclePlate = "";
}

// RegularSlot Implementation
RegularSlot::RegularSlot(const string& id, int lvl) : ParkingSlot(id, lvl) {}

bool RegularSlot::canPark(const Vehicle& vehicle) const {
    return !occupied && vehicle.getVehicleType() != VehicleType::EV;
}

double RegularSlot::calculateSurcharge(double baseRate) const {
    return baseRate;
}

string RegularSlot::getTypeName() const { 
    return "Regular"; 
}

// EVSlot Implementation
EVSlot::EVSlot(const string& id, int lvl) : ParkingSlot(id, lvl) {}

bool EVSlot::canPark(const Vehicle& vehicle) const {
    return !occupied && vehicle.getVehicleType() == VehicleType::EV;
}

double EVSlot::calculateSurcharge(double baseRate) const {
    return baseRate;
}

string EVSlot::getTypeName() const { 
    return "EV"; 
}

// VIPSlot Implementation
VIPSlot::VIPSlot(const string& id, int lvl) 
    : ParkingSlot(id, lvl), reserved(false), reservedFor(""), reservationHours(0) {}

bool VIPSlot::canPark(const Vehicle& vehicle) const {
    if (occupied) return false;
    if (reserved && vehicle.getPlate() != reservedFor) return false;
    return true;
}

double VIPSlot::calculateSurcharge(double baseRate) const {
    return baseRate * 1.5;
}

bool VIPSlot::reserve(const string& plate, int durationHours) {
    if (occupied) return false;
    reserved = true;
    reservedFor = plate;
    reservationHours = durationHours;
    return true;
}

void VIPSlot::cancelReservation() {
    reserved = false;
    reservedFor = "";
    reservationHours = 0;
}

string VIPSlot::getTypeName() const { 
    return "VIP"; 
}

bool VIPSlot::isReserved() const { 
    return reserved; 
}

string VIPSlot::getReservedFor() const { 
    return reservedFor; 
}