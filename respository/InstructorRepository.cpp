#include <fstream>
#include <iostream>
#include <vector>
#include "../repository_header/InstructorRepository.h"


bool InstructorRepository::insertEntity(Instructor instructor) {
    Car car = carRepository->getEntity(instructor.getCarId());
    Instructor instructorInDB = getEntity(instructor.getId());
    if (car.getId() == 0 || instructorInDB.getId() != 0 && instructorInDB.isEnabled())
        return false;

    ifstream instructorRf("instructors.dat", ios::in | ios::binary);
    ofstream instructorWf("instructors.dat", ios::app | ios::binary);

    instructorWf.seekp(0, ios::end);
    instructor.setEnabled(true);
    instructor.setNextRecord(0);

    if (instructorInDB.getId() != 0 && !instructorInDB.isEnabled()) {
        instructor.setAddress(instructorInDB.getAddress());
        updateEntity(instructor);
    } else {
        instructor.setAddress(instructorWf.tellp() / sizeof(Instructor) + 1);
        instructorWf.write((char *) &instructor, sizeof(Instructor));
    }

    int curRecord = car.getInstructorAddr();
    if (curRecord == 0) {
        car.setInstructorAddr(instructor.getAddress());
        carRepository->updateEntity(car, false);
    } else {
        Instructor curInstructor;

        while (curRecord != 0) {
            instructorRf.seekg((curRecord - 1) * sizeof(Instructor), ios::beg);
            instructorRf.read((char *) &curInstructor, sizeof(Instructor));
            curRecord = curInstructor.getNextRecord();
        }
        curInstructor.setNextRecord(instructor.getAddress());
        updateEntity(curInstructor);
    }
    instructorRf.close();
    instructorWf.close();

    return true;
}

Instructor InstructorRepository::getEntity(int instructorId, int carId) {
    ifstream instructorRf("instructors.dat", ios::in | ios::binary);
    int curRecord = carRepository->getEntity(carId).getInstructorAddr();
    Instructor instructor;
    while (curRecord != 0 && instructor.getId() != instructorId) {
        instructorRf.seekg((curRecord - 1) * sizeof(Instructor), ios::beg);
        instructorRf.read((char *) &instructor, sizeof(Instructor));
        curRecord = instructor.getNextRecord();
    }

    if (instructor.getId() == instructorId)
        return instructor;
    else return {};
}

Instructor InstructorRepository::getEntity(int instructorId) {
    ifstream instructorRf("instructors.dat", ios::in | ios::binary);
    int curRecord = 1;
    Instructor instructor;
    while (!instructorRf.eof() && instructor.getId() != instructorId) {
        instructorRf.seekg((curRecord - 1) * sizeof(Instructor), ios::beg);
        instructorRf.read((char *) &instructor, sizeof(Instructor));
        curRecord++;
    }

    if (instructor.getId() == instructorId)
        return instructor;
    else return {};
}

bool InstructorRepository::deleteEntity(int id, int carId) {
    vector<Instructor> instructors = getAllForCar(carId);
    int index = 0;
    while (instructors[index].getId() != id && index++ < instructors.size()) {}
    Instructor instructorToDel = instructors[index];
    instructorToDel.setEnabled(false);
    updateEntity(instructorToDel);
    if (index == 0) {
        Car car = carRepository->getEntity(instructorToDel.getCarId());
        car.setInstructorAddr(instructorToDel.getNextRecord());
        carRepository->updateEntity(car, false);
    } else {
        Instructor prevInstructor = instructors[index - 1];
        prevInstructor.setNextRecord(instructorToDel.getNextRecord());
        updateEntity(prevInstructor);
    }

    return true;
}

bool InstructorRepository::updateEntity(Instructor instructor) {
    FILE *file;
    file = fopen("instructors.dat", "rb+");
    fseek(file, (instructor.getAddress() - 1) * sizeof(Instructor), SEEK_SET);
    fwrite((char *) &instructor, 1, sizeof(Instructor), file);
    fclose(file);
    return true;
}

int InstructorRepository::getNumOfRows() {
    ifstream carIndRf("instructors.dat", ios::in | ios::binary);
    carIndRf.seekg(0, ios::end);
    return carIndRf.tellg() / sizeof(Instructor);
}

vector<Instructor> InstructorRepository::getAllForCar(int carId) {
    vector<Instructor> result;
    ifstream instructorRf("instructors.dat", ios::in | ios::binary);
    int curRecord = carRepository->getEntity(carId).getInstructorAddr();
    Instructor curInstructor;
    while (curRecord != 0) {
        instructorRf.seekg((curRecord - 1) * sizeof(Instructor), ios::beg);
        instructorRf.read((char *) &curInstructor, sizeof(Instructor));
        result.push_back(curInstructor);
        curRecord = curInstructor.getNextRecord();
    }

    return result;
}

list<Instructor> InstructorRepository::getAll() {
    list<Instructor> result;
    ifstream instructorRf("instructors.dat", ios::in | ios::binary);
    int i = 0;
    int n = getNumOfRows();
    while (i < n) {
        Instructor instructor;
        instructorRf.seekg(i * sizeof(Instructor), ios::beg);
        instructorRf.read((char *) &instructor, sizeof(Instructor));
        if (instructor.isEnabled())
            result.insert(result.end(), instructor);
        i++;
    }
    instructorRf.close();

    return result;
}
