//
// Created by Tulane on 12/11/22.
//

#include "common.h"
#include "Alien1.h"
#include <chrono>

using namespace tcg;

Alien1::Alien1() {
    state.cur_location = vec2(0.0, 0.0);
    state.pointing = vec4(1.0, 1.0, 0.0, 0.0);
    state.velocity = vec2(0.01, 0.0);
    state.angle = M_PI/4;
    state.accel = 0.0001;
//    state.start_time = (long int)std::chrono::duration_cast<std::chrono::milliseconds>
//                       (std::chrono::system_clock::now().time_since_epoch());
    state.start_time = std::chrono::system_clock::now();


    float width = 0.016 * 3;
    float height = 0.016 * 3;

    vec2 p0, p1, p2, p3;

    p0 = vec2(-width/2., -width/2.);

    p1 = vec2(-width/2., height);
    p2 = vec2(width/2., -width/2.);
    p3 = vec2(width/2., height);

    alien1_vert.push_back(p0); alien1_uv.push_back(tcg::vec2(0.0,0.0));
    alien1_vert.push_back(p1); alien1_uv.push_back(tcg::vec2(0.0,1.0));
    alien1_vert.push_back(p2); alien1_uv.push_back(tcg::vec2(1.0,0.0));
    alien1_vert.push_back(p3); alien1_uv.push_back(tcg::vec2(1.0,1.0));

    alien1_bbox[0] = p0;
    alien1_bbox[1] = p3;

    std::string file_loc = "/Users/tulane/whealy/Comp_graphics/Asteroids!/sprites/default_car.png";
    unsigned error = lodepng::decode(alien1_im, im_width, im_height, file_loc.c_str());
    std::cout << im_width << " X " << im_height << " image loaded\n";
}

void Alien1::update_state(vec4 extents) {
    float damping = 0.8;
    state.end_time = std::chrono::system_clock::now();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(state.end_time - state.start_time);
    long long duration = milliseconds.count();

    if (duration > 3000) {
        state.pointing.x = -state.pointing.x;
        state.pointing.y = state.pointing.y;
        state.start_time = std::chrono::system_clock::now();
    }
    if (length(state.velocity) > 0.0100055) {
        state.velocity = damping * state.velocity;
    }
    state.velocity = state.velocity +
                      state.accel * normalize(tcg::vec2(state.pointing.x, state.pointing.y));
//    std::cout << "velocity (" << state.velocity.x << ", " << state.velocity.y << ")\n" <<
//    "length: " << length(state.velocity) << std::endl;
    state.cur_location = state.cur_location + state.velocity;
    if(state.cur_location.x < extents[0] || state.cur_location.x > extents[1]){
//        state.cur_location.x = -state.cur_location.x;
        state.velocity.x = -state.velocity.x;
//        state.pointing.x = -state.pointing.x;
    }
    if(state.cur_location.y < -0.0 ||state.cur_location.y > extents[3]) {
//        state.cur_location.y = -state.cur_location.y;
        state.velocity.y = -state.velocity.y;
//        state.pointing.y = -state.pointing.y;
    }
//    change_angle();
}

void Alien1::change_angle() {
//    float ang = 0.2;
//    state.pointing = vec4(state.pointing.x-state.angle, state.pointing.y-state.angle, 0.0, 0.0);
//    std::cout<<"\npointing: (" << state.pointing.x << ", " << state.pointing.y << ")";
//    if (state.angle < -3.15) {
//        state.angle += 0.5;
//    }
//    if (state.angle > 3.15) {
//        state.angle -= 0.5;
//    }

}

mat4 Alien1::activate() {
    mat4 M;
//    state.velocity = state.velocity +
//                     0.00000001*normalize(tcg::vec2(state.pointing.x, state.pointing.y));
    state.alien1_M = tcg::Translate(state.cur_location.x, state.cur_location.y, 0.0);
//    std::cout <<"\nvel" << state.velocity.x;

    return M;
}

void Alien1::gl_init() {

    unsigned int alien1_vert_size = alien1_vert.size()*sizeof(tcg::vec2);
    unsigned int alien1_uv_size = alien1_uv.size()*sizeof(tcg::vec2);

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
    glUseProgram(GLvars.program);

    glGenTextures( 1, &GLvars.alien1_texture );

    glBindTexture( GL_TEXTURE_2D, GLvars.alien1_texture );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, im_width, im_height,
                  0, GL_RGBA, GL_UNSIGNED_BYTE, &alien1_im[0]);
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
    glBufferData( GL_ARRAY_BUFFER, alien1_vert_size + alien1_uv_size, NULL, GL_STATIC_DRAW );
    //First part of array holds vertices
    glBufferSubData( GL_ARRAY_BUFFER, 0, alien1_vert_size, &alien1_vert[0] );
    //Second part of array hold colors (offset by sizeof(triangle))
    glBufferSubData( GL_ARRAY_BUFFER, alien1_vert_size, alien1_uv_size, &alien1_uv[0] );

    glEnableVertexAttribArray(GLvars.vpos_location);
    glEnableVertexAttribArray(GLvars.vcolor_location );

    glVertexAttribPointer( GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    glVertexAttribPointer( GLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(alien1_vert_size) );

    glBindVertexArray(0);
}


void Alien1::draw(tcg::mat4 Projection){
    glUseProgram( GLvars.program );
    glBindVertexArray( GLvars.vao );

    tcg::mat4 M;

//    state.alien1_M = activate();
    M = activate();
//
//    M = tcg::Translate(state.cur_location.x, state.cur_location.y, 0.0);

    glUniformMatrix4fv( GLvars.M_location, 1, GL_TRUE, Projection*state.alien1_M);

    glLineWidth(1.2);

    glBindTexture( GL_TEXTURE_2D, GLvars.alien1_texture );
    glDrawArrays( GL_TRIANGLE_STRIP, 0, alien1_vert.size() );



    glBindVertexArray(0);
    glUseProgram(0);
}