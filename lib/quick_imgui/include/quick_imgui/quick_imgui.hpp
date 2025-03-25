#pragma once
#include <imgui/imgui.h>
#include <chrono>
#include <functional>
#include <vector>

namespace quick_imgui {

struct Callbacks {
    std::function<void()> init { []() {} };
    std::function<void()> loop { []() {} };
    std::function<void(int, int, int, int)> key_callback { [](int key, int scancode, int action, int mods) {} }; // NOLINT(*-easily-swappable-parameters)
    std::function<void(int, int, int)> mouse_button_callback { [](int button, int action, int mods) {} }; // NOLINT(*-easily-swappable-parameters)
    std::function<void(double, double)> cursor_position_callback { [](double xpos, double ypos) {} }; // NOLINT(*-easily-swappable-parameters)
    std::function<void(double, double)> scroll_callback { [](double xoffset, double yoffset) {} }; // NOLINT(*-easily-swappable-parameters)
    std::function<void(int, int)> window_size_callback { [](int width, int height) {} }; // NOLINT(*-easily-swappable-parameters)
};

void loop(const char* window_name, Callbacks callbacks);

/// A convenience class to measure the performance of a block of code, and display it with ImGui
/// Press space to pause the graphics
class AverageTime {
public:
    void start();
    void stop();
    auto average_time_ms() const -> float;
    void imgui_plot() const;

private:
    std::chrono::steady_clock::time_point _start_time{};
    std::vector<float>                    _times{};
    mutable std::vector<float>            _times_when_paused{};
};

} // namespace quick_imgui
