//
// Created by HP EliteBook 840 G3 on 3/27/2023.
//

#include "../repository_header/Repository.h"

int findCarAddress(int id, int l, int r, ifstream &carRf) {
    int leftId, medId, rightId;
    carRf.seekg(l * 8, ios::beg);
    carRf.read((char *) &leftId, 4);
    carRf.seekg(((l + r) / 2) * 8, ios::beg);
    carRf.read((char *) &medId, 4);
    carRf.seekg(r * 8, ios::beg);
    carRf.read((char *) &rightId, 4);

    if (id >= leftId && id < medId)
        return findCarAddress(id, l, (l + r) / 2 - 1, carRf);
    else if (id > medId && id <= rightId)
        return findCarAddress(id, (l + r) / 2 + 1, r, carRf);
    else if (id == medId) {
        int result;
        carRf.seekg((l + r) / 2 * 8 + 4, ios::beg);;
        carRf.read((char *) &result, 4);
        return result;
    } else return INT_MIN;
}

int findInGarbage(int id) {
    ifstream carGarRf("cars_garbage.dat", ios::in | ios::binary);
    carGarRf.seekg(0, ios::end);
    int total = carGarRf.tellg() / 8;

    int i = 0, curId = 0;
    while (id != curId && i <= total - 1) {
        carGarRf.seekg(8 * i, ios::beg);
        carGarRf.read(reinterpret_cast<char *>(&curId), 4);
        i++;
    }

    if (id == curId) {
        carGarRf.seekg(8 * (i - 1) + 4, ios::beg);
        int address;
        carGarRf.read((char *) &address, 4);
        return address;
    } else return INT_MIN;
}

bool Repository::insertCarEntity(Car car) {
    ifstream carRf("cars.dat", ios::in | ios::binary);
    ofstream carWf("cars.dat", ios::app | ios::binary);
    ifstream carIndRf("cars_ind.dat", ios::in | ios::binary);
    ofstream carIndWf("cars_ind.dat", ios::in | ios::out | ios::binary);

    bool result = true;
    int total = getNumOfCarRows();
    int i = 0, curId = 0;
    while (curId < car.getId() && i++ <= total - 1) {
        carIndRf.seekg(8 * (i - 1), ios::beg);
        carIndRf.read(reinterpret_cast<char *>(&curId), 4);
    }

    if (car.getId() == curId) {
        Car oldCar;
        int address;
        carIndRf.read(reinterpret_cast<char *>(&address), 4);
        carRf.seekg((address - 1) * sizeof(Car), ios::beg);
        carRf.read((char *) &oldCar, sizeof(Car));
        if (oldCar.isEnabled())
            result = false;
        else {
            FILE *file;
            file = fopen("cars.dat", "rb+");
            fseek(file, (address - 1) * sizeof(Car), SEEK_SET);
            fwrite((char *) &car, 1, sizeof(Car), file);
            fclose(file);
        }
    } else {
        carWf.write((char *) &car, sizeof(Car));
        int carId = car.getId();
        int j = 0;
        int id, address;
        carIndRf.seekg((total - 1) * 8, ios::beg);
        carIndRf.read((char *) &id, 4);
        carIndRf.read((char *) &address, 4);
        while (id > car.getId() && j < total) {
            carIndWf.seekp((total - j) * 8, ios::beg);
            carIndWf.write((char *) &id, 4);
            carIndWf.write((char *) &address, 4);

            j++;

            carIndRf.seekg((total - j - 1) * 8, ios::beg);
            carIndRf.read((char *) &id, 4);
            carIndRf.read((char *) &address, 4);
        }
        carIndWf.seekp(8 * (total - j), ios::beg);
        total++;
        carIndWf.write(reinterpret_cast<const char *>(&carId), 4);
        carIndWf.write(reinterpret_cast<const char *>(&total), 4);
    }
    carIndRf.close();
    carIndWf.close();
    carWf.close();

    return result;
}

Car Repository::getCarEntity(int id) {
    ifstream carIndRf("cars_ind.dat", ios::in | ios::binary);


    carIndRf.seekg(0, ios::end);
    int address = findCarAddress(id, 0, carIndRf.tellg() / 8 - 1, carIndRf);
    Car car = {};
    if (address != INT_MIN) {
        ifstream carRf("cars.dat", ios::in | ios::binary);
        carRf.seekg((address - 1) * sizeof(Car), ios::beg);
        carRf.read((char *) &car, sizeof(Car));
        carRf.close();
    }
    carIndRf.close();

    if (car.isEnabled())
        return car;
    else return {};
}

bool Repository::deleteCarEntity(int id) {
    Car car = getCarEntity(id);
    if (car.getId() == 0)
        return false;

    vector<Instructor> instructors = getAllInstrForCar(car.getId());
    for (Instructor instructor: instructors) {
        deleteInstrEntity(instructor.getId(), id);
    }
    car.setEnabled(false);
    updateCarEntity(car, true);
    return true;
}

bool Repository::updateCarEntity(Car car, bool keepInstructorAddr) {
    ifstream carRf("cars.dat", ios::in | ios::binary);
    ifstream carIndRf("cars_ind.dat", ios::in | ios::binary);

    int address = findCarAddress(car.getId(), 0, getNumOfCarRows() - 1, carIndRf);

    if (address != INT_MIN) {

        if (keepInstructorAddr) {
            Car oldCar;
            carRf.seekg((address - 1) * sizeof(Car), ios::beg);
            carRf.read((char *) &oldCar, sizeof(Car));
            car.setInstructorAddr(oldCar.getInstructorAddr());
        }

        FILE *file;
        file = fopen("cars.dat", "rb+");
        fseek(file, (address - 1) * sizeof(Car), SEEK_SET);
        fwrite((char *) &car, 1, sizeof(Car), file);
        fclose(file);
    }
    carRf.close();
    carIndRf.close();
    return true;
}

