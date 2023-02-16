cmake_minimum_required(VERSION 3.25)
include("cmake/Drawgon_Utils.cmake")

#############################################################################
#PROJECT INIT ###############################################################
#############################################################################

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(BUILD_SHARED_LIBS OFF)

project(Drawgon VERSION 0.1.0 LANGUAGES C CXX)

set(target_name "Drawgon-Console")
set(cxx_version 20)


add_executable("${target_name}")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "${target_name}")

set_target_properties(
   "${target_name}"
      PROPERTIES
         CXX_STANDARD "${cxx_version}"
         CXX_STANDARD_REQUIRED ON
         CXX_EXTENSIONS OFF
         VS_DEBUGGER_WORKING_DIRECTORY "${Drawgon_SOURCE_DIR}/resources"
)

file(
   GLOB_RECURSE 
      sources src/*.cpp src/*.h src/*.glsl src/*.jpg src/*.png
)

file(
   GLOB_RECURSE 
      resources resources/*.glsl resources/*.jpg resources/*.png
)

drawgon_group_sources(resources "${Drawgon_SOURCE_DIR}/resources" "Resources")
drawgon_group_sources(sources "${Drawgon_SOURCE_DIR}/src" "Source")

target_sources(
   "${target_name}"
   PRIVATE "${sources}"
)
   
target_include_directories(
   "${target_name}"
   PRIVATE "${Drawgon_SOURCE_DIR}/src"
)

#############################################################################
#Dependencies ###############################################################
#############################################################################

add_subdirectory(vendor/Tigraf-Core)

target_link_libraries(
   "${target_name}"
   PRIVATE Tigraf-Core
)

#############################################################################
#Targets Hierarchy ##########################################################
#############################################################################

drawgon_group_targets("${CMAKE_CURRENT_LIST_DIR}")