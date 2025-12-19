# Parking Management System

## Deskripsi
Sistem manajemen parkir multizona dengan fitur:
- 3 jenis kendaraan: Car, Motorcycle, EV
- 3 jenis slot: Regular, EV, VIP
- 2 lantai parkir
- Reservasi slot VIP
- Perhitungan biaya otomatis dengan diskon
- Exception handling yang lengkap

## Cara Kompilasi
```bash
# Menggunakan g++
g++ -c Vehicle.cpp -o Vehicle.o
g++ -c ParkingSlot.cpp -o ParkingSlot.o
g++ -c ParkingFloor.cpp -o ParkingFloor.o
g++ -c ParkingGarage.cpp -o ParkingGarage.o
g++ -c Exceptions.cpp -o Exceptions.o
g++ -c main.cpp -o main.o
g++ main.o Vehicle.o ParkingSlot.o ParkingFloor.o ParkingGarage.o Exceptions.o -o parking_system

# Atau kompilasi langsung
g++ main.cpp Vehicle.cpp ParkingSlot.cpp ParkingFloor.cpp ParkingGarage.cpp Exceptions.cpp -o parking_system