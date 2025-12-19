#include "Vehicle.h"
#include <string>

using namespace std;

// ArrivalTime Implementation
ArrivalTime::ArrivalTime() : hour(0), minute(0) {}
ArrivalTime::ArrivalTime(int h, int m) : hour(h), minute(m) {}

// Vehicle Implementation
Vehicle::Vehicle(const string& p, const string& o, VehicleType type) 
    : plate(p), owner(o), vehicleType(type) {}

Vehicle::~Vehicle() {}

double Vehicle::calculateRate(ArrivalTime start, ArrivalTime end) const {
    int startMinutes = start.hour * 60 + start.minute;
    int endMinutes = end.hour * 60 + end.minute;
    int durationMinutes = endMinutes - startMinutes;
    int durationHours = (durationMinutes + 59) / 60;
    return calculateRate(durationHours);
}

string Vehicle::getPlate() const { return plate; }
string Vehicle::getOwner() const { return owner; }
ArrivalTime Vehicle::getArrivalTime() const { return arrivalTime; }
VehicleType Vehicle::getVehicleType() const { return vehicleType; }

void Vehicle::setArrivalTime(int h, int m) { 
    arrivalTime.hour = h; 
    arrivalTime.minute = m; 
}

void Vehicle::setVehicleType(VehicleType type) { 
    vehicleType = type; 
}

// Car Implementation
Car::Car(const string& p, const string& o) 
    : Vehicle(p, o, VehicleType::Car) {}

double Car::calculateRate(int durationHours) const {
    double rate = 5000 * durationHours;
    if (durationHours > 24) {
        rate *= 0.9;
    }
    return rate;
}

string Car::getTypeName() const { 
    return "Car"; 
}

// Motorcycle Implementation
Motorcycle::Motorcycle(const string& p, const string& o) 
    : Vehicle(p, o, VehicleType::Motorcycle) {}

double Motorcycle::calculateRate(int durationHours) const {
    double rate = 2000 * durationHours;
    if (durationHours > 24) {
        rate *= 0.9;
    }
    return rate;
}

string Motorcycle::getTypeName() const { 
    return "Motorcycle"; 
}

// EV Implementation
EV::EV(const string& p, const string& o, bool needCharging) 
    : Vehicle(p, o, VehicleType::EV), chargingRequired(needCharging) {}

double EV::calculateRate(int durationHours) const {
    double rate = 4000 * durationHours;
    if (chargingRequired) {
        rate += 3000;
    }
    if (durationHours > 24) {
        rate *= 0.9;
    }
    return rate;
}

bool EV::needsCharging() const { 
    return chargingRequired; 
}

string EV::getTypeName() const { 
    return "EV"; 
}