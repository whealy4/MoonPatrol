//
//  Ship.cpp
//  Asteroids
//
//  Created by Brian Summa on 6/5/15.
//
//

#include "common.h"


Ship::Ship(){
    state.cur_location = tcg::vec2(0.0f,0.0f);
    state.should_location = tcg::vec2(0.0f,0.0f);
    state.pointing = tcg::vec4(0.0f,-1.0f,0.0f,0.0f);
    state.velocity = tcg::vec2(0.0f,0.0f);
//      state.thruster_on = false;
    state.angle = 0.0;
    
    max_speed = 0.05;
    damping_fact = 0.98;
    accel = 0.008;
    
    
    state.thruster_on = false;
  
//  ship_pos.resize(11);
//  ship_color.resize(11);
//
//  flame_offset = 4;
    
    ship_pos.resize(39);
    ship_color.resize(39);
    
    flame_offset = 27;
    
    ship_pos[0] = tcg::vec2(0,     -0.085);  ship_color[0] = tcg::vec3(0.0,0.0,1.0);
    ship_pos[1] = tcg::vec2(0.04,   -0.055);  ship_color[1] = tcg::vec3(0.0,0.0,1.0);
    ship_pos[2] = tcg::vec2(-0.04,   -0.055);  ship_color[2] = tcg::vec3(0.0,0.0,1.0);
    
    ship_pos[3] = tcg::vec2(0.03,     -0.055);  ship_color[3] = tcg::vec3(0.5,0.5,0.5);
    ship_pos[4] = tcg::vec2(0.03,   0.015);  ship_color[4] = tcg::vec3(0.5,0.5,0.5);
    ship_pos[5] = tcg::vec2(-0.03,   0.015);  ship_color[5] = tcg::vec3(0.5,0.5,0.5);
    
    ship_pos[6] = tcg::vec2(0.03,     -0.055);  ship_color[6] = tcg::vec3(0.5,0.5,0.5);
    ship_pos[7] = tcg::vec2(-0.03,   0.015);  ship_color[7] = tcg::vec3(0.5,0.5,0.5);
    ship_pos[8] = tcg::vec2(-0.03,   -0.055);  ship_color[8] = tcg::vec3(0.5,0.5,0.5);
//right
    ship_pos[9] = tcg::vec2(0.03,     -0.035);  ship_color[9] = tcg::vec3(1.0,1.0,0);
    ship_pos[10] = tcg::vec2(0.07,   -0.015);  ship_color[10] = tcg::vec3(1.0,1.0,0);
    ship_pos[11] = tcg::vec2(0.03,   -0.015);  ship_color[11] = tcg::vec3(1.0,1.0,0);
    
    ship_pos[12] = tcg::vec2(0.06,     -0.015);  ship_color[12] = tcg::vec3(1.0,0,1.0);
    ship_pos[13] = tcg::vec2(0.06,   0.025);  ship_color[13] = tcg::vec3(1.0,0,1.0);
    ship_pos[14] = tcg::vec2(0.05,   0.025);  ship_color[14] = tcg::vec3(1.0,0,1.0);
    
    ship_pos[15] = tcg::vec2(0.06,     -0.015);  ship_color[15] = tcg::vec3(1.0,0,1.0);
    ship_pos[16] = tcg::vec2(0.05,   0.025);  ship_color[16] = tcg::vec3(1.0,0,1.0);
    ship_pos[17] = tcg::vec2(0.05,   -0.015);  ship_color[17] = tcg::vec3(1.0,0,1.0);
    
    
//left
    ship_pos[18] = tcg::vec2(-0.03,     -0.035);  ship_color[18] = tcg::vec3(1.0,1.0,0);
    ship_pos[19] = tcg::vec2(-0.07,   -0.015);  ship_color[19] = tcg::vec3(1.0,1.0,0);
    ship_pos[20] = tcg::vec2(-0.03,   -0.015);  ship_color[20] = tcg::vec3(1.0,1.0,0);
    
    ship_pos[21] = tcg::vec2(-0.06,     -0.015);  ship_color[21] = tcg::vec3(1.0,0,1.0);
    ship_pos[22] = tcg::vec2(-0.06,   0.025);  ship_color[22] = tcg::vec3(1.0,0,1.0);
    ship_pos[23] = tcg::vec2(-0.05,   0.025);  ship_color[23] = tcg::vec3(1.0,0,1.0);
    
    ship_pos[24] = tcg::vec2(-0.06,     -0.015);  ship_color[24] = tcg::vec3(1.0,0,1.0);
    ship_pos[25] = tcg::vec2(-0.05,   0.025);  ship_color[25] = tcg::vec3(1.0,0,1.0);
    ship_pos[26] = tcg::vec2(-0.05,   -0.015);  ship_color[26] = tcg::vec3(1.0,0,1.0);
    
    //Flame
  //    right
      ship_pos[27] = tcg::vec2(0.055,     -0.025);  ship_color[27] = tcg::vec3(1.0,1.0,0);
      ship_pos[28] = tcg::vec2(0.07,   0.085);  ship_color[28] = tcg::vec3(1.0,0,0);
      ship_pos[29] = tcg::vec2(0.055,   0.075);  ship_color[29] = tcg::vec3(1.0,0,0);
      
      ship_pos[30] = tcg::vec2(0.055,     -0.025);  ship_color[30] = tcg::vec3(1.0,1.0,0);
      ship_pos[31] = tcg::vec2(0.04,   0.085);  ship_color[31] = tcg::vec3(1.0,0,0);
      ship_pos[32] = tcg::vec2(0.055,   0.075);  ship_color[32] = tcg::vec3(1.0,0,0);
  //left
      ship_pos[33] = tcg::vec2(-0.055,     -0.025);  ship_color[33] = tcg::vec3(1.0,1.0,0);
      ship_pos[34] = tcg::vec2(-0.07,   0.085);  ship_color[34] = tcg::vec3(1.0,0,0);
      ship_pos[35] = tcg::vec2(-0.055,   0.075);  ship_color[35] = tcg::vec3(1.0,0,0);
      
      ship_pos[36] = tcg::vec2(-0.055,     -0.025);  ship_color[36] = tcg::vec3(1.0,1.0,0);
      ship_pos[37] = tcg::vec2(-0.04,   0.085);  ship_color[37] = tcg::vec3(1.0,0,0);
      ship_pos[38] = tcg::vec2(-0.055,   0.075);  ship_color[38] = tcg::vec3(1.0,0,0);
    
    
    
    
  
  //The nose of the ship is pointing in the -y direction for this model
  //Vector to keep track of this
  state.pointing = tcg::vec4(0.0f,-1.0f,0.0f,0.0f);

};



