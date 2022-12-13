//
// Created by Tulane on 12/8/22.
//
#include "Common.h"

Wheel::Wheel(unsigned int index) {
    float width = 0.05 / 1.0;
    float height = 0.05 / 1.0;

    tcg::vec2 p0, p1, p2, p3;
    p0 = tcg::vec2(-width, -width);

    p1 = tcg::vec2(-width, height);
    p2 = tcg::vec2(width, -height);
    p3 = tcg::vec2(width, height);

    state.cur_location = tcg::vec2(0, -0.45);
    state.angle = 0.00;
    state.angle_speed = 0.01;

    wheel_vert.resize(4);

    wheel_vert[0] = p0; wheel_uv.push_back(tcg::vec2(0.0,0.0));
    wheel_vert[1] = p1; wheel_uv.push_back(tcg::vec2(0.0,1.0));
    wheel_vert[2] = p2; wheel_uv.push_back(tcg::vec2(1.0,0.0));
    wheel_vert[3] = p3; wheel_uv.push_back(tcg::vec2(1.0,1.0));

    wheel_bbox[0] = p0;
    wheel_bbox[1] = p3;
//
//    wheel_vert[4] = tcg::vec2(-0.0025, -1.0);
//    wheel_vert[5] = tcg::vec2(-0.0025, 0.0);
//    wheel_vert[6] = tcg::vec2(0.0025, -1.0);
//    wheel_vert[7] = tcg::vec2(0.0025, 0.0);

    std::string file_loc = "/Users/tulane/whealy/Comp_graphics/Asteroids!/sprites/wheel_1.png";
    unsigned error = lodepng::decode(wheel_im, im_width, im_height, file_loc.c_str());
    std::cout << im_width << " X wheel " << im_height << " image loaded\n";
}


void Wheel::gl_init() {

    unsigned int wheel_vert_size = wheel_vert.size()*sizeof(tcg::vec2);
    unsigned int wheel_uv_size = wheel_uv.size()*sizeof(tcg::vec2);

    std::string vshader = shader_path + "vshader_Texture.glsl";
    std::string fshader = shader_path + "fshader_Texture.glsl";

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

    glGenTextures( 1, &GLvars.wheel_texture );

    glBindTexture( GL_TEXTURE_2D, GLvars.wheel_texture );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, im_width, im_height,
                  0, GL_RGBA, GL_UNSIGNED_BYTE, &wheel_im[0]);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );


    glBindFragDataLocation(GLvars.program, 0, "fragColor");

    GLvars.vpos_location   = glGetAttribLocation(GLvars.program, "vPos");
    GLvars.vcolor_location = glGetAttribLocation(GLvars.program, "vTexCoord" );
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
    glBufferData( GL_ARRAY_BUFFER, wheel_vert_size + wheel_uv_size, NULL, GL_STATIC_DRAW );
    //First part of array holds vertices
    glBufferSubData( GL_ARRAY_BUFFER, 0, wheel_vert_size, &wheel_vert[0] );
    //Second part of array hold colors (offset by sizeof(triangle))
    glBufferSubData( GL_ARRAY_BUFFER, wheel_vert_size, wheel_uv_size, &wheel_uv[0] );

    glEnableVertexAttribArray(GLvars.vpos_location);
    glEnableVertexAttribArray(GLvars.vcolor_location );

    glVertexAttribPointer( GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    glVertexAttribPointer( GLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(wheel_vert_size) );

    glBindVertexArray(0);
}

void Wheel::draw(tcg::mat4 Projection){
    glUseProgram( GLvars.program );
    glBindVertexArray( GLvars.vao );

    tcg::mat4 M;
    // tcg::vec2 move = tcg::vec2(0.01, 0.01);
    // tcg::vec

    //state.cur_location.x += accel*state.velocity;

    // M = tcg::RotateZ(rand_angle) * tcg::Translate(state.cur_location.x, state.cur_location.y, 0.0) * tcg::RotateZ(state.angle);// *
    state.angle = state.angle + state.angle_speed;
    M = tcg::Translate(state.cur_location.x, state.cur_location.y, 0.0) * tcg::RotateZ(state.angle);


    glUniformMatrix4fv( GLvars.M_location, 1, GL_TRUE, Projection*M);

    glLineWidth(1.2);

    glBindTexture( GL_TEXTURE_2D, GLvars.wheel_texture );
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4);
//    glDrawArrays( GL_TRIANGLE_STRIP, 4, 4);
    // DRAW MINI RECTANGLE THING NOW



    glBindVertexArray(0);
    glUseProgram(0);
}