#ifndef LAB1_INSTRUCTOR_H
#define LAB1_INSTRUCTOR_H

#include <string>
#include <cstring>

using namespace std;

class Instructor {
private:
    int id;
    char email[50];
    char firstName[50];
    char secondName[50];
    int carId;
    bool enabled;
    int address;
    int nextRecord;

public:
    Instructor() {
        id = 0;
    }

    Instructor(int id, const char* email, const char* firstName, const char* secondName, int carId) {
        this->id = id;
        strcpy(this->email, email);
        strcpy(this->firstName, firstName);
        strcpy(this->secondName, secondName);
        this->carId = carId;
    }

    int getId() {
        return id;
    }

    string getEmail() {
        return email;
    }

    string getFirstName() {
        return firstName;
    }

    string getSecondName() {
        return secondName;
    }


    int getCarId() {
        return carId;
    }

    void setCarId(int carId) {
        this->carId = carId;
    }

    bool isEnabled() {
        return enabled;
    }

    void setEnabled(bool enabled) {
        this->enabled = enabled;
    }

    int getAddress() {
        return address;
    }

    void setAddress(int address) {
        this->address = address;
    }

    int getNextRecord() {
        return nextRecord;
    }

    void setNextRecord(int nextRecord) {
        this->nextRecord = nextRecord;
    }

    string toString() {
        return to_string(id) + " " + email + " " + firstName + " " + secondName + " " + to_string(carId) + "  " +
                to_string(enabled) + "     " + to_string(nextRecord);
    }
};


#endif //LAB1_INSTRUCTOR_H
