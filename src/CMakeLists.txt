include_directories("${PROJECT_INCLUDE_DIR}")

ADD_EXECUTABLE(main main.cpp tcp_client.cpp udp_multicast_client.cpp servo_fk.cpp coordinator.cpp)

# add_library(Servo servo.cpp)
# target_link_libraries(Servo pigpiod_if2)
			
# ADD_EXECUTABLE(blink_led_m2 blink_led_m2.cpp)
# target_link_libraries(blink_led_m2 pigpiod_if2)

# ADD_EXECUTABLE(move_servo move_servo.cpp)
# target_link_libraries(move_servo pigpiod_if2)


