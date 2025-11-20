\c academic_grant_db;

-- Обновляем education_level для существующих записей
UPDATE students SET education_level = 'bachelor' WHERE education_level = '';

-- Период семестров 
INSERT INTO academic_semesters (semester_name, semester_year, start_date, end_date, is_current) VALUES
('Осенний семестр 2024', 2024, '2024-09-01', '2025-01-31', true),
('Весенний семестр 2025', 2025, '2025-02-08', '2025-05-31', false);

-- Дисциплины осеннего семестра
INSERT INTO academic_subjects (subject_name, semester_id, credits, is_required) VALUES
('Электротехника', 1, 5, true),
('Программирование', 1, 4, true),
('Основы информационной безопасности', 1, 4, true),
('Иностранный язык', 1, 3, true),
('Физическая культура', 1, 2, false);

-- Период сессий
INSERT INTO exam_sessions (session_name, semester_id, session_type, start_date, end_date, is_completed) VALUES
('Зимняя сессия 2024-2025', 1, 'winter', '2024-12-09', '2025-01-25', true);

-- Студенты
INSERT INTO students (full_name, student_group, course_number, education_type, education_level, social_category, ege_score, has_olympiad, is_foreign, has_disability_hearing, has_disability_vision, is_need_based, regional_coefficient) VALUES
('Иванов Иван Иванович', 'БИ-201', 1, 'budget', 'bachelor', '', 270, false, false, false, false, false, true),
('Петрова Мария Сергеевна', 'БИ-201', 1, 'budget', 'bachelor', 'сирота', 260, false, false, false, false, true, false),
('Сидоров Алексей Петрович', 'БИ-201', 1, 'budget', 'bachelor', '', 240, false, false, false, false, false, true),
('Козлова Анна Дмитриевна', 'БИ-301', 3, 'budget', 'bachelor', '', 0, false, false, false, false, false, false),
('Николаев Денис Игоревич', 'МА-101', 1, 'budget', 'master', '', 0, false, false, false, false, false, true),
('Федорова Елена Викторовна', 'БИ-201', 1, 'budget', 'bachelor', '', 255, false, false, true, false, false, false);

-- Оценки за зимнюю сессию
INSERT INTO student_grades (student_id, subject_id, session_id, grade_value, exam_date, teacher_name) VALUES
-- Отличник бакалавриат
(1, 1, 1, '5', '2024-12-15', 'Доцент Иванов'),
(1, 2, 1, '5', '2024-12-18', 'Доцент Петрова'),
(1, 3, 1, '5', '2024-12-22', 'Старший преподаватель Сидоров'),
(1, 4, 1, '5', '2025-01-10', 'Доцент Козлова'),
(1, 5, 1, 'зачет', '2025-01-15', 'Старший преподаватель Федоров'),

-- Хорошист с социальной категорией
(2, 1, 1, '4', '2024-12-15', 'Доцент Иванов'),
(2, 2, 1, '5', '2024-12-18', 'Доцент Петрова'),
(2, 3, 1, '4', '2024-12-22', 'Старший преподаватель Сидоров'),
(2, 4, 1, '5', '2025-01-10', 'Доцент Козлова'),
(2, 5, 1, 'зачет', '2025-01-15', 'Старший преподаватель Федоров'),

-- С троиками
(3, 1, 1, '3', '2024-12-15', 'Доцент Иванов'),
(3, 2, 1, '4', '2024-12-18', 'Доцент Петрова'),
(3, 3, 1, '3', '2024-12-22', 'Старший преподаватель Сидоров'),
(3, 4, 1, '4', '2025-01-10', 'Доцент Козлова'),
(3, 5, 1, 'зачет', '2025-01-15', 'Старший преподаватель Федоров'),

-- Отличник магистратура
(5, 1, 1, '5', '2024-12-15', 'Доцент Иванов'),
(5, 2, 1, '5', '2024-12-18', 'Доцент Петрова'),
(5, 3, 1, '5', '2024-12-22', 'Старший преподаватель Сидоров'),
(5, 4, 1, '5', '2025-01-10', 'Доцент Козлова'),
(5, 5, 1, 'зачет', '2025-01-15', 'Старший преподаватель Федоров'),

