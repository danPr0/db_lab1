#include "../service_header/CarService.h"

bool CarService::saveCar(Car car) {
    car.setEnabled(true);
    car.setInstructorAddr(0);
    return carRepository.insertEntity(car);
}

Car CarService::getCar(int id) {
    return carRepository.getEntity(id);
}

bool CarService::deleteCar(int id) {
    return carRepository.deleteEntity(id);
}

bool CarService::updateCar(Car car) {
    car.setEnabled(true);
    return carRepository.updateEntity(car, true);
}

int CarService::countAllCars() {
    return carRepository.getAll().size();
}

list<Car> CarService::getAllCars() {
    return carRepository.getAll();
}

