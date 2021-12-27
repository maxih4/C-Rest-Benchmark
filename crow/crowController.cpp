//
// Created by max on 26.12.21.
//
#define CROW_MAIN

#include <rapidjson/document.h>
#include "crowController.h"
#include "../service/studentregistryservice.hpp"
#include "../data/student.hpp"

crowController::crowController(){
    Studentregistryservice srs;
    this->service=srs;
};



void crowController::setupServer(){
    crow::SimpleApp app;
    rapidjson::Document document;

    //Get
    CROW_ROUTE(app,"/students/<int>").methods(crow::HTTPMethod::GET)([this](int id){
        Student stud = this->service.fetching(id);
        return stud.toJson();
    });

    //Post
    CROW_ROUTE(app,"/students/").methods(crow::HTTPMethod::POST)([&document,this](const crow::request& req){

        document.Parse<0>(req.body.c_str());
        int id = document["id"].GetInt();
        int age = document["age"].GetInt();
        std::string name = document["name"].GetString();

        Student stud(id,name,age);
        this->service.adding(stud);
        return crow::response{stud.toJson()};

    });

    //Delete
    CROW_ROUTE(app,"/students/<int>").methods(crow::HTTPMethod::DELETE)([this](int id){
        this->service.removing(id);
        return crow::response{"Successful removed"};
    });

    //Put
    CROW_ROUTE(app,"/students/<int>").methods(crow::HTTPMethod::PUT)([&document,this](const crow::request& req,int id){

        document.Parse<0>(req.body.c_str());
        int age = document["age"].GetInt();
        std::string name = document["name"].GetString();

        Student stud = this->service.fetching(id);


        this->service.removing(id);

        stud.setAge(age);
        stud.setName(name);
        this->service.adding(stud);
        return crow::response{stud.toJson()};

    });

    app.port(10000).multithreaded().run();
}