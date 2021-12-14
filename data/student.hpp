//
// Created by max on 21.11.21.
//

#ifndef CPPRESTSDK_STUDENT_HPP
#define CPPRESTSDK_STUDENT_HPP
using namespace std;

#include <string>
#include <cpprest/json.h>

class Student {

public:
    Student()=default;

    int getId() const;

    const string &getName() const;

    int getAge() const;
    std::string toJson();

    Student(int id, std::string name, int age);

    web::json::value toJson2();
private:
    int id;
    string name;
    int age;
};


#endif //CPPRESTSDK_STUDENT_HPP
