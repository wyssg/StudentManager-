#pragma    once
#include <map>
#include <string>
#include "Student.hpp"
#include <iostream>
#include <fstream>

class StudentManager
{
private:
std::map<int,Student>data;    //用map存储学生信息，key为id，value为Student对象,map自动排序且id唯一
const std::string StudentData="data.txt";  //文件名
 public:
    StudentManager(){
        loadFromFile();   //构造函数中加载数据
    }

    ~StudentManager(){
        saveToFile();    //析构函数中保存数据
    }


    //增
bool addStudent(const Student& s){
    if(data.find(s.id)!=data.end()){
        std::cout<<"Student with ID "<<s.id<<" already exists."<<std::endl;
        return false;
    }
    data[s.id]=s;  //插入
    return true;
}

//删
bool removeStudent(int id){
    auto it=data.find(id);
    if(it==data.end()){    //data.end()表示最后一个数据的后一个，即没有找到
        std::cout<<"Student with ID "<<id<<" not found."<<std::endl;
        return false;
    }
    data.erase(it);   //来自map的erase，擦除
    std::cout<<"Student with ID "<<id<<" removed."<<std::endl;
    return true;
}


//改(所有信息都可以改)
bool updateStudent(const Student& s){
    auto it=data.find(s.id);
    if(it==data.end()){
        std::cout<<"Student with ID "<<s.id<<" not found."<<std::endl;
        return false;
    }
    if(it != data.end()){
        it ->second.id=s.id;
        it ->second.name=s.name;
        it ->second.age=s.age;
        it ->second.score=s.score;
        std::cout<<"Student with ID "<<s.id<<" updated."<<std::endl;
        return true;
    }
};


//查（单）
Student* getStudent(int id){
    auto it=data.find(id);
    if(it==data.end()){
        std::cout<<"Student with ID "<<id<<" not found."<<std::endl;
        return nullptr;
    }
    std::cout<<it->second.toString()<<std::endl;
    return &(it->second);  // 返回指向Student对象的指针

}

//查（所有）

void getAllStudents()
{
std::cout<<"All Students:"<<std::endl;
    for(const auto& pair:data)
    {
        std::cout<<pair.second.toString()<<std::endl;
    }
}



private:
//保存数据
void saveToFile()
{
    std::ofstream ofs(StudentData);  //ofstream用于写文件，ifstream用于读文件，fstream用于读写文件
    //来自<fstream> ，ofs打开一个文件没有则创建，有则覆盖
    
    if(!ofs)      //!表否，即打开文件失败                       
    {
        std::cerr<<"Error opening file for writing: "<<StudentData<<std::endl;
        return;
    }
    for(const auto& pair:data)   //const 只读不改，auto 自动推导类型，&引用原始数据避免拷贝
    {
        ofs<<pair.first<<" "       //ofs将数据写入文件，pair.first是key，pair.second是value
       <<pair.second.name<<" "
       <<pair.second.age<<" "
        <<pair.second.score<<std::endl;
    }
    ofs.close();  //关闭文件
    std::cout<<"Data saved to "<<StudentData<<std::endl;
    
}


/*
//加载数据
void loadFromFile()
{
    std::ifstream ifs(StudentData);  //ifstream用于读文件
    if(!ifs)    //打开文件失败
    {
        std::cerr<<"Error opening file for reading: "<<StudentData<<std::endl;
        return;
    }
    //data.clear();   //清空当前数据   //风险太高
    Student s;
    while(ifs>>s.id>>s.name>>s.age>>s.score)  //从文件读取数据到Student对象
    {
        data[s.id]=s;

    }
    ifs.close();   //关闭文件
    std::cout<<"Data loaded from "<<StudentData<<std::endl;
}
*/

//方案一，存在清空数据，风险太大

//加载数据方案二

void loadFromFile()
{
    std::ifstream ifs(StudentData);

    if(!ifs)
    {
        std::cerr<<"Error opening file for reading: "<<StudentData<<std::endl;
        return;
    }

    //先读取到临时map，再赋值给data，避免清空数据的风险
std::map <int,Student> tempData;
Student s;
int tempcCount=0;
while(ifs>>s.id>>s.name>>s.age>>s.score)
{
    tempData[s.id]=s;

    tempcCount++;
}
ifs.close();


//删除data（内存）中不在tempData的记录

int deletedCount=0;

auto it = data.begin();   //data.begin()返回指向map第一个元素的迭代器
while(it!=data.end())
{
    if(tempData.find(it->first)==tempData.end())
    {
        it=data.erase(it);
        deletedCount++;
    }
    else
    {
        ++it;  //让迭代器指向下一个元素，迭代器自增
    }
}

int updatedCount=0;
int addedCount=0;

for(const auto& pair:tempData)
{
    if (data.find(pair.first) !=data.end())
    {
        data[pair.first]=pair.second;
        updatedCount++;

    }
    else
    {
        data[pair.first]=pair.second;
        addedCount++;
    }
}



//更新和添加数据


}


};