#include "core/AuthManager.h"
#include "database/DataBaseManager.h"
#include <random>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <openssl/sha.h>

using namespace std;

class PasswordHasher {
public:
    static string hashPassword(const string& password) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, password.c_str(), password.length());
        SHA256_Final(hash, &sha256);
        
        stringstream ss;
        for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            ss << hex << setw(2) << setfill('0') << (int)hash[i];
        }
        
        return ss.str();
    }
    
    static bool verifyPassword(const string& password, const string& stored_hash) {
        string computed_hash = hashPassword(password);
        return computed_hash == stored_hash;
    }
};

AuthManager::AuthManager() {}

AuthResponse AuthManager::login(const string& username, const string& password) {
    AuthResponse response;
    DatabaseManager db;
    
    // Получаем пользователя из базы данных
    User db_user = db.getUserByUsername(username);
    
    if (db_user.user_id == 0) {
        // Пользователь не найден
        response.success = false;
        response.message = "Пользователь не найден";
        cout << "Ошибка входа: " << response.message << endl;
        return response;
    }
    
    if (!db_user.is_active) {
        // Пользователь неактивен
        response.success = false;
        response.message = "Учетная запись заблокирована";
        cout << "Ошибка входа: " << response.message << endl;
        return response;
    }
    
    // Проверяем пароль с хешированием
    if (PasswordHasher::verifyPassword(password, db_user.password_hash)) {
        // Пароль верный
        response.success = true;
        response.message = "Успешный вход";
        response.token = generateToken();
        response.user = db_user;
        
        // Сохраняем сессию
        active_sessions[response.token] = db_user;
        
        cout << "Успешный вход: " << db_user.full_name << " (" << db_user.role << ")" << endl;
        
        // Обновляем время последнего входа (в реальном приложении)
        
    } else {
        // Неверный пароль
        response.success = false;
        response.message = "Неверный пароль";
        cout << "Ошибка входа: " << response.message << endl;
        
    }
    
    return response;
}

bool AuthManager::logout(const string& token) {
    auto it = active_sessions.find(token);
    if (it != active_sessions.end()) {
        active_sessions.erase(it);
        cout << "Сессия завершена" << endl;
        return true;
    }
    cout << "Сессия не найдена" << endl;
    return false;
}

bool AuthManager::validateToken(const string& token) {
    if (token.empty()) {
        return false;
    }
    
    auto it = active_sessions.find(token);
    if (it != active_sessions.end()) {
        return true;
    }
    
    return false;
}

User AuthManager::getUserByToken(const string& token) {
    if (!validateToken(token)) {
        User empty_user;
        empty_user.user_id = 0;
        empty_user.is_active = false;
        return empty_user;
    }
    
    return active_sessions[token];
}

bool AuthManager::hasPermission(const string& token, const string& required_role) {
    if (!validateToken(token)) {
        cout << "Доступ запрещен: недействительный токен" << endl;
        return false;
    }
    
    User user = getUserByToken(token);
    
    if (!user.is_active) {
        cout << "Доступ запрещен: учетная запись заблокирована" << endl;
        return false;
    }
    
    // Администратор имеет все права
    if (user.role == "admin") {
        return true;
    }
    
    // Проверяем конкретную роль
    if (required_role == "teacher" && user.role == "teacher") {
        return true;
    }
    
    if (required_role == "student" && user.role == "student") {
        return true;
    }
    
    cout << "Недостаточно прав. Требуется роль: " << required_role << ", текущая роль: " << user.role << endl;
    return false;
}

bool AuthManager::isAdmin(const string& token) {
    return hasPermission(token, "admin");
}

bool AuthManager::isTeacher(const string& token) {
    return hasPermission(token, "teacher");
}

bool AuthManager::isStudent(const string& token) {
    return hasPermission(token, "student");
}

string AuthManager::generateToken() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 15);
    uniform_int_distribution<> char_dis(0, 25);
    
    stringstream ss;
    ss << hex;
    
    // Генерируем случайный токен
    for (int i = 0; i < 64; i++) {
        if (i % 2 == 0) {
            ss << dis(gen); // hex цифры
        } else {
            ss << (char)('a' + char_dis(gen)); // буквы
        }
    }
    
    // Добавляем временную метку
    ss << "_" << time(nullptr);
    
    return ss.str();
}

bool AuthManager::verifyPassword(const string& password, const string& hash) {
    return PasswordHasher::verifyPassword(password, hash);
}

// Дополнительные методы для управления сессиями
void AuthManager::cleanupExpiredSessions() {
    time_t now = time(nullptr);
    
    for (auto it = active_sessions.begin(); it != active_sessions.end(); ) {
        // Проверяем время создания токена (последняя часть после '_')
        size_t pos = it->first.find('_');
        if (pos != string::npos) {
            time_t created_time = stol(it->first.substr(pos + 1));
            if (now - created_time > 24 * 60 * 60) { // 24 часа
                it = active_sessions.erase(it);
                continue;
            }
        }
        ++it;
    }
}

size_t AuthManager::getActiveSessionsCount() const {
    return active_sessions.size();
}