//
// Created by Tulane on 12/13/22.
//

#ifndef ASTEROIDS_ROCK_H
#define ASTEROIDS_ROCK_H

#include "common.h"
#include "utils/vec.h"

using namespace tcg;

class Rock {
public:
    std::vector <vec2> rock_pos;
    std::vector <vec3> rock_color;
    vec2 rock_bbox[2];

    struct {
        vec2 cur_location;
        vec2 velocity;
        mat4 rock_M;
    } state;

    struct {
        GLuint vao;           //Vertex array object
        GLuint program;       //shader program
        GLuint buffer;        //Vertex buffer objects
        GLuint vertex_shader, fragment_shader;  //Shaders
        GLint vpos_location, vcolor_location;   //reference to pos and color in shaders
        GLint M_location;     //Reference to matrix in shader
    } GLvars;
    tcg::mat4 M;

    Rock(float x_start);

    void gl_init();
    void draw(tcg::mat4 proj);
    void update_state(tcg::vec4 extents);
};

#endif //ASTEROIDS_ROCK_H
