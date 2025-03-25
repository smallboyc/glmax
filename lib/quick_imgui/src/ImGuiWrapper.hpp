#pragma once
#include "imgui/imgui.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

namespace ImGuiWrapper {

GLFWwindow* create_window(const char* title);
void        begin_frame(ImVec4 background_color = {0.45f, 0.55f, 0.60f, 1.00f});
void        end_frame(GLFWwindow* window);
void        shutdown(GLFWwindow* window);

} // namespace ImGuiWrapper