cmake_minimum_required(VERSION 3.13)

project (shatter)

include_directories(src  test)

add_library(shatter-static STATIC src/shtr_buf.c)
set_target_properties(shatter-static
                      PROPERTIES OUTPUT_NAME shatter
                      CLEAN_DIRECT_OUTPUT 1)

add_library(shatter-shared SHARED src/shtr_buf.c)
set_target_properties(shatter-shared
                      PROPERTIES OUTPUT_NAME shatter
                      CLEAN_DIRECT_OUTPUT 1)

add_executable(test_shatter test/test_shatter.c)

target_link_libraries(test_shatter shatter-static)
