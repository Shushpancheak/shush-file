cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project (
  "shush-file"
  VERSION 1.0.0
  DESCRIPTION "A file manager for my projects."
)
set (
  SOURCES
  src/${PROJECT_NAME}.cpp
)
set (
  PUBLIC_HEADERS
  include/${PROJECT_NAME}.hpp
)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# - - - - - - - - - - - - LIBRARY INITIALIZATION- - - - - - - - - - - - - - - -
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set (
  LIBRARY_NAME
  ${PROJECT_NAME}
)
set (
  LIBRARY_TYPE STATIC
  CACHE STRING "Type of library to build. STATIC or SHARED."
)

add_library (
  ${LIBRARY_NAME} ${LIBRARY_TYPE}
  ${SOURCES}
)
set_target_properties (
  ${LIBRARY_NAME} PROPERTIES
  VERSION         ${PROJECT_VERSION}
  PUBLIC_HEADER   ${PUBLIC_HEADERS}
)
target_include_directories(${LIBRARY_NAME} PUBLIC  include)
target_include_directories(${LIBRARY_NAME} PRIVATE src)

include(GNUInstallDirs)
install (
  TARGETS                   ${LIBRARY_NAME}
  LIBRARY       DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

configure_file(${LIBRARY_NAME}.pc.in ${LIBRARY_NAME}.pc @ONLY)
install (
  FILES       ${CMAKE_BINARY_DIR}/${LIBRARY_NAME}.pc
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)

set(BUILD_TESTS OFF CACHE BOOL "Build tests")
if (BUILD_TESTS)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# - - - - - - - - - - - - - GTEST INITIALIZATION- - - - - - - - - - - - - - - -
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_subdirectory(googletest)
enable_testing()
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
include_directories(${gtest_SOURCE_DIR})

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# - - - - - - - - - - - - - - - - - TESTS - - - - - - - - - - - - - - - - - - -
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set(UNIT_TESTS_NAME "run-tests-${PROJECT_NAME}")
set(UNIT_TESTS_FILE "test/test.cpp")

add_executable(${UNIT_TESTS_NAME} ${UNIT_TESTS_FILE})

# Link test executable against gtest & gtest_main
target_link_libraries(${UNIT_TESTS_NAME} gtest_main ${LIBRARY_NAME})
add_test(${UNIT_TESTS_NAME} ${UNIT_TESTS_NAME})

# For next libraries.
set(BUILD_TESTS OFF CACHE BOOL "Build tests" FORCE)

endif() # BUILD_TESTS

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# - - - - - - - - - - - - DEPENDENCIES- - - - - - - - - - - - - - - - - - - - -
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#add_subdirectory(submodules/shush-format)
#add_subdirectory(submodules/shush-dump)
#
#target_link_libraries(shush-dump shush-format)
#target_link_libraries(${PROJECT_NAME} shush-dump shush-format)
#
#include_directories(include)
