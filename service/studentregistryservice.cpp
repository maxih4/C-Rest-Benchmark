//
// Created by max on 13.12.21.
//

#include <mutex>
#include "studentregistryservice.hpp"


std::mutex m;

Studentregistryservice::Studentregistryservice(){
    std::map<int, Student> map;
    Student s1(1,"Max",20);
    Student s2(2,"Paul",30);
    Student s3(3,"Jan",22);
    map.insert(std::make_pair(s1.getId(),s1));
    map.insert(std::make_pair(s2.getId(),s2));
    map.insert(std::make_pair(s3.getId(),s3));
    this->studentMap=map;
}
Student Studentregistryservice::fetching(int id){
    return this->studentMap.at(id);
}

bool Studentregistryservice::adding(Student student){
    m.lock();
    this->studentMap.insert(std::make_pair(student.getId(),student));
    m.unlock();
    return true;
}

bool Studentregistryservice::removing(int id) {
    m.lock();
    this->studentMap.erase(id);
    m.unlock();
    return true;
}



