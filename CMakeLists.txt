cmake_minimum_required(VERSION 3.10)

project(EvolutionMeetingPlugin)

# Устанавливаем переменную с версией Evolution
set(REQUIRED_EVOLUTION_VERSION "3.36.0")

# Устанавливаем компилятор
set(CMAKE_C_COMPILER gcc)

# Находим необходимые пакеты
find_package(PkgConfig REQUIRED)
pkg_check_modules(EVOLUTION REQUIRED evolution-data-server-${REQUIRED_EVOLUTION_VERSION} libebackend-${REQUIRED_EVOLUTION_VERSION} gtk+-3.0)

# Указываем пути к заголовочным файлам и библиотекам
include_directories(${EVOLUTION_INCLUDE_DIRS})
link_directories(${EVOLUTION_LIBRARY_DIRS})

# Добавляем флаги компиляции
add_definitions(${EVOLUTION_CFLAGS_OTHER})

# Добавляем исходный файл
add_library(e_meeting_plugin MODULE src/e-meeting-plugin.c)

# Линкуем наш плагин с библиотеками Evolution и GTK
target_link_libraries(e_meeting_plugin ${EVOLUTION_LIBRARIES})
