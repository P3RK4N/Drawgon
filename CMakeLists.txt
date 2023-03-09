cmake_minimum_required(VERSION 3.25)
include("cmake/Drawgon_Utils.cmake")

#TODO: Add Dist Configuration UPDATE #1: Maybe just macro?

#############################################################################
#PROJECT INIT ###############################################################
#############################################################################

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(BUILD_SHARED_LIBS OFF)
set(DRAWGON_DISABLE_CONSOLE ON)

if(DRAWGON_DISABLE_CONSOLE)
   set(DRAWGON_WIN32 "WIN32")
endif()

project(Drawgon VERSION 0.1.0 LANGUAGES C CXX)

set(target_name "Drawgon")
set(cxx_version 20)

add_executable("${target_name}" "${DRAWGON_WIN32}")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "${target_name}")

set_target_properties(
   "${target_name}"
      PROPERTIES
         CXX_STANDARD "${cxx_version}"
         CXX_STANDARD_REQUIRED ON
         CXX_EXTENSIONS OFF
         VS_DEBUGGER_WORKING_DIRECTORY "${Drawgon_SOURCE_DIR}/resources"
)

file(GLOB_RECURSE sources src/*.*)
file(GLOB_RECURSE resources resources/*.*)

drawgon_group_sources(resources "${Drawgon_SOURCE_DIR}/resources" "Resources")
drawgon_group_sources(sources "${Drawgon_SOURCE_DIR}/src" "Source")

target_sources(
   "${target_name}"
   PRIVATE "${sources};${resources}"
)
   
target_include_directories(
   "${target_name}"
   PRIVATE "${Drawgon_SOURCE_DIR}/src"
)

#############################################################################
#Dependencies ###############################################################
#############################################################################

#Tigraf-Core
set(TIGRAF_DISABLE_CONSOLE "${DRAWGON_DISABLE_CONSOLE}")
add_subdirectory(vendor/Tigraf-Core)

#YAML-CPP
set(YAML_BUILD_SHARED_LIBS OFF)
add_subdirectory(vendor/yaml)

#imgui, nfd, ...
add_subdirectory(vendor)

target_link_libraries(
   "${target_name}"
      PRIVATE Tigraf-Core
      PRIVATE imgui
      PRIVATE yaml-cpp
      PRIVATE nfd
)

#############################################################################
#Targets Hierarchy ##########################################################
#############################################################################

drawgon_group_targets("${CMAKE_CURRENT_LIST_DIR}")