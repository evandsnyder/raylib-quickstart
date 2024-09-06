project(Toolkit)

add_library(${PROJECT_NAME})

find_package(raylib CONFIG REQUIRED)
find_package(tmx REQUIRED)
find_package(fmt)

target_sources(${PROJECT_NAME}
	PUBLIC
		FILE_SET headers TYPE HEADERS
		BASE_DIRS include
		FILES 
			include/DialogBox.hpp
			include/GameConfiguration.hpp
			include/Menu.hpp
	PRIVATE
		"src/DialogBox.cpp"
		"src/GameConfiguration.cpp"
		"src/Menu.cpp"
		"src/BoxAttributes.cpp"
		"src/MenuOption.cpp"
		"src/Level.cpp"
 "src/TiledMap.cpp" "src/MapExceptions.cpp")

target_link_libraries(${PROJECT_NAME} 
	raylib
	fmt::fmt
)
