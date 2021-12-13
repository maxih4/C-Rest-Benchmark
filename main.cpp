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


int main(int argc, char** argv)
{

    cpprestsdkController controller;

    controller.createServer();
    controller.openListeners();
    controller.openServer().then([&controller](){std::cout << "started";}).wait();
    while(true);


}



