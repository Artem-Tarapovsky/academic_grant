#pragma once
#include "../database/Models.h"
#include <vector>

using namespace std;

class ScholarshipCalculator {
public:
    vector<ScholarshipResult> calculateForSession(int session_id);
    ScholarshipResult calculateForStudent(int student_id, int session_id);

private:
    const double BASIC_AMOUNT = 1000.0;
    const double INCREASED_EXCELLENT = 5000.0;
    const double SOCIAL_AMOUNT = 1500.0;
    const double SOCIAL_INCREASED = 5500.0;
}

