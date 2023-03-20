#include <vector>
#include <iostream>
#include "../service_header/InstructorService.h"

bool InstructorService::saveInstructor(Instructor instructor) {
    instructor.setEnabled(true);
//    Instructor instructorInDB = instructorRepository.getEntity(instructor.getId(), instructor.getCarId());
////    cout << instructorInDB.toString() << endl;
//    if (instructorInDB.getId() != 0) {
////        if (instructorInDB.isEnabled())
////            return false;
////        else {
////            cout << instructorRepository.getNumOfRows() << "101" << endl;
////            instructorRepository.updateEntity(instructor);
////            cout << instructorRepository.getNumOfRows() << "202" << endl;
////            return true;
////        }
//        return false;
//    }
    return instructorRepository.insertEntity(instructor);
}

Instructor InstructorService::getInstructor(int id, int carId) {
//    Instructor instructor = instructorRepository.getEntity(id, carId);
//    if (instructor.getId() != 0 && instructor.isEnabled())
//        return instructor;
//    else return {};
//    Instructor instructor = instructorRepository.getEntity(id, carId);
//    return instructor.getId() != 0 && instructor.isEnabled() ? instructor : Instructor();
    return instructorRepository.getEntity(id, carId);
}

bool InstructorService::deleteInstructor(int id, int carId) {
    return instructorRepository.deleteEntity(id, carId);
}

bool InstructorService::updateInstructor(Instructor instructor) {
    Instructor instructorInDB = instructorRepository.getEntity(instructor.getId(), instructor.getCarId());
    if (instructorInDB.getId() == 0)
        return false;
    else {
        instructor.setEnabled(true);
        instructor.setAddress(instructorInDB.getAddress());
        instructor.setNextRecord(instructorInDB.getNextRecord());
        return instructorRepository.updateEntity(instructor);
    }
}

int InstructorService::countAllInstructors() {
    list<Instructor> instructors =instructorRepository.getAll();
    int count = 0;
    for (Instructor instructor : instructors) {
        if (instructor.isEnabled())
            count++;
    }

    return count;
}

int InstructorService::countAllInstructorsForCar(int carId) {
    return instructorRepository.getAllForCar(carId).size();
}

list<Instructor> InstructorService::getAllInstructors() {
    return instructorRepository.getAll();
}
