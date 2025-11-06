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
    string social_category;
    
    json to_json() const {
        return {
            {"id", id},
            {"full_name", full_name},
            {"student_group", student_group},
            {"course_number", course_number},
            {"education_type", education_type},
            {"social_category", social_category}
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
    
    json to_json() const {
        return {
            {"student_id", student_id},
            {"scholarship_type", scholarship_type},
            {"amount", amount},
            {"status", status},
            {"message", message}
        };
    }
};