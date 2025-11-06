#include <iostream>
#include "database/DataBaseManager.h"
#include "core/ScholarshipCalculator.h"

using namespace std;

void demonstrateStudents() {
    cout << "Список студентов" << endl;
    
    DatabaseManager db;
    auto students = db.getStudents();
    
    json students_json;
    for (const auto& student : students) {
        students_json["students"].push_back(student.to_json());
        cout << "- " << student.full_name << " (" << student.student_group << ")" 
             << " - " << student.education_type;
        if (!student.social_category.empty()) {
            cout << " [" << student.social_category << "]";
        }
        cout << endl;
    }
    
    cout << endl << "JSON формат:" << endl;
    cout << students_json.dump(2) << endl;
}

void demonstrateScholarships() {
    cout << "Расчет стипендий" << endl;
    
    ScholarshipCalculator calculator;
    auto results = calculator.calculateForSession(1);
    
    json results_json;
    for (const auto& result : results) {
        results_json["scholarships"].push_back(result.to_json());
        
        cout << "Студент ID " << result.student_id << ": " << endl;
        cout << "  Тип: " << result.scholarship_type << endl;
        cout << "  Сумма: " << result.amount << " руб." << endl;
        cout << "  Статус: " << result.status << endl;
        cout << "  Примечание: " << result.message << endl;
        cout << endl;
    }
    
    cout << "JSON формат:" << endl;
    cout << results_json.dump(2) << endl;
}

void demonstrateGrades() {
    cout << "Оценки студентов" << endl;
    DatabaseManager db;
    
    for (int i = 1; i <= 3; i++) {
        auto grades = db.getStudentGrades(i, 1);
        if (!grades.empty()) {
            cout << "Студент ID " << i << " оценки:" << endl;
            
            json grades_json;
            for (const auto& grade : grades) {
                grades_json["grades"].push_back(grade.to_json());
                cout << "  - " << grade.grade_value << " по предмету " << grade.subject_id 
                     << " (" << grade.teacher_name << ")" << endl;
            }
            
            cout << "JSON формат:" << endl;
            cout << grades_json.dump(2) << endl << endl;
        }
    }
}

int main() {
    cout << "СИСТЕМА РАСЧЕТА СТИПЕНДИЙ" << endl;
    
    demonstrateStudents();
    demonstrateScholarships();
    demonstrateGrades();
    

    return 0;
}