// Asteroid.cpp
// Asteroids

#include "common.h"
#include <time.h>

Asteroid::Asteroid() {
    srand(time(NULL));
//    float rand_x = (float)rand()/(float)RAND_MAX * 2 - 1;
//    float rand_y = (float)rand()/(float)RAND_MAX * 2 - 1;
    float rand_x = 0.2;
    float rand_y = 0.4;
    state.cur_location = tcg::vec2(rand_x, rand_y);
    state.pointing = tcg::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    state.velocity = tcg::vec2(1.0f, 1.0f) / 500;
    state.angle = 0.00;
    angle_speed = 0.01;
    accel = 0.000000;
    rand_angle = (float)rand()/(float)RAND_MAX * 2 - 1;
    rand_angle = 0.5;
    int num_points = 20;

    asteroid_pos.resize(num_points + 1);
    asteroid_color.resize(num_points + 1);
    flame_offset = 4;

    // asteroid_pos[0] = tcg::vec2(0.0, 0.0);  asteroid_color[0] = tcg::vec3(1.0,1.0,1.0);
    // asteroid_pos[1] = tcg::vec2(1.0, 0.0);   asteroid_color[1] = tcg::vec3(1.0,1.0,1.0);
    // asteroid_pos[2] = tcg::vec2(1.0, 1.0);  asteroid_color[2] = tcg::vec3(1.0,1.0,1.0);
    // asteroid_pos[3] = tcg::vec2(0.0, 1.0);   asteroid_color[3] = tcg::vec3(1.0,1.0,1.0);

    float theta;
    float x_circle, y_circle, r_circle;
    float rand_num;
    r_circle = 0.05;

    for (int i = 0; i < num_points; i++) {
        rand_num = ((float)rand()/(float)RAND_MAX/75);
        theta = (i * 2 * M_PI) / (num_points - 1);
        std::cout << theta << std::endl;
        x_circle = r_circle * cos(theta) - rand_num;
        y_circle = r_circle * sin(theta) + rand_num;
        asteroid_pos[i] = tcg::vec2(x_circle, y_circle);
        asteroid_color[i] = tcg::vec3(1.0, 1.0, 1.0);
    }
};

void Asteroid::move_forward() {
    // // this->asteroid_M = tcg::Translate(0.001, 0.001, 0.0)*this->asteroid_M;
    // state.cur_location = tcg::Translate(0.001, 0.001, 0.0)*this->;

}

void Asteroid::update_state(tcg::vec4 extents) {
    // state.velocity = state.velocity + accel * (tcg::normalize(tcg::vec2(state.pointing.x, state.pointing.y)/100));
    // tcg::vec2 tmp_move = tcg::vec2(0.1, 1/10000);
    state.cur_location = state.cur_location + state.velocity;
    state.angle = state.angle + angle_speed;
}

void Asteroid::gl_init() {

    unsigned int asteroid_vert_size = asteroid_pos.size()*sizeof(tcg::vec2);
    unsigned int asteroid_color_size = asteroid_color.size()*sizeof(tcg::vec3);

    std::string vshader = shader_path + "vshader_Asteroid.glsl";
    std::string fshader = shader_path + "fshader_Asteroid.glsl";

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
    glBufferData( GL_ARRAY_BUFFER, asteroid_vert_size + asteroid_color_size, NULL, GL_STATIC_DRAW );
    //First part of array holds vertices
    glBufferSubData( GL_ARRAY_BUFFER, 0, asteroid_vert_size, &asteroid_pos[0] );
    //Second part of array hold colors (offset by sizeof(triangle))
    glBufferSubData( GL_ARRAY_BUFFER, asteroid_vert_size, asteroid_color_size, &asteroid_color[0] );

    glEnableVertexAttribArray(GLvars.vpos_location);
    glEnableVertexAttribArray(GLvars.vcolor_location );

    glVertexAttribPointer( GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    glVertexAttribPointer( GLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(asteroid_vert_size) );

    glBindVertexArray(0); 
}

tcg::mat4 Asteroid::gen_M() {
    mat4 M;
    M = tcg::Translate(state.cur_location.x, state.cur_location.y, 0.0) * tcg::RotateZ(state.angle);
//    M = tcg::Translate(state.cur_location.x, state.cur_location.y, 0.0) *
//        tcg::RotateZ(state.angle);
    return M;
}

void Asteroid::switch_dir() {
    state.angle = -1 * state.angle;
}

void Asteroid::draw(tcg::mat4 Projection){
    glUseProgram( GLvars.program );
    glBindVertexArray( GLvars.vao );

//    tcg::vec2 move = tcg::vec2(0.01, 0.01);

//    state.asteroid_M = tcg::RotateZ(rand_angle) * tcg::Translate(state.cur_location.x, state.cur_location.y, 0.0) * tcg::RotateZ(state.angle);// *
    state.asteroid_M = gen_M();
    glUniformMatrix4fv( GLvars.M_location, 1, GL_TRUE, Projection*state.asteroid_M);
    glLineWidth(1.2);
    glDrawArrays( GL_TRIANGLE_FAN, 0, 20);
    // glDrawArrays( GL_QUADS, 1, 1);
    // glDrawArrays( GL_QUADS, 2, 1);
    // glDrawArrays( GL_QUADS, 3, 1);



    glBindVertexArray(0);
    glUseProgram(0);
  
}