int Repository::getNumOfCarRows() {
    ifstream carIndRf("cars_ind.dat", ios::in | ios::binary);
    carIndRf.seekg(0, ios::end);
    return carIndRf.tellg() / 8;
}

list<Car> Repository::getAllCars() {
    list<Car> result;
    ifstream carIndRf("cars_ind.dat", ios::in | ios::binary);
    ifstream carRf("cars.dat", ios::in | ios::binary);
    int i = 0;
    int n = getNumOfCarRows();
    while (i < n) {
        int address;
        carIndRf.seekg(8 * i + 4, ios::beg);
        carIndRf.read(reinterpret_cast<char *>(&address), 4);
        Car car;
        carRf.seekg((address - 1) * sizeof(Car), ios::beg);
        carRf.read((char *) &car, sizeof(Car));
        if (car.isEnabled())
            result.insert(result.end(), car);
        i++;
    }
    carIndRf.close();
    carRf.close();
    return result;
}


bool Repository::insertInstrEntity(Instructor instructor) {
    Car car = getCarEntity(instructor.getCarId());
    Instructor instructorInDB = getInstrEntity(instructor.getId());
    if (car.getId() == 0 || instructorInDB.getId() != 0 && instructorInDB.isEnabled())
        return false;

    ifstream instructorRf("instructors.dat", ios::in | ios::binary);
    ofstream instructorWf("instructors.dat", ios::app | ios::binary);

    instructorWf.seekp(0, ios::end);
    instructor.setEnabled(true);
    instructor.setNextRecord(0);

    if (instructorInDB.getId() != 0 && !instructorInDB.isEnabled()) {
        instructor.setAddress(instructorInDB.getAddress());
        updateInstrEntity(instructor);
    } else {
        instructor.setAddress(instructorWf.tellp() / sizeof(Instructor) + 1);
        instructorWf.write((char *) &instructor, sizeof(Instructor));
    }

    int curRecord = car.getInstructorAddr();
    if (curRecord == 0) {
        car.setInstructorAddr(instructor.getAddress());
        updateCarEntity(car, false);
    } else {
        Instructor curInstructor;

        while (curRecord != 0) {
            instructorRf.seekg((curRecord - 1) * sizeof(Instructor), ios::beg);
            instructorRf.read((char *) &curInstructor, sizeof(Instructor));
            curRecord = curInstructor.getNextRecord();
        }
        curInstructor.setNextRecord(instructor.getAddress());
        updateInstrEntity(curInstructor);
    }
    instructorRf.close();
    instructorWf.close();

    return true;
}

Instructor Repository::getInstrEntity(int instructorId, int carId) {
    ifstream instructorRf("instructors.dat", ios::in | ios::binary);
    int curRecord = getCarEntity(carId).getInstructorAddr();
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

Instructor Repository::getInstrEntity(int instructorId) {
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

bool Repository::deleteInstrEntity(int id, int carId) {
    vector<Instructor> instructors = getAllInstrForCar(carId);
    int index = 0;
    while (instructors[index].getId() != id && index++ < instructors.size()) {}
    Instructor instructorToDel = instructors[index];
    instructorToDel.setEnabled(false);
    updateInstrEntity(instructorToDel);
    if (index == 0) {
        Car car = getCarEntity(instructorToDel.getCarId());
        car.setInstructorAddr(instructorToDel.getNextRecord());
        updateCarEntity(car, false);
    } else {
        Instructor prevInstructor = instructors[index - 1];
        prevInstructor.setNextRecord(instructorToDel.getNextRecord());
        updateInstrEntity(prevInstructor);
    }

    return true;
}

bool Repository::updateInstrEntity(Instructor instructor) {
    FILE *file;
    file = fopen("instructors.dat", "rb+");
    fseek(file, (instructor.getAddress() - 1) * sizeof(Instructor), SEEK_SET);
    fwrite((char *) &instructor, 1, sizeof(Instructor), file);
    fclose(file);
    return true;
}

int Repository::getNumOfInstrRows() {
    ifstream carIndRf("instructors.dat", ios::in | ios::binary);
    carIndRf.seekg(0, ios::end);
    return carIndRf.tellg() / sizeof(Instructor);
}

vector<Instructor> Repository::getAllInstrForCar(int carId) {
    vector<Instructor> result;
    ifstream instructorRf("instructors.dat", ios::in | ios::binary);
    int curRecord = getCarEntity(carId).getInstructorAddr();
    Instructor curInstructor;
    while (curRecord != 0) {
        instructorRf.seekg((curRecord - 1) * sizeof(Instructor), ios::beg);
        instructorRf.read((char *) &curInstructor, sizeof(Instructor));
        result.push_back(curInstructor);
        curRecord = curInstructor.getNextRecord();
    }

    return result;
}

list<Instructor> Repository::getAllInstr() {
    list<Instructor> result;
    ifstream instructorRf("instructors.dat", ios::in | ios::binary);
    int i = 0;
    int n = getNumOfInstrRows();
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
