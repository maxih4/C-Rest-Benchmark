//
// Created by max on 15.11.21.
//

#ifndef CPPRESTSDK_CPPRESTSDKCONTROLLER_HPP
#define CPPRESTSDK_CPPRESTSDKCONTROLLER_HPP
#include <cpprest/http_listener.h>
#include <pplx/pplxtasks.h>
#include "../service/studentregistryservice.hpp"
using namespace web;
using namespace http;
using namespace http::experimental::listener;

class cpprestsdkController {
public:
    cpprestsdkController();

    void createServer();
    pplx::task<void> openServer();
    pplx::task<void> closeServer();
    void openListeners();
    void handle_get(http_request request);

    void handle_post(http_request request);

    void handle_update(http_request request);

    void handle_remove(http_request request);

    http_listener listener;
private:
    Studentregistryservice service;

};


#endif //CPPRESTSDK_CPPRESTSDKCONTROLLER_HPP
