// Asteroid.h


#ifndef __Asteroids__Asteroid__
#define __Asteroids__Asteroid__

#include "common.h"
#include "utils/vec.h"

class Asteroid {
    std::vector < tcg::vec2 > asteroid_pos;
    std::vector < tcg::vec3 > asteroid_color;

    unsigned int flame_offset;

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
        tcg::mat4 asteroid_M;
        float angle;
    } state;

    // OpenGL variables for an asteroid (?)
    struct {
        GLuint vao;           //Vertex array object
        GLuint program;       //shader program
        GLuint buffer;        //Vertex buffer objects
        GLuint vertex_shader, fragment_shader;  //Shaders
        GLint vpos_location, vcolor_location;   //reference to pos and color in shaders
        GLint M_location;     //Reference to matrix in shader
    } GLvars;

    // Modelview matrix
    // tcg::mat4 M;

public:

    Asteroid();

    void update_state(tcg::vec4 extents);
    void gl_init();
    void draw(tcg::mat4 proj);
    void move_forward();
    void switch_dir();
    tcg::mat4 gen_M();

    // GLfloat length(const tcg::vec2& v);
    // tcg::vec2 normalize(const tcg::vec2& v);
};




// inline 
// GLfloat length( const tcg::vec2& v ) {
//     return sqrt( dot(v,v) );
// }

// inline 
// tcg::vec2 normalize( const tcg::vec2& v ) {
//     return v / length(v);
// }




#endif /* defined(__Asteroids__Asteroid__) */