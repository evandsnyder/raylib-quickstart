set(LESSONS
HelloWorld
Variables
)

foreach(LESSON ${LESSONS})
	add_subdirectory(${LESSON})
endforeach()