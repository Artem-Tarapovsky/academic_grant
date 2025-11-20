#include <iostream>
#include <string>
#include "database/DataBaseManager.h"
#include "core/ScholarshipCalculator.h"
#include "core/AuthManager.h"

using namespace std;

// Глобальные переменные для текущей сессии
AuthManager authManager;
string current_token;
User current_user;

void showLoginMenu() {
    cout << "Вход" << endl;
    cout << endl << "Доступные тестовые пользователи:" << endl;
    cout << "Администратор - admin / admin123" << endl;
    cout << "Преподаватель - teacher / teacher123" << endl;
    cout << "Студент 1 - student1 / student123 (Иванов Иван)" << endl;
    cout << "Студент 2 - student2 / student123 (Петрова Мария)" << endl;
    cout << "Студент 3 - student3 / student123 (Сидоров Алексей)" << endl;
    cout << endl;
}

bool login() {
    string username, password;
    
    cout << "Имя пользователя: ";
    cin >> username;
    cout << "Пароль: ";
    cin >> password;
    
    AuthResponse response = authManager.login(username, password);
    
    if (response.success) {
        current_token = response.token;
        current_user = response.user;
        return true;
    } else {
        return false;
    }
}

void showAdminMenu() {
    cout << endl << "Панель администратора" << endl;
    cout << "1. Просмотр всех студентов" << endl;
    cout << "2. Расчет стипендий для сессии" << endl;
    cout << "3. Управление пользователями" << endl;
    cout << "4. Просмотр статистики" << endl;
    cout << "5. Выход" << endl;
}

void showTeacherMenu() {
    cout << endl << "Панель преподавателя" << endl;
    cout << "1. Просмотр студентов" << endl;
    cout << "2. Ввод оценок" << endl;
    cout << "3. Просмотр стипендий" << endl;
    cout << "4. Выход" << endl;
}

void showStudentMenu() {
    cout << endl << "Панель студента" << endl;
    cout << "1. Мои данные" << endl;
    cout << "2. Мои оценки" << endl;
    cout << "3. Моя стипендия" << endl;
    cout << "4. Выход" << endl;
}

// Функции для Администратора
void adminViewAllStudents() {
    cout << endl << "Все студенты" << endl;
    DatabaseManager db;
    auto students = db.getStudents();
    
    for (const auto& student : students) {
        cout << "ID: " << student.id << " | " << student.full_name << " | " 
             << student.student_group << " | Курс: " << student.course_number;
        if (student.ege_score > 0) {
            cout << " | ЕГЭ: " << student.ege_score;
        }
        cout << endl;
    }
}

void adminManageUsers() {
    cout << endl << "Управление всеми пользователями" << endl;
    DatabaseManager db;
    auto users = db.getAllUsers();
    
    for (const auto& user : users) {
        cout << "ID: " << user.user_id << " | " << user.username << " | " 
             << user.role << " | " << user.full_name;
        if (user.student_id > 0) {
            cout << " | Student ID: " << user.student_id;
        }
        cout << " | " << (user.is_active ? "Активен" : "Неактивен") << endl;
    }
}

void demonstrateScholarshipCalculation() {
    cout << endl << "Расчёт стипендии" << endl;
    
    ScholarshipCalculator calculator;
    auto results = calculator.calculateForSession(1);
    
    double total_amount = 0;
    int approved_count = 0;
    
    for (const auto& result : results) {
        total_amount += result.amount;
        if (result.status == "approved") {
            approved_count++;
        }
        
        cout << " Студент ID: " << result.student_id << endl;
        cout << " Тип стипендии: " << result.scholarship_type << endl;
        cout << " Правило: " << result.rule_name << endl;
        cout << " Сумма: " << result.amount << " руб." << endl;
        cout << " Статус: " << result.status << endl;
        cout << " Примечание: " << result.message << endl;
        cout << endl;
    }
    
    cout << "ИТОГО: " << approved_count << " студентов получают стипендию" << endl;
    cout << "ОБЩАЯ СУММА: " << total_amount << " руб." << endl;
}

// Функции для Преподавателя
void teacherViewStudents() {
    cout << endl << "Список студентов" << endl;
    DatabaseManager db;
    auto students = db.getStudents();
    
    for (const auto& student : students) {
        cout << student.full_name << " | Группа: " << student.student_group 
             << " | Курс: " << student.course_number << endl;
    }
}

