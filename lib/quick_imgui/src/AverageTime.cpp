#include <imgui.h>
#include <numeric>
#include "quick_imgui/quick_imgui.hpp"

namespace quick_imgui {

void AverageTime::start()
{
    _start_time = std::chrono::steady_clock::now();
}

void AverageTime::stop()
{
    if (_start_time == std::chrono::steady_clock::time_point{}) // start() was never called
        return;
    auto const end_time = std::chrono::steady_clock::now();
    _times.push_back(static_cast<float>((end_time - _start_time).count()) / 1'000'000.f);
    if (_times.size() > 300)
        _times.erase(_times.begin());
}

auto AverageTime::average_time_ms() const -> float
{
    auto const& times = _times_when_paused.empty() ? _times : _times_when_paused;
    return std::accumulate(times.begin(), times.end(), 0.f) / static_cast<float>(times.size());
}

void AverageTime::imgui_plot() const
{
    if (ImGui::IsKeyPressed(ImGuiKey_Space))
    {
        if (_times_when_paused.empty())
            _times_when_paused = _times;
        else
            _times_when_paused.clear();
    }

    auto const& times = _times_when_paused.empty() ? _times : _times_when_paused;
    ImGui::Text("%.2f ms", average_time_ms());
    ImGui::PlotLines("Timings (ms)", times.data(), static_cast<int>(times.size()));
}

} // namespace quick_imgui
