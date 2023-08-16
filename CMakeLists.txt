cmake_minimum_required(VERSION 3.7)
project(carry 
    VERSION 1.0.0
    LANGUAGES C
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fms-extensions -D_GNU_SOURCE=1")


configure_file(manifest.h.in manifest.h)
include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)


# Install
install(FILES carry.c DESTINATION "include")
install(FILES carry.h DESTINATION "include")


# CPack
set(CPACK_PACKAGE_FILE_NAME "libcarry-${PROJECT_VERSION}")
set(CPACK_SET_DESTDIR true)
set(CPACK_PACKAGE_NAME libcarry)
set(CPACK_PACKAGE_CONTACT "Vahid Mardani <vahid.mardani@gmail.com>")
set(CPACK_GENERATOR DEB)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libclog (>= 1.1)")
include(CPack)


# Testing
if (NOT DEFINED ENV{SKIP_TESTS})
include(CTest)
list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")

add_library(fcarry OBJECT fcarry.c fcarry.h) 
add_library(icarry OBJECT icarry.c icarry.h) 


# Valgrind, Profiling
add_custom_target(profile 
    DEPENDS 
    profile_test_carry
)

# Test carry
add_executable(test_carry 
    test_carry.c
    $<TARGET_OBJECTS:fcarry>
    $<TARGET_OBJECTS:icarry>
)
target_include_directories(test_carry PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(test_carry PUBLIC clog)
add_test(NAME test_carry COMMAND test_carry)
add_custom_target(profile_test_carry
    COMMAND "valgrind" 
    ${VALGRIND_FLAGS}
    $<TARGET_FILE:test_carry>
)
endif()
