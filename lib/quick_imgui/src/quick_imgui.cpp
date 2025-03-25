#include "quick_imgui/quick_imgui.hpp"
#include "GLFW/glfw3.h"
#include "ImGuiWrapper.hpp"
#include "backends/imgui_impl_glfw.h"
#include "imgui.h"

namespace quick_imgui {

static auto get_callbacks(GLFWwindow* window) -> Callbacks&
{
    return *static_cast<Callbacks*>(glfwGetWindowUserPointer(window));
}

static void set_glfw_callbacks(GLFWwindow* window, Callbacks& callbacks)
{
    glfwSetWindowUserPointer(window, &callbacks);

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) { // NOLINT(*-easily-swappable-parameters)
        ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
        if (!ImGui::GetIO().WantTextInput)
            get_callbacks(window).key_callback(key, scancode, action, mods);
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) { // NOLINT(*-easily-swappable-parameters)
        ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
        if (!ImGui::GetIO().WantCaptureMouse)
            get_callbacks(window).mouse_button_callback(button, action, mods);
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) { // NOLINT(*-easily-swappable-parameters)
        ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);
        get_callbacks(window).cursor_position_callback(xpos, ypos);
    });

    glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) { // NOLINT(*-easily-swappable-parameters)
        ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
        if (!ImGui::GetIO().WantCaptureMouse)
            get_callbacks(window).scroll_callback(xoffset, yoffset);
    });

    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) { // NOLINT(*-easily-swappable-parameters)
        get_callbacks(window).window_size_callback(width, height);
    });
}

void loop(const char* window_name, Callbacks callbacks)
{
    GLFWwindow* const window = ImGuiWrapper::create_window(window_name);
    set_glfw_callbacks(window, callbacks);
    callbacks.init();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        ImGuiWrapper::begin_frame({0.302f, 0.302f, 0.302f, 1.000f});
        callbacks.loop();
        ImGuiWrapper::end_frame(window);
    }

    ImGuiWrapper::shutdown(window);
}

} // namespace quick_imgui
