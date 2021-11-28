//
// Created by max on 15.11.21.
//

#include "cpprestsdkController.h"
#include <cpprest/http_listener.h>
#include <pplx/pplxtasks.h>


cpprestsdkController::cpprestsdkController() {}



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
//to implement
}

void cpprestsdkController::handle_update(http_request request) {
    //to implement
}

void cpprestsdkController::handle_post(http_request request) {
    //to implement

}


void cpprestsdkController::handle_get(http_request request){
    //to implement
    std::cout <<"\nhandle GET\n";
    std::cout <<"\nHello World\n";
    request.reply(status_codes::OK);

}


