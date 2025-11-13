cmake_minimum_required(VERSION 3.10)
project(VersionControlSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем все предупреждения
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

# Исходные файлы
set(SOURCES
    src/main.cpp
    src/storage.cpp
    src/object.cpp
    src/index.cpp
)

# Исполняемый файл
add_executable(myvcs ${SOURCES})

# Подключаем заголовочные файлы
target_include_directories(myvcs PRIVATE include)

# Добавляем тест производительности
add_executable(performance_test tests/performance_test.cpp src/storage.cpp src/object.cpp src/index.cpp)
target_include_directories(performance_test PRIVATE include)