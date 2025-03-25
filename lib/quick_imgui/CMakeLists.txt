cmake_minimum_required(VERSION 3.8)

set(WARNINGS_AS_ERRORS_FOR_QUICK_IMGUI OFF CACHE BOOL "ON iff you want to treat warnings as errors")

add_library(quick_imgui)
add_library(quick_imgui::quick_imgui ALIAS quick_imgui)
target_compile_features(quick_imgui PUBLIC cxx_std_14)

# ---Add source files---
if(WARNINGS_AS_ERRORS_FOR_QUICK_IMGUI)
    target_include_directories(quick_imgui PUBLIC include)
else()
    target_include_directories(quick_imgui SYSTEM PUBLIC include)
endif()

target_sources(quick_imgui PRIVATE
    src/quick_imgui.cpp
    src/ImGuiWrapper.cpp
    src/AverageTime.cpp
)

# ---Setup warnings---
if(WARNINGS_AS_ERRORS_FOR_QUICK_IMGUI)
    if(MSVC)
        target_compile_options(quick_imgui PRIVATE /WX /W4)
    else()
        target_compile_options(quick_imgui PRIVATE -Werror -Wall -Wextra -Wpedantic -pedantic-errors -Wconversion -Wsign-conversion)
    endif()
endif()

# ---Add GLFW---
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
add_subdirectory(lib/glfw)
target_link_libraries(quick_imgui PUBLIC glfw)

# ---Add glad---
add_library(glad lib/glad/src/glad.c)
target_include_directories(glad SYSTEM PUBLIC lib/glad/include)
target_link_libraries(quick_imgui PUBLIC glad)

# ---Add Dear ImGui---
add_library(ImGui)
target_sources(ImGui PRIVATE
    lib/imgui/imgui_demo.cpp
    lib/imgui/imgui_draw.cpp
    lib/imgui/imgui_tables.cpp
    lib/imgui/imgui_widgets.cpp
    lib/imgui/imgui.cpp
    lib/imgui/misc/cpp/imgui_stdlib.cpp
)
target_include_directories(ImGui SYSTEM PUBLIC lib/imgui)
target_compile_features(ImGui PUBLIC cxx_std_11)

# Build ImGui with glfw
target_link_libraries(ImGui PUBLIC glfw)
target_sources(ImGui PRIVATE lib/imgui/backends/imgui_impl_glfw.cpp)

# Build ImGui with OpenGL
target_sources(ImGui PRIVATE lib/imgui/backends/imgui_impl_opengl3.cpp)

# Link to ImGui
target_link_libraries(quick_imgui PUBLIC ImGui)
target_include_directories(quick_imgui SYSTEM PUBLIC lib)
