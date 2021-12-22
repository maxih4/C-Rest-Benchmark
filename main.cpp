#include <cpprest/http_listener.h>


using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;
#include <iostream>
#include <utility>
#include <string>
#include "cpprestsdk/cpprestsdkController.hpp"


#include "data/student.hpp"
#include <map>
#include "service/studentregistryservice.hpp"

#include "pistacheLib/HelloHandler.h"
#include "pistache/endpoint.h"


void startCppRestSdk(){
    cpprestsdkController controller;

    controller.createServer();
    controller.openListeners();
    controller.openServer().then([&controller](){std::cout << "started";}).wait();
    while(true);
}

void startPistache(){
    Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(9080));
    auto opts = Pistache::Http::Endpoint::options()
            .threads(1);
    Pistache::Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(Pistache::Http::make_handler<HelloHandler>());
    server.serve();
}
int main(int argc, char** argv)
{
    startPistache();


}



