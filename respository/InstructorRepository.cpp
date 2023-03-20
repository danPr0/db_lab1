#include <fstream>
#include <iostream>
#include <vector>
#include "../repository_header/InstructorRepository.h"


bool InstructorRepository::insertEntity(Instructor instructor) {
    Instructor instructorInDB = getEntity(instructor.getId());
    if (instructorInDB.getId() != 0 && instructorInDB.isEnabled())
        return false;

    ifstream instructorRf("instructors.dat", ios::in | ios::binary);
    ofstream instructorWf("instructors.dat", ios::app | ios::binary);


    instructorWf.seekp(0, ios::end);
    instructor.setEnabled(true);
    instructor.setNextRecord(0);

    cout << "instructor In DB : " << instructorInDB.toString() << endl;
    if (instructorInDB.getId() != 0 && !instructorInDB.isEnabled()) {
        instructor.setAddress(instructorInDB.getAddress());
        updateEntity(instructor);
    }
    else {
        instructor.setAddress(instructorWf.tellp() / sizeof(Instructor) + 1);
        instructorWf.write((char*) &instructor, sizeof(Instructor));
    }

    Car car = carRepository->getEntity(instructor.getCarId());
    if (car.getId() == 0)
        return false;

    int curRecord = car.getInstructorAddr();
    cout << curRecord << endl;
    if (curRecord == 0) {
//        instructorWf.write((char*) &instructor, sizeof(Instructor));
//        car.setInstructorAddr(instructorWf.tellp() / sizeof(Instructor));
        car.setInstructorAddr(instructor.getAddress());
        carRepository->updateEntity(car, false);
    }
    else {
        Instructor curInstructor;

        while (curRecord != 0) {
            instructorRf.seekg((curRecord - 1) * sizeof(Instructor), ios::beg);
            instructorRf.read((char*) &curInstructor, sizeof(Instructor));
            curRecord = curInstructor.getNextRecord();
        }
//        curInstructor.setNextRecord(instructorWf.tellp() / sizeof(Instructor));
        curInstructor.setNextRecord(instructor.getAddress());
        cout << curInstructor.getNextRecord() << endl;
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
        instructorRf.read((char*) &instructor, sizeof(Instructor));
        curRecord = instructor.getNextRecord();
    }
    cout << instructor.toString() << "1000001" << endl;

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
        instructorRf.read((char*) &instructor, sizeof(Instructor));
        curRecord++;
    }

    if (instructor.getId() == instructorId)
        return instructor;
    else return {};
}

bool InstructorRepository::deleteEntity(int id, int carId) {
    vector<Instructor> instructors = getAllForCar(carId);
    int index = 0;
//    for (int i = 0; i < instructors.size(); i++) {
//        if (instructors[i].getId() == id)
//            index = i;
//    }
    while (instructors[index].getId() != id && index++ < instructors.size()) {}
    Instructor instructorToDel = instructors[index];
    instructorToDel.setEnabled(false);
    updateEntity(instructorToDel);
    if (index == 0) {
        Car car = carRepository->getEntity(instructorToDel.getCarId());
        car.setInstructorAddr(instructorToDel.getNextRecord());
        carRepository->updateEntity(car, false);
    }
    else {
        Instructor prevInstructor = instructors[index - 1];
        prevInstructor.setNextRecord(instructorToDel.getNextRecord());
        updateEntity(prevInstructor);
    }

//    Instructor instructor = getEntity(id, carId);
//    cout << instructor.isEnabled() << endl;
//    instructor.setEnabled(false);

    return true;
}

bool InstructorRepository::updateEntity(Instructor instructor) {
//    ifstream instructorRf("instructors.dat", ios::in | ios::binary);
//    int curRecord = carRepository->getEntity(instructor.getCarId()).getInstructorAddr();
//    Instructor curInstructor;
//    while (curRecord != 0 && !(instructor.getId() == curInstructor.getId() && instructor.isEnabled())) {
//        instructorRf.seekg((curRecord - 1) * sizeof(Instructor), ios::beg);
//        instructorRf.read((char*) &curInstructor, sizeof(Instructor));
//        curRecord = curInstructor.getNextRecord();
//    }
//
//    cout << instructor.toString() << endl;
//    cout << curInstructor.toString() << endl;

//    if (instructor.getId() == curInstructor.getId()) {
//        instructor.setNextRecord(curInstructor.getNextRecord());
//        FILE *file;
//        file = fopen("instructors.dat", "rb+");
//        fseek(file, (instructorRf.tellg() / sizeof(Car) - 1) * sizeof(Car), SEEK_SET);
//        fwrite((char*) &instructor, 1, sizeof(Instructor), file);
//        fclose(file);
//        return true;
//    }
//    else return false;
        FILE *file;
        file = fopen("instructors.dat", "rb+");
        fseek(file, (instructor.getAddress() - 1) * sizeof(Instructor), SEEK_SET);
        fwrite((char*) &instructor, 1, sizeof(Instructor), file);
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
//    int curRecord = carRepository->getEntity(cardId).getInstructorAddr();
    int curRecord = carRepository->getEntity(carId).getInstructorAddr();
    Instructor curInstructor;
    while (curRecord != 0) {
        instructorRf.seekg((curRecord - 1) * sizeof(Instructor), ios::beg);
        instructorRf.read((char*) &curInstructor, sizeof(Instructor));
        result.push_back(curInstructor);
        curRecord = curInstructor.getNextRecord();
        cout << curInstructor.toString() << "  1111" << endl;
    }

    return result;
}


list<Instructor> InstructorRepository::getAll() {
    list<Instructor> result;
    ifstream instructorRf("instructors.dat", ios::in | ios::binary);
    int i = 0;
    int n = getNumOfRows();
    cout << n << endl;
    while (i < n) {
        Instructor instructor;
        instructorRf.seekg(i * sizeof(Instructor), ios::beg);
        instructorRf.read((char*) &instructor, sizeof(Instructor));
        cout << instructor.isEnabled() << endl;
//        if (instructor.isEnabled())
            result.insert(result.end(), instructor);
        i++;
    }
    instructorRf.close();

    return result;
}
