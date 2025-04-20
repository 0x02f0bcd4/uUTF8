set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
cmake_minimum_required(VERSION 3.00)
project("uUTF8"  LANGUAGES "C" VERSION 0.0.0)
include(CTest)
add_library("uUTF8" SHARED "src/uUTF8_FI.c" "src/uUTF8.c")
target_include_directories("uUTF8" PUBLIC "include")

if(TESTING)
add_executable("uUTF8_Test" "tests/main.c" "src/uUTF8.c" "src/uUTF8_FI.c")
target_include_directories("uUTF8_Test" PUBLIC "include")
target_include_directories("uUTF8_Test" PUBLIC "tests")
add_test(NAME "uUTF8_Test" COMMAND "uUTF8_Test")


add_executable("uUTF8_DecodingTest" "tests/test_decoding.c" "tests/test-main.c" "src/uUTF8.c" "src/uUTF8_FI.c")
target_include_directories("uUTF8_DecodingTest" PUBLIC "include")
target_include_directories("uUTF8_DecodingTest" PUBLIC "tests")
add_test(NAME "uUTF8_DecodingTest" COMMAND "uUTF8_DecodingTest")

add_executable("uUTF8_FindSubstringTest" "tests/test_findSubstring.c" "tests/test-main.c" "src/uUTF8.c" "src/uUTF8_FI.c")
target_include_directories("uUTF8_FindSubstringTest" PUBLIC "include")
target_include_directories("uUTF8_FindSubstringTest" PUBLIC "tests")
add_test(NAME "uUTF8_FindSubstringTest" COMMAND "uUTF8_FindSubstringTest")


add_custom_command(TARGET "uUTF8" POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/tests/test-file.txt" "${CMAKE_CURRENT_BINARY_DIR}/test-file.txt")
add_custom_command(TARGET "uUTF8" POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/tests/test-pat.txt" "${CMAKE_CURRENT_BINARY_DIR}/test-pat.txt")

add_custom_command(TARGET "uUTF8" POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/tests/test-src.txt" "${CMAKE_CURRENT_BINARY_DIR}/test-src.txt")

endif()
