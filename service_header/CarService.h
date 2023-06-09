#ifndef LAB1_CARSERVICE_H
#define LAB1_CARSERVICE_H

#include <string>
#include <list>
#include "../entity/Car.h"
#include "../repository_header/Repository.h"

using namespace std;

class CarService {
private:
    Repository repository;
public:
    bool saveCar(Car car);
    Car getCar(int id);
    bool deleteCar(int id);
    bool updateCar(Car car);
    int countAllCars();
    list<Car> getAllCars();
};


#endif //LAB1_CARSERVICE_H
