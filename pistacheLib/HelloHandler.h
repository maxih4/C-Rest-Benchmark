//
// Created by max on 22.12.21.
//

#ifndef CPPRESTSDK_HELLOHANDLER_H
#define CPPRESTSDK_HELLOHANDLER_H

#include <pistache/endpoint.h>

using namespace Pistache;

class HelloHandler : public Http::Handler {
public:
HTTP_PROTOTYPE(HelloHandler)


    void onRequest(const Http::Request& request, Http::ResponseWriter response) {
        response.send(Http::Code::Ok, "Hello, World\n");
    }
};


#endif //CPPRESTSDK_HELLOHANDLER_H
