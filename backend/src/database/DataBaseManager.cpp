#include "DataBaseManager.h"
#include <iostream>

using namespace std;

DatabaseManager::DatabaseManager() {}

bool DatabaseManager::connect() {
    cout << "Cоединение с базой данных" << endl;
    return true;
}

vector<Student> DatabaseManager::getStudents() {
    vector<Student> students;
    
    // Тестовые данные 
    students.push_back({1, "Иванов Алексей Сергеевич", "АБ-321", 2, "budget", ""});
    students.push_back({2, "Петрова Мария Дмитриевна", "АБ-321", 2, "budget", "сирота"});
    students.push_back({3, "Сидоров Денис Игоревич", "АБ-321", 2, "budget", ""});
    students.push_back({4, "Козлова Анна Викторовна", "АБ-321", 2, "contract", ""});
    students.push_back({5, "Смирнов Владислав Андреевич", "АБ-321", 2, "budget", "инвалидность"});
    students.push_back({6, "Федорова Екатерина Максимовна", "АБ-321", 2, "budget", ""});
    
    return students;
}

vector<Grade> DatabaseManager::getStudentGrades(int student_id, int session_id) {
    vector<Grade> grades;
    
    // Тестовые данные 
    if (student_id == 1) {
        grades.push_back({1, 1, 1, 1, "5", "2024-12-15", "Доцент Иванов"});
        grades.push_back({2, 1, 2, 1, "5", "2024-12-18", "Доцент Петрова"});
        grades.push_back({3, 1, 3, 1, "5", "2024-12-22", "Старший преподаватель Сидоров"});
    } else if (student_id == 2) {
        grades.push_back({4, 2, 1, 1, "4", "2024-12-15", "Доцент Иванов"});
        grades.push_back({5, 2, 2, 1, "5", "2024-12-18", "Доцент Петрова"});
        grades.push_back({6, 2, 3, 1, "4", "2024-12-22", "Старший преподаватель Сидоров"});
    }
    
    return grades;
}

Student DatabaseManager::getStudent(int student_id) {
    auto students = getStudents();
    for (const auto& student : students) {
        if (student.id == student_id) {
            return student;
        }
    }
    return {0, "Не найден", "", 0, "", ""};
}