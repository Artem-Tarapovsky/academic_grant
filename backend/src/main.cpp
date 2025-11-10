#include <iostream>
#include "database/DataBaseManager.h"
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
    cout << endl << "Загрузка данных студентов" << endl;
    
    DatabaseManager db;
    auto students = db.getStudents();
    
    json students_json;
    for (const auto& student : students) {
        students_json["students"].push_back(student.to_json());
        
        cout << " " << student.full_name << endl;
        cout << " Группа: " << student.student_group << endl;
        cout << " Курс: " << student.course_number << endl;
        cout << " Уровень: " << student.education_level << endl;
        cout << " Форма обучения: " << student.education_type << endl;
        if (!student.social_category.empty()) {
            cout << " Соц. категория: " << student.social_category << endl;
        }
        if (student.ege_score > 0) {
            cout << " Баллы ЕГЭ: " << student.ege_score << endl;
        }
        if (student.has_olympiad) {
            cout << " Победитель олимпиады" << endl;
        }
        if (student.is_foreign) {
            cout << " Иностранный студент" << endl;
        }
        if (student.has_disability_hearing || student.has_disability_vision) {
            cout << " Инвалидность: " << (student.has_disability_hearing ? "слух" : "зрение") << endl;
        }
        if (student.is_need_based) {
            cout << " Нуждающийся студент" << endl;
        }
        cout << " Районный коэффициент: " << (student.regional_coefficient ? "да" : "нет") << endl;
        cout << endl;
    }
    
    cout << "JSON формат данных:" << endl;
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
        cout << " Правило: " << result.rule_name << endl;
        cout << " Сумма: " << result.amount << " руб." << endl;
        cout << " Статус: " << result.status << endl;
        cout << " Примечание: " << result.message << endl;
        cout << endl;
    }
    
    cout << "Общая сумма к выплате: " << total_amount << " руб." << endl;
    
    cout << endl << "JSON формат результатов:" << endl;
    cout << results_json.dump(2) << endl;
}

void demonstrateGrades() {
    cout << endl << "Загрузка оценок" << endl;
    
    DatabaseManager db;
    
    for (int student_id = 1; student_id <= 6; student_id++) {
        auto grades = db.getStudentGrades(student_id, 1);
        if (!grades.empty()) {
            cout << "Оценки студента ID " << student_id << ":" << endl;
            
            json grades_json;
            double sum = 0;
            int count = 0;
            
            for (const auto& grade : grades) {
                grades_json["grades"].push_back(grade.to_json());
                cout << "   - " << grade.grade_value << " (предмет " << grade.subject_id << ") - " << grade.teacher_name << endl;
                
                // Расчет среднего балла
                if (grade.grade_value == "5" || grade.grade_value == "зачет") {
                    sum += 5.0;
                    count++;
                } else if (grade.grade_value == "4") {
                    sum += 4.0;
                    count++;
                } else if (grade.grade_value == "3") {
                    sum += 3.0;
                    count++;
                }
            }
            
            if (count > 0) {
                cout << "   Средний балл: " << (sum / count) << endl;
            }
            
            cout << "   JSON формат:" << endl;
            cout << "   " << grades_json.dump(2) << endl << endl;
        }
    }
}

int main() {
    cout << "ACADEMIC GRANT - РАСШИРЕННАЯ ВЕРСИЯ" << endl;
    cout << "База данных: PostgreSQL" << endl;
    cout << "Библиотека: libpqxx" << endl;
    cout << "Формат данных: JSON" << endl;
    cout << "Поддержка всех видов стипендий 2025/2026" << endl;
    cout << endl;
    
    demonstrateDatabaseConnection();
    demonstrateStudents();
    demonstrateGrades();
    demonstrateScholarshipCalculation();
    
    return 0;
}