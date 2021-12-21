//
// Created by max on 15.11.21.
//

#include "cpprestsdkController.hpp"
#include <cpprest/http_listener.h>
#include <pplx/pplxtasks.h>
#include "../service/studentregistryservice.hpp"
#include "../data/student.hpp"


cpprestsdkController::cpprestsdkController() {
    Studentregistryservice srs;
    this->service=srs;
}



using namespace std;
using namespace web;
using namespace http;
using namespace http::experimental::listener;






void cpprestsdkController::createServer(){
   listener = http_listener("http://localhost:8080");
}

void cpprestsdkController::openListeners(){
    listener.support(methods::GET, std::bind(&cpprestsdkController::handle_get,this,std::placeholders::_1));
    listener.support(methods::POST,  std::bind(&cpprestsdkController::handle_post,this,std::placeholders::_1));
    listener.support(methods::PUT,  std::bind(&cpprestsdkController::handle_update,this,std::placeholders::_1));
    listener.support(methods::DEL,  std::bind(&cpprestsdkController::handle_remove,this,std::placeholders::_1));
}

pplx::task<void> cpprestsdkController::openServer(){
    return listener.open();
}

pplx::task<void> cpprestsdkController::closeServer(){

    return listener.close();
}

void cpprestsdkController::handle_remove(http_request request) {

    //Get Id from last position of the string
    vector<basic_string<char>> paths=http::uri::split_path(http::uri::decode(request.relative_uri().path()));
    int id;
    if(!paths.empty()){
        id = std::stoi(paths.back());
    }

    //Remove the student
    this->service.removing(id);


    //Send the Reply with HTTP Code OK and Json
    request.reply(status_codes::OK,"Successful");
}

void cpprestsdkController::handle_update(http_request request) {
    //Get Id from last position of the string
    vector<basic_string<char>> paths=http::uri::split_path(http::uri::decode(request.relative_uri().path()));
    int id;
    json::value jsonObjectRequest;
    json::value jsonObjectResponse;
    if(!paths.empty()){
        id = std::stoi(paths.back());
    }



    request.extract_json()
            .then([&jsonObjectRequest,&jsonObjectResponse,&id,this](json::value jo){

                //Fetch the student
                Student student = this->service.fetching(id);

                //remove the student
                this->service.removing(id);

//update the student
                jsonObjectRequest = jo;
                student.setName(jsonObjectRequest[U("name")].as_string());
                student.setAge(jsonObjectRequest[U("age")].as_integer());
                this->service.adding(student);
                jsonObjectResponse = student.toJson2();
                //Add json Object to our Map and then answer with success
                //jsonObjectResponse = this->service.adding()
            })
            .wait();


    //Send the Reply with HTTP Code OK and Json
    //request.reply(status_codes::OK,student.toJson());
    request.reply(status_codes::OK,jsonObjectResponse);
}

void cpprestsdkController::handle_post(http_request request) {
    json::value jsonObjectRequest;
    json::value jsonObjectResponse;
    int id;
    std::string name;
    int age;

        request.extract_json()
                .then([&jsonObjectRequest,&jsonObjectResponse,&id,&name,&age,this](json::value jo){
                    jsonObjectRequest = jo;
                    id = jsonObjectRequest[U("id")].as_integer();
                    name = jsonObjectRequest[U("name")].as_string();
                    age = jsonObjectRequest[U("age")].as_integer();
                    Student student(id,name,age);
                    this->service.adding(student);
                    jsonObjectResponse = student.toJson2();

                })
                .wait();



   request.reply(status_codes::OK,jsonObjectResponse);
}


void cpprestsdkController::handle_get(http_request request){

    //Get Id from last position of the string
    vector<basic_string<char>> paths=http::uri::split_path(http::uri::decode(request.relative_uri().path()));
    int id;
    if(!paths.empty()){
       id = std::stoi(paths.back());
    }

    //Fetch the student
    Student student = this->service.fetching(id);


    //Send the Reply with HTTP Code OK and Json
    //request.reply(status_codes::OK,student.toJson());
    request.reply(status_codes::OK,student.toJson2());


}


