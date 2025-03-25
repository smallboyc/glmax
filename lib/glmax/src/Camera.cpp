#include "Camera.hpp"
#include <GLFW/glfw3.h>
#include "glm/ext/matrix_transform.hpp"

namespace glmax {

glm::mat4 Camera::get_view_matrix()
{
    if (_is_track_ball)
    {
        _position = glm::vec3(
            _radius * cos(glm::radians(_pitch)) * sin(glm::radians(_yaw)),
            _radius * sin(glm::radians(_pitch)),
            _radius * cos(glm::radians(_pitch)) * cos(glm::radians(_yaw))

        );
        return glm::lookAt(_position, _target, _up);
    }
    return glm::lookAt(_position, _position + _front, _up);
}

void Camera::process_mouse_movement(double xpos, double ypos)
{
    if (_first_mouse)
    {
        _last_x      = xpos;
        _last_y      = ypos;
        _first_mouse = false;
    }

    float xoffset = xpos - _last_x;
    float yoffset = ypos - _last_y;
    _last_x       = xpos;
    _last_y       = ypos;

    _yaw += xoffset * _sensitivity;
    _pitch -= yoffset * _sensitivity;

    if (_pitch > 45.0f)
        _pitch = 45.0f;
    if (_pitch < 0.0f)
        _pitch = 0.0f;
}

void Camera::process_scroll(double yoffset)
{
    _radius -= yoffset * 0.1f;
    if (_radius < 1.0f)
        _radius = 1.0f;
    if (_radius > 32.0f)
        _radius = 32.0f;
}

void Camera::process_input(int key, int action)
{
    if (key == GLFW_KEY_Z && action == GLFW_PRESS)
    {
        _position += _sensitivity * _front;
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        _position -= _sensitivity * _front;
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        _position -= glm::normalize(glm::cross(_front, _up)) * _sensitivity;
    }
    if (key == GLFW_KEY_C && action == GLFW_PRESS)
    {
        _position += glm::normalize(glm::cross(_front, _up)) * _sensitivity;
    }
}

// callbacks
void Camera::free_move_callback(int key, int action)
{
    if (!is_track_ball() && !_isLocked)
        process_input(key, action);
}

void Camera::zoom_callback(double yoffset)
{
    if (is_track_ball() && !_isLocked)
        process_scroll(yoffset);
}

void Camera::track_ball_move_callback(double xpos, double ypos)
{
    if (is_track_ball() && !_isLocked)
        process_mouse_movement(xpos, ypos);
}
} // namespace glmax
