# include_directories("${HEADERS_DIR}")

# RPI MAIN PROGRAM
# add_executable(rpi_main main.cpp tcp_client.cpp udp_multicast_client.cpp servo.cpp coordinator.cpp)
# target_link_libraries(rpi_main pigpiod_if2)

# APPLE SIMULATOR MAIN PROGRAM
add_executable(apple_fake_main main.cpp tcp_client.cpp udp_multicast_client.cpp servo_fk.cpp coordinator.cpp)
target_include_directories(apple_fake_main PRIVATE ${HEADERS_DIR})
target_link_libraries(apple_fake_main)

# add_library(Servo servo.cpp)
# target_link_libraries(Servo pigpiod_if2)

# ADD_EXECUTABLE(blink_led_m2 blink_led_m2.cpp)
# target_link_libraries(blink_led_m2 pigpiod_if2)

# ADD_EXECUTABLE(move_servo move_servo.cpp)
# target_link_libraries(move_servo pigpiod_if2)


