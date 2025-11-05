#pragma once
#include <vector>
#include "Models.h"

using namespace std;

class DataBaseManager {
public:
    DataBaseManager();
    bool connect();
    vector<Student> getStudents();
    vector<Grade> getStudentsGrades(int student_id, int session_id);
    Sudent getStudent(int student_id);

private:
    string connection_string = " ";
};