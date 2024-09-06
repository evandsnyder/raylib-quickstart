# CMakeList.txt : CMake project for gdp_raylib_prototype, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("gdp_raylib_prototype")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

add_subdirectory(lib)

find_package(raylib 3.0 REQUIRED)
find_package(fmt)

add_executable(gdp_raylib_prototype "src/main.cpp")

target_link_libraries(${PROJECT_NAME} 
	raylib
	Toolkit
	fmt::fmt
)

if(APPLE)
	target_link_libraries(${PROJECT_NAME} "-framework IOKit")
	target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
	target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

# Must copy resources into build directory...
file(GLOB resources assets/*)
file(COPY ${resources} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)
