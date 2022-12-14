//
// Created by Tulane on 12/13/22.
//

#ifndef ASTEROIDS_HOLE_H
#define ASTEROIDS_HOLE_H

#include "common.h"
#include "utils/vec.h"

using namespace tcg;

class Hole {
    std::vector <tcg::vec2> hole_pos;
    std::vector <tcg::vec3> hole_color;



public:
    vec2 hole_bbox[2];

    Hole(float x_loc);
    void gl_init();
    void draw(mat4 proj);
    void update_state(vec4 extents);

    struct {
        vec2 cur_location;
        vec2 velocity;
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
};
#endif //ASTEROIDS_HOLE_H