-- Хорошист с инвалидностью по слуху
(6, 1, 1, '4', '2024-12-15', 'Доцент Иванов'),
(6, 2, 1, '4', '2024-12-18', 'Доцент Петрова'),
(6, 3, 1, '4', '2024-12-22', 'Старший преподаватель Сидоров');

-- Правила стипендий (существующие правила)
INSERT INTO scholarship_rules (rule_name, scholarship_type, education_level, min_average_grade, min_ege_score, max_ege_score, required_grade, social_requirement, requires_olympiad, requires_foreign, requires_disability, requires_need_based, is_first_course, amount_base, amount_regional, priority_level, description) VALUES
('Бак_1курс_базовая', 'академическая', 'bachelor', NULL, NULL, NULL, NULL, false, false, false, false, false, true, 4712, 5654, 1, 'Первый курс (первый семестр)'),
('Бак_хорошо', 'академическая', 'bachelor', 4.0, NULL, NULL, '4', false, false, false, false, false, false, 4712, 5654, 2, 'Учащимся на "хорошо"'),
('Бак_отл_хор', 'академическая', 'bachelor', 4.5, NULL, NULL, NULL, false, false, false, false, false, false, 5397, 6476, 3, 'Учащимся на "отлично" и "хорошо"'),
('Бак_отлично', 'академическая', 'bachelor', 4.75, NULL, NULL, '5', false, false, false, false, false, false, 5842, 7010, 4, 'Учащимся на "отлично"'),
('Бак_ЕГЭ_255', 'академическая', 'bachelor', NULL, 0, 254, NULL, false, false, false, false, false, true, 4712, 5654, 5, 'ЕГЭ < 255 баллов'),
('Бак_ЕГЭ_255_275', 'академическая', 'bachelor', NULL, 255, 275, NULL, false, false, false, false, false, true, 10000, 10000, 6, 'ЕГЭ 255-275 баллов'),
('Бак_ЕГЭ_276_300', 'академическая', 'bachelor', NULL, 276, 300, NULL, false, false, false, false, false, true, 12500, 12500, 7, 'ЕГЭ 276-300 баллов'),
('Бак_олимпиада', 'академическая', 'bachelor', NULL, NULL, NULL, NULL, false, true, false, false, false, true, 22500, 22500, 8, 'Победители олимпиад'),
('Маг_1курс', 'академическая', 'master', NULL, NULL, NULL, NULL, false, false, false, false, false, true, 5842, 7010, 9, 'Магистратура 1 курс'),
('Маг_хорошо', 'академическая', 'master', 4.0, NULL, NULL, '4', false, false, false, false, false, false, 5842, 7010, 10, 'Магистратура на "хорошо"'),
('Маг_отл_хор', 'академическая', 'master', 4.5, NULL, NULL, NULL, false, false, false, false, false, false, 6677, 8012, 11, 'Магистратура на "отлично" и "хорошо"'),
('Маг_отлично', 'академическая', 'master', 4.75, NULL, NULL, '5', false, false, false, false, false, false, 6982, 8378, 12, 'Магистратура на "отлично"'),
('Соц_высшее', 'социальная', NULL, NULL, NULL, NULL, NULL, true, false, false, false, false, false, 7061, 8473, 19, 'Социальная стипендия высшее образование'),
('Соц_повыш_1_2курс', 'социальная', NULL, NULL, NULL, NULL, NULL, true, false, false, false, true, false, 15473, 15473, 21, 'Социальная повышенная для нуждающихся 1-2 курс');

-- Пользователи
INSERT INTO users (username, password_hash, role, student_id, full_name, email, is_active) VALUES
('admin', 'admin123', 'admin', NULL, 'Администратор Системы', 'admin@university.ru', true),
('teacher', 'teacher123', 'teacher', NULL, 'Преподаватель Иванов', 'teacher@university.ru', true),
('student1', 'student123', 'student', 1, 'Иванов Иван Иванович', 'student1@university.ru', true),
('student2', 'student123', 'student', 2, 'Петрова Мария Сергеевна', 'student2@university.ru', true),
('student3', 'student123', 'student', 3, 'Сидоров Алексей Петрович', 'student3@university.ru', true);