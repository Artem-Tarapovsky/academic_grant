#pragma once
#include <string>
#include <vector>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

struct Student {
    int id;
    string full_name;
    string student_group;
    int course_number;
    string education_type;
    string education_level;
    string social_category;
    int ege_score;
    bool has_olympiad;
    bool is_foreign;
    bool has_disability_hearing;
    bool has_disability_vision;
    bool is_need_based;
    bool regional_coefficient;
    
    json to_json() const {
        return {
            {"id", id},
            {"full_name", full_name},
            {"student_group", student_group},
            {"course_number", course_number},
            {"education_type", education_type},
            {"education_level", education_level},
            {"social_category", social_category},
            {"ege_score", ege_score},
            {"has_olympiad", has_olympiad},
            {"is_foreign", is_foreign},
            {"has_disability_hearing", has_disability_hearing},
            {"has_disability_vision", has_disability_vision},
            {"is_need_based", is_need_based},
            {"regional_coefficient", regional_coefficient}
        };
    }
};

struct Grade {
    int id;
    int student_id;
    int subject_id;
    int session_id;
    string grade_value;
    string exam_date;
    string teacher_name;
    
    json to_json() const {
        return {
            {"id", id},
            {"student_id", student_id},
            {"subject_id", subject_id},
            {"session_id", session_id},
            {"grade_value", grade_value},
            {"exam_date", exam_date},
            {"teacher_name", teacher_name}
        };
    }
};

struct ScholarshipResult {
    int student_id;
    string scholarship_type;
    double amount;
    string status;
    string message;
    string rule_name;
    
    json to_json() const {
        return {
            {"student_id", student_id},
            {"scholarship_type", scholarship_type},
            {"amount", amount},
            {"status", status},
            {"message", message},
            {"rule_name", rule_name}
        };
    }
};

struct ScholarshipRule {
    int rule_id;
    string rule_name;
    string scholarship_type;
    string education_level;
    double min_average_grade;
    int min_ege_score;
    int max_ege_score;
    string required_grade;
    bool social_requirement;
    bool requires_olympiad;
    bool requires_foreign;
    bool requires_disability;
    bool requires_need_based;
    bool is_first_course;
    double amount_base;
    double amount_regional;
    int priority_level;
    string description;
    bool is_active;
};