#include "view.h"
#include "../entity/Car.h"
#include "../service_header/CarService.h"
#include <string>
#include <iostream>

const string MAIN_FUNCTIONS = "(0) Exit\n(1) Add car\n(2) Get car\n(3) Remove car\n(4) Update car\n"
                              "(5) Add instructor\n(6) Get instructor\n(7) Remove instructor\n(8) Update instructor\n"
                              "(9) Count all cars\n(10) Count all instructors\n(11) Show all instructors for a specific car\n"
                              "(12) Show all cars\n(13) Show all instructors";

const string CAR_ID_REQUEST = "Enter car id: ";
const string CAR_BRAND_REQUEST = "Enter car brand: ";
const string CAR_MODEL_REQUEST = "Enter car model: ";
const string CAR_YEAR_REQUEST = "Enter car year: ";

//const string CAR_NEW_ID_REQUEST = "Enter new car id: ";
//const string CAR_NEW_BRAND_REQUEST = "Enter new car brand: ";
//const string CAR_NEW_MODEL_REQUEST = "Enter new car model: ";
//const string CAR_NEW_YEAR_REQUEST = "Enter new car year: ";

const string INSTRUCTOR_ID_REQUEST = "Enter instructor id: ";
const string INSTRUCTOR_EMAIL_REQUEST = "Enter instructor email: ";
const string INSTRUCTOR_FIRST_NAME_REQUEST = "Enter instructor first name: ";
const string INSTRUCTOR_SECOND_NAME_REQUEST = "Enter instructor second name: ";
const string INSTRUCTOR_CAR_ID_REQUEST = "Enter instructor car id: ";

const string ERROR_ADD_CAR = "Cannot add car. The car with this id already exist.";
const string ERROR_GET_CAR = "Cannot get car. No such car.";
const string ERROR_DELETE_CAR = "Cannot delete car. No such car.";
const string ERROR_UPDATE_CAR = "Cannot update car. The car with this id already exist.";

const string ERROR_ADD_INSTRUCTOR = "Cannot add instructor. The instructor with this id already exist.";
const string ERROR_GET_INSTRUCTOR = "Cannot get instructor. No such instructor.";
const string ERROR_DELETE_INSTRUCTOR = "Cannot delete instructor. No such instructor.";
const string ERROR_UPDATE_INSTRUCTOR = "Cannot update instructor. The instructor with this id already exist.";


int readInt(string msg) {
    int value;
    cout << msg << endl;
    cin >> value;
    return value;
}

string readString(string msg) {
    string value;
    cout << msg << endl;
    cin >> value;
    return value;
}

string readStringWithDefault(string msg, string presetValue) {
    cout << msg << " [default = " << presetValue << "]" << endl;

    cin.clear();
    cin.sync();
    string value;
    getline(cin, value);
    if (value.empty())
        value = presetValue;

    return value;
}

void View::handleMainInput() {
    string userInput = readString(MAIN_FUNCTIONS);

    if (userInput == "0")
        return;
    else if (userInput == "1")
        addCar();
    else if (userInput == "2")
        getCar();
    else if (userInput == "3")
        deleteCar();
    else if (userInput == "4")
        updateCar();
    else if (userInput == "5")
        addInstructor();
    else if (userInput == "6")
        getInstructor();
    else if (userInput == "7")
        deleteInstructor();
    else if (userInput == "8")
        updateInstructor();
    else if (userInput == "9")
        countAllCars();
    else if (userInput == "10")
        countAllInstructors();
    else if (userInput == "11")
        showAllInstructorsForCar();
    else if (userInput == "12")
        showAllCars();
    else if (userInput == "13")
        showAllInstructors();
    else {
        cout << "Incorrect input. Please try again." << endl;
    }
    handleMainInput();
}

void View::addCar() {
    int id = readInt(CAR_ID_REQUEST);
    string brand = readString(CAR_BRAND_REQUEST);
    string model = readString(CAR_MODEL_REQUEST);
    int year = readInt(CAR_YEAR_REQUEST);

    if (!carService.saveCar(Car(id, brand.c_str(), model.c_str(), year)))
        cout << ERROR_ADD_CAR << endl;
}

void View::getCar() {
    int id = readInt(CAR_ID_REQUEST);
    Car car = carService.getCar(id);

    if (car.getId() == 0)
        cout << ERROR_GET_CAR << endl;
    else cout << car.toString() << endl;
}

