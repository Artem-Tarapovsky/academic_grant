\c academic_grant_db;

-- Период семестров 
INSERT INTO academic_semesters (semester_name, semester_year, start_date, end_date, is_current) VALUES
('Осенний семестр 2024', 2024, '2024-09-01', '2025-01-31', true),
('Весенний семестр 2025', 2025, '2025-02-08', '2025-05-31', false);

-- Студенты разных категорий
INSERT INTO students (full_name, student_group, course_number, education_type, education_level, social_category, ege_score, has_olympiad, is_foreign, has_disability_hearing, has_disability_vision, is_need_based, regional_coefficient) VALUES
-- Бакалавриат - разные случаи
('Иванов Алексей Сергеевич', 'БС-201', 1, 'budget', 'bachelor', NULL, 250, false, false, false, false, false, false),
('Петрова Мария Дмитриевна', 'БС-201', 1, 'budget', 'bachelor', 'сирота', 280, true, false, false, false, true, true),
('Сидоров Денис Игоревич', 'БС-201', 2, 'budget', 'bachelor', NULL, NULL, false, false, false, false, false, true),
('Козлова Анна Викторовна', 'БС-201', 2, 'contract', 'bachelor', NULL, NULL, false, false, false, false, false, false),

-- Магистратура
('Смирнов Владислав Андреевич', 'МГ-101', 1, 'budget', 'master', NULL, NULL, false, false, false, false, false, false),
('Федорова Екатерина Максимовна', 'МГ-101', 2, 'budget', 'master', 'инвалидность', NULL, false, false, true, false, false, true),

-- Аспирантура
('Николаев Артем Олегович', 'АС-301', 1, 'budget', 'postgraduate', NULL, NULL, false, false, false, false, false, true),
('Орлова Дарья Сергеевна', 'АС-301', 2, 'budget', 'postgraduate', NULL, NULL, false, false, false, false, false, false),

-- СПО
('Васильев Игорь Петрович', 'ТП-401', 1, 'budget', 'secondary', NULL, NULL, false, false, false, false, false, true),
('Григорьева Светлана Игоревна', 'ТП-401', 2, 'budget', 'secondary', 'сирота', NULL, false, false, false, false, true, false),

-- Иностранные студенты
('John Smith', 'ИС-501', 2, 'budget', 'bachelor', NULL, NULL, false, true, false, false, false, false),
('Chen Wei', 'ИС-501', 1, 'budget', 'postgraduate', NULL, NULL, false, true, false, false, false, true);

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

-- Оценки за зимнюю сессию (разные сценарии успеваемости)
INSERT INTO student_grades (student_id, subject_id, session_id, grade_value, exam_date, teacher_name) VALUES
-- Отличник бакалавриат
(1, 1, 1, '5', '2024-12-15', 'Доцент Иванов'),
(1, 2, 1, '5', '2024-12-18', 'Доцент Петрова'),
(1, 3, 1, '5', '2024-12-22', 'Старший преподаватель Сидоров'),

-- Хорошист с социальной категорией
(2, 1, 1, '4', '2024-12-15', 'Доцент Иванов'),
(2, 2, 1, '5', '2024-12-18', 'Доцент Петрова'),
(2, 3, 1, '4', '2024-12-22', 'Старший преподаватель Сидоров'),

-- С троиками
(3, 1, 1, '3', '2024-12-15', 'Доцент Иванов'),
(3, 2, 1, '4', '2024-12-18', 'Доцент Петрова'),
(3, 3, 1, '3', '2024-12-22', 'Старший преподаватель Сидоров'),

-- Отличник магистратура
(5, 1, 1, '5', '2024-12-15', 'Доцент Иванов'),
(5, 2, 1, '5', '2024-12-18', 'Доцент Петрова'),
(5, 3, 1, '5', '2024-12-22', 'Старший преподаватель Сидоров'),

-- Хорошист с инвалидностью по слуху
(6, 1, 1, '4', '2024-12-15', 'Доцент Иванов'),
(6, 2, 1, '4', '2024-12-18', 'Доцент Петрова'),
(6, 3, 1, '5', '2024-12-22', 'Старший преподаватель Сидоров'),

-- Отличник СПО
(9, 1, 1, '5', '2024-12-15', 'Доцент Иванов'),
(9, 2, 1, '5', '2024-12-18', 'Доцент Петрова'),
(9, 3, 1, '5', '2024-12-22', 'Старший преподаватель Сидоров'),

-- Иностранный студент
(11, 1, 1, '4', '2024-12-15', 'Доцент Иванов'),
(11, 2, 1, '3', '2024-12-18', 'Доцент Петрова'),
(11, 3, 1, '4', '2024-12-22', 'Старший преподаватель Сидоров');

