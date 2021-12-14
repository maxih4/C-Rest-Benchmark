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
    //to implement
}

void cpprestsdkController::handle_post(http_request message) {
    //to implement
    try {
        message.extract_json().then([message](web::json::value body)
                                    {std::cout << body["id"];
                                        message.reply(status_codes::OK, body);
                                    });
    }catch(const exception& e){
        std::cout << "JOJO";
        std::cout << e.what();
    }

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


