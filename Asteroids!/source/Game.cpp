//
// Created by Tulane on 12/9/22.
//

#include "Game.h"

using namespace tcg;

void Game::WheelGroundCollision(Wheel *w, Ground *g) {
    for (int idx=0; idx < g->relative_pos.size(); idx+=1) {
        if (abs(w->state.cur_location.x - g->relative_pos[idx].x) < 0.04) {
            w->state.cur_location.y = g->relative_pos[idx].y;
        }
    }
}

bool Game::CheckCollision(Car* &one, Hole* &two) // AABB - AABB collision
{


    if(one->state.cur_location.x +  (one->car_bbox[1].x- one->car_bbox[0].x)/2  >= two->state.cur_location.x &&
       two->state.cur_location.x + (two->hole_bbox[1].x -two->hole_bbox[0].x )/2>= one->state.cur_location.x){
         if(one->jump_ <= 0){
            return  true;
        }
        else {
            total_score += 1;
        }
    }
    return false;
//    if(one->state.cur_location.x < two->state.cur_location.x + two->hole_bbox[1].x &&
//       one->state.cur_location.x > two->state.cur_location.x) {
//        std::cout<< "hit hole" << std::endl;
//    }
}

bool Game::CheckRockCollision(Car* &one, Rock* &two) // AABB - AABB collision
{
//    std::cout<<"wheel_bbox[0]:"<<one->car_bbox[0]<<'\n';
//    std::cout<<"wheel_bbox[1]:"<<one->car_bbox[1]<<'\n' ;

    if(one->state.cur_location.x +  (one->car_bbox[1].x- one->car_bbox[0].x)/2 >= two->state.cur_location.x &&
       two->state.cur_location.x + (two->rock_bbox[1].x -two->rock_bbox[0].x )/2 >= one->state.cur_location.x){
        if(one->jump_ <= 0){
            return true;
        }
        else{
            total_score += 1;
        }
    }
    return false;
}
void Game::testIntersections(Car *c_inter, Ground *g_inter) {
    std::vector<vec2> car_boundaries;
    float c_width, c_height, g_width, g_height;

    c_width = c_inter->car_bbox[1].x - c_inter->car_bbox[0].x;
    c_height = c_inter->car_bbox[1].y - c_inter->car_bbox[0].y;

    g_width = g_inter->ground_bbox[1].x - g_inter->ground_bbox[0].x;
    g_height = g_inter->ground_bbox[1].y - g_inter->ground_bbox[0].y;

    tcg::vec2 c_p0, c_p1, c_p2, c_p3,
            g_p0, g_p1, g_p2, g_p3;
    c_p0 = vec2(c_inter->state.cur_location.x, c_inter->state.cur_location.y);
    c_p1 = vec2(c_inter->state.cur_location.x, c_inter->state.cur_location.y + c_height);
    c_p2 = vec2(c_inter->state.cur_location.x + c_width, c_inter->state.cur_location.y);
    c_p3 = vec2(c_inter->state.cur_location.x + c_width, c_inter->state.cur_location.y + c_height);

    g_p0 = vec2(g_inter->state.cur_location.x, g_inter->state.cur_location.y);
    g_p1 = vec2(g_inter->state.cur_location.x, g_inter->state.cur_location.y + g_height);
    g_p2 = vec2(g_inter->state.cur_location.x + g_width, g_inter->state.cur_location.y);
    g_p3 = vec2(g_inter->state.cur_location.x + g_width, g_inter->state.cur_location.y + g_height);


    for (unsigned int i = 0; i < holes.size(); i++) {
//        for (unsigned int j=0; j < wheels.size(); j ++) {
//        std::cout << holes[i]->state.cur_location.x << "\n";
        bool result = CheckCollision(car, holes[i]);
//            std::cout<<"wheels[j]:"<<wheels[j]->state.cur_location;
        if (result) {
            game_over = true;
        }
    }
    for (unsigned int j = 0; j < rocks.size(); j++) {
//        std::cout << rocks[j]->state.cur_location.x << "\n";

//        for (unsigned int j=0; j < wheels.size(); j ++) {
        bool result2 = CheckRockCollision(car, rocks[j]);
//            std::cout<<"wheels[j]:"<<wheels[j]->state.cur_location;
        if (result2) {
            game_over = true;
        }
    }
}
//            return false;

