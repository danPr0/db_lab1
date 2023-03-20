#include "../service_header/CarService.h"

bool CarService::saveCar(Car car) {
//    Car oldCar;
//    carRf.read((char*) &oldCar, sizeof(Car));
//    car.setEnabled(oldCar.g)
    car.setEnabled(true);
    car.setInstructorAddr(0);
//    Car carInDB = carRepository.getEntity(car.getId());
//    if (carInDB.getId() != 0) {
//        if (!carInDB.isEnabled())
//            return carRepository.updateEntity(car);
//        else return false;
//    }
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
    list<Car> cars =carRepository.getAll();
    int count = 0;
    for (Car car : cars) {
        if (car.isEnabled())
            count++;
    }

    return count;
}

list<Car> CarService::getAllCars() {
    return carRepository.getAll();
}

