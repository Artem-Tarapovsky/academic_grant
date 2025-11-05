#include <iostream>
#include "database/DataBaseManager.h"
#include "core/ScholarshipCalculator.h"

using namespace std;

int main() {
    cout << "Academic Grant" << endl;
    
    DataBaseManager db;
    auto students = db.getStudent();

    cout << "Найдено студентов: " << students.size() << endl;
    for (const auto& student : students) {
        cout << student.full_name << " (" << student.student_group << ") " << endl;
    }

    ScholarshipCalculator calculator;
    auto results = calculator.calculateForSession(1);

    cout << endl << "Резудьтат расчёта стипендий: " << endl;
    for (const auto& result : results){
        cout << "Студент " << result.student_id << ": "
        << result.scholarship_type << " - "
        << result.amount << " руб." << endl;
    }

    return 0;
}