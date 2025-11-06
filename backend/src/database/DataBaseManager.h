#pragma once
#include <vector>
#include "Models.h"

using namespace std;

class DatabaseManager {
public:
    DatabaseManager();
    bool connect();
    vector<Student> getStudents();
    vector<Grade> getStudentGrades(int student_id, int session_id);
    Student getStudent(int student_id);
    
private:
    string connection_string = "host=localhost port=5432 dbname=academic_grant_db user=academic_grant password=academic_grant";
};