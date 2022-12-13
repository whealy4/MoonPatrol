//
// Created by Tulane on 12/11/22.
//

#ifndef ASTEROIDS_ALIEN1_H
#define ASTEROIDS_ALIEN1_H

#include "common.h"
#include "utils/vec.h"

using namespace tcg;

class Alien1 {
    friend class Game;
    std::vector<unsigned char> alien1_im;
    std::vector<vec2> alien1_vert;
    std::vector<vec2> alien1_uv;
    unsigned im_width, im_height;
    tcg::vec2 alien1_bbox[2];

    float angle_speed;
    float accel;
//    float angle;

    // Alien State
    struct {
        vec2 cur_location;
        vec4 pointing;
        vec2 velocity;
        mat4 alien1_M;
        float angle;
        float accel;
        std::chrono::time_point<std::chrono::system_clock> start_time;
        std::chrono::time_point<std::chrono::system_clock> end_time;
    } state;

    // OpenGL variables for Alien1
    struct {
        GLuint vao;           //Vertex array object
        GLuint program;       //shader program
        GLuint buffer;        //Vertex buffer objects
        GLuint vertex_shader, fragment_shader;  //Shaders
        GLint vpos_location, vcolor_location;   //reference to pos and color in shaders
        GLint M_location;     //Reference to matrix in shader
        GLuint alien1_texture;
    } GLvars;

public:
    Alien1();
    void update_state(vec4 extents);
    void gl_init();
    void draw(mat4 proj);
    mat4 activate();
    void change_angle();
//    void

};


#endif //ASTEROIDS_ALIEN1_H
