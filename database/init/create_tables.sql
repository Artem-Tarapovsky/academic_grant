CREATE DATABASE academic_grant_db;

\c academic_grant_db;

CREATE TABLE students (
student_id SERIAL PRIMARY KEY,
full_name VARCHAR(255) NOT NULL,
student_group VARCHAR(50) NOT NULL,
course_number INTEGER NOT NULL CHECK (course_number BETWEEN 1 AND 6),
education_type VARCHAR(20) NOT NULL CHECK (education_type IN ('budget', 'contract')),
social_category VARCHAR(100),
created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE academic_semesters (
semester_id SERIAL PRIMARY KEY,
semester_name VARCHAR(100) NOT NULL,
semester_year INTEGER NOT NULL,
start_date DATE NOT NULL,
end_date DATE NOT NULL,
is_current BOOLEAN DEFAULT false
);

CREATE TABLE academic_subjects (
subject_id SERIAL PRIMARY KEY,
subject_name VARCHAR(255) NOT NULL,
semester_id INTEGER REFERENCES academic_semesters(semester_id),
credits INTEGER DEFAULT 3,
is_required BOOLEAN DEFAULT true
);

CREATE TABLE exam_sessions (
session_id SERIAL PRIMARY KEY,
session_name VARCHAR(100) NOT NULL,
semester_id INTEGER REFERENCES academic_semesters(semester_id),
session_type VARCHAR(20) CHECK (session_type IN ('winter', 'summer')),
start_date DATE NOT NULL,
end_date DATE NOT NULL,
is_completed BOOLEAN DEFAULT false
);

CREATE TABLE student_grades (
grade_id SERIAL PRIMARY KEY,
student_id INTEGER REFERENCES students(student_id),
subject_id INTEGER REFERENCES academic_subjects(subject_id),
session_id INTEGER REFERENCES exam_sessions(session_id),
grade_value VARCHAR(10) NOT NULL CHECK (grade_value IN ('5', '4', '3', '2', 'зачет', 'незачет')),
exam_date DATE NOT NULL,
teacher_name VARCHAR(255),
created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE scholarship_rules (
rule_id SERIAL PRIMARY KEY,
rule_name VARCHAR(255) NOT NULL,
scholarship_type VARCHAR(100) NOT NULL,
min_average_grade DECIMAL(3,2),
required_grade VARCHAR(10),
social_requirement BOOLEAN DEFAULT false,
amount_value DECIMAL(10,2) NOT NULL,
is_active BOOLEAN DEFAULT true,
priority_level INTEGER DEFAULT 0,
description TEXT
);

CREATE TABLE scholarship_payments (
payment_id SERIAL PRIMARY KEY,
student_id INTEGER REFERENCES students(student_id),
session_id INTEGER REFERENCES exam_sessions(session_id),
rule_id INTEGER REFERENCES scholarship_rules(rule_id),
scholarship_type VARCHAR(100) NOT NULL,
payment_amount DECIMAL(10,2) NOT NULL,
payment_month DATE NOT NULL,
payment_status VARCHAR(20) DEFAULT 'approved' CHECK (payment_status IN ('approved', 'rejected', 'pending')),
calculation_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
payment_date TIMESTAMP,
notes TEXT
);
