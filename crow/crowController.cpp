//
// Created by max on 26.12.21.
//

#include "crowController.h"

crowController::crowController(){
    crow::SimpleApp lo;
    app = lo;
};

void setRoutes(){
    CROW_ROUTE(this->app,"/students/")([](){
        return "Hello world";
    });
}

void setupServer(){
    this->app.port(1000).multithreaded().run();
}