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

#include "pistacheLib/pistacheController.h"
#include "pistache/endpoint.h"


void startCppRestSdk(){
    cpprestsdkController controller;

    controller.createServer();
    controller.openListeners();
    controller.openServer().then([&controller](){std::cout << "started";}).wait();
    while(true);
}

void startPistache(){
    pistacheController app({Ipv4::any(), 9000});
    app.serve();
}
int main(int argc, char** argv)
{
    startPistache();


}



