cmake_minimum_required( VERSION 3.11 )

# Apple: Don't modify install_name when touching RPATH.
# if(POLICY CMP0068)
#    cmake_policy(SET CMP0068 NEW)
# endif()

project(evr-internals-api)

# Fix behavior of CMAKE_CXX_STANDARD when targeting macOS.
if (POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif ()

include(CheckCXXCompilerFlag)

CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" "/usr/local/share/cmake-3.11/Modules")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(LT_VERSION "1")
set(LT_REVISION "1")

option(${CMAKE_PROJECT_NAME}_INCLUDE_EXAMPLES "Wrap the curl examples from https://curl.haxx.se/libcurl/c/example.html" ON)

option(${CMAKE_PROJECT_NAME}_SWIG "Wrap with swig" ON)
option(${CMAKE_PROJECT_NAME}_SWIG_LUA "Wrap it to lua" OFF)
option(${CMAKE_PROJECT_NAME}_SWIG_PYTHON "Wrap it to python" ON)
option(${CMAKE_PROJECT_NAME}_SWIG_JAVA "Wrap it to java" OFF)
option(${CMAKE_PROJECT_NAME}_SWIG_GO "Wrap it to go" OFF)
option(${CMAKE_PROJECT_NAME}_SWIG_RUBY "Wrap it to ruby" OFF)
option(${CMAKE_PROJECT_NAME}_SWIG_OCTAVE "Wrap it to octave" OFF)
option(${CMAKE_PROJECT_NAME}_SWIG_CSHARP "Wrap it to csharp" OFF)
option(${CMAKE_PROJECT_NAME}_SWIG_JAVASCRIPT "Wrap it to javascript (node)" OFF)
option(${CMAKE_PROJECT_NAME}_SWIG_PHP "Wrap it to php" OFF)
option(${CMAKE_PROJECT_NAME}_SWIG_PERL "Wrap it to php" OFF)

file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/source/*.c*")
file(GLOB_RECURSE INCLUDE_FILES "${CMAKE_SOURCE_DIR}/source/*.h*")
file(GLOB_RECURSE PUBLIC_INCLUDE_FILES "${CMAKE_SOURCE_DIR}/public_include/*.h*")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/source")
set(PUBLIC_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/public_include")
set(TEST_MAIN_FILE "${CMAKE_SOURCE_DIR}/test/scriptrunner/main.cpp")
file(GLOB TEST_INCLUDE_FILE "${CMAKE_SOURCE_DIR}/test/scriptrunner/*.h*")
set(TEST_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/test/scriptrunner")

set(${CMAKE_PROJECT_NAME}_DEFINITIONS RAPIDJSON_ENDIAN)

if(NOT ${${CMAKE_PROJECT_NAME}_INCLUDE_EXAMPLES})
  file(GLOB_RECURSE EXAMPLE_SOURCE_FILES "${CMAKE_SOURCE_DIR}/source/allexamples/*.c")
  list(APPEND EXAMPLE_SOURCE_FILES "${CMAKE_SOURCE_DIR}/source/allexamples/CurlExample.cpp")

  file(GLOB_RECURSE EXAMPLE_INCLUDE_FILES "${CMAKE_SOURCE_DIR}/source/allexamples/*.h")
  list(APPEND EXAMPLE_INCLUDE_FILES "${CMAKE_SOURCE_DIR}/source/allexamples/CurlExample.h")

  foreach(_FNAME ${EXAMPLE_SOURCE_FILES})
    LIST(REMOVE_ITEM SOURCE_FILES ${_FNAME} )
  endforeach()

  foreach(_FNAME ${EXAMPLE_INCLUDE_FILES})
    LIST(REMOVE_ITEM INCLUDE_FILES ${_FNAME} )
  endforeach()
else()
  list(APPEND ${CMAKE_PROJECT_NAME}_DEFINITIONS WRAP_EXAMPLES)
endif()

find_package(CURL REQUIRED)
if(CURL_FOUND)
  message(STATUS "CURL_INCLUDE_DIRS ${CURL_INCLUDE_DIRS}")
  message(STATUS "CURL_LIBRARIES ${CURL_LIBRARIES}")
  message(STATUS "CURL_FOUND ${CURL_FOUND}")
  message(STATUS "CURL_VERSION_STRING ${CURL_VERSION_STRING}")

  list(APPEND EXTRA_LIBS ${CURL_LIBRARIES})
  list(APPEND THIRDPARTY_INCLUDE_DIR ${CURL_INCLUDE_DIRS})
endif()
find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
  message(STATUS "OPENSSL_ROOT_DIR ${OPENSSL_ROOT_DIR}")
  message(STATUS "OPENSSL_FOUND ${OPENSSL_FOUND}")
  message(STATUS "OPENSSL_INCLUDE_DIR ${OPENSSL_INCLUDE_DIR}")
  message(STATUS "OPENSSL_LIBRARIES ${OPENSSL_LIBRARIES}")
  message(STATUS "OPENSSL_VERSION ${OPENSSL_VERSION}")

  list(APPEND EXTRA_LIBS ${OPENSSL_LIBRARIES})
  list(APPEND THIRDPARTY_INCLUDE_DIR ${OPENSSL_INCLUDE_DIR})
endif()
message(STATUS "${CMAKE_PROJECT_NAME}_DEFINITIONS ${${CMAKE_PROJECT_NAME}_DEFINITIONS}")

add_library(${CMAKE_PROJECT_NAME}-static STATIC ${SOURCE_FILES} ${INCLUDE_FILES})
target_include_directories(${CMAKE_PROJECT_NAME}-static
  PRIVATE $<BUILD_INTERFACE:${THIRDPARTY_INCLUDE_DIR}>
  PRIVATE $<BUILD_INTERFACE:${INCLUDE_DIR}>
  PUBLIC $<BUILD_INTERFACE:${PUBLIC_INCLUDE_FILES}>
  )
set_target_properties(${CMAKE_PROJECT_NAME}-static PROPERTIES PUBLIC_HEADER ${PUBLIC_INCLUDE_FILES})

set(_INSTALL_LIBS "${CMAKE_PROJECT_NAME}-static" ${_INSTALL_LIBS})
target_link_libraries(${CMAKE_PROJECT_NAME}-static ${EXTRA_LDFLAGS})
foreach(EXTRA_LIB ${EXTRA_LIBS})
  target_link_libraries( ${CMAKE_PROJECT_NAME}-static ${EXTRA_LIB})
endforeach()
target_compile_definitions(${CMAKE_PROJECT_NAME}-static PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})

if(${CMAKE_PROJECT_NAME}_SWIG)

  find_package(SWIG REQUIRED)
  include(UseSWIG)

  if(${SWIG_FOUND})
    MESSAGE(STATUS "SWIG_FOUND ${SWIG_FOUND}")
    MESSAGE(STATUS "SWIG_DIR ${SWIG_DIR}")
    MESSAGE(STATUS "SWIG_EXECUTABLE ${SWIG_EXECUTABLE}")
    MESSAGE(STATUS "SWIG_VERSION ${SWIG_VERSION}")

    include(${SWIG_USE_FILE})

    if(${CMAKE_PROJECT_NAME}_SWIG_LUA)
      include(${CMAKE_SOURCE_DIR}/cmake/swig_lua.cmake)
      LUA_SWIG()
    endif()

    if(${CMAKE_PROJECT_NAME}_SWIG_PYTHON)
      include(${CMAKE_SOURCE_DIR}/cmake/swig_python.cmake)
      PYTHON_SWIG()
    endif()

    if(${CMAKE_PROJECT_NAME}_SWIG_JAVA)
      include(${CMAKE_SOURCE_DIR}/cmake/swig_java.cmake)
      JAVA_SWIG()
    endif()

    if(${CMAKE_PROJECT_NAME}_SWIG_GO)
      include(${CMAKE_SOURCE_DIR}/cmake/swig_go.cmake)
      GO_SWIG()
    endif()

    if(${CMAKE_PROJECT_NAME}_SWIG_RUBY)
      include(${CMAKE_SOURCE_DIR}/cmake/swig_ruby.cmake)
      RUBY_SWIG()
    endif()

    if(${CMAKE_PROJECT_NAME}_SWIG_OCTAVE)
      include(${CMAKE_SOURCE_DIR}/cmake/swig_octave.cmake)
      OCTAVE_SWIG()
    endif()

    if(${CMAKE_PROJECT_NAME}_SWIG_CSHARP)
      include(${CMAKE_SOURCE_DIR}/cmake/swig_csharp.cmake)
      CSHARP_SWIG()
    endif()

    if(${CMAKE_PROJECT_NAME}_SWIG_JAVASCRIPT)
      include(${CMAKE_SOURCE_DIR}/cmake/swig_javascript.cmake)
      JAVASCRIPT_SWIG()
    endif()

    if(${CMAKE_PROJECT_NAME}_SWIG_PHP)
      include(${CMAKE_SOURCE_DIR}/cmake/swig_php.cmake)
      PHP_SWIG()
    endif()

    if(${CMAKE_PROJECT_NAME}_SWIG_PERL)
      include(${CMAKE_SOURCE_DIR}/cmake/swig_perl.cmake)
      PERL_SWIG()
    endif()

  endif()
endif()


enable_testing()
add_subdirectory(test)
