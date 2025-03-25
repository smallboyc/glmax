#pragma once
#include <glm/glm.hpp>
#include "glm/fwd.hpp"

namespace glmax {

class Camera {
private:
    glm::vec3 _position = glm::vec3(0.0f, 0.0f, 16.0f);
    glm::vec3 _target   = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 _front    = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 _up       = glm::vec3(0.0f, 1.0f, 0.0f);

    float _yaw    = 0.0f;
    float _pitch  = 24.0f;
    float _radius = 16.0f;

    float _sensitivity = 0.2f;
    float _last_x      = 0.0f;
    float _last_y      = 0.0f;

    bool _first_mouse = true;
    bool _is_track_ball;
    bool _isLocked = false;

public:
    Camera(bool is_track_ball)
        : _is_track_ball(is_track_ball){};

    glm::mat4 get_view_matrix();
    glm::vec3 get_position() { return _position; };
    void      process_mouse_movement(double xpos, double ypos);
    void      process_scroll(double yoffset);
    void      process_input(int key, int action);
    void      set_position(const glm::vec3& position) { _position = position; }
    void      set_target(const glm::vec3& target) { _target = target; }
    void      set_front(const glm::vec3& front) { _front = front; }
    void      set_up(const glm::vec3& up) { _up = up; }
    void      set_sensitivity(float sensitivity) { _sensitivity = sensitivity; }
    //
    void toggle_lock() { _isLocked = !_isLocked; };
    //
    bool is_track_ball() const { return _is_track_ball; };
    //
    // callbacks
    void free_move_callback(int key, int action);
    void zoom_callback(double yoffset);
    void track_ball_move_callback(double xpos, double ypos);
};

} // namespace glmax
