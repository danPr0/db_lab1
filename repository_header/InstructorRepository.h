//
// Created by HP EliteBook 840 G3 on 2/12/2023.
//

#ifndef LAB1_INSTRUCTORREPOSITORY_H
#define LAB1_INSTRUCTORREPOSITORY_H

#include <list>
#include <vector>
#include "../entity/Instructor.h"
#include "../entity/Car.h"
#include "CarRepository.h"

class CarRepository;

class InstructorRepository {
private:
    CarRepository* carRepository;
public:
    bool insertEntity(Instructor instructor);
    Instructor getEntity(int instructorId, int carId);
    Instructor getEntity(int instructorId);
    bool deleteEntity(int id, int carId);
    bool updateEntity(Instructor instructor);
    int getNumOfRows();
    list<Instructor> getAll();
    vector<Instructor> getAllForCar(int carId);
};


#endif //LAB1_INSTRUCTORREPOSITORY_H
