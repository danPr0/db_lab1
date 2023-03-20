#ifndef LAB1_CAR_H
#define LAB1_CAR_H

#include <fstream>
#include <string>
#include <cstring>

using namespace std;

struct Car {
private:
    long id;
    char brand[50];
    char model[50];
    int year;
    bool enabled;
    int instructorAddr;

public:
    Car() {
        id = 0;
    }

    Car(long id, const char* brand, const char* model, int year) {
        this->id = id;
        strcpy(this->brand, brand);
//        this->brand ;
//        this->model = model.c_str();
        strcpy(this->model, model);
        this->year = year;
    }

    void save(ofstream& of) {
        of.write(reinterpret_cast<const char *>(&id), 4);
        of.write(brand, 50);
        of.write(model, 50);
        of.write(reinterpret_cast<const char *>(&year), 4);
    }

    void load(ifstream& inf) {
        inf.read(reinterpret_cast<char *>(&id), 4);
        inf.read(brand, 50);
        inf.read(model, 50);
        inf.read(reinterpret_cast<char *>(&year), 4);
    }

    long getId() {
        return id;
    }

    string getModel() {
        return model;
    }

    string getBrand() {
        return brand;
    }

    int getYear() {
        return year;
    }

    void setId(long id) {
        this->id = id;
    }

    bool isEnabled() {
        return enabled;
    }

    void setEnabled(bool enabled) {
        this->enabled = enabled;
    }

    int getInstructorAddr() {
        return instructorAddr;
    }

    void setInstructorAddr(int instructorAddr) {
        this->instructorAddr = instructorAddr;
    }

    string toString() {
        return to_string(id) + " " + brand + " " + model + " " + to_string(year) + "    " + to_string(instructorAddr) + "   " + to_string(enabled);
    }
};


#endif //LAB1_CAR_H
