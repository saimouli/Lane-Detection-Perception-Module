add_executable(vision-app main.cpp)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries( vision-app ${OpenCV_LIBS} )
