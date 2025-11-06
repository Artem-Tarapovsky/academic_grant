#include <iostream>
#include "database/DatabaseManager.h"
#include "core/ScholarshipCalculator.h"

using namespace std;

void demonstrateDatabaseConnection() {
    cout << "Подключение к БД" << endl;
    
    DatabaseManager db;
    if (db.connect()) {
        cout << "Подключено" << endl;
    } else {
        cout << "Не удалось подключиться к БД" << endl;
        return;
    }
}

void demonstrateStudents() {
    cout << endl << "Загрзка данных студентов" << endl;
    
    DatabaseManager db;
    auto students = db.getStudents();
    
    json students_json;
    for (const auto& student : students) {
        students_json["students"].push_back(student.to_json());
        
        cout << " " << student.full_name << endl;
        cout << " Группа: " << student.student_group << endl;
        cout << " Курс: " << student.course_number << endl;
        cout << " Форма обучения: " << student.education_type << endl;
        if (!student.social_category.empty()) {
            cout << " Соц. категория: " << student.social_category << endl;
        }
        cout << endl;
    }
    
    cout << "json формат данных:" << endl;
    cout << students_json.dump(2) << endl;
}

void demonstrateScholarshipCalculation() {
    cout << endl << "Расчёт стипендий" << endl;
    
    ScholarshipCalculator calculator;
    auto results = calculator.calculateForSession(1);
    
    json results_json;
    double total_amount = 0;
    
    for (const auto& result : results) {
        results_json["scholarships"].push_back(result.to_json());
        total_amount += result.amount;
        
        cout << " Студент ID: " << result.student_id << endl;
        cout << " Тип стипендии: " << result.scholarship_type << endl;
        cout << " Сумма: " << result.amount << " руб." << endl;
        cout << " Статус: " << result.status << endl;
        cout << " Примечание: " << result.message << endl;
    }
    
    cout << "Общая сумма к выплате: " << total_amount << " руб." << endl;
    
    cout << endl << "оыщт формат результатов:" << endl;
    cout << results_json.dump(2) << endl;
}

void demonstrateGrades() {
    cout << endl << "Загрзка оценок" << endl;
    
    DatabaseManager db;
    
    for (int student_id = 1; student_id <= 3; student_id++) {
        auto grades = db.getStudentGrades(student_id, 1);
        if (!grades.empty()) {
            cout << "Оценки студента ID " << student_id << ":" << endl;
            
            json grades_json;
            for (const auto& grade : grades) {
                grades_json["grades"].push_back(grade.to_json());
                cout << "   - " << grade.grade_value << " (предмет " << grade.subject_id << ") - " << grade.teacher_name << endl;
            }
            
            cout << "   json формат:" << endl;
            cout << "   " << grades_json.dump(2) << endl << endl;
        }
    }
}

int main() {
    cout << "ACADEMIC GRANT" << endl;
    cout << "База данных: PostgreSQL" << endl;
    cout << "Библиотека: libpqxx" << endl;
    cout << "Формат данных: JSON" << endl;
    cout << endl;
    
    demonstrateDatabaseConnection();
    demonstrateStudents();
    demonstrateGrades();
    demonstrateScholarshipCalculation();
    
    return 0;
}