//Function updates state.cur_location and state.velocity

void Ship::update_state(tcg::vec4 extents){
    
    if (state.thruster_on== true){
        state.velocity = state.velocity+accel*normalize(tcg::vec2(state.pointing.x,state.pointing.y));
    }
    
    else{
        if(length(state.velocity)>0){
          state.velocity = damping_fact*tcg::vec2(state.velocity.x,state.velocity.y);
        }
    }
    
  
  //If the thruster is on:
  //  Increase velocity by a factor of accel in the direction the ship is pointing
  //  If velocity has manitude is more than the max_speed, reduce it to have
  //  magnitude max_speed
  
  //Apply damping_fact to velocity so ship will eventually slow down if thrusters
  //aren't on
  
  //Update cur_location based on velocity
  
  //If cur_location is outside one of the extents, have it wrap to the other side.
  // (i.e. if the ship goes off the left of the screen, it appears on the right.
  //extents = (left, right, bottom, top)
    
    if(state.cur_location.x < extents[0] || state.cur_location.x > extents[1]){
        state.cur_location.x = -state.cur_location.x;
      }
      if(state.cur_location.y < extents[2] ||state.cur_location.y > extents[3]){
        state.cur_location.y = -state.cur_location.y;
      }

}


void Ship::gl_init(){

  unsigned int ship_vert_size = ship_pos.size()*sizeof(tcg::vec2);
  unsigned int ship_color_size = ship_color.size()*sizeof(tcg::vec3);

  std::string vshader = shader_path + "vshader_Ship.glsl";
  std::string fshader = shader_path + "fshader_Ship.glsl";

  GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
  GLchar* fragment_shader_source = readShaderSource(fshader.c_str());

  GLvars.vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(GLvars.vertex_shader, 1, (const GLchar**) &vertex_shader_source, NULL);
  glCompileShader(GLvars.vertex_shader);
  check_shader_compilation(vshader, GLvars.vertex_shader);

  GLvars.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(GLvars.fragment_shader, 1, (const GLchar**) &fragment_shader_source, NULL);
  glCompileShader(GLvars.fragment_shader);
  check_shader_compilation(fshader, GLvars.fragment_shader);

  GLvars.program = glCreateProgram();
  glAttachShader(GLvars.program, GLvars.vertex_shader);
  glAttachShader(GLvars.program, GLvars.fragment_shader);

  glLinkProgram(GLvars.program);
  check_program_link(GLvars.program);

  glBindFragDataLocation(GLvars.program, 0, "fragColor");

  GLvars.vpos_location   = glGetAttribLocation(GLvars.program, "vPos");
  GLvars.vcolor_location = glGetAttribLocation(GLvars.program, "vColor" );
  GLvars.M_location = glGetUniformLocation(GLvars.program, "M" );

  // Create a vertex array object
  glGenVertexArrays( 1, &GLvars.vao );
  //Set GL state to use vertex array object
  glBindVertexArray( GLvars.vao );

  //Generate buffer to hold our vertex data
  glGenBuffers( 1, &GLvars.buffer );
  //Set GL state to use this buffer
  glBindBuffer( GL_ARRAY_BUFFER, GLvars.buffer );

  //Create GPU buffer to hold vertices and color
  glBufferData( GL_ARRAY_BUFFER, ship_vert_size + ship_color_size, NULL, GL_STATIC_DRAW );
  //First part of array holds vertices
  glBufferSubData( GL_ARRAY_BUFFER, 0, ship_vert_size, &ship_pos[0] );
  //Second part of array hold colors (offset by sizeof(triangle))
  glBufferSubData( GL_ARRAY_BUFFER, ship_vert_size, ship_color_size, &ship_color[0] );

  glEnableVertexAttribArray(GLvars.vpos_location);
  glEnableVertexAttribArray(GLvars.vcolor_location );

  glVertexAttribPointer( GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glVertexAttribPointer( GLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(ship_vert_size) );

  glBindVertexArray(0);
  
}

void Ship::draw(tcg::mat4 Projection){
  glUseProgram( GLvars.program );
  glBindVertexArray( GLvars.vao );
  
  tcg::mat4 M;
  //Rotate and move the rendering of the ship by constructing the modelview M
//    M = tcg::RotateZ(M_PI/2);
  M = this->M;
  M = tcg::Translate(state.cur_location.x+state.velocity.x, state.cur_location.y+state.velocity.y, 0.0)*M;
  state.cur_location = state.cur_location+state.velocity;
  glUniformMatrix4fv( GLvars.M_location, 1, GL_TRUE, Projection*M);
  
  if(state.thruster_on){
    glLineWidth(5.0);
      glDrawArrays( GL_TRIANGLES, 27, 3 );
      glDrawArrays( GL_TRIANGLES, 30, 3 );
      glDrawArrays( GL_TRIANGLES, 33, 3 );
      glDrawArrays( GL_TRIANGLES, 36, 3 );
//    glDrawArrays( GL_LINE_LOOP, flame_offset, ship_pos.size()-flame_offset);
  }
  
  glLineWidth(1.2);
//  glDrawArrays( GL_LINE_LOOP, 0, flame_offset );
    glDrawArrays( GL_TRIANGLES, 0, 3 );
      glDrawArrays( GL_TRIANGLES, 3, 3 );
      glDrawArrays( GL_TRIANGLES, 6, 3 );
      glDrawArrays( GL_TRIANGLES, 9, 3 );
      glDrawArrays( GL_TRIANGLES, 12, 3 );
      glDrawArrays( GL_TRIANGLES, 15, 3 );
      glDrawArrays( GL_TRIANGLES, 18, 3 );
      glDrawArrays( GL_TRIANGLES, 21, 3 );
      glDrawArrays( GL_TRIANGLES, 24, 3 );
  
  
  glBindVertexArray(0);
  glUseProgram(0);
  
}

