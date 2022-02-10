#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

struct Config {
    // Window Settings
    bool is_fullscreen = false;
    int width = 800;
    int height = 600;
    std::string title = "Particle Swarm Optimization";

    // OpenGL Settings
    int opengl_major_version = 3;
    int opengl_minor_version = 3;
    std::string glsl_version = "#version 330";
};

#endif