// Функции для Студента
void studentViewMyData() {
    cout << endl << "Мои данные" << endl;
    if (current_user.student_id > 0) {
        DatabaseManager db;
        Student student = db.getStudent(current_user.student_id);
        
        cout << "ФИО: " << student.full_name << endl;
        cout << "Группа: " << student.student_group << endl;
        cout << "Курс: " << student.course_number << endl;
        cout << "Форма обучения: " << student.education_type << endl;
        if (student.ege_score > 0) {
            cout << "Баллы ЕГЭ: " << student.ege_score << endl;
        }
        if (!student.social_category.empty()) {
            cout << "Соц. категория: " << student.social_category << endl;
        }
    } else {
        cout << "Нет привязанного студента" << endl;
    }
}

void studentViewMyGrades() {
    cout << endl << "Мои оценки" << endl;
    if (current_user.student_id > 0) {
        DatabaseManager db;
        auto grades = db.getStudentGrades(current_user.student_id, 1);
        
        if (grades.empty()) {
            cout << "Нет оценок для отображения" << endl;
            return;
        }
        
        double sum = 0;
        int count = 0;
        
        for (const auto& grade : grades) {
            cout << " " << grade.grade_value << " - Предмет " << grade.subject_id;
            if (!grade.teacher_name.empty()) {
                cout << " (" << grade.teacher_name << ")";
            }
            cout << endl;
            
            // Расчет среднего балла
            if (grade.grade_value == "5" || grade.grade_value == "зачет") {
                sum += 5.0;
                count++;
            } else if (grade.grade_value == "4") {
                sum += 4.0;
                count++;
            } else if (grade.grade_value == "3") {
                sum += 3.0;
                count++;
            }
        }
        
        if (count > 0) {
            cout << endl << "Средний балл: " << (sum / count) << endl;
        }
    } else {
        cout << "Нет привязанного студента" << endl;
    }
}

void studentViewMyScholarship() {
    cout << endl << "Моя стипендия" << endl;
    if (current_user.student_id > 0) {
        ScholarshipCalculator calculator;
        auto result = calculator.calculateForStudent(current_user.student_id, 1);
        
        cout << "Тип: " << result.scholarship_type << endl;
        cout << "Сумма: " << result.amount << " руб." << endl;
        cout << "Статус: " << result.status << endl;
        cout << "Примечание: " << result.message << endl;
        if (!result.rule_name.empty() && result.rule_name != "none") {
            cout << "Правило: " << result.rule_name << endl;
        }
    } else {
        cout << "Нет привязанного студента" << endl;
    }
}

// Основные панели
void runAdminPanel() {
    int choice;
    do {
        showAdminMenu();
        cout << "Выберите действие: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                adminViewAllStudents();
                break;
            case 2:
                demonstrateScholarshipCalculation();
                break;
            case 3:
                adminManageUsers();
                break;
            case 4:
                cout << "Статистика (в разработке)" << endl;
                break;
            case 5:
                cout << "Выход из системы..." << endl;
                break;
            default:
                cout << "Неверный выбор!" << endl;
        }
    } while (choice != 5);
}

void runTeacherPanel() {
    int choice;
    do {
        showTeacherMenu();
        cout << "Выберите действие: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                teacherViewStudents();
                break;
            case 2:
                cout << "Ввод оценок (в разработке)" << endl;
                break;
            case 3:
                demonstrateScholarshipCalculation();
                break;
            case 4:
                cout << "Выход из системы..." << endl;
                break;
            default:
                cout << "Неверный выбор!" << endl;
        }
    } while (choice != 4);
}

void runStudentPanel() {
    int choice;
    do {
        showStudentMenu();
        cout << "Выберите действие: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                studentViewMyData();
                break;
            case 2:
                studentViewMyGrades();
                break;
            case 3:
                studentViewMyScholarship();
                break;
            case 4:
                cout << "Выход из системы..." << endl;
                break;
            default:
                cout << "Неверный выбор!" << endl;
        }
    } while (choice != 4);
}

int main() {
    cout << "Academic Grant" << endl;
    cout << endl;
    
    // Цикл аутентификации
    while (true) {
        showLoginMenu();
        if (login()) {
            break;
        }
        cout << endl << "Попробуйте снова..." << endl;
    }
    
    // Запуск соответствующей панели
    cout << endl << endl;
    if (current_user.role == "admin") {
        runAdminPanel();
    } else if (current_user.role == "teacher") {
        runTeacherPanel();
    } else if (current_user.role == "student") {
        runStudentPanel();
    }
    
    cout << endl << "До свидания, " << current_user.full_name << "!" << endl;
    return 0;
}