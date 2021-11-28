//
// Created by max on 15.11.21.
//

#ifndef CPPRESTSDK_CPPRESTSDKCONTROLLER_H
#define CPPRESTSDK_CPPRESTSDKCONTROLLER_H
#include <cpprest/http_listener.h>
#include <pplx/pplxtasks.h>
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
};


#endif //CPPRESTSDK_CPPRESTSDKCONTROLLER_H
