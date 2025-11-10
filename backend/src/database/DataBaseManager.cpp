#include "DataBaseManager.h"
#include <pqxx/pqxx>
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
        
        pqxx::result result = txn.exec(
            "SELECT student_id, full_name, student_group, course_number, education_type, "
            "education_level, social_category, ege_score, has_olympiad, is_foreign, "
            "has_disability_hearing, has_disability_vision, is_need_based, regional_coefficient "
            "FROM students"
        );
        
        for (const auto& row : result) {
            Student s;
            s.id = row["student_id"].as<int>();
            s.full_name = row["full_name"].as<string>();
            s.student_group = row["student_group"].as<string>();
            s.course_number = row["course_number"].as<int>();
            s.education_type = row["education_type"].as<string>();
            s.education_level = row["education_level"].as<string>();
            s.social_category = row["social_category"].is_null() ? "" : row["social_category"].as<string>();
            s.ege_score = row["ege_score"].is_null() ? 0 : row["ege_score"].as<int>();
            s.has_olympiad = row["has_olympiad"].as<bool>();
            s.is_foreign = row["is_foreign"].as<bool>();
            s.has_disability_hearing = row["has_disability_hearing"].as<bool>();
            s.has_disability_vision = row["has_disability_vision"].as<bool>();
            s.is_need_based = row["is_need_based"].as<bool>();
            s.regional_coefficient = row["regional_coefficient"].as<bool>();
            
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
        
        string query = 
            "SELECT grade_id, student_id, subject_id, session_id, grade_value, exam_date, teacher_name "
            "FROM student_grades WHERE student_id = " + to_string(student_id) + 
            " AND session_id = " + to_string(session_id);
        
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
        
        cout << "Загружено оценок для студента " << student_id << ": " << grades.size() << endl;
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
        
        string query = 
            "SELECT student_id, full_name, student_group, course_number, education_type, "
            "education_level, social_category, ege_score, has_olympiad, is_foreign, "
            "has_disability_hearing, has_disability_vision, is_need_based, regional_coefficient "
            "FROM students WHERE student_id = " + to_string(student_id);
        
        pqxx::result result = txn.exec(query);
        
        if (!result.empty()) {
            const auto& row = result[0];
            student.id = row["student_id"].as<int>();
            student.full_name = row["full_name"].as<string>();
            student.student_group = row["student_group"].as<string>();
            student.course_number = row["course_number"].as<int>();
            student.education_type = row["education_type"].as<string>();
            student.education_level = row["education_level"].as<string>();
            student.social_category = row["social_category"].is_null() ? "" : row["social_category"].as<string>();
            student.ege_score = row["ege_score"].is_null() ? 0 : row["ege_score"].as<int>();
            student.has_olympiad = row["has_olympiad"].as<bool>();
            student.is_foreign = row["is_foreign"].as<bool>();
            student.has_disability_hearing = row["has_disability_hearing"].as<bool>();
            student.has_disability_vision = row["has_disability_vision"].as<bool>();
            student.is_need_based = row["is_need_based"].as<bool>();
            student.regional_coefficient = row["regional_coefficient"].as<bool>();
        }
        
        txn.commit();
        
    } catch (const exception& e) {
        cout << "Ошибка при загрузке студента: " << e.what() << endl;
    }
    
    return student;
}

vector<ScholarshipRule> DatabaseManager::getScholarshipRules() {
    vector<ScholarshipRule> rules;
    
    try {
        pqxx::connection conn(connection_string);
        pqxx::work txn(conn);
        
        string query = 
            "SELECT rule_id, rule_name, scholarship_type, education_level, min_average_grade, "
            "min_ege_score, max_ege_score, required_grade, social_requirement, requires_olympiad, "
            "requires_foreign, requires_disability, requires_need_based, is_first_course, "
            "amount_base, amount_regional, priority_level, description "
            "FROM scholarship_rules WHERE is_active = true ORDER BY priority_level";
        
        pqxx::result result = txn.exec(query);
        
        for (const auto& row : result) {
            ScholarshipRule rule;
            rule.rule_id = row["rule_id"].as<int>();
            rule.rule_name = row["rule_name"].as<string>();
            rule.scholarship_type = row["scholarship_type"].as<string>();
            rule.education_level = row["education_level"].is_null() ? "" : row["education_level"].as<string>();
            rule.min_average_grade = row["min_average_grade"].is_null() ? 0.0 : row["min_average_grade"].as<double>();
            rule.min_ege_score = row["min_ege_score"].is_null() ? 0 : row["min_ege_score"].as<int>();
            rule.max_ege_score = row["max_ege_score"].is_null() ? 0 : row["max_ege_score"].as<int>();
            rule.required_grade = row["required_grade"].is_null() ? "" : row["required_grade"].as<string>();
            rule.social_requirement = row["social_requirement"].as<bool>();
            rule.requires_olympiad = row["requires_olympiad"].as<bool>();
            rule.requires_foreign = row["requires_foreign"].as<bool>();
            rule.requires_disability = row["requires_disability"].as<bool>();
            rule.requires_need_based = row["requires_need_based"].as<bool>();
            rule.is_first_course = row["is_first_course"].as<bool>();
            rule.amount_base = row["amount_base"].as<double>();
            rule.amount_regional = row["amount_regional"].as<double>();
            rule.priority_level = row["priority_level"].as<int>();
            rule.description = row["description"].as<string>();
            
            rules.push_back(rule);
        }
        
        cout << "Загружено правил стипендий: " << rules.size() << endl;
        txn.commit();
        
    } catch (const exception& e) {
        cout << "Ошибка при загрузке правил стипендий: " << e.what() << endl;
    }
    
    return rules;
}