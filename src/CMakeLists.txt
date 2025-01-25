INCLUDE_DIRECTORIES("${PROJECT_INCLUDE_DIR}")

			
ADD_EXECUTABLE(blink_led_m2 blink_led_m2.cpp)


target_link_libraries(blink_led_m2 pigpiod_if2)