-- Правила стипендий (полный перечень по новым требованиям)
INSERT INTO scholarship_rules (rule_name, scholarship_type, education_level, min_average_grade, min_ege_score, max_ege_score, required_grade, social_requirement, requires_olympiad, requires_foreign, requires_disability, requires_need_based, is_first_course, amount_base, amount_regional, priority_level, description) VALUES
-- БАКАЛАВРИАТ/СПЕЦИАЛИТЕТ - Государственная академическая
('Бак_1курс_базовая', 'академическая', 'bachelor', NULL, NULL, NULL, NULL, false, false, false, false, false, true, 4712, 5654, 1, 'Первый курс (первый семестр)'),
('Бак_хорошо', 'академическая', 'bachelor', 4.0, NULL, NULL, '4', false, false, false, false, false, false, 4712, 5654, 2, 'Учащимся на "хорошо"'),
('Бак_отл_хор', 'академическая', 'bachelor', 4.5, NULL, NULL, NULL, false, false, false, false, false, false, 5397, 6476, 3, 'Учащимся на "отлично" и "хорошо"'),
('Бак_отлично', 'академическая', 'bachelor', 4.75, NULL, NULL, '5', false, false, false, false, false, false, 5842, 7010, 4, 'Учащимся на "отлично"'),

-- Повышенная для первокурсников по ЕГЭ
('Бак_ЕГЭ_255', 'академическая', 'bachelor', NULL, 0, 254, NULL, false, false, false, false, false, true, 4712, 5654, 5, 'ЕГЭ < 255 баллов'),
('Бак_ЕГЭ_255_275', 'академическая', 'bachelor', NULL, 255, 275, NULL, false, false, false, false, false, true, 10000, 10000, 6, 'ЕГЭ 255-275 баллов'),
('Бак_ЕГЭ_276_300', 'академическая', 'bachelor', NULL, 276, 300, NULL, false, false, false, false, false, true, 12500, 12500, 7, 'ЕГЭ 276-300 баллов'),
('Бак_олимпиада', 'академическая', 'bachelor', NULL, NULL, NULL, NULL, false, true, false, false, false, true, 22500, 22500, 8, 'Победители олимпиад'),

-- МАГИСТРАТУРА
('Маг_1курс', 'академическая', 'master', NULL, NULL, NULL, NULL, false, false, false, false, false, true, 5842, 7010, 9, 'Магистратура 1 курс'),
('Маг_хорошо', 'академическая', 'master', 4.0, NULL, NULL, '4', false, false, false, false, false, false, 5842, 7010, 10, 'Магистратура на "хорошо"'),
('Маг_отл_хор', 'академическая', 'master', 4.5, NULL, NULL, NULL, false, false, false, false, false, false, 6677, 8012, 11, 'Магистратура на "отлично" и "хорошо"'),
('Маг_отлично', 'академическая', 'master', 4.75, NULL, NULL, '5', false, false, false, false, false, false, 6982, 8378, 12, 'Магистратура на "отлично"'),

-- АСПИРАНТУРА
('Асп_гуманитар', 'академическая', 'postgraduate', NULL, NULL, NULL, NULL, false, false, false, false, false, false, 11979, 14375, 13, 'Аспирантура гуманитарная'),
('Асп_техническая', 'академическая', 'postgraduate', NULL, NULL, NULL, NULL, false, false, false, false, false, false, 16503, 19804, 14, 'Аспирантура техническая'),

-- СПО
('СПО_1курс', 'академическая', 'secondary', NULL, NULL, NULL, NULL, false, false, false, false, false, true, 1457, 1748, 15, 'СПО 1 курс'),
('СПО_хорошо', 'академическая', 'secondary', 4.0, NULL, NULL, '4', false, false, false, false, false, false, 1457, 1748, 16, 'СПО на "хорошо"'),
('СПО_отл_хор', 'академическая', 'secondary', 4.5, NULL, NULL, NULL, false, false, false, false, false, false, 1652, 1982, 17, 'СПО на "отлично" и "хорошо"'),
('СПО_отлично', 'академическая', 'secondary', 4.75, NULL, NULL, '5', false, false, false, false, false, false, 1792, 2150, 18, 'СПО на "отлично"'),

-- СОЦИАЛЬНЫЕ СТИПЕНДИИ
('Соц_высшее', 'социальная', NULL, NULL, NULL, NULL, NULL, true, false, false, false, false, false, 7061, 8473, 19, 'Социальная стипендия высшее образование'),
('Соц_СПО', 'социальная', 'secondary', NULL, NULL, NULL, NULL, true, false, false, false, false, false, 2171, 2605, 20, 'Социальная стипендия СПО'),
('Соц_повыш_1_2курс', 'социальная', NULL, NULL, NULL, NULL, NULL, true, false, false, false, true, false, 15473, 15473, 21, 'Социальная повышенная для нуждающихся 1-2 курс'),

-- ИНОСТРАННЫЕ СТУДЕНТЫ
('Иностр_высшее', 'иностранная', NULL, NULL, NULL, NULL, NULL, false, false, true, false, false, false, 2224, 2669, 22, 'Иностранные студенты высшее образование'),
('Иностр_асп_гуманитар', 'иностранная', 'postgraduate', NULL, NULL, NULL, NULL, false, false, true, false, false, false, 4380, 5256, 23, 'Иностранные аспиранты гуманитарные'),
('Иностр_асп_технич', 'иностранная', 'postgraduate', NULL, NULL, NULL, NULL, false, false, true, false, false, false, 10513, 12616, 24, 'Иностранные аспиранты технические');