//    bool in_x = false;
//    bool in_y = false;
//
//    if (c_p0.x < g_p2.x && c_p2.x > g_p0.x) {
//        in_x = true;
//    }
//
//    if (c_p0.y < g_p1.y && c_p1.y > c_p0.y) {
//        in_y = true;
//    }
//
//    if (in_y && in_x) {
////        std::cout << "True" << std::endl;
//        return true;
//    } else {
////        std::cout << "False" << std::endl;
//        return false;
//    }

//    std::cout<<"car min"<<car_min<<"\ncar max"<<car_max<<"\nground min"<<ground_min<<"\nground max"<<ground_max<<std::endl;
//    std::cout<<"car pos ("<<c_inter->state.cur_location.x<<", "<<c_inter->state.cur_location.y << ")\n";

void Game::attachWheels() {
    for (unsigned int i=0; i < wheels.size(); i ++){
        wheels[i]->gl_init();
    }
    float y_change = 0.15;
    if (car->jump_ >0) {
        wheels[0]->state.cur_location = vec2(car->state.cur_location.x - 0.05, car->state.cur_location.y - y_change);
        wheels[1]->state.cur_location = vec2(car->state.cur_location.x, car->state.cur_location.y - y_change);
        wheels[2]->state.cur_location = vec2(car->state.cur_location.x + 0.05, car->state.cur_location.y - y_change);
    }
    else{
        wheels[0]->state.cur_location = vec2(car->state.cur_location.x - 0.05, wheels[0]->state.cur_location.y);
        wheels[1]->state.cur_location = vec2(car->state.cur_location.x, wheels[1]->state.cur_location.y);
        wheels[2]->state.cur_location = vec2(car->state.cur_location.x + 0.05, wheels[1]->state.cur_location.y);
    }
}


Game::Game() {
    lose = new GameOver(1);
    win = new GameOver(2);
    car = new Car();
    ground = new Ground();
//    alien1 = new Alien1();
//    hole = new Hole(0.0);

    holes.resize(5);
    holes[0] = new Hole(1.3);
    holes[1] = new Hole(2.6);
    holes[2] = new Hole(8.3);
    holes[3] = new Hole(12.9);
    holes[4] = new Hole(16.4);


    wheels.resize(3);
    wheelCheck = new WheelCheck();
    wheels[0] = new Wheel(1);
    wheels[1] = new Wheel(2);
    wheels[2] = new Wheel(3);

    rocks.resize(5);
    rocks[0] = new Rock(3.6);
    rocks[1] = new Rock(5.9);
    rocks[2] = new Rock(9.3);
    rocks[3] = new Rock(14.2);
    rocks[4] = new Rock(18.2);

    aliens.resize(count_enemies);
    for(unsigned int i=0;i<count_enemies;i++){
        aliens[i] = new Alien1();
    }
    std::string file_location =  "/Users/tulane/whealy/Comp_graphics/Asteroids!/sprites/game_over.png";
    unsigned error = lodepng::decode(game_over_im, go_width, go_height, file_location.c_str());
    std::cout << go_width << " X " << go_height << " game image loaded\n";

    game_over = false;

}

