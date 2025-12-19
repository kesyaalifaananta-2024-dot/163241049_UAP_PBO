#ifndef PARKINGSLOT_H
#define PARKINGSLOT_H

#include "Vehicle.h"
#include <string>

class ParkingSlot {
    protected:
        std::string id;
        int level;
        bool occupied;
        std::string vehiclePlate;
        
    public:
        ParkingSlot(const std::string& slotId, int lvl);
        virtual ~ParkingSlot();
        
        virtual bool canPark(const Vehicle& vehicle) const = 0;
        virtual double calculateSurcharge(double baseRate) const = 0;
        
        std::string getId() const;
        int getLevel() const;
        bool isOccupied() const;
        std::string getVehiclePlate() const;
        
        void occupy(const std::string& plate);
        void vacate();
        
        virtual std::string getTypeName() const = 0;
};

class RegularSlot : public ParkingSlot {
    public:
        RegularSlot(const std::string& id, int lvl);
        bool canPark(const Vehicle& vehicle) const override;
        double calculateSurcharge(double baseRate) const override;
        std::string getTypeName() const override;
};

class EVSlot : public ParkingSlot {
    public:
        EVSlot(const std::string& id, int lvl);
        bool canPark(const Vehicle& vehicle) const override;
        double calculateSurcharge(double baseRate) const override;
        std::string getTypeName() const override;
};

class VIPSlot : public ParkingSlot {
    private:
        bool reserved;
        std::string reservedFor;
        int reservationHours;
        
    public:
        VIPSlot(const std::string& id, int lvl);
        bool canPark(const Vehicle& vehicle) const override;
        double calculateSurcharge(double baseRate) const override;
        bool reserve(const std::string& plate, int durationHours);
        void cancelReservation();
        std::string getTypeName() const override;
        bool isReserved() const;
        std::string getReservedFor() const;
};

#endif //PARKINGSLOT_H