include_directories("${PROJECT_INCLUDE_DIR}")
	
add_executable(test_servo test_servo.cpp)
target_link_libraries(test_servo Servo)

# target_include_directories(test_servo PRIVATE ${CMAKE_SOURCE_DIR}/include)