cmake_minimum_required(VERSION 3.18)
project(lvgl_linux C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(LV_HOR_RES
    320
    CACHE STRING "Display horizontal resolution")
set(LV_VER_RES
    240
    CACHE STRING "Display vertical resolution")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(FETCHCONTENT_QUIET OFF)
include(FetchContent)
get_filename_component(BUILD_FOLDER_NAME "${CMAKE_BINARY_DIR}" NAME)

set(FETCHCONTENT_BASE_DIR
    "${CMAKE_SOURCE_DIR}/deps/${BUILD_FOLDER_NAME}"
    CACHE PATH "Directory for fetched dependencies" FORCE)

# LVGL
FetchContent_Declare(
  lvgl
  GIT_REPOSITORY https://github.com/lvgl/lvgl.git
  GIT_TAG v9.6.0
  # GIT_SHALLOW TRUE
  SOURCE_SUBDIR "skip_add_subdirectory")

FetchContent_GetProperties(lvgl)
FetchContent_MakeAvailable(lvgl)

# LVGL Configuration
find_package(Python3 REQUIRED COMPONENTS Interpreter)
set(LV_CONF_DEFAULTS "${CMAKE_SOURCE_DIR}/lv_conf.defaults")
set(LV_CONF_GEN_PATH "${lvgl_SOURCE_DIR}/scripts/generate_lv_conf.py")
set(LV_CONF_TEMPLATE "${lvgl_SOURCE_DIR}/lv_conf_template.h")
set(LV_BUILD_CONF_PATH
    "${CMAKE_BINARY_DIR}/lv_conf.h"
    CACHE PATH "Path to lv_conf.h" FORCE)

execute_process(
  COMMAND
    ${Python3_EXECUTABLE} "${LV_CONF_GEN_PATH}" --template "${LV_CONF_TEMPLATE}"
    --defaults "${LV_CONF_DEFAULTS}" --config "${LV_BUILD_CONF_PATH}"
  RESULT_VARIABLE _conf_result
  OUTPUT_VARIABLE _conf_output
  ERROR_VARIABLE _conf_output)
if(NOT _conf_result EQUAL 0)
  message(FATAL_ERROR "Failed to generate lv_conf.h:\n${_conf_output}")
endif()

message(STATUS "Generated ${LV_BUILD_CONF_PATH} from ${LV_CONF_DEFAULTS}")

set_property(
  DIRECTORY
  APPEND
  PROPERTY CMAKE_CONFIGURE_DEPENDS "${LV_CONF_DEFAULTS}")
set_property(
  DIRECTORY
  APPEND
  PROPERTY CMAKE_CONFIGURE_DEPENDS "${LV_CONF_GEN_PATH}")
set_property(
  DIRECTORY
  APPEND
  PROPERTY CMAKE_CONFIGURE_DEPENDS "${LV_CONF_TEMPLATE}")

set(LV_BUILD_SET_CONFIG_OPTS
    ON
    CACHE BOOL "" FORCE)

add_subdirectory(${lvgl_SOURCE_DIR} ${lvgl_BINARY_DIR})

include(ui)

# Application
add_executable(
  ${CMAKE_PROJECT_NAME}
  src/backends/backend.c
  src/backends/drm.c
  src/backends/evdev.c
  src/backends/fbdev.c
  src/backends/sdl2.c
  src/backends/wayland.c
  src/backends/x11.c
  src/main.c)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE lvgl)

if(TARGET ${UI_LIB})
  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${UI_LIB})
endif()

target_compile_definitions(
  ${CMAKE_PROJECT_NAME}
  PRIVATE
    $<$<BOOL:${UI_LIB}>:UI_PROJECT_EXISTS>
    # The init function name: <project_name>_init(...)
    # Override with: cmake -DUI_PROJECT_NAME=project_name
    $<$<BOOL:${UI_PROJECT_NAME}>:UI_PROJECT_NAME=${UI_PROJECT_NAME}>
    # Path to the UI directory (as a string literal)
    # Override with: cmake -DUI_DIR=/some/other/path
    $<$<BOOL:${UI_LIB}>:UI_DIR_PATH="${UI_DIR}">
    # Default screen name empty string if none found
    # Override with: cmake -DUI_DEFAULT_SCREEN=screen_name
    $<$<BOOL:${UI_DEFAULT_SCREEN}>:UI_DEFAULT_SCREEN=${UI_DEFAULT_SCREEN}>
    # Default resolution
    # Override with: cmake -DLV_HOR_RES=1280 -DLV_VER_RES=800
    LV_HOR_RES=${LV_HOR_RES}
    LV_VER_RES=${LV_VER_RES})
