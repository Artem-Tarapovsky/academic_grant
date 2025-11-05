#include "DataBaseManager.h"
#include <iostream>

using namespace std;

DataBaseManager::DataBaseManager() {}

bool DataBaseManager::connect() {
    cout << "Подключение к базе данных..." << endl;
    return true;
}

vector<Student> DataBaseManager::getStudents(){
    vector<Student> students;

    return students;
}

vector<Grade> DataBaseManager::getStudentGrades(int student_id, int session_id){
    vector<Grade> grades;

    return grades;
}

Student DataBaseManager::getStudent(int student_id){
    retutn {};
}