//
// Created by max on 12.12.21.
//

#ifndef CPPRESTSDK_STUDENTREGISTRYSERVICE_HPP
#define CPPRESTSDK_STUDENTREGISTRYSERVICE_HPP


#include <map>
#include "../data/student.hpp"

class Studentregistryservice {

public:


    Student fetching(int id);
    bool adding(Student student);
    bool removing(Student student);

    Studentregistryservice();

private:
    std::map<int, Student> studentMap;

};


#endif //CPPRESTSDK_STUDENTREGISTRYSERVICE_HPP
