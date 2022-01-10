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


#include "crow/crowController.h"


#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/oatppController.h"
#include "oatpp/network/Server.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"



void startCppRestSdk(Studentregistryservice srs){
    cpprestsdkController controller(srs);

    controller.createServer();
    controller.openListeners();
    controller.openServer().then([&controller](){std::cout << "started";}).wait();
    while(true);
}

void startPistache(Studentregistryservice srs){
    pistacheController app({Ipv4::any(), 9000},srs);
    app.serve();
}

void startCrow(Studentregistryservice srs){
    crowController controller(srs);
    controller.setupServer();
}

void startOatpp(Studentregistryservice srs){
    oatpp::base::Environment::init();
    /* Create Router for HTTP requests routing */
    auto router = oatpp::web::server::HttpRouter::createShared();

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)([] {
        auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
        objectMapper->getDeserializer()->getConfig()->allowUnknownFields = false;
        return objectMapper;
    }());

    router->addController(std::make_shared<oatppController>());

    /* Create HTTP connection handler with router */
    auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);

    /* Create TCP connection provider */
    auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared({"localhost", 8000, oatpp::network::Address::IP_4});

    /* Create server which takes provided TCP connections and passes them to HTTP connection handler */
    oatpp::network::Server server(connectionProvider, connectionHandler);

    /* Print info about server port */
    OATPP_LOGI("MyApp", "Server running on port %s", connectionProvider->getProperty("port").getData());

    /* Run server */
    server.run();
    oatpp::base::Environment::destroy();
}


int main(int argc, char** argv)
{
    Studentregistryservice srs;
    //startCrow(srs);
    //startPistache(srs);

    startOatpp(srs);


}



