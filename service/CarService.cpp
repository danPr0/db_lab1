#include "../service_header/CarService.h"

bool CarService::saveCar(Car car) {
    car.setEnabled(true);
    car.setInstructorAddr(0);
    return repository.insertCarEntity(car);
}

Car CarService::getCar(int id) {
    return repository.getCarEntity(id);
}

bool CarService::deleteCar(int id) {
    return repository.deleteCarEntity(id);
}

bool CarService::updateCar(Car car) {
    car.setEnabled(true);
    return repository.updateCarEntity(car, true);
}

int CarService::countAllCars() {
    return repository.getAllCars().size();
}

list<Car> CarService::getAllCars() {
    return repository.getAllCars();
}

