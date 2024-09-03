project(Toolkit)

add_library(${PROJECT_NAME})

find_package(raylib CONFIG REQUIRED)

target_sources(${PROJECT_NAME}
	PRIVATE
		src/dialogbox.cpp
	PUBLIC
		FILE_SET headers TYPE HEADERS
		BASE_DIRS include
		FILES 
			include/dialogbox.hpp
)

target_link_libraries(${PROJECT_NAME} raylib)
