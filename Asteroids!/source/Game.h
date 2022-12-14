//
// Created by Tulane on 12/9/22.
//

#ifndef ASTEROIDS_GAME_H
#define ASTEROIDS_GAME_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

#include <list>
#include <vector>
#include <utils/shader_process.h>
#include <path/path.h>

#include <utils/vec.h>
#include <utils/mat.h>
#include <utils/lodepng.h>
#include <utils/loadTexture.h>

//
#include "Car.h"
#include "Ground.h"
#include "Alien1.h"
#include "Wheel.h"
#include "WheelCheck.h"
#include "common.h"
#include "Bullets.h"
#include "Hole.h"
#include "Rock.h"
#include "GameOver.h"


class Game {

public:
    Car *car;
    GameOver *win, *lose;
    Ground *ground;
    bool done;
//    Alien1 *alien1;
    void gl_init();
    std::chrono::time_point<std::chrono::system_clock> start_time;
    std::chrono::time_point<std::chrono::system_clock> end_time;
    bool close_window = false;
    std::vector <Rock *> rocks;
    std::vector <Wheel *> wheels;
    std::vector <Alien1 *> aliens;
    std::vector <Hole *> holes;
    Bullets bullets;
    WheelCheck *wheelCheck;
    Hole *hole;
    //left right bottom top of window
    tcg::vec4 screen_extents;
    int count_enemies = 10;
    int activated = 0;
    int shown = 0;
    int total_score = 0;
    bool game_over;
    std::vector<unsigned char> game_over_im;
    unsigned go_width, go_height;
    Game();
    float randvec(float min, float max){
        float p1 = (max-min)*((float)rand()/(float)RAND_MAX) - ((max-min)/2.0);
        //  float p2 = (max-min)*((float)rand()/(float)RAND_MAX) - ((max-min)/2.0);
        return p1;
    }

    struct {
        GLuint vao;           //Vertex array object
        GLuint program;       //shader program
        GLuint buffer;        //Vertex buffer objects
        GLuint vertex_shader, fragment_shader;  //Shaders
        GLint vpos_location, vtex_location;   //reference to pos and color in shaders
        GLint M_location;     //Reference to matrix in shader
        GLuint texture;
    } GOGLvars;

    void init() {
        done = false;
        start_time = std::chrono::system_clock::now();
        win->gl_init(); lose->gl_init();
        for (unsigned int i=0; i < wheels.size(); i ++){
            wheels[i]->gl_init();
        }
        for (unsigned int i=0; i < holes.size(); i ++){
            holes[i]->gl_init();
        }
        for (unsigned int i=0; i < rocks.size(); i ++){
            rocks[i]->gl_init();
        }
        car->gl_init();
        ground->gl_init();
//        alien1->gl_init();
        wheelCheck->gl_init();
        bullets.gl_init();
//        hole->gl_init();
        for (unsigned int i=0;i<count_enemies;i++) {
            aliens[i]->gl_init();
        }

//        wheel->gl_init();
    }

    void draw(tcg::mat4 proj) {
        for (unsigned int i=0; i < rocks.size(); i ++){
            rocks[i]->draw(proj);
        }
        ground->draw(proj);
        for (unsigned int i=0; i < holes.size(); i ++){
            holes[i]->draw(proj);
        }
//        hole->draw(proj);

        car->draw(proj);
//        alien1->draw(proj);
        bullets.draw(proj);
        for (unsigned int i=0; i < wheels.size(); i ++) {
            wheels[i]->draw(proj);
        }
        for (unsigned int i=0;i<count_enemies;i++) {
            if(aliens[i]->active==true) {
                aliens[i]->draw(proj);
            }
        }

        if (game_over) {
//            total_score += bullets.value.score;
//            lose->draw(proj);
//            end_time = std::chrono::system_clock::now();
//            auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
//            long long duration = milliseconds.count();
//            if (!done) {
//                total_score -= 500;
//                done = true;
//                std::cout << "Final Score: " << total_score << std::endl;
//            }
        }



        if (ground->state.cur_location.x < -21.0) {
            win->draw(proj);
            end_time = std::chrono::system_clock::now();
            auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
            long long duration = milliseconds.count();
            if (!done) {
                total_score -= (int)duration / 100;
                std::cout << "Final Score: " << total_score << std::endl;
                done = true;
            }

        }
//        wheelCheck->draw(proj);
//        car->car_bbox[0].x += 1;

//        std::cout << "car bbox: " << car->car_bbox[0].x << "\n";
        float p = rand() % 1000;

        float t = 0.1;

        if(activated<count_enemies) {
            if(p<5 && shown < 3) {
                aliens[activated]->active = true;
                activated++;
                shown=0;
                for(int i=0; i<10;i++) {
                    if(aliens[i]->active == true){
                        shown++;
                    }
                }
            }
        }
//        gameOver->draw(proj);
}



