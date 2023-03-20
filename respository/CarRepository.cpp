
#include <fstream>
#include <iostream>
#include <vector>
#include "../repository_header/CarRepository.h"

int findAddress(int id, int l, int r, ifstream &carRf) {
    int leftId, medId, rightId;
    carRf.seekg(l * 8, ios::beg);
    carRf.read((char *) &leftId, 4);
    carRf.seekg(((l + r) / 2) * 8, ios::beg);
    carRf.read((char *) &medId, 4);
    carRf.seekg(r * 8, ios::beg);
    carRf.read((char *) &rightId, 4);

    if (id >= leftId && id < medId)
        return findAddress(id, l, (l + r) / 2 - 1, carRf);
    else if (id > medId && id <= rightId)
        return findAddress(id, (l + r) / 2 + 1, r, carRf);
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

bool CarRepository::insertEntity(Car car) {
    ifstream carRf("cars.dat", ios::in | ios::binary);
    ofstream carWf("cars.dat", ios::app | ios::binary);
    ifstream carIndRf("cars_ind.dat", ios::in | ios::binary);
    ofstream carIndWf("cars_ind.dat", ios::in | ios::out | ios::binary);

    bool result = true;
    int total = getNumOfRows();
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

Car CarRepository::getEntity(int id) {
    ifstream carIndRf("cars_ind.dat", ios::in | ios::binary);

    carIndRf.seekg(0, ios::end);
    int address = findAddress(id, 0, carIndRf.tellg() / 8 - 1, carIndRf);
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

bool CarRepository::deleteEntity(int id) {
    Car car = getEntity(id);
    if (car.getId() == 0)
        return false;

    vector<Instructor> instructors = instructorRepository->getAllForCar(id);
    for (Instructor instructor: instructors) {
        instructorRepository->deleteEntity(instructor.getId(), id);
    }
    car.setEnabled(false);
    updateEntity(car, true);
    return true;
}

bool CarRepository::updateEntity(Car car, bool keepInstructorAddr) {
    ifstream carRf("cars.dat", ios::in | ios::binary);
    ifstream carIndRf("cars_ind.dat", ios::in | ios::binary);

    int address = findAddress(car.getId(), 0, getNumOfRows() - 1, carIndRf);

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

int CarRepository::getNumOfRows() {
    ifstream carIndRf("cars_ind.dat", ios::in | ios::binary);
    carIndRf.seekg(0, ios::end);
    return carIndRf.tellg() / 8;
}

list<Car> CarRepository::getAll() {
    list<Car> result;
    ifstream carIndRf("cars_ind.dat", ios::in | ios::binary);
    ifstream carRf("cars.dat", ios::in | ios::binary);
    int i = 0;
    int n = getNumOfRows();
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
