//
// Created by max on 26.12.21.
//
#define CROW_MAIN

#include <rapidjson/document.h>
#include "crowController.h"
#include "../service/studentregistryservice.hpp"
#include "../data/student.hpp"

crowController::crowController(Studentregistryservice srs):service(srs) {

};



void crowController::setupServer(){
    crow::SimpleApp app;
    rapidjson::Document document;



    //Get
    CROW_ROUTE(app,"/students/<int>").methods(crow::HTTPMethod::GET)([this](int id){
        Student stud = this->service.fetching(id);
        crow::json::wvalue studJ;
        studJ["age"] = stud.getAge();
        studJ["id"] = stud.getId();
        studJ["name"] = stud.getName();
        return studJ;
    });

    //Post
    CROW_ROUTE(app,"/students/").methods(crow::HTTPMethod::POST)([&document,this](const crow::request& req){
        auto jsonObj= crow::json::load(req.body);


        Student stud(jsonObj["id"].i(),jsonObj["name"].s(),jsonObj["age"].i());

        this->service.adding(stud);
        crow::json::wvalue w(jsonObj);

        return crow::response(w.dump());

    });

    //Delete
    CROW_ROUTE(app,"/students/<int>").methods(crow::HTTPMethod::DELETE)([this](int id){
        this->service.removing(id);
        return crow::response{"Successful removed"};
    });

    //Put
    CROW_ROUTE(app,"/students/<int>").methods(crow::HTTPMethod::PUT)([&document,this](const crow::request& req,int id){
        auto jsonObj= crow::json::load(req.body);

        Student stud = this->service.fetching(id);


        this->service.removing(id);

        stud.setAge(jsonObj["age"].i());
        stud.setName(jsonObj["name"].s());
        this->service.adding(stud);


        crow::json::wvalue jsonResp(jsonObj);
        jsonResp["id"] = id;
        return crow::response(jsonResp.dump());
    });


    app.port(10000).multithreaded().run();
}