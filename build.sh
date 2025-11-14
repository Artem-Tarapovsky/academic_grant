set -e 

if [ ! -f "CMakeLists.txt" ]; then
    echo "Ошибка: Запустите скрипт из корневой папки проекта (где находится CMakeLists.txt)"
    exit 1
fi

if [ ! -d "build" ]; then
    echo "Создаем папку build..."
    mkdir build
fi

cd build

echo "Запускаем CMake..."
cmake ..

echo "Компилируем проект..."
make

echo "=== Сборка завершена успешно! ==="
echo "Для запуска программы выполните: ./academic_grant_backend"