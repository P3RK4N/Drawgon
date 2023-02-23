add_library(imgui)

target_sources(
   imgui
      PRIVATE
         #Main
         "${Drawgon_SOURCE_DIR}/vendor/imgui/imgui.cpp"
         "${Drawgon_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp"
         "${Drawgon_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp"
         "${Drawgon_SOURCE_DIR}/vendor/imgui/imgui_tables.cpp"
         
         #Backends
         "${Drawgon_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_sdl3.cpp"
         "${Drawgon_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.cpp"
         #TODO: Add other graphic apis
)

# target_compile_definitions(
#    imgui
#       PRIVATE "IMGUI_IMPL_OPENGL_LOADER_CUSTOM"
# )

target_include_directories(
   imgui
      PUBLIC "${Drawgon_SOURCE_DIR}/vendor/imgui"
)

target_link_libraries(
   imgui
      PRIVATE SDL3-static
)