//
//  Ship.h
//  Asteroids
//
//  Created by Brian Summa on 6/5/15.
//
//

#ifndef __Asteroids__Ship__
#define __Asteroids__Ship__

#include "common.h"

class Ship{

  std::vector < tcg::vec2 > ship_pos;
  std::vector < tcg::vec2 > ship_pos_new;
  std::vector < tcg::vec3 > ship_color;
  
  unsigned int flame_offset;
  
  //Initialized in constructor
  float max_speed;
  float damping_fact;
  float accel;

  //Ship State
  struct {
      tcg::vec2 should_location;
      tcg::vec2 cur_location;
      tcg::vec4 pointing;
      tcg::vec2 velocity;
      bool thruster_on;
      float angle;
  } state;
  
  //OpenGL variables for a ship
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

  Ship();
  
  inline void start_thruster(){ state.thruster_on= true;}
  inline void stop_thruster() { state.thruster_on= false;}
    
inline
GLfloat length( const tcg::vec2& v ) {
    return sqrt( dot(v,v) );
}

inline
tcg::vec2 normalize( const tcg::vec2& v ) {
    return v / length(v);
}
    
    inline
    GLfloat length_4( const tcg::vec4& v ) {
        return sqrt( dot(v,v) );
    }

    inline
    tcg::vec4 normalize_4( const tcg::vec4& v ) {
        return v / length_4(v);
    }
    
//    tcg::mat4  M_L = tcg::RotateZ(M_PI/4);
  inline void rotateLeft() {
      // M = tcg::RotateZ(M_PI/2)*M;
      
      std::cout << "pointing: " << this->state.pointing;
       M = tcg::Translate(state.cur_location.x, state.cur_location.y, 0.0)
                          *tcg::RotateZ(M_PI/4)
                          *tcg::Translate(-state.cur_location.x, -state.cur_location.y, 0.0)
                          *M;
      this->state.pointing = tcg::RotateZ(M_PI/4)*this->state.pointing;

      state.angle = state.angle+M_PI/4;
      std::cout << "cur: " << state.cur_location;
  }
  
  inline void rotateRight(){
      M = tcg::Translate(state.cur_location.x, state.cur_location.y, 0.0)
                        *tcg::RotateZ(-M_PI/4)
                        *tcg::Translate(-state.cur_location.x, -state.cur_location.y, 0.0)
                        *M;
      this->state.pointing = tcg::RotateZ(-M_PI/4)*this->state.pointing;

      state.angle = state.angle-M_PI/4;
  }
    
  void update_state(tcg::vec4 extents);
  
  void gl_init();  
  
  void draw(tcg::mat4 proj);
  
};


#endif /* defined(__Asteroids__Ship__) */
