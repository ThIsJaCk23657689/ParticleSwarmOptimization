#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

enum CameraMovement : unsigned int {
    LEFT = 0,
    RIGHT = 1,
    DOWN = 2,
    UP = 3,
    FORWARD = 4,
    BACKWARD = 5,
};

struct Camera {
    Camera(glm::vec3 pos, bool is_prscpt = false);

    // TODO: 需要球型坐標系相機以及正交投影切換功能

    struct Viewport {
        int x;
        int y;
        int width;
        int height;
    } viewport;

    struct Proj {
        float left;
        float right;
        float bottom;
        float top;
        float near;
        float far;
    } frustum;

    float AspectRatio();
    glm::mat4 View();
    glm::mat4 Projection();
    glm::mat4 Orthogonal();
    glm::mat4 Perspective();
    void SetViewPort();

    void ProcessKeyboard();
    void ProcessMouseMovement(bool constrain = true);
    void ProcessMouseScroll(float yoffset);
    void ToggleMouseControl();
    void Update(float dt);

    float pitch, yaw;
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;
    float move_speed;
    float mouse_sensitivity;
    float zoom;
    bool mouse_control;
    bool is_perspective;

private:
    void UpdateCameraVectors();
    void UpdateProjectionParameters();
};
#endif
