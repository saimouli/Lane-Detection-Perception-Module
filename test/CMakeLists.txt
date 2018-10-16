set(GTEST_SHUFFLE 1)

add_executable(
    cpp-test
    main.cpp
    VisionModuleTest.cpp
    FrameParserTest.cpp
    UserInterfaceTest.cpp
    ../app/VisionModule.cpp
    ../app/FrameParser.cpp
    ../app/UserInterface.cpp
)

target_include_directories(cpp-test PUBLIC ../vendor/googletest/googletest/include ../vendor/googletest/googlemock/include
                                           ${CMAKE_SOURCE_DIR}/include ${OpenCV_INCLUDE_DIRS})
target_link_libraries(cpp-test PUBLIC gtest ${OpenCV_LIBS})