    void update() {
//        std::cout << ground->state.cur_location.x << std::endl;
//        std::c out << "Total Score: " << total_score << std::endl;
        for(int i=0; i<holes.size();i++){
            holes[i]->state.cur_location -= car->state.velocity;
        }
        for (unsigned int i=0; i <wheels.size(); i++) {
            WheelGroundCollision(wheels[i], ground);
        }
//        car->update_state(screen_extents);
//        alien1->update_state(screen_extents);
//        ground->update_state(screen_extents);
        bullets.update_state(screen_extents, aliens);
        for (unsigned int i=0; i < rocks.size(); i ++){
//            rocks[i]->update_state(screen_extents);
            rocks[i]->state.cur_location -= car->state.velocity;
        }
        for (unsigned int i=0; i < holes.size(); i ++){
            holes[i]->update_state(screen_extents);
        }
        if (car->jump_>25){
            car->update_state(screen_extents);
            car->state.cur_location+=vec2(0.0f, 0.01f);
            car->state.cur_location-=car->state.velocity;
            attachWheels();
            car->jump_--;
        } else if (car->jump_>0){
            car->update_state(screen_extents);
            car->state.cur_location-=vec2(0.0f, 0.01f);
            car->state.cur_location-=car->state.velocity;
            attachWheels();
            car->jump_--;
        } else {
            car->update_state(screen_extents);
            car->state.cur_location -= car->state.velocity;
            attachWheels();
        }
        for(unsigned int i=0; i<count_enemies;i++){
            if(aliens[i]->active == true){
                if(aliens[i]->state.cur_location.y < 0.0){
                    aliens[i]->state.velocity += vec2(-randvec(-0.2,0.2)*aliens[i]->state.cur_location.x, -randvec(-0.2,0.2)*aliens[i]->state.cur_location.y);
                    aliens[i]->state.cur_location.y = 0.0;
                }
                if(aliens[i]->state.cur_location.y > 0.8){
                    aliens[i]->state.velocity += vec2(-randvec(-0.2,0.2)*aliens[i]->state.cur_location.x, -randvec(-0.2,0.2)*aliens[i]->state.cur_location.y);
                    aliens[i]->state.cur_location.y = 0.8;
                }
                if(aliens[i]->state.cur_location.x < car->state.cur_location.x - 1){
                    aliens[i]->state.velocity += vec2(-randvec(-0.2,0.2)*aliens[i]->state.cur_location.x, -randvec(-0.2,0.2)*aliens[i]->state.cur_location.y);
                }
                if(aliens[i]->state.cur_location.x < car->state.cur_location.x + 1){
                    aliens[i]->state.velocity += vec2(-randvec(-0.2,0.2)*aliens[i]->state.cur_location.x, -randvec(-0.2,0.2)*aliens[i]->state.cur_location.y);
                }
                bullets.update_state(screen_extents, aliens);
                aliens[i]->update_state(screen_extents);
            }
        }
//        hole->update_state(screen_extents);
//        wheelCheck->update_state(screen_extents);
        attachWheels();

        ground->state.cur_location -= car->state.velocity;
        testIntersections(car,ground);
    }

public:

//    void gl_init();

    void testIntersections(Car *c_inter, Ground *g_inter);
    void attachWheels();
    bool CheckCollision(Car* &one, Ground* &two);
//    void draw_game_over(mat4 proj);
    void WheelGroundCollision(Wheel *w, Ground *g);
    bool CheckCollision(Car* &one, Hole* &two) ;
    bool CheckRockCollision(Car* &one, Rock* &two);
    void restart();

};
#endif //ASTEROIDS_GAME_H