void Game::gl_init(){

    std::vector <vec2> pos(4);
    std::vector <vec2> uv(4);

    pos[0] = vec2(screen_extents[0],  screen_extents[3]);
    pos[1] = vec2(screen_extents[0],  screen_extents[2]);
    pos[2] = vec2(screen_extents[1],  screen_extents[3]);
    pos[3] = vec2(screen_extents[1],  screen_extents[2]);

    uv[0] = vec2(0.0,0.0);
    uv[1] = vec2(0.0,1.0);
    uv[2] = vec2(1.0,0.0);
    uv[3] = vec2(1.0,1.0);


    unsigned int vert_size = pos.size()*sizeof(vec2);
    unsigned int uv_size = uv.size()*sizeof(vec2);

    std::string vshader =  shader_path + "vshader_Texture.glsl";
    std::string fshader =  shader_path + "fshader_Texture.glsl";


    GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
    GLchar* fragment_shader_source = readShaderSource(fshader.c_str());

    GOGLvars.vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(GOGLvars.vertex_shader, 1, (const GLchar**) &vertex_shader_source, NULL);
    glCompileShader(GOGLvars.vertex_shader);
    check_shader_compilation(vshader, GOGLvars.vertex_shader);

    GOGLvars.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(GOGLvars.fragment_shader, 1, (const GLchar**) &fragment_shader_source, NULL);
    glCompileShader(GOGLvars.fragment_shader);
    check_shader_compilation(fshader, GOGLvars.fragment_shader);

    GOGLvars.program = glCreateProgram();
    glAttachShader(GOGLvars.program, GOGLvars.vertex_shader);
    glAttachShader(GOGLvars.program, GOGLvars.fragment_shader);

    glLinkProgram(GOGLvars.program);
    check_program_link(GOGLvars.program);
    glUseProgram(GOGLvars.program);

    glBindFragDataLocation(GOGLvars.program, 0, "fragColor");

    GOGLvars.vpos_location   = glGetAttribLocation(GOGLvars.program, "vPos");
    GOGLvars.vtex_location = glGetAttribLocation(GOGLvars.program, "vTexCoord" );
    GOGLvars.M_location = glGetUniformLocation(GOGLvars.program, "M" );

    glGenTextures( 1, &GOGLvars.texture );

    glBindTexture( GL_TEXTURE_2D, GOGLvars.texture );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, go_width, go_height,
                  0, GL_RGBA, GL_UNSIGNED_BYTE, &game_over_im[0]);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );


    // Create a vertex array object
    glGenVertexArrays( 1, &GOGLvars.vao );
    //Set GL state to use vertex array object
    glBindVertexArray( GOGLvars.vao );

    //Generate buffer to hold our vertex data
    glGenBuffers( 1, &GOGLvars.buffer );
    //Set GL state to use this buffer
    glBindBuffer( GL_ARRAY_BUFFER, GOGLvars.buffer );

    //Create GPU buffer to hold vertices and color
    glBufferData( GL_ARRAY_BUFFER, vert_size + uv_size, NULL, GL_STATIC_DRAW );
    //First part of array holds vertices
    glBufferSubData( GL_ARRAY_BUFFER, 0, vert_size, &pos[0] );
    //Second part of array hold colors (offset by sizeof(triangle))
    glBufferSubData( GL_ARRAY_BUFFER, vert_size, uv_size, &uv[0] );

    glEnableVertexAttribArray(GOGLvars.vpos_location);
    glEnableVertexAttribArray(GOGLvars.vtex_location );

    glVertexAttribPointer( GOGLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    glVertexAttribPointer( GOGLvars.vtex_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vert_size) );

    glBindVertexArray(0);

}

void Game::restart(){
    game_over=false;
    car->state.cur_location.x = 0.0;

}

//void Game::draw_game_over(mat4 proj){
//
//    glUseProgram(GOGLvars.program);
//    glBindVertexArray( GOGLvars.vao );
//    glBindBuffer( GL_ARRAY_BUFFER, GOGLvars.buffer );
//
//    glUniformMatrix4fv( GOGLvars.M_location, 1, GL_TRUE, proj);
//
//    glBindTexture( GL_TEXTURE_2D, GOGLvars.texture  );
//    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );
//
//    glBindVertexArray(0);
//    glBindBuffer( GL_ARRAY_BUFFER, 0);
//
////    std::cout<<"game over!!!";
//
////  glfwSetWindowShouldClose(window, GLFW_TRUE);
////    game_over = true;
//    close_window = true;
//}
//
