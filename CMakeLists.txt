cmake_minimum_required(VERSION 3.14)

project(
  furi

  LANGUAGES
    CXX

  VERSION
    1.0.0
)

set(CMAKE_CXX_STANDARD "14" CACHE STRING "Required C++ standard")
if(CMAKE_CXX_STANDARD LESS 14)
  message(FATAL_ERROR "Minimum C++14 version not met!")
endif()

find_package(Boost 1.71 REQUIRED)

include(GNUInstallDirs)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_library(
  furi
    src/parse_uri.cpp
)

target_include_directories(
  furi
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}-${PROJECT_VERSION}>
)

target_link_libraries(furi PUBLIC Boost::headers)

include(CTest)
if (BUILD_TESTING)
  include("cmake/FuriAddTest.cmake")
  add_subdirectory(test)
endif()

option(
  FURI_ADD_SUBDIRECTORY
  "set(FURI_ADD_SUBDIRECTORY ON CACHE BOOL \"\") to disable installation rules allowing Furi to support add_subdirectory"
  OFF
)

if (FURI_ADD_SUBDIRECTORY)
  add_library(Furi::furi ALIAS furi)
endif()

if (NOT FURI_ADD_SUBDIRECTORY)
  install(
    TARGETS
      furi

    EXPORT
      furi-targets

    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

  install(
    EXPORT
      furi-targets

    NAMESPACE Furi::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION}
  )

  install(
    DIRECTORY
      include/

    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}-${PROJECT_VERSION}
    FILES_MATCHING PATTERN "*.hpp"
  )

  include(CMakePackageConfigHelpers)
  write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
  )

  configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/${PROJECT_NAME}-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION}
  )

  install(
    FILES
      ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
      ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION}
  )
endif()
