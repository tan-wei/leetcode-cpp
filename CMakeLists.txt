cmake_minimum_required(VERSION 4.1 FATAL_ERROR)

project(
  leetcode-cpp
  VERSION 0.0.1
  DESCRIPTION "My Leetcode Solution in C++"
  HOMEPAGE_URL https://github.com/tan-wei/leetcode-cpp
  LANGUAGES CXX
)

include(cmake/defaults.cmake)
include(FindThreads)
include(CTest)

# Ensure tests are built by default so files under src/solution/ are compiled
# unless the user explicitly disables BUILD_TESTING in the cache.
if(NOT DEFINED BUILD_TESTING)
  set(BUILD_TESTING ON CACHE BOOL "Build tests" FORCE)
endif()

# Find CURL provided by Conan or system
find_package(CURL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_library(warnings INTERFACE)
set_target_warnings(warnings)

add_library(options INTERFACE)
target_compile_features(options INTERFACE cxx_std_23)
enable_sanitizers(options)
enable_hardenings(options)
enable_coverage(options)

# Top-level executable (from CMakeLists-ref.txt)
add_executable(leetcode_cpp src/main.cpp src/fetcher.cpp)
target_include_directories(leetcode_cpp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
if(MSVC)
  target_compile_definitions(leetcode_cpp PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
target_link_libraries(
  leetcode_cpp
  PRIVATE CURL::libcurl nlohmann_json::nlohmann_json warnings options
)

# Add a convenient run target so callers can invoke `cmake --build --target
# run_leetcode_cpp`
if(TARGET leetcode_cpp)
  add_custom_target(
    run_leetcode_cpp
    COMMAND ${CMAKE_COMMAND} -E echo "Running leetcode_cpp..."
    COMMAND $<TARGET_FILE:leetcode_cpp>
    DEPENDS leetcode_cpp
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
endif()

# put unit tests that run on your pc here
if(NOT CMAKE_CROSSCOMPILING AND BUILD_TESTING)
  # Tests target: compile all src/solution/*.cpp into a test executable and link
  # gtest Use CONFIGURE_DEPENDS so CMake will re-run configure when files are
  # added/removed
  enable_testing()
  file(
    GLOB_RECURSE SOLUTION_SRC
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/solution/*.cpp"
  )
  if(SOLUTION_SRC)
    # Ensure GTest is available (from Conan or system)
    find_package(GTest REQUIRED)
    add_executable(leetcode_tests ${SOLUTION_SRC})
    target_include_directories(
      leetcode_tests
      PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    )
    target_compile_definitions(leetcode_tests PRIVATE ENABLE_GTEST=1)
    target_link_libraries(
      leetcode_tests
      PRIVATE GTest::gtest_main CURL::libcurl
    )
    # Register individual GoogleTest cases with CTest so each gtest is reported
    # as a separate test (gtest_discover_tests requires the GoogleTest CMake
    # module)
    include(GoogleTest)
    gtest_discover_tests(leetcode_tests)
  else()
    message(
      WARNING
      "No solution sources found in src/solution; skipping leetcode_tests target"
    )
  endif()

  # Optional: build and run a single solution via -DSOLUTION=<filename without
  # .cpp>
  set(
    SOLUTION
    ""
    CACHE STRING
    "Solution file basename in src/solution (e.g. s0001_two_sum)"
  )
  if(SOLUTION)
    set(SOLUTION_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/solution/${SOLUTION}.cpp")
    if(EXISTS ${SOLUTION_SRC})
      add_executable(
        run_solution_exec
        ${SOLUTION_SRC}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/runner.cpp
      )
      target_include_directories(
        run_solution_exec
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
      )
      add_custom_target(
        run_solution
        COMMAND $<TARGET_FILE:run_solution_exec>
        DEPENDS run_solution_exec
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      )
    else()
      message(
        WARNING
        "SOLUTION ${SOLUTION_SRC} not found; run_solution target will not be created"
      )
    endif()
  endif()
endif()
