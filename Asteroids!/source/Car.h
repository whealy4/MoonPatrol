// Car.h


#ifndef __Asteroids__Car__
#define __Asteroids__Car__

#include "common.h"
#include "Bullets.h"
#include "utils/vec.h"

class Ground;

class Car {
    friend class Game;
//    friend class Wheel;
    // Is this how you include another class to be used in functions? e.g. drive_on_ground() below
//    std::vector < tcg::vec2 > car_pos;
//    std::vector < tcg::vec3 > car_color;

    std::vector<unsigned char> car_im;
    std::vector<tcg::vec2> Car_vert;
    std::vector<tcg::vec2> Car_uv;
    unsigned im_width, im_height;
    tcg::vec2 car_bbox[2];

    // Initialized in constructor
    float angle_speed;
    float accel;
    float rand_angle;
    // tcg::mat4 asteroid_M;

    // Asteroid State
    struct {
        tcg::vec2 cur_location;
        tcg::vec4 pointing;
        tcg::vec2 velocity;
        tcg::mat4 car_M;
        float angle;
    } state;
    tcg::mat4 M;

    // OpenGL variables for an asteroid (?)
    struct {
        GLuint vao;           //Vertex array object
        GLuint program;       //shader program
        GLuint buffer;        //Vertex buffer objects
        GLuint vertex_shader, fragment_shader;  //Shaders
        GLint vpos_location, vcolor_location;   //reference to pos and color in shaders
        GLint M_location;     //Reference to matrix in shader
        GLuint car_texture;
    } GLvars;

    // Modelview matrix
    // tcg::mat4 M;

public:

    Car();
    int jump_ = 0;
    void update_state(tcg::vec4 extents);
    void gl_init();
    void draw(tcg::mat4 proj);
    void move_forward();
    void dampen();
    void drive_on_ground(Ground* ground);
    Bullet fireUp() {
        return Bullet(state.cur_location, tcg::vec2(0.0, 0.05));
    }

    Bullet fireRight() {
        return Bullet(state.cur_location, tcg::vec2(0.05, 0.0));
    }
    // GLfloat length(const tcg::vec2& v);
    // tcg::vec2 normalize(const tcg::vec2& v);


// inline void move_forward() {
    
//     state.velocity = state.velocity + 
//                      accel*normalize(tcg::vec2(state.pointing.x, state.pointing.y));
//     state.velocity = normalize(state.velocity);
// }
    inline void jump(){
        jump_ = 50;
    }

};
#endif /* defined(__Asteroids__Asteroid__) */