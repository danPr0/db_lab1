//
// Created by HP EliteBook 840 G3 on 2/12/2023.
//

#ifndef LAB1_CARREPOSITORY_H
#define LAB1_CARREPOSITORY_H

#include <list>
#include "../entity/Car.h"
#include "InstructorRepository.h"

class InstructorRepository;

class CarRepository {
private:
    InstructorRepository* instructorRepository;
public:
    bool insertEntity(Car car);
    Car getEntity(int id);
    bool deleteEntity(int id);
    bool updateEntity(Car car, bool keepInstructorAddr);
    int getNumOfRows();
    list<Car> getAll();
};


#endif //LAB1_CARREPOSITORY_H
