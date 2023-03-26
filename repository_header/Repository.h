#ifndef LAB1_REPOSITORY_H
#define LAB1_REPOSITORY_H

#include <iostream>
#include <list>
#include <vector>
#include "../entity/Car.h"
#include "../entity/Instructor.h"

class Repository {
public:
    bool insertCarEntity(Car car);
    Car getCarEntity(int id);
    bool deleteCarEntity(int id);
    bool updateCarEntity(Car car, bool keepInstructorAddr);
    int getNumOfCarRows();
    list<Car> getAllCars();

    bool insertInstrEntity(Instructor instructor);
    Instructor getInstrEntity(int instructorId, int carId);
    Instructor getInstrEntity(int instructorId);
    bool deleteInstrEntity(int id, int carId);
    bool updateInstrEntity(Instructor instructor);
    int getNumOfInstrRows();
    list<Instructor> getAllInstr();
    vector<Instructor> getAllInstrForCar(int carId);
};


#endif //LAB1_REPOSITORY_H
