#pragma once
#include<string>
#include<iostream>

struct Student
{
    int id;
    std::string  name;   //std::string用于存储字符串,来自<string>头文件，自动管理内存
    int age;
    double score;
    // 把对象变成字符串
    std::string toString() const
    {
        return "Student{id=" + std::to_string(id) +
               ", name='" + name + "'" +
               ", age=" + std::to_string(age) +
               ", score=" + std::to_string(score) + "}";
    }

};
