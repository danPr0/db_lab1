#include "../service_header/InstructorService.h"

bool InstructorService::saveInstructor(Instructor instructor) {
    instructor.setEnabled(true);
    return repository.insertInstrEntity(instructor);
}

Instructor InstructorService::getInstructor(int id, int carId) {
    return repository.getInstrEntity(id, carId);
}

bool InstructorService::deleteInstructor(int id, int carId) {
    return repository.deleteInstrEntity(id, carId);
}

bool InstructorService::updateInstructor(Instructor instructor) {
    Instructor instructorInDB = repository.getInstrEntity(instructor.getId(), instructor.getCarId());
    if (instructorInDB.getId() == 0)
        return false;
    else {
        instructor.setEnabled(true);
        instructor.setAddress(instructorInDB.getAddress());
        instructor.setNextRecord(instructorInDB.getNextRecord());
        return repository.updateInstrEntity(instructor);
    }
}

int InstructorService::countAllInstructors() {
    return repository.getAllInstr().size();
}

vector<Instructor> InstructorService::getAllInstructorsForCar(int carId) {
    return repository.getAllInstrForCar(carId);
}

list<Instructor> InstructorService::getAllInstructors() {
    return repository.getAllInstr();
}
