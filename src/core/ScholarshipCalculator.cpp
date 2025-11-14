#include "core/ScholarshipCalculator.h"
#include "database/DataBaseManager.h"
#include <algorithm>
#include <iostream>

using namespace std;

vector<ScholarshipResult> ScholarshipCalculator::calculateForSession(int session_id) {
    vector<ScholarshipResult> results;
    DatabaseManager db;
    
    auto students = db.getStudents();
    
    for (const auto& student : students) {
        auto result = calculateForStudent(student.id, session_id);
        results.push_back(result);
    }
    
    return results;
}

ScholarshipResult ScholarshipCalculator::calculateForStudent(int student_id, int session_id) {
    DatabaseManager db;
    ScholarshipResult result;
    result.student_id = student_id;
    
    auto student = db.getStudent(student_id);
    auto grades = db.getStudentGrades(student_id, session_id);
    
    // Проверяем право на стипендию
    if (student.education_type != "budget") {
        result.scholarship_type = "Не имеет права";
        result.amount = 0;
        result.status = "rejected";
        result.message = "Контрактная форма обучения";
        result.rule_name = "none";
        return result;
    }
    
    // Проверяем есть ли неудовлетворительные оценки
    if (hasLowGrades(grades)) {
        result.scholarship_type = "Не имеет права";
        result.amount = 0;
        result.status = "rejected";
        result.message = "Есть удовлетворительные или неудовлетворительные оценки";
        result.rule_name = "none";
        return result;
    }
    
    // Рассчитываем средний балл
    double average_grade = calculateAverageGrade(grades);
    
    // Получаем applicable правила
    auto applicable_rules = getApplicableRules(student, grades, average_grade);
    
    if (applicable_rules.empty()) {
        result.scholarship_type = "Не имеет права";
        result.amount = 0;
        result.status = "rejected";
        result.message = "Не подходит ни под одно правило стипендии";
        result.rule_name = "none";
        return result;
    }
    
    // Выбираем правило с наивысшим приоритетом
    auto best_rule = *max_element(applicable_rules.begin(), applicable_rules.end(),
        [](const ScholarshipRule& a, const ScholarshipRule& b) {
            return a.priority_level < b.priority_level;
        });
    
    result.scholarship_type = best_rule.scholarship_type;
    result.amount = getScholarshipAmount(best_rule, student.regional_coefficient);
    result.status = "approved";
    result.message = best_rule.description;
    result.rule_name = best_rule.rule_name;
    
    return result;
}

double ScholarshipCalculator::calculateAverageGrade(const vector<Grade>& grades) {
    if (grades.empty()) return 0.0;
    
    double sum = 0.0;
    int count = 0;
    
    for (const auto& grade : grades) {
        if (grade.grade_value == "5" || grade.grade_value == "зачет") {
            sum += 5.0;
            count++;
        } else if (grade.grade_value == "4") {
            sum += 4.0;
            count++;
        } else if (grade.grade_value == "3") {
            sum += 3.0;
            count++;
        } else if (grade.grade_value == "2") {
            sum += 2.0;
            count++;
        }
        // "незачет" не учитывается в среднем балле
    }
    
    return count > 0 ? sum / count : 0.0;
}

bool ScholarshipCalculator::hasRequiredGrades(const vector<Grade>& grades, const string& required_grade) {
    if (required_grade.empty()) return true;
    
    for (const auto& grade : grades) {
        if (grade.grade_value == "зачет" || grade.grade_value == "незачет") {
            continue; // Зачеты не учитываются для требований к оценкам
        }
        if (required_grade == "5" && grade.grade_value != "5") {
            return false;
        }
        if (required_grade == "4" && (grade.grade_value == "3" || grade.grade_value == "2")) {
            return false;
        }
    }
    return true;
}

bool ScholarshipCalculator::hasLowGrades(const vector<Grade>& grades) {
    for (const auto& grade : grades) {
        if (grade.grade_value == "3" || grade.grade_value == "2" || grade.grade_value == "незачет") {
            return true;
        }
    }
    return false;
}

bool ScholarshipCalculator::hasSocialCategory(const Student& student) {
    return !student.social_category.empty();
}

bool ScholarshipCalculator::hasDisability(const Student& student) {
    return student.has_disability_hearing || student.has_disability_vision;
}

double ScholarshipCalculator::getScholarshipAmount(const ScholarshipRule& rule, bool has_regional_coefficient) {
    return has_regional_coefficient ? rule.amount_regional : rule.amount_base;
}

vector<ScholarshipRule> ScholarshipCalculator::getApplicableRules(const Student& student, const vector<Grade>& grades, double average_grade) {
    DatabaseManager db;
    auto all_rules = db.getScholarshipRules();
    vector<ScholarshipRule> applicable_rules;
    
    for (const auto& rule : all_rules) {
        if (!rule.is_active) continue;
        
        // Проверка уровня образования
        if (!rule.education_level.empty() && rule.education_level != student.education_level) {
            continue;
        }
        
        // Проверка среднего балла
        if (rule.min_average_grade > 0 && average_grade < rule.min_average_grade) {
            continue;
        }
        
        // Проверка оценок
        if (!hasRequiredGrades(grades, rule.required_grade)) {
            continue;
        }
        
        // Проверка ЕГЭ
        if (rule.min_ege_score > 0 && student.ege_score < rule.min_ege_score) {
            continue;
        }
        if (rule.max_ege_score > 0 && student.ege_score > rule.max_ege_score) {
            continue;
        }
        
        // Проверка олимпиад
        if (rule.requires_olympiad && !student.has_olympiad) {
            continue;
        }
        
        // Проверка социальных требований
        if (rule.social_requirement && !hasSocialCategory(student)) {
            continue;
        }
        
        // Проверка иностранцев
        if (rule.requires_foreign && !student.is_foreign) {
            continue;
        }
        
        // Проверка инвалидности
        if (rule.requires_disability && !hasDisability(student)) {
            continue;
        }
        
        // Проверка нуждаемости
        if (rule.requires_need_based && !student.is_need_based) {
            continue;
        }
        
        // Проверка первого курса
        if (rule.is_first_course && student.course_number != 1) {
            continue;
        }
        
        applicable_rules.push_back(rule);
    }
    
    return applicable_rules;
}