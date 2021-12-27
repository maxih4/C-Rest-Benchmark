//
// Created by max on 22.12.21.
//

#include "pistacheController.h"

pistacheController::pistacheController(Address addr,Studentregistryservice srs):Http::Endpoint(addr),service(srs) {



    Pistache::Rest::Routes::Get(pistacheController::router,"/students/:id",Pistache::Rest::Routes::bind(
            &pistacheController::handleGet, this));

    Pistache::Rest::Routes::Post(pistacheController::router,"/students",Pistache::Rest::Routes::bind(
            &pistacheController::handlePost, this));

    Pistache::Rest::Routes::Put(pistacheController::router,"/students/:id",Pistache::Rest::Routes::bind(
            &pistacheController::handlePut, this));

    Pistache::Rest::Routes::Delete(pistacheController::router,"/students/:id",Pistache::Rest::Routes::bind(
            &pistacheController::handleDel, this));


    setHandler(router.handler());
}

void pistacheController::handleGet(const Rest::Request &req, Http::ResponseWriter res) {
    auto id = req.param(":id").as<int>();
    Student stud = this->service.fetching(id);
    res.send(Http::Code::Ok,stud.toJson());
}

void pistacheController::handlePost(const Rest::Request &req, Http::ResponseWriter res) {
    rapidjson::Document document;
    document.Parse<0>(req.body().c_str());
    int id = document["id"].GetInt();
    int age = document["age"].GetInt();
    std::string name = document["name"].GetString();

    Student stud(id,name,age);
    this->service.adding(stud);
    res.send(Http::Code::Ok,stud.toJson());
}

void pistacheController::handlePut(const Rest::Request &req, Http::ResponseWriter res) {
    auto id = req.param(":id").as<int>();
    Student stud = this->service.fetching(id);
    this->service.removing(id);

    rapidjson::Document document;
    document.Parse<0>(req.body().c_str());
    int age = document["age"].GetInt();
    std::string name = document["name"].GetString();

    stud.setAge(age);
    stud.setName(name);

    this->service.adding(stud);
    res.send(Http::Code::Ok,stud.toJson());

}

void pistacheController::handleDel(const Rest::Request &req, Http::ResponseWriter res) {
    auto id = req.param(":id").as<int>();
    this->service.removing(id);
    res.send(Http::Code::Ok,"Successfull removed");
}