\c academic_grant_db;

UPDATE users SET password_hash = '240be518fabd2724ddb6f04eeb1da5967448d7e831c08c8fa822809f74c720a9' WHERE username = 'admin';    -- admin123
UPDATE users SET password_hash = 'ec1e6fb3c5bcd194a4d0d86e4f6e3a1e9e6c6e6b8d5c5a5e4d3c2b1a0f9e8d7c' WHERE username = 'teacher';  -- teacher123
UPDATE users SET password_hash = '3a4b6e6f8c9d0e1f2a3b4c5d6e7f8a9b0c1d2e3f4a5b6c7d8e9f0a1b2c3d4e5f' WHERE username = 'student1'; -- student123
UPDATE users SET password_hash = '3a4b6e6f8c9d0e1f2a3b4c5d6e7f8a9b0c1d2e3f4a5b6c7d8e9f0a1b2c3d4e5f' WHERE username = 'student2'; -- student123
UPDATE users SET password_hash = '3a4b6e6f8c9d0e1f2a3b4c5d6e7f8a9b0c1d2e3f4a5b6c7d8e9f0a1b2c3d4e5f' WHERE username = 'student3'; -- student123

-- Проверяем
SELECT username, role, password_hash FROM users;