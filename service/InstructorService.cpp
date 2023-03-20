#include "../service_header/InstructorService.h"

bool InstructorService::saveInstructor(Instructor instructor) {
    instructor.setEnabled(true);
    return instructorRepository.insertEntity(instructor);
}

Instructor InstructorService::getInstructor(int id, int carId) {
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
    return instructorRepository.getAll().size();
}

vector<Instructor> InstructorService::getAllInstructorsForCar(int carId) {
    return instructorRepository.getAllForCar(carId);
}

list<Instructor> InstructorService::getAllInstructors() {
    return instructorRepository.getAll();
}
