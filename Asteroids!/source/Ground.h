// Ground.h

#ifndef __Asteroids__Ground__
#define __Asteroids__Ground__

#include "common.h"
#include "utils/vec.h"

class Ground {
    std::vector <tcg::vec2> ground_pos;
    std::vector <tcg::vec3> ground_color;
    tcg::vec2 ground_bbox[2];
    friend class Game;
    friend class Car;

    struct {
        tcg::vec2 cur_location;
        tcg::vec4 pointing;
        tcg::vec2 velocity;
        tcg::mat4 car_M;
        float angle;
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

public:
    Ground();

    void gl_init();
    void draw(tcg::mat4 proj);
};

#endif /* defined(__Asteroids__Asteroid__) */