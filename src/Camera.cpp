#include "Camera.hpp"

#include <SDL.h>
#include <glad/glad.h>

Camera::Camera(glm::vec3 pos, bool is_prscpt) :
    pitch(0.0f),
    yaw(0.0f),
    position(pos),
    velocity(glm::vec3(0.0f)),
    acceleration(glm::vec3(0.0f)),
    world_up(glm::vec3(0.0f, 1.0f, 0.0f)),
    front(glm::vec3(0.0, 0.0, -1.0)),
    right(glm::vec3(1.0, 0.0, 0.0)),
    up(glm::vec3(0.0, 1.0, 0.0)),
    move_speed(50.0f),
    mouse_sensitivity(0.1f),
    zoom(45.0f),
    mouse_control(false),
    is_perspective(is_prscpt) {
    UpdateCameraVectors();

    // Default Value
    frustum.near = 0.1f;
    frustum.far = 500.0f;
    UpdateProjectionParameters();
}

void Camera::UpdateCameraVectors() {
    // 更新攝影機的三軸方向向量：前、右、上，注意攝影機朝向負 z 軸
    glm::vec4 temp_front = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);

    // 利用 rotation 矩陣來旋轉攝影機的【前】向量，pitch 為垂直旋轉、yaw 為水平旋轉、roll 為側滾旋轉，單位是角度
    // 因為 rotation 是逆時針旋轉(角度為正時)，而因為攝影機朝向負 z 軸，滑鼠的相對座標（螢幕坐標系）往右是正（向左轉），往左是負（向右轉）
    // 所以 Yaw 必須轉為負值，或者是將旋轉軸反過來也可以，另外旋轉的順序也有關係，一般而言是 YXZ 的順序
    // 而萬向鎖就是只要 Pitch 旋轉是 ±90°，因為 Pitch 旋轉會影響到 Roll，所以此時 Yaw 以及 Roll 旋轉將會是一樣的效果（失去一個旋轉自由度）
    glm::mat4 rotateMatrix = glm::mat4(1.0f);
    rotateMatrix = glm::rotate(rotateMatrix, glm::radians(-yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateMatrix = glm::rotate(rotateMatrix, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));

    // 記住攝影機的初始【前】向量永遠面向世界座標的 -z 軸。
    temp_front = rotateMatrix * temp_front;

    // Gram-Schmidt Orthogonalization 正交化求攝影機三軸
    front = glm::normalize(glm::vec3(temp_front.x, temp_front.y, temp_front.z));
    right = glm::normalize(glm::cross(front, world_up));
    up = glm::normalize(glm::cross(right, front));
}

float Camera::AspectRatio() {
    return static_cast<float>(viewport.width) / static_cast<float>(viewport.height);
}

glm::mat4 Camera::View() {
    // 等價於 gluLookAt()
    glm::mat4 view = glm::lookAt(position, position + front, world_up);
    return view;
}

void Camera::ProcessKeyboard() {
    // SDL2 鍵盤控制移動建議使用這個 SDL_GetKeyboardState()，才不會覺得卡卡頓頓的
    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_W]) {
        acceleration += front * move_speed;
    }
    if (state[SDL_SCANCODE_S]) {
        acceleration -= front * move_speed;
    }
    if (state[SDL_SCANCODE_D]) {
        acceleration += right * move_speed;
    }
    if (state[SDL_SCANCODE_A]) {
        acceleration -= right * move_speed;
    }
    if (state[SDL_SCANCODE_SPACE]) {
        acceleration.y += move_speed * 2.0f;
    }
    if (state[SDL_SCANCODE_LSHIFT]) {
        acceleration.y -= move_speed * 2.0f;
    }
}

void Camera::ProcessMouseMovement(bool constrain) {
    // 當 SDL_SetRelativeMouseMode() 為 TRUE 時，鼠標會不見
    // 並且使用的是【相對位置】，一般來說就是與上一幀滑鼠位置的相對位置
    // 就不用還要自己去計算，會方便許多！
    if (!mouse_control) {
        SDL_SetRelativeMouseMode(SDL_FALSE);
        return;
    }

    int xoffset, yoffset;
    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_GetRelativeMouseState(&xoffset, &yoffset);

    yaw += xoffset * mouse_sensitivity;
    pitch += -yoffset * mouse_sensitivity;

    if (yaw >= 360.0f) {
        yaw = 0.0f;
    }
    if (yaw <= -360.0f) {
        yaw = 0.0f;
    }

    // 限制 Pitch 不能為 ±90°，不然會產生萬向鎖問題（Yaw 跟 Pitch 合併在一起，此時 Yaw 跟 Roll 會是一樣的作用）。
    if (constrain) {
        if (pitch > 89.0f) {
            pitch = 89.0f;
        }
        if (pitch < -89.0f) {
            pitch = -89.0f;
        }
    }

    // 更新攝影機三軸座標
    UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
    if (zoom >= 1.0f && zoom <= 90.0f) {
        zoom -= yoffset;
    }
    if (zoom < 1.0f) {
        zoom = 1.0f;
    }
    if (zoom > 90.0f) {
        zoom = 90.0f;
    }
}

void Camera::ToggleMouseControl() {
    mouse_control = !mouse_control;
}

void Camera::Update(float dt) {
    UpdateCameraVectors();

    velocity += acceleration * dt;
    position += velocity * dt;

    acceleration = glm::vec3(0.0f);
    velocity *= 0.95f;
}

glm::mat4 Camera::Projection() {
    UpdateProjectionParameters();
    if (is_perspective) {
        return Perspective();
    } else {
        return Orthogonal();
    }
}

glm::mat4 Camera::Orthogonal() {
    glm::mat4 proj = glm::ortho(frustum.left, frustum.right, frustum.bottom, frustum.top, frustum.near, frustum.far);
    return proj;
}

glm::mat4 Camera::Perspective() {
    glm::mat4 proj = glm::perspective(glm::radians(zoom), AspectRatio(), frustum.near, frustum.far);
    return proj;
}

void Camera::SetViewPort() {
    const auto& [x, y, w, h] = viewport;
    glViewport(x, y, w, h);
}

void Camera::UpdateProjectionParameters() {
    // 計算 ViewVolume 使用
    if (is_perspective) {
        frustum.top = tan(glm::radians(zoom / 2.0f)) * frustum.near;
        frustum.right = AspectRatio() * frustum.top;
        frustum.bottom = -frustum.top;
        frustum.left = -frustum.right;
    } else {
        frustum.top = tan(glm::radians(zoom / 2.0f)) * frustum.near * 1000.0f;
        frustum.right = AspectRatio() * frustum.top;
        frustum.bottom = -frustum.top;
        frustum.left = -frustum.right;
    }
}