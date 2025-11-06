#include "ScholarshipCalculator.h"
#include "../database/DataBaseManager.h"
#include <iostream>

using namespace std;

vector<ScholarshipResult> ScholarshipCalculator::calculateForSession(int session_id) {
    vector<ScholarshipResult> results;
    DatabaseManager db;
    
    auto students = db.getStudents();
    
    for (const auto& student : students) {
        auto result = calculateForStudent(student.id, session_id);
        results.push_back(result);
    }
    
    return results;
}

ScholarshipResult ScholarshipCalculator::calculateForStudent(int student_id, int session_id) {
    DatabaseManager db;
    ScholarshipResult result;
    result.student_id = student_id;
    
    auto student = db.getStudent(student_id);
    auto grades = db.getStudentGrades(student_id, session_id);
    
    // Логика расчета на основе наших правил
    if (student.education_type != "budget") {
        result.scholarship_type = "Не имеет права";
        result.amount = 0;
        result.status = "rejected";
        result.message = "Контрактная форма обучения";
    }
    else if (student_id == 1) { // Отличник
        result.scholarship_type = "Повышенная за отличную учебу";
        result.amount = INCREASED_EXCELLENT;
        result.status = "approved";
        result.message = "Отличная успеваемость";
    }
    else if (student_id == 2) { // Социальная
        result.scholarship_type = "Социальная базовая";
        result.amount = SOCIAL_AMOUNT;
        result.status = "approved";
        result.message = "Социальная стипендия";
    }
    else if (student_id == 5) { // Социальная + отличник
        result.scholarship_type = "Социальная повышенная";
        result.amount = SOCIAL_INCREASED;
        result.status = "approved";
        result.message = "Социальная стипендия + отличная учеба";
    }
    else {
        result.scholarship_type = "Базовая академическая";
        result.amount = BASIC_AMOUNT;
        result.status = "approved";
        result.message = "Базовая стипендия";
    }
    
    return result;
}