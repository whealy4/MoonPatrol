//
// Created by Tulane on 12/13/22.
//

#ifndef ASTEROIDS_WHEELCHECK_H
#define ASTEROIDS_WHEELCHECK_H

#include "common.h"
#include "utils/vec.h"

using namespace tcg;

class WheelCheck {

    std::vector<vec2> wheel_check_pos;
    std::vector<vec3> wheel_check_color;

    tcg::vec2 wheel_check_bbox[2];

    struct {
        tcg::vec2 cur_location;
        tcg::vec4 pointing;
        tcg::vec2 velocity;
        tcg::mat4 wheel_M;
        float angle;
        float angle_speed;
    } state;

    struct {
        GLuint vao;           //Vertex array object
        GLuint program;       //shader program
        GLuint buffer;        //Vertex buffer objects
        GLuint vertex_shader, fragment_shader;  //Shaders
        GLint vpos_location, vcolor_location;   //reference to pos and color in shaders
        GLint M_location;     //Reference to matrix in shader
        GLuint wheel_texture;
    } GLvars;

public:
    WheelCheck();
    void update_state(vec4 extents);
    void gl_init();
    void draw(mat4 proj);
};

#endif //ASTEROIDS_WHEELCHECK_H
