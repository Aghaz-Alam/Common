cmake_minimum_required(VERSION 3.10)

project(CPP_Practice LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find all cpp files
file(GLOB CPP_FILES "${CMAKE_SOURCE_DIR}/*.cpp")

set(EXECUTABLES "")

foreach(CPP_FILE ${CPP_FILES})
    get_filename_component(EXE_NAME ${CPP_FILE} NAME_WE)
    add_executable(${EXE_NAME} ${CPP_FILE})
    list(APPEND EXECUTABLES ${EXE_NAME})
endforeach()

# -----------------------------
# Run all executables on `make`
# -----------------------------
add_custom_target(run_all ALL
    COMMENT "Running all C++ programs"
)

foreach(EXE ${EXECUTABLES})
    add_custom_command(
        TARGET run_all
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "--------------------------------------"
        COMMAND ${CMAKE_COMMAND} -E echo "Running ${EXE}"
        COMMAND ${CMAKE_COMMAND} -E echo "--------------------------------------"
        COMMAND $<TARGET_FILE:${EXE}>
    )
endforeach()

add_dependencies(run_all ${EXECUTABLES})

