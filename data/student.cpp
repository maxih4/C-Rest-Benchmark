//
// Created by max on 21.11.21.
//

#include "student.hpp"




Student::Student(int id, std::string name, int age) {
    this->id = id;
    this->name = name;
    this->age=age;
}

int Student::getId() const {
    return id;
}

const string &Student::getName() const {
    return name;
}

int Student::getAge() const {
    return age;
}
std::string Student::toJson(){
    std::string json;
    json.append("{\n");
    json.append("\t\"id\": ");
    json.append(std::to_string(this->id));
    json.append(",\n");
    json.append("\t\"name\": ");
    json.append("\"");
    json.append(this->name);
    json.append("\",\n");
    json.append("\t\"age\": ");
    json.append(std::to_string(this->age));
    json.append("\n");
    json.append("}");

return json;
}


web::json::value Student::toJson2(){

    using namespace web;
    json::value object;
    object["id"]=json::value::number(this->id);
    object["name"]=json::value::string(this->name);
    object["alter"]=json::value::number(this->age);
    return object;
}