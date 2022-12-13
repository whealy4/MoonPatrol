//
// Created by Tulane on 12/8/22.
//

#ifndef ASTEROIDS_WHEEL_H
#define ASTEROIDS_WHEEL_H

#include "common.h"
//#include "Car.h"
#include "utils/vec.h"

class Wheel {
    friend class Game;
//    friend class Car;

    std::vector < tcg::vec2 > wheel_vert;
    std::vector < tcg::vec2 > wheel_uv;

    tcg::vec2 wheel_bbox[2];

    std::vector<unsigned char> wheel_im;
    unsigned  im_width, im_height;

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
    Wheel(unsigned int index);
//    void update_state(tcg::vec4 extents);
    void gl_init();
    void draw(tcg::mat4 proj);


};
#endif //ASTEROIDS_WHEEL_H
