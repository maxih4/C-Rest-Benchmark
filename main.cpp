#include <cpprest/http_listener.h>


using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;
#include <iostream>
#include <utility>
#include <string>
using namespace std;

#define TRACE(msg)  cout << msg



void handle_get(http_request request){
    TRACE("\nhandle GET\n");
    TRACE("\nHello World\n");
    request.reply(status_codes::OK);

};

int main(int argc, char** argv)
{

    http_listener listener("http://localhost:8080");

    listener.support(methods::GET, [](http_request request) {handle_get(request);});
    
    try{
        listener
        .open()
        .then([&listener]() {TRACE("\nstarting to listen\n");})
        .wait();
        while(true);
    }catch(exception const & e){
        cout << "Exception";
        cout << e.what() << endl;
    }
    
    
    return 0;


}


