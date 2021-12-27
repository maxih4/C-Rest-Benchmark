//
// Created by max on 22.12.21.
//

#ifndef CPPRESTSDK_PISTACHECONTROLLER_H
#define CPPRESTSDK_PISTACHECONTROLLER_H

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/description.h>
#include "../service/studentregistryservice.hpp"
#include "../rapidjson/document.h"



using namespace Pistache;



class pistacheController : public Http::Endpoint {


    Pistache::Rest::Router router;
    Studentregistryservice service;
public:
    pistacheController(Address addr, Studentregistryservice srs);
    void handleGet(const Rest::Request& req, Http::ResponseWriter res);
    void handlePost(const Rest::Request& req, Http::ResponseWriter res);
    void handlePut(const Rest::Request& req, Http::ResponseWriter res);
    void handleDel(const Rest::Request& req, Http::ResponseWriter res);

};


#endif //CPPRESTSDK_PISTACHECONTROLLER_H
