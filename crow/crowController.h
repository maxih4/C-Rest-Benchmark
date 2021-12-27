//
// Created by max on 26.12.21.
//

#ifndef CPPRESTSDK_CROWCONTROLLER_H
#define CPPRESTSDK_CROWCONTROLLER_H

#include "../ressources/crow/crow_all.h"
#include "../service/studentregistryservice.hpp"


class crowController {



public:
    crowController();

void setupServer();

private:
    Studentregistryservice service;
};


#endif //CPPRESTSDK_CROWCONTROLLER_H
