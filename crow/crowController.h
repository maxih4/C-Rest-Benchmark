//
// Created by max on 26.12.21.
//

#ifndef CPPRESTSDK_CROWCONTROLLER_H
#define CPPRESTSDK_CROWCONTROLLER_H

#include "../ressources/crow/crow_all.h"


class crowController {



public:
    crowController();
    void setRoutes();
void setupServer();

private:
    crow::SimpleApp app;
};


#endif //CPPRESTSDK_CROWCONTROLLER_H
