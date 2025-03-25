cmake_minimum_required(VERSION 3.8)

add_library(ImGui)
add_library(ImGui::ImGui ALIAS ImGui)
target_compile_features(ImGui PUBLIC cxx_std_11)

if (WIN32)
    target_link_libraries(ImGui PRIVATE imm32) # Required only when using mingw, not Visual Studio
endif()

target_include_directories(ImGui PUBLIC ./)
target_sources(ImGui PRIVATE
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui.cpp
    misc/cpp/imgui_stdlib.cpp
)