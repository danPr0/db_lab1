//
// Created by HP EliteBook 840 G3 on 2/12/2023.
//

#ifndef LAB1_INSTRUCTORSERVICE_H
#define LAB1_INSTRUCTORSERVICE_H

#include <list>
#include "../entity/Instructor.h"
#include "../repository_header/InstructorRepository.h"

class InstructorService {
private:
    CarRepository carRepository;
    InstructorRepository instructorRepository;
public:
    bool saveInstructor(Instructor instructor);
    Instructor getInstructor(int id, int carId);
    bool deleteInstructor(int id, int carId);
    bool updateInstructor(Instructor instructor);
    int countAllInstructors();
    vector<Instructor> getAllInstructorsForCar(int carId);
    list<Instructor> getAllInstructors();
};


#endif //LAB1_INSTRUCTORSERVICE_H
