#include "DatabaseManager.h"
#include <pqxx>
#include <iostream>

using namespace std;

DatabaseManager::DatabaseManager() {}

bool DatabaseManager::connect() {
    try {
        pqxx::connection conn(connection_string);
        cout << "Успешно подключились к PostgreSQL!" << endl;
        return true;
    } catch (const exception& e) {
        cout << "Ошибка подключения: " << e.what() << endl;
        return false;
    }
}

vector<Student> DatabaseManager::getStudents() {
    vector<Student> students;
    
    try {
        pqxx::connection conn(connection_string);
        pqxx::work txn(conn);
        
        pqxx::result result = txn.exec("SELECT student_id, full_name, student_group, course_number, education_type, social_category FROM students");
        
        for (const auto& row : result) {
            Student s;
            s.id = row["student_id"].as<int>();
            s.full_name = row["full_name"].as<string>();
            s.student_group = row["student_group"].as<string>();
            s.course_number = row["course_number"].as<int>();
            s.education_type = row["education_type"].as<string>();
            s.social_category = row["social_category"].is_null() ? "" : row["social_category"].as<string>();
            
            students.push_back(s);
        }
        
        cout << "Загружено студентов: " << students.size() << endl;
        txn.commit();
        
    } catch (const exception& e) {
        cout << "Ошибка при загрузке студентов: " << e.what() << endl;
    }
    
    return students;
}

vector<Grade> DatabaseManager::getStudentGrades(int student_id, int session_id) {
    vector<Grade> grades;
    
    try {
        pqxx::connection conn(connection_string);
        pqxx::work txn(conn);
        
        string query = "SELECT grade_id, student_id, subject_id, session_id, grade_value, exam_date, teacher_name FROM student_grades WHERE student_id = " + to_string(student_id) + " AND session_id = " + to_string(session_id);
        
        pqxx::result result = txn.exec(query);
        
        for (const auto& row : result) {
            Grade g;
            g.id = row["grade_id"].as<int>();
            g.student_id = row["student_id"].as<int>();
            g.subject_id = row["subject_id"].as<int>();
            g.session_id = row["session_id"].as<int>();
            g.grade_value = row["grade_value"].as<string>();
            g.exam_date = row["exam_date"].as<string>();
            g.teacher_name = row["teacher_name"].is_null() ? "" : row["teacher_name"].as<string>();
            
            grades.push_back(g);
        }
        
        cout << "📝 Загружено оценок для студента " << student_id << ": " << grades.size() << endl;
        txn.commit();
        
    } catch (const exception& e) {
        cout << "Ошибка при загрузке оценок: " << e.what() << endl;
    }
    
    return grades;
}

Student DatabaseManager::getStudent(int student_id) {
    Student student;
    
    try {
        pqxx::connection conn(connection_string);
        pqxx::work txn(conn);
        
        string query = "SELECT student_id, full_name, student_group, course_number, education_type, social_category FROM students WHERE student_id = " + to_string(student_id);
        
        pqxx::result result = txn.exec(query);
        
        if (!result.empty()) {
            const auto& row = result[0];
            student.id = row["student_id"].as<int>();
            student.full_name = row["full_name"].as<string>();
            student.student_group = row["student_group"].as<string>();
            student.course_number = row["course_number"].as<int>();
            student.education_type = row["education_type"].as<string>();
            student.social_category = row["social_category"].is_null() ? "" : row["social_category"].as<string>();
        }
        
        txn.commit();
        
    } catch (const exception& e) {
        cout << "Ошибка при загрузке студента: " << e.what() << endl;
    }
    
    return student;
}