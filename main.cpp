#include <iostream>
#include "StudentManager.hpp"
#include <string>

void showMenu() {
    std::cout << "\n1. Add Student\n";
    std::cout << "2. Remove Student\n";
    std::cout << "3. Update Score\n";
    std::cout << "4. Find Student\n";
    std::cout << "5. List All\n";
    std::cout << "0. Exit\n";
    std::cout << "Select: ";
}

int main() {
      // 这一步会自动加载文件
    StudentManager db;  

    int choice;
    while (true) {
        showMenu();
        std::cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            Student s;
            std::cout << "Enter ID Name Age Score: ";
            // 比如输入: 1001 Jack 20 88.5
            std::cin >> s.id >> s.name >> s.age >> s.score;
            db.addStudent(s);
        }
        else if (choice == 2) {
            int id;
            std::cout << "Enter ID to delete: ";
            std::cin >> id;
            db.removeStudent(id);
        }
        else if (choice == 3) {
            int id;
            std::cout << "Enter ID to update: ";
            std::cin >> id;
            Student* s = db.getStudent(id);
            if (s == nullptr)
            {
               continue;
            }
            else 
            {
                std::cout << "\nEnter new info"<< std::endl;
                std::cin>> s->id >> s->name >> s->age >> s->score;
                db.updateStudent(*s);

            }



        }
        else if (choice == 4) {
            int id;
            std::cout << "Enter ID to find: ";
            std::cin >> id;
            db.getStudent(id);
        }
        else if (choice == 5) {
            db.getAllStudents();
        }
        
    }
    
    return 0; // 退出时会自动调用析构函数保存文件
}