void View::deleteCar() {
    int id = readInt(CAR_ID_REQUEST);

    if (!carService.deleteCar(id))
        cout << ERROR_DELETE_CAR << endl;
}

void View::updateCar() {
    int id = readInt(CAR_ID_REQUEST);
    Car car = carService.getCar(id);

    if (car.getId() == 0)
        cout << ERROR_GET_CAR << endl;
    else {
        cout << car.toString() << endl;
        string newBrand = readStringWithDefault(CAR_BRAND_REQUEST, car.getBrand());
        string newModel = readStringWithDefault(CAR_MODEL_REQUEST, car.getModel());
        int newYear = stoi(readStringWithDefault(CAR_YEAR_REQUEST, to_string(car.getYear())));

        if (!carService.updateCar(Car(id, newBrand.c_str(), newModel.c_str(), newYear)))
            cout << ERROR_UPDATE_CAR << endl;
    }
}

void View::addInstructor() {
    int id = readInt(INSTRUCTOR_ID_REQUEST);
    string email = readString(INSTRUCTOR_EMAIL_REQUEST);
    string firstName = readString(INSTRUCTOR_FIRST_NAME_REQUEST);
    string secondName = readString(INSTRUCTOR_SECOND_NAME_REQUEST);
    int carId = readInt(INSTRUCTOR_CAR_ID_REQUEST);

    if (!instructorService.saveInstructor(Instructor(id, email.c_str(), firstName.c_str(), secondName.c_str(), carId)))
        cout << ERROR_ADD_INSTRUCTOR << endl;
}

void View::getInstructor() {
    int id = readInt(INSTRUCTOR_ID_REQUEST);
    int carId = readInt(CAR_ID_REQUEST);
    Instructor instructor = instructorService.getInstructor(id, carId);

    if (instructor.getId() == 0)
        cout << ERROR_GET_INSTRUCTOR << endl;
    else cout << instructor.toString() << endl;
}

void View::deleteInstructor() {
    int id = readInt(INSTRUCTOR_ID_REQUEST);
    int carId = readInt(CAR_ID_REQUEST);

    if (!instructorService.deleteInstructor(id, carId))
        cout << ERROR_DELETE_INSTRUCTOR << endl;
}

void View::updateInstructor() {
    int id = readInt(INSTRUCTOR_ID_REQUEST);
    int carId = readInt(CAR_ID_REQUEST);
    Instructor instructor = instructorService.getInstructor(id, carId);

    if (instructor.getId() == 0)
        cout << ERROR_GET_INSTRUCTOR << endl;
    else {
        cout << instructor.toString() << endl;
        string newEmail = readStringWithDefault(INSTRUCTOR_EMAIL_REQUEST, instructor.getEmail());
        string newFirstName = readStringWithDefault(INSTRUCTOR_FIRST_NAME_REQUEST, instructor.getFirstName());
        string newSecondName = readStringWithDefault(INSTRUCTOR_SECOND_NAME_REQUEST, instructor.getSecondName());
//        int newCarId = readInt(INSTRUCTOR_CAR_ID_REQUEST);

        if (!instructorService.updateInstructor(
                Instructor(id, newEmail.c_str(), newFirstName.c_str(), newSecondName.c_str(), instructor.getCarId())))
            cout << ERROR_UPDATE_INSTRUCTOR << endl;
    }
}

void View::countAllCars() {
    cout << to_string(carService.countAllCars()) + " cars in total" << endl;
}

void View::countAllInstructors() {
    cout << to_string(instructorService.countAllInstructors()) + " instructors in total" << endl;
}

void View::showAllInstructorsForCar() {
    int carId = readInt(CAR_ID_REQUEST);
    vector<Instructor> instructors = instructorService.getAllInstructorsForCar(carId);
    if (instructors.empty()) {
        cout << "No instructors for car with id = " << carId << endl;
    }
    else {
        for (Instructor instructor: instructors) {
            cout << instructor.toString() << endl;
        }
    }
}

void View::showAllCars() {
    list<Car> cars = carService.getAllCars();
    if (cars.empty()) {
        cout << "No cars." << endl;
    }
    else {
        for (Car car: cars) {
            cout << car.toString() << endl;
        }
    }
}

void View::showAllInstructors() {
    list<Instructor> instructors = instructorService.getAllInstructors();
    if (instructors.empty())
        cout << "No instructors." << endl;
    else {
        for (Instructor instructor: instructors) {
            cout << instructor.toString() << endl;
        }
    }
}

