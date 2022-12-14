//
// Created by Tulane on 12/14/22.
//

#ifndef ASTEROIDS_GAME_OVER_H
#define ASTEROIDS_GAME_OVER_H

#include "common.h"

using namespace tcg;

class GameOver {
public:
    std::vector<unsigned char> g_im;
    std::vector<vec2> g_vert;
    std::vector<vec2> g_uv;
    unsigned im_width, im_height;

    struct {
        GLuint vao;           //Vertex array object
        GLuint program;       //shader program
        GLuint buffer;        //Vertex buffer objects
        GLuint vertex_shader, fragment_shader;  //Shaders
        GLint vpos_location, vcolor_location;   //reference to pos and color in shaders
        GLint M_location;     //Reference to matrix in shader
        GLuint g_texture;
    } GLvars;

    struct {
        tcg::vec2 cur_location;
        tcg::vec4 pointing;
        tcg::vec2 velocity;
        tcg::mat4 car_M;
        float angle;
    } state;
    GameOver(int type);

    void gl_init();
    void draw(mat4 proj);
};

#endif //ASTEROIDS_GAME_OVER_H
