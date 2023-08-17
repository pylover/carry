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


# Tests
if (NOT DEFINED ENV{SKIP_TESTS})
    enable_testing()
    # list(APPEND CMAKE_CTEST_ARGUMENTS "--verbose")
    add_subdirectory(tests)
    list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")
endif()
