cmake_minimum_required(VERSION 3.16)
project(Academic_Grant)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Библиотеки
find_package(libpqxx REQUIRED)

#Пути
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/database
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core
)

#Исходные файлы
set(SOURCES
    src/main.cpp
    src/database/DatabaseManager.cpp
    src/database/Models.cpp
    src/core/ScholarshipCalculator.cpp
)

add_executable(academic_grant_backend ${SOURCES})

#Подключение библиотек
target_link_libraries(academic_grant_backend PRIVATE libpqxx)

target_compile_options(academic_grant_backend PRIVATE -O2 -Wall)