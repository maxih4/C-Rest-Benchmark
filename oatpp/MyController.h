#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/component.hpp"
#include "../service/studentregistryservice.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) ///< Begin ApiController codegen section

class MyController : public oatpp::web::server::api::ApiController {
public:

    MyController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) /* Inject object mapper */
    : oatpp::web::server::api::ApiController(objectMapper)
            {}

    ENDPOINT("GET", "students/{userId}", fetching,
             PATH(Int32, userId))
    {
        return createResponse(Status::CODE_200,service.fetching(userId).toJson());
    }
    // TODO - more endpoints here
private: Studentregistryservice service;


};

#include OATPP_CODEGEN_END(ApiController)