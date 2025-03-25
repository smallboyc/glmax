# quick_imgui

This library was designed to quickly get a test ImGui project up and running. It is not meant for production-ready apps, but instead for tests or quick demos. We use it inside CoolLibs to test libraries that require clients to have ImGui installed.

## Usage

To download and link this library to your project, simply add these lines to your *CMakeLists.txt*:
```cmake
include(FetchContent)
FetchContent_Declare(
    quick_imgui
    GIT_REPOSITORY https://github.com/CoolLibs/quick_imgui
    GIT_TAG 7b1cae59aca608381d8bfaf2d1e8e3a291d080f5
)
FetchContent_MakeAvailable(quick_imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE quick_imgui::quick_imgui)
```
If the library you are testing needs to link ImGui, also add this line in your *CMakeLists.txt*:
```cmake
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${quick_imgui_SOURCE_DIR}/lib)
```
Then you can use it like this:
```cpp
#include "quick_imgui/quick_imgui.hpp"

int main()
{
    quick_imgui::loop(
        "Quick ImGui",
        {
            .loop = []() { ImGui::ShowDemoWindow(); },
        }
    );
}
```

and your `loop` function will be called every frame. You can also pass an `init` function (that will be called once the OpenGL context is created) as well as glfw callbacks:

```cpp
quick_imgui::loop(
    "Quick ImGui",
    {
        .init                     = []() { std::cout << "Init\n"; },
        .loop                     = []() { ImGui::ShowDemoWindow(); },
        .key_callback             = [](int key, int scancode, int action, int mods) { std::cout << "Key: " << key << " Scancode: " << scancode << " Action: " << action << " Mods: " << mods << '\n'; },
        .mouse_button_callback    = [](int button, int action, int mods) { std::cout << "Button: " << button << " Action: " << action << " Mods: " << mods << '\n'; },
        .cursor_position_callback = [](double xpos, double ypos) { std::cout << "Position: " << xpos << ' ' << ypos << '\n'; },
        .scroll_callback          = [](double xoffset, double yoffset) { std::cout << "Scroll: " << xoffset << ' ' << yoffset << '\n'; },
        .window_size_callback     = [](int width, int height) { std::cout << "Resized: " << width << ' ' << height << '\n'; },
    }
);
```

## Running the tests

Simply use "tests/CMakeLists.txt" to generate a project, then run it.<br/>
If you are using VSCode and the CMake extension, this project already contains a *.vscode/settings.json* that will use the right CMakeLists.txt automatically.
