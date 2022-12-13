// Ground.cpp
// Asteroids

#include "common.h"
#include <cstdlib>

Ground::Ground() {
    int num_points = 50;
    float loc_x = -1.0;
    float y_start = -0.5;
    float x_step1, x_step2, y_step1, y_step2;
    tcg::vec3 brown = tcg::vec3(0.5,0.35,0.0);
    tcg::vec3 red = tcg::vec3(1.0, 0.0, 0.0);

    float hole_step_x = 0.5;
    float hole_step_y = 0.5;
    for (int i=0; i<num_points; i++) {

        // Random values to simulate jagged terrain
        x_step1 = rand() % 10 / 100.;
        x_step2 = rand() % 10 / 100.;
        y_step1 = rand() % 10 / 1000. + 0.5;
        y_step2 = rand() % 10 / 1000. + 0.5;

        // Create a 4 sided polygon for one part of the ground
        ground_pos.push_back(tcg::vec2(loc_x, y_start));
        ground_pos.push_back(tcg::vec2(loc_x+x_step1, y_start+y_step1));
        ground_pos.push_back(tcg::vec2(loc_x +x_step2, y_start));
        ground_pos.push_back(tcg::vec2(loc_x+x_step2, y_start+y_step2));

        if (i > num_points / 5) {
            ground_pos.push_back(tcg::vec2(loc_x+x_step1, -1* (y_start+y_step1)));
            ground_pos.push_back(tcg::vec2(loc_x, y_start));
            ground_pos.push_back(tcg::vec2(loc_x+x_step2, -1*(y_start+y_step2)));
            ground_pos.push_back(tcg::vec2(loc_x +x_step2, y_start));



//            ground_pos.push_back(tcg::vec2(loc_x, y_start));
//            ground_pos.push_back(tcg::vec2(loc_x+x_step1, -1* (y_start+y_step1)));
//            ground_pos.push_back(tcg::vec2(loc_x +x_step2, y_start));
//            ground_pos.push_back(tcg::vec2(loc_x+x_step2, -1*(y_start+y_step2)));
            ground_color.push_back(red);
            ground_color.push_back(red);
            ground_color.push_back(red);
            ground_color.push_back(red);
            loc_x += x_step1;
        }
        else {
            ground_pos.push_back(tcg::vec2(loc_x, y_start));
            ground_pos.push_back(tcg::vec2(loc_x+x_step1, y_start+y_step1));
            ground_pos.push_back(tcg::vec2(loc_x +x_step2, y_start));
            ground_pos.push_back(tcg::vec2(loc_x+x_step2, y_start+y_step2));

            ground_color.push_back(brown);
            ground_color.push_back(brown);
            ground_color.push_back(brown);
            ground_color.push_back(brown);
            loc_x += x_step1;
        }
//        ground_color.push_back(brown);
//        ground_color.push_back(brown);
//        ground_color.push_back(brown);
//        ground_color.push_back(brown);
//        loc_x += x_step1;
    }

    ground_bbox[0] = ground_pos[0];
    ground_bbox[1] = ground_pos.back();



//    for (int i=0, inc=3; i<= num_points; i+=inc) {
//        rand_inc = rand() / 1000 - 0.05;
//        ground_pos[i] = tcg::vec2(loc_x, y_axis+y_step);
//        ground_pos[i+1] = tcg::vec2(loc_x+x_step, y_axis-y_step);
//        ground_pos[i+2] = tcg::vec2(loc_x+2*x_step+rand_inc, y_axis+y_step);
//        ground_color[i] = tcg::vec3(0.5, 0.35, 0.0);
//        ground_color[i+1] = tcg::vec3(0.5, 0.35, 0.0);
//        ground_color[i+2] = tcg::vec3(0.5, 0.35, 0.0);
//        loc_x += 2 * (x_step+rand_inc);
//    }

};

void Ground::gl_init() {

    unsigned int ground_vert_size = ground_pos.size()*sizeof(tcg::vec2);
    unsigned int ground_color_size = ground_color.size()*sizeof(tcg::vec3);

    std::string vshader = shader_path + "vshader_Ground.glsl";
    std::string fshader = shader_path + "fshader_Ground.glsl";

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
    glBufferData( GL_ARRAY_BUFFER, ground_vert_size + ground_color_size, NULL, GL_STATIC_DRAW );
    //First part of array holds vertices
    glBufferSubData( GL_ARRAY_BUFFER, 0, ground_vert_size, &ground_pos[0] );
    //Second part of array hold colors (offset by sizeof(triangle))
    glBufferSubData( GL_ARRAY_BUFFER, ground_vert_size, ground_color_size, &ground_color[0] );

    glEnableVertexAttribArray(GLvars.vpos_location);
    glEnableVertexAttribArray(GLvars.vcolor_location );

    glVertexAttribPointer( GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    glVertexAttribPointer( GLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(ground_vert_size) );

    glBindVertexArray(0);
}

void Ground::draw(tcg::mat4 Projection) {
    glUseProgram( GLvars.program );
    glBindVertexArray( GLvars.vao );
    tcg::mat4 M;
    M = tcg::Translate(0.0,0.0,0.0);
    tcg::vec2 t = tcg::vec2(0.0,0.0);


    glUniformMatrix4fv( GLvars.M_location, 1, GL_TRUE, Projection*M);

    glLineWidth(1.2);
    glDrawArrays( GL_TRIANGLE_STRIP, 0, ground_pos.size());

    glBindVertexArray(0);
    glUseProgram(0);
}