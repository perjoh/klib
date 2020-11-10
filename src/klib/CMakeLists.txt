find_package(Catch2 CONFIG REQUIRED)

set(IS_MSVC "$<CXX_COMPILER_ID:MSVC>")
set(IS_GCC "$<CXX_COMPILER_ID:GNU>")

function(enable_compile_options target)
    # Warning level (MSVC)
    #target_compile_options(${target} PUBLIC "$<${IS_MSVC}:/W4>")
    #target_compile_options(${target} PUBLIC "$<${IS_MSVC}:/bigobj>")

    # Optimizations GCC (Release)
    target_compile_options(${target} PUBLIC "$<$<AND:${IS_GCC},$<CONFIG:RELEASE>>:-O3>")
endfunction(enable_compile_options)

# Library
add_library(${PROJECT_NAME} STATIC file_io.cpp task_runner.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
enable_compile_options(${PROJECT_NAME})

# Test executable
add_executable(${PROJECT_NAME}test main.test.cpp fast_delegate.test.cpp)
target_link_libraries(${PROJECT_NAME}test ${PROJECT_NAME} Catch2::Catch2)
add_test(NAME ${PROJECT_NAME}test COMMAND ${PROJECT_NAME}test)
