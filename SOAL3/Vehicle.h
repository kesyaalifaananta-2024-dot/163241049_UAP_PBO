#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

enum class VehicleType {
    Car,
    Motorcycle,
    EV
};

struct ArrivalTime {
    int hour;
    int minute;
    ArrivalTime();
    ArrivalTime(int h, int m);
};

class Vehicle {
    protected:
        std::string plate;
        std::string owner;
        ArrivalTime arrivalTime;
        VehicleType vehicleType;
        
    public:
        Vehicle(const std::string& p, const std::string& o, VehicleType type);
        virtual ~Vehicle();
        
        virtual double calculateRate(int durationHours) const = 0;
        double calculateRate(ArrivalTime start, ArrivalTime end) const;
        
        std::string getPlate() const;
        std::string getOwner() const;
        ArrivalTime getArrivalTime() const;
        VehicleType getVehicleType() const;
        
        void setArrivalTime(int h, int m);
        void setVehicleType(VehicleType type);
        
        virtual std::string getTypeName() const = 0;
};

class Car : public Vehicle {
    public:
        Car(const std::string& p, const std::string& o);
        double calculateRate(int durationHours) const override;
        std::string getTypeName() const override;
};

class Motorcycle : public Vehicle {
    public:
        Motorcycle(const std::string& p, const std::string& o);
        double calculateRate(int durationHours) const override;
        std::string getTypeName() const override;
};

class EV : public Vehicle {
    private:
        bool chargingRequired;
        
    public:
        EV(const std::string& p, const std::string& o, bool needCharging);
        double calculateRate(int durationHours) const override;
        bool needsCharging() const;
        std::string getTypeName() const override;
};

#endif //VEHICLE_H