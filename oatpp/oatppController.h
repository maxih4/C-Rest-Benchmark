#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/component.hpp"
#include "../service/studentregistryservice.hpp"
#include "oatppStudent.h"
#include OATPP_CODEGEN_BEGIN(ApiController) ///< Begin ApiController codegen section

class oatppController : public oatpp::web::server::api::ApiController {
private:
    OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, m_objectMapper);
public:

    oatppController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) /* Inject object mapper */
    : oatpp::web::server::api::ApiController(objectMapper)
            {}
    ENDPOINT("POST", "students/", adding,
             BODY_DTO(Object<OatppStudent>,oatppStudent))
    {

        Student stud(oatppStudent->id,oatppStudent->name,oatppStudent->age);


        service.adding(stud);
        return createResponse(Status::CODE_200,m_objectMapper->writeToString(oatppStudent));
    }
    ENDPOINT("GET", "students/{userId}", fetching,
             PATH(Int32, userId))
    {
        Student student = service.fetching(userId);
        auto resStudent = OatppStudent::createShared();
        resStudent->name = student.getName();
        resStudent->id = student.getId();
        resStudent->age = student.getAge();
        return createResponse(Status::CODE_200,m_objectMapper->writeToString(resStudent));
    }

    ENDPOINT("DELETE", "students/{userId}", removing,
             PATH(Int32, userId))
    {
        service.removing(userId);
        return createResponse(Status::CODE_200,"successfully removed");
    }

    ENDPOINT("PUT", "students/{userId}", update,
             PATH(Int32, userId),
             BODY_DTO(Object<OatppStudent>,oatppStudent))
    {
        Student stud = service.fetching(userId);
        stud.setName(oatppStudent->name);
        stud.setAge(oatppStudent->age);
        oatppStudent->id = userId;

        service.removing(userId);
        service.adding(stud);
        return createResponse(Status::CODE_200,m_objectMapper->writeToString(oatppStudent));
    }


    // TODO -more endpoints here
private: Studentregistryservice service;


};

#include OATPP_CODEGEN_END(ApiController)



