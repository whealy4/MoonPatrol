//
// Created by Tulane on 12/13/22.
//

#include "common.h"

Hole::Hole(float x_loc) {
    hole_pos.resize(4);
    hole_color.resize(4);
    vec2 p0, p1, p2, p3;
    float y_max = -0.13;

    state.cur_location = vec2(x_loc, -0.45);

    state.velocity = tcg::vec2(-0.01, 0.0);
    vec3 black = vec3(0.0,0.0,0.0);
    float height = (double)(rand() % 2) / 10 + 0.1;
    float width = (double)(rand() % 2) / 10 + 0.05;
    float height_rand = (double)(rand() % 10) / 100;
    float width_rand = (double)(rand() % 10) / 100;
    height += height_rand;
    width += width_rand;
//    float height = 29.;
//    float width = 0.5;
    std::cout <<"Height: " << height << " Width: " << width << "\n";
//    float height = rand() % 10 / 10;
//    float width = rand() % 10 / 10;
    p0 = vec2(x_loc, y_max);
    p1 = vec2(x_loc, y_max-height);
    p2 = vec2(x_loc+width, y_max);
    p3 = vec2(x_loc+width, y_max-height);

    hole_pos[0] = p0;
    hole_pos[1] = p1;
    hole_pos[2] = p2;
    hole_pos[3] = p3;

    hole_color[0] = black;
    hole_color[1] = black;
    hole_color[2] = black;
    hole_color[3] = black;

    hole_bbox[0] = p0;
    hole_bbox[1] = p3;
}

void Hole::update_state(vec4 extents) {
    state.cur_location = state.cur_location + state.velocity;
}


void Hole::gl_init() {

    unsigned int hole_vert_size = hole_pos.size()*sizeof(tcg::vec2);
    unsigned int hole_color_size = hole_color.size()*sizeof(tcg::vec3);

    std::string vshader = shader_path + "vshader_Hole.glsl";
    std::string fshader = shader_path + "fshader_Hole.glsl";

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
    glBufferData( GL_ARRAY_BUFFER, hole_vert_size + hole_color_size, NULL, GL_STATIC_DRAW );
    //First part of array holds vertices
    glBufferSubData( GL_ARRAY_BUFFER, 0, hole_vert_size, &hole_pos[0] );
    //Second part of array hold colors (offset by sizeof(triangle))
    glBufferSubData( GL_ARRAY_BUFFER, hole_vert_size, hole_color_size, &hole_color[0] );

    glEnableVertexAttribArray(GLvars.vpos_location);
    glEnableVertexAttribArray(GLvars.vcolor_location );

    glVertexAttribPointer( GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    glVertexAttribPointer( GLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(hole_vert_size) );

    glBindVertexArray(0);
}

void Hole::draw(tcg::mat4 Projection) {
    glUseProgram( GLvars.program );
    glBindVertexArray( GLvars.vao );
    tcg::mat4 M;
//    M = tcg::Translate(0.0,0.0,0.0);
    M = tcg::Translate(state.cur_location.x, state.cur_location.y, 0.0);
//    tcg::vec2 t = tcg::vec2(0.0,0.0);


    glUniformMatrix4fv( GLvars.M_location, 1, GL_TRUE, Projection*M);

    glLineWidth(1.2);
    glDrawArrays( GL_TRIANGLE_STRIP, 0, hole_pos.size());

    glBindVertexArray(0);
    glUseProgram(0);
}