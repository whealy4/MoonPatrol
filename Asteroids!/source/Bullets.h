//
// Created by Tulane on 12/13/22.
//

#ifndef ASTEROIDS_BULLETS_H
#define ASTEROIDS_BULLETS_H

#include "common.h"
#include "Game.h"
#include "Alien1.h"

using namespace tcg;

class Bullet {
    friend class Bullets;
    friend class Game;
    friend class Alien1;

    // Bullet State
    struct {
        vec2 cur_location;
        vec2 move;
    } state;

public:
    Bullet(vec2 cur_location, vec2 move) {
        state.cur_location = cur_location;
        state.move = move;
    }

    void update_state() {
        state.cur_location += state.move;
    }
};

class Bullets {
public:
    void update_state(vec4 extents, std::vector<Alien1 *> t);

    //OpenGL variables for a bullet
    struct {
        GLuint vao;           //Vertex array object
        GLuint program;       //shader program
        GLuint buffer;        //Vertex buffer objects
        GLuint vertex_shader, fragment_shader;  //Shaders
        GLint vpos_location, vcolor_location;   //reference to pos and color in shaders
        GLint M_location;     //Reference to matrix in shader
    } GLvars;

    struct {
        int score;
        int points;
    } value;

    std::list < Bullet > bullets;
    std::vector < vec2 > bullets_vec;

    Bullets(){}

    ~Bullets(){
        bullets.clear();
        bullets_vec.clear();
    }

    void gl_init();


    void draw(mat4 proj);

    void add(Bullet b){ bullets.push_back(b); }
};
#endif //ASTEROIDS_BULLETS_H
