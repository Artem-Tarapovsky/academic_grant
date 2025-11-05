#include "ScholarshipCalculator.h"
#include "../database/DataBaseManager.h"
#include <iostream>

using namespace std;

vector<ScholarshipResult> ScholarshipCalculator::calculateForSession(int session_id) {
    vector<ScholarshipResult> results;
    DataBaseManager db;

    auto students = db.getStudent();

    for (const auto& student : students) {
        auto result = calculateForStudent(students.id, session_id);
        results.push_back(result);
    }
    return results;
}

ScholarshipResult ScholarshipCalculator::calculateForStudent(int student_id, int session_id) {
    DataBaseManager db;
    ScholarshipResult result;
    result.student_id = student_id;

    auto student = db.getStudent(student_id);
    auto grades = db.getStudentsGrades(student_id, session_id);

    if (student_id == 1) {
        result.scholarship_type = "Повышенная за отличную учебу";
        result.amount = INCREASED_EXCELLENT;
        result.status = "approved";
        result.message = "Отличная успеваемость";
    } else if (student_id == 2) {
        result.scholarship_type = "Социальная базовая";
        result.amount = SOCIAL_AMOUNT;
        result.status = "approved";
        result.message = "Социальная стипендия";
    } else {
        result.scholarship_type = "Базовая академическая";
        result.amount = BASIC_AMOUNT;
        result.status = "approved";
        result.message = "Базовая стипендия";
    }

    return result;

}