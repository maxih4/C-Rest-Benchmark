#include <cpprest/http_listener.h>


using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;
#include <iostream>
#include <utility>
#include <string>
#include "cpprestsdk/cpprestsdkController.h"


#include "service/student.h"


#include <unordered_map>


int main(int argc, char** argv)
{
    using namespace std;
    cpprestsdkController controller;
    controller.createServer();
    controller.openListeners();
    controller.openServer().then([&controller](){std::cout << "started";}).wait();
    while(true);


}

void createData(){
    std::unordered_map<int, student> map;
    student s1(1,"Max",20);
    student s2(2,"Paul",30);
    student s3(3,"Jan",22);

}

