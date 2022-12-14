// Car.cpp
// Asteroids

#include "common.h"
//#include "path/path.h"
#include <time.h>

Car::Car() {
//    class Ground;
    srand(time(NULL));
    float rand_x = (float)rand()/(float)RAND_MAX * 2 - 1;
    float rand_y = (float)rand()/(float)RAND_MAX * 2 - 1;
//    state.cur_location = tcg::vec2(rand_x, rand_y);
    state.pointing = tcg::vec4(1.0f, 0.0f, 0.0f, 0.0f);
    state.velocity = tcg::vec2(0.0f, 0.0f);
    state.angle = 0.00;
    angle_speed = 0.01;
    accel = 0.00000001;
    int num_points = 6;

//    car_pos.resize(num_points);
//    car_color.resize(num_points);

    // Car img 32x19
    float width = 0.032 * 8;
    float height = 0.003 * 8;

    tcg::vec2 p0, p1, p2, p3;
    p0 = tcg::vec2(-width/2., -width/2.);

    p1 = tcg::vec2(-width/2., height);
    p2 = tcg::vec2(width/2., -width/2.);
    p3 = tcg::vec2(width/2., height);

    state.cur_location = tcg::vec2(-1.2, -0.4);

    Car_vert.push_back(p0); Car_uv.push_back(tcg::vec2(0.0,0.0));
    Car_vert.push_back(p1); Car_uv.push_back(tcg::vec2(0.0,1.0));
    Car_vert.push_back(p2); Car_uv.push_back(tcg::vec2(1.0,0.0));
    Car_vert.push_back(p3); Car_uv.push_back(tcg::vec2(1.0,1.0));

    car_bbox[0] = p0;
    car_bbox[1] = p3;

//    std::string file_location = source_path + "sprites/default_car.png";
    std::string file_loc = "/Users/tulane/whealy/Comp_graphics/Asteroids!/sprites/default_car.png";
    unsigned error = lodepng::decode(car_im, im_width, im_height, file_loc.c_str());
    std::cout << im_width << " X " << im_height << " image loaded\n";
};

void Car::move_forward() {
    state.velocity = state.velocity + 
                     0.01*normalize(tcg::vec2(state.pointing.x, state.pointing.y));

}

void Car::update_state(tcg::vec4 extents) {
    state.cur_location = state.cur_location + state.velocity;
    if(state.cur_location.x < extents[0] || state.cur_location.x > extents[1]){
        state.cur_location.x = -state.cur_location.x;
    }
    if(state.cur_location.y < extents[2] ||state.cur_location.y > extents[3]) {
        state.cur_location.y = -state.cur_location.y;
    }
//    std::cout << "cur location: (" << state.cur_location.x << ", " << state.cur_location
}

void Car::drive_on_ground(Ground* ground) {
//    state.cur_location = state.cur_location + state.velocity +
//                         0.1 * normalize(tcg::vec2(state.pointing.x, state.pointing.y));
//    if (state.cur_location.y < ground->ground_pos[state.cur_location.x].y) {
//        state.cur_location.y = ground->ground_pos[state.cur_location.x].y;
//    }
}

void Car::gl_init() {

    unsigned int car_vert_size = Car_vert.size()*sizeof(tcg::vec2);
    unsigned int car_uv_size = Car_uv.size()*sizeof(tcg::vec2);

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
//    glUseProgram(GLvars.program);

    glGenTextures( 1, &GLvars.car_texture );

    glBindTexture( GL_TEXTURE_2D, GLvars.car_texture );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, im_width, im_height,
                  0, GL_RGBA, GL_UNSIGNED_BYTE, &car_im[0]);
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
    glBufferData( GL_ARRAY_BUFFER, car_vert_size + car_uv_size, NULL, GL_STATIC_DRAW );
    //First part of array holds vertices
    glBufferSubData( GL_ARRAY_BUFFER, 0, car_vert_size, &Car_vert[0] );
    //Second part of array hold colors (offset by sizeof(triangle))
    glBufferSubData( GL_ARRAY_BUFFER, car_vert_size, car_uv_size, &Car_uv[0] );

    glEnableVertexAttribArray(GLvars.vpos_location);
    glEnableVertexAttribArray(GLvars.vcolor_location );

    glVertexAttribPointer( GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    glVertexAttribPointer( GLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(car_vert_size) );

    glBindVertexArray(0); 
}


void Car::draw(tcg::mat4 Projection){
    glUseProgram( GLvars.program );
    glBindVertexArray( GLvars.vao );

    tcg::mat4 M;
    // tcg::vec2 move = tcg::vec2(0.01, 0.01);
    // tcg::vec

    //state.cur_location.x += accel*state.velocity;

    // M = tcg::RotateZ(rand_angle) * tcg::Translate(state.cur_location.x, state.cur_location.y, 0.0) * tcg::RotateZ(state.angle);// *
    M = tcg::Translate(state.cur_location.x, state.cur_location.y, 0.0);


    glUniformMatrix4fv( GLvars.M_location, 1, GL_TRUE, Projection*M);

    glLineWidth(1.2);

    glBindTexture( GL_TEXTURE_2D, GLvars.car_texture );
    glDrawArrays( GL_TRIANGLE_STRIP, 0, Car_vert.size() );



    glBindVertexArray(0);
    glUseProgram(0);
}