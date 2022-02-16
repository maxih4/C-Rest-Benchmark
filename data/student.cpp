//
// Created by max on 21.11.21.
//

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
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

    rapidjson::Document document;
    const char* json="{\"id\":1,\"age\":1}";
    document.Parse(json);
    document["id"] = this->id;
    rapidjson::Value name;
    {
        name.SetString(this->name.c_str(),document.GetAllocator());
    }
    document.AddMember("name",name,document.GetAllocator());
    document["age"] = this->age;
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    return buffer.GetString();
}


web::json::value Student::toJson2(){

    using namespace web;
    json::value object;
    object["id"]=json::value::number(this->id);
    object["name"]=json::value::string(this->name);
    object["alter"]=json::value::number(this->age);
    return object;
}

void Student::setName(const string &name) {
    Student::name = name;
}

void Student::setAge(int age) {
    Student::age = age;
}
