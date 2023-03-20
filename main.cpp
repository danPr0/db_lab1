#include <iostream>
#include <fstream>
#include "view/view.h"

using namespace std;

int main() {
//    ofstream wf;
//    wf.open("cars.dat", ios::binary | ios::app);
//    if (!wf)
//        cout << "false" << endl;
//
//    int x = 12345;
//    int y = 1334242323;
//    wf.seekp(0, ios::beg);
//    cout << wf.tellp() << endl;
//    wf.write(reinterpret_cast<const char *>(&x), sizeof(int));
//    wf.write(reinterpret_cast<const char *>(&y), sizeof(int));
//    wf.write("\n", 1);
////    wf.write(reinterpret_cast<const char *>(&x), sizeof(int));
////    wf.write(reinterpret_cast<const char *>(&y), sizeof(int));
////    wf.write("\n", 1);
////    wf.write(reinterpret_cast<const char *>(&x), sizeof(int));
////    wf.write(reinterpret_cast<const char *>(&y), sizeof(int));
////    wf.write("\n", 1);
//    wf.close();
////    wf.flush();
//
////
//    ifstream rf;
//    rf.open("cars.dat", ios::binary | ios::in);
//    rf.seekg(0, ios::end);
//    cout << rf.tellg() << endl;
//
//    int z;
//    cout << rf.tellg() << endl;
//    rf.read(reinterpret_cast<char *>(&z), sizeof(int));
//    cout << z << endl;
//    cout << rf.tellg() << endl;
//    rf.read(reinterpret_cast<char *>(&z), sizeof(int));
//    cout << z << endl;
//    char s1;
//    rf.read(reinterpret_cast<char *>(&s1), 1);
//    cout << s1;
//    rf.read(reinterpret_cast<char *>(&z), sizeof(int));
//    cout << z << endl;
////    cout << rf.tellg() << endl;
//    cout << rf.tellg() << endl;
//    rf.close();
//cout << sizeof(string) << endl;
    CarRepository carRepository;
    InstructorRepository instructorRepository;
//    carRepository.insertEntity(Car(12, "brand1", "model1", 2012));
//    carRepository.insertEntity(Car(15, "brand", "model", 2015));
//    carRepository.insertEntity(Car(14, "brand", "model", 2014));
//    carRepository.updateEntity(Car(12, "brand12", "model12", 2012));
//carRepository.deleteEntity(13);
//list<Car> cars = carRepository.getAll();
//
//for (Car car : cars) {
//    cout << car.toString() << endl;
//}
//    instructorRepository.insertEntity(Instructor(14, "sdf", "dfsd", "dsfsd", 12));
//    instructorRepository.insertEntity(Instructor(13, "sdf", "dfsd", "dsfsd", 12));
//    cout << instructorRepository.getNumOfRows() << endl;
//    cout << carRepository.getEntity(12).getInstructorAddr() << endl;
//    cout << instructorRepository.getEntity(13, 12).toString() << endl;
//    instructorRepository.deleteEntity(13, 12);
//    cout << instructorRepository.getNumOfRows() << endl;
//    cout << carRepository.getEntity(15).toString() << endl;
//    cout << carRepository.getEntity(14).toString() << endl;
//cout << sizeof(Instructor) << endl;
//    instructorRepository.deleteEntity(1, 1);
    View view;
    view.handleMainInput();
    return 0;
}

