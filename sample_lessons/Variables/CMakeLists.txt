project("GDP_Variables")
cmake_minimum_required (VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

find_package(raylib)

set(game_name LearningVariables)

add_executable(${game_name}
	"main.cpp"
)

target_link_libraries(${game_name}
	raylib
	Toolkit
)