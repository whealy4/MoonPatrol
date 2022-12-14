//
// Created by Tulane on 12/13/22.
//

#include "common.h"

WheelCheck::WheelCheck() {
    state.cur_location = vec2(0, 0.0);

    wheel_check_pos.resize(4);
    wheel_check_color.resize(4);

    vec3 green = vec3(0.0,0.0,1.0);

    wheel_check_pos[0] = tcg::vec2(-0.025, -1.0); wheel_check_color[0] = green;
    wheel_check_pos[1] = tcg::vec2(-0.025, 0.0); wheel_check_color[1] = green;
    wheel_check_pos[2] = tcg::vec2(0.025, -1.0); wheel_check_color[2] = green;
    wheel_check_pos[3] = tcg::vec2(0.025, 0.0); wheel_check_color[3] = green;


    wheel_check_bbox[0] = wheel_check_pos[0];
    wheel_check_bbox[1] = wheel_check_pos[3];
}

void WheelCheck::gl_init() {

    unsigned int wheel_check_vert_size = wheel_check_pos.size()*sizeof(tcg::vec2);
    unsigned int wheel_check_color_size = wheel_check_color.size()*sizeof(tcg::vec3);

    std::string vshader = shader_path + "vshader_WheelCheck.glsl";
    std::string fshader = shader_path + "fshader_WheelCheck.glsl";

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
    glBufferData( GL_ARRAY_BUFFER, wheel_check_vert_size + wheel_check_color_size, NULL, GL_STATIC_DRAW );
    //First part of array holds vertices
    glBufferSubData( GL_ARRAY_BUFFER, 0, wheel_check_vert_size, &wheel_check_pos[0] );
    //Second part of array hold colors (offset by sizeof(triangle))
    glBufferSubData( GL_ARRAY_BUFFER, wheel_check_vert_size, wheel_check_color_size, &wheel_check_color[0] );

    glEnableVertexAttribArray(GLvars.vpos_location);
    glEnableVertexAttribArray(GLvars.vcolor_location );

    glVertexAttribPointer( GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    glVertexAttribPointer( GLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(wheel_check_vert_size) );

    glBindVertexArray(0);
}

void WheelCheck::draw(tcg::mat4 Projection) {
    glUseProgram( GLvars.program );
    glBindVertexArray( GLvars.vao );
    tcg::mat4 M;
    M = tcg::Translate(0.0,0.0,0.0);
    tcg::vec2 t = tcg::vec2(0.0,0.0);


    glUniformMatrix4fv( GLvars.M_location, 1, GL_TRUE, Projection*M);

    glLineWidth(1.2);
    glDrawArrays( GL_TRIANGLE_STRIP, 0, wheel_check_pos.size());

    glBindVertexArray(0);
    glUseProgram(0);
}