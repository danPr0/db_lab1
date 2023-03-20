#ifndef LAB1_VIEW_H
#define LAB1_VIEW_H

#include "../service_header/CarService.h"
#include "../service_header/InstructorService.h"

using namespace std;

class View {
private:
    CarService carService;
    InstructorService instructorService;

    void addCar();
    void getCar();
    void deleteCar();
    void updateCar();

    void addInstructor();
    void getInstructor();
    void deleteInstructor();
    void updateInstructor();

    void countAllCars();
    void countAllInstructors();
    void countAllInstructorsForCar();

    void showAllCars();
    void showAllInstructors();
public:
    void handleMainInput();
};



#endif //LAB1_VIEW_H
