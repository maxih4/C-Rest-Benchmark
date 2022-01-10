//
// Created by max on 10.01.22.
//

#ifndef CPPRESTSDK_OATPPSTUDENT_H
#define CPPRESTSDK_OATPPSTUDENT_H

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include OATPP_CODEGEN_BEGIN(DTO) ///< Begin DTO codegen section

class OatppStudent : public oatpp::DTO {

    DTO_INIT(OatppStudent, DTO /* extends */)

    DTO_FIELD(String, name, "name");
    DTO_FIELD(Int32, age, "age");
    DTO_FIELD(Int32, id, "id");


};

#include OATPP_CODEGEN_END(DTO) ///< End DTO codegen section
#endif //CPPRESTSDK_OATPPSTUDENT_H
