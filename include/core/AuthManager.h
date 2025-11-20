#pragma once
#include "database/Models.h"
#include <string>
#include <map>

using namespace std;

class AuthManager {
private:
    map<string, User> active_sessions; // token -> user
    
public:
    AuthManager();
    
    // Аутентификация
    AuthResponse login(const string& username, const string& password);
    bool logout(const string& token);
    
    // Валидация
    bool validateToken(const string& token);
    User getUserByToken(const string& token);
    
    // Проверка прав
    bool hasPermission(const string& token, const string& required_role);
    bool isAdmin(const string& token);
    bool isTeacher(const string& token);
    bool isStudent(const string& token);
    
private:
    string generateToken();
    bool verifyPassword(const string& password, const string& hash);
};