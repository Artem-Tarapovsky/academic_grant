cmake_minimum_required(VERSION 3.16)
project(Academic_Grant)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск необходимых пакетов
find_package(OpenSSL REQUIRED)

# Ручное указание путей для Homebrew на Apple Silicon
set(LIBPQXX_INCLUDE_DIR "/opt/homebrew/include")
set(LIBPQXX_LIB_DIR "/opt/homebrew/lib")

# Пути для nlohmann/json (если установлен через Homebrew)
set(NLOHMANN_JSON_INCLUDE_DIR "/opt/homebrew/include")
set(NLOHMANN_JSON_LIB_DIR "/opt/homebrew/lib")

# Проверка наличия библиотек
if(NOT EXISTS "${LIBPQXX_INCLUDE_DIR}")
    message(WARNING "libpqxx not found in ${LIBPQXX_INCLUDE_DIR}")
    message(STATUS "Trying to find libpqxx via pkg-config...")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(LIBPQXX REQUIRED libpqxx)
endif()

# Явно указываем все нужные пути
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/database
    ${CMAKE_CURRENT_SOURCE_DIR}/include/core
    ${LIBPQXX_INCLUDE_DIR}
    ${NLOHMANN_JSON_INCLUDE_DIR}
)

# Исходные файлы
set(SOURCES
    src/main.cpp
    src/database/DataBaseManager.cpp
    src/database/Models.cpp
    src/core/ScholarshipCalculator.cpp
    src/core/AuthManager.cpp
)

# Создание исполняемого файла
add_executable(academic_grant_backend ${SOURCES})

# Подключаем библиотеки
target_link_directories(academic_grant_backend PRIVATE 
    ${LIBPQXX_LIB_DIR}
    ${NLOHMANN_JSON_LIB_DIR}
)

target_link_libraries(academic_grant_backend PRIVATE 
    pqxx
    OpenSSL::SSL
    OpenSSL::Crypto
)

# Опции компиляции
target_compile_options(academic_grant_backend PRIVATE 
    -O2 
    -Wall
    -Wextra
    -Wpedantic
)

# Настройки для отладки
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(academic_grant_backend PRIVATE 
        -g
        -DDEBUG
    )
endif()
