#include "Exceptions.h"
#include <string>

using namespace std;

ParkingException::ParkingException(const string& msg) : message(msg) {}
const char* ParkingException::what() const noexcept { 
    return message.c_str(); 
}

NoAvailableSlotException::NoAvailableSlotException() 
    : ParkingException("No available slot for this vehicle type") {}

InvalidTicketException::InvalidTicketException() 
    : ParkingException("Invalid ticket ID") {}

ReservationException::ReservationException() 
    : ParkingException("VIP slot reservation failed") {}

PaymentException::PaymentException() 
    : ParkingException("Payment processing failed") {}

PaymentException::PaymentException(const string& msg) 
    : ParkingException(msg) {}