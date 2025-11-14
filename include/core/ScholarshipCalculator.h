#pragma once
#include "database/Models.h"
#include <vector>

using namespace std;

class ScholarshipCalculator {
public:
    vector<ScholarshipResult> calculateForSession(int session_id);
    ScholarshipResult calculateForStudent(int student_id, int session_id);
    
private:
    double calculateAverageGrade(const vector<Grade>& grades);
    bool hasRequiredGrades(const vector<Grade>& grades, const string& required_grade);
    bool hasLowGrades(const vector<Grade>& grades);
    bool hasSocialCategory(const Student& student);
    bool hasDisability(const Student& student);
    double getScholarshipAmount(const ScholarshipRule& rule, bool has_regional_coefficient);
    vector<ScholarshipRule> getApplicableRules(const Student& student, const vector<Grade>& grades, double average_grade);
};