CXX=clang++
CXX_FLAGS=-g -std=c++20
# CXX_FLAGS=-g -std=c++20 -gdwarf-4 -fstandalone-debug -Wall -Wextra -Werror -pedantic

main: main.cpp schedule.cpp schedule.h course.cpp course.h section.cpp section.h json_parser.cpp json_parser.h schedule_maker.cpp schedule_maker.h
	${CXX} ${CXX_FLAGS} -o build/main main.cpp -I src/ -I cget/include