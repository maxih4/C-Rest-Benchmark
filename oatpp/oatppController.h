//
// Created by max on 28.12.21.
//

#ifndef CPPRESTSDK_OATPPCONTROLLER_H
#define CPPRESTSDK_OATPPCONTROLLER_H


#include "../service/studentregistryservice.hpp"

class oatppController {

    Studentregistryservice service;

public: oatppController(Studentregistryservice srs);
};


#endif //CPPRESTSDK_OATPPCONTROLLER_H
