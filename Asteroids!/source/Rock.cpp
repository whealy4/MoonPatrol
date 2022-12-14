//
// Created by Tulane on 12/13/22.
//

#include "common.h"

using namespace tcg;

Rock::Rock(float x_start) {
    vec2 p0, p1, p2, p3;
    vec3 green = vec3(0.25, 0.15, 0.0);
    state.velocity = vec2(0.0, 0.0);
    float y_start, y_step1, y_step2, x_step;
//    x_start = 0.0;
    y_start = -0.6;
//    y_step1 = 0.1;
//    y_step2 = 0.04;
//    x_step = 0.01;
    y_step1 = (double)(rand() % 2)/ 10 + 0.02;
    y_step2 = (double)(rand() % 2)/ 10 + 0.02;
    x_step = (double)(rand() % 2)/ 10 + 0.03;
    float y_step1_rand = (double)(rand() % 10) / 100;
    float y_step2_rand = (double)(rand() % 10) / 100;
    float x_step_rand = (double)(rand() % 10) / 100;
    y_step1 += y_step1_rand;
    y_step2 += y_step2_rand;
    x_step += x_step_rand;

    p0 = vec2(0, y_start);
    p1 = vec2(0, y_start + y_step1);
    p2 = vec2(x_step, y_start);
    p3 = vec2(x_step, y_start+y_step2);

    rock_pos.push_back(p0);
    rock_pos.push_back(p1);
    rock_pos.push_back(p2);
    rock_pos.push_back(p3);

    rock_color.push_back(green);
    rock_color.push_back(green);
    rock_color.push_back(green);
    rock_color.push_back(green);

    rock_bbox[0] = p0;
    rock_bbox[1] = p3;

    state.cur_location = vec2(x_start, 0.0);
}
void Rock::update_state(tcg::vec4 extents) {
    state.cur_location = state.cur_location + state.velocity;
}

void Rock::gl_init() {

    unsigned int rock_vert_size = rock_pos.size()*sizeof(tcg::vec2);
    unsigned int rock_color_size = rock_color.size()*sizeof(tcg::vec3);

    std::string vshader = shader_path + "vshader_Rock.glsl";
    std::string fshader = shader_path + "fshader_Rock.glsl";

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
    glBufferData( GL_ARRAY_BUFFER, rock_vert_size + rock_color_size, NULL, GL_STATIC_DRAW );
    //First part of array holds vertices
    glBufferSubData( GL_ARRAY_BUFFER, 0, rock_vert_size, &rock_pos[0] );
    //Second part of array hold colors (offset by sizeof(triangle))
    glBufferSubData( GL_ARRAY_BUFFER, rock_vert_size, rock_color_size, &rock_color[0] );

    glEnableVertexAttribArray(GLvars.vpos_location);
    glEnableVertexAttribArray(GLvars.vcolor_location );

    glVertexAttribPointer( GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    glVertexAttribPointer( GLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(rock_vert_size) );

    glBindVertexArray(0);
}

void Rock::draw(tcg::mat4 Projection) {
    glUseProgram( GLvars.program );
    glBindVertexArray( GLvars.vao );
    tcg::mat4 M;
//    M = tcg::Translate(0.0,0.0,0.0);
    M = tcg::Translate(state.cur_location.x, state.cur_location.y, 0.0);
//    tcg::vec2 t = tcg::vec2(0.0,0.0);


    glUniformMatrix4fv( GLvars.M_location, 1, GL_TRUE, Projection*M);

    glLineWidth(1.2);
    glDrawArrays( GL_TRIANGLE_STRIP, 0, rock_pos.size());

    glBindVertexArray(0);
    glUseProgram(0);
}