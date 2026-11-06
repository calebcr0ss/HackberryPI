set(UI_DIR "${CMAKE_SOURCE_DIR}/ui")
set(UI_PROJECT_XML "${UI_DIR}/project.xml")
set(UI_SCREENS_DIR "${UI_DIR}/screens")

set(UI_LIB "")
set(UI_DEFAULT_SCREEN "")
if(EXISTS "${UI_DIR}/CMakeLists.txt"
   AND EXISTS "${UI_PROJECT_XML}"
   AND EXISTS "${UI_SCREENS_DIR}")
  message(STATUS "Found exported UI project in: ${UI_DIR}")
  add_subdirectory(${UI_DIR} ${CMAKE_BINARY_DIR}/ui)
  set(UI_LIB lib-ui)

  get_filename_component(UI_PROJECT_NAME "${UI_DIR}" NAME)
  message(STATUS "UI project name: ${UI_PROJECT_NAME}")

  file(GLOB _screen_xml_files "${UI_SCREENS_DIR}/*.xml"
       "${UI_SCREENS_DIR}/*/*.xml")
  if(_screen_xml_files)
    list(GET _screen_xml_files 0 _first_screen)
    get_filename_component(UI_DEFAULT_SCREEN "${_first_screen}" NAME_WE)
    message(STATUS "Default UI screen: ${UI_DEFAULT_SCREEN} (${_first_screen})")
  else()
    message(
      STATUS
        "No screens found in ${UI_SCREENS_DIR}, will use built-in default UI")
  endif()
endif()
