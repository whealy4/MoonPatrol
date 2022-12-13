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
#include "common.h"


class Game {

public:
    Car *car;
    Ground *ground;
    Alien1 *alien1;
    std::vector <Wheel *> wheels;
    //left right bottom top of window
    tcg::vec4 screen_extents;

    Game();

    void init() {
        for (unsigned int i=0; i < wheels.size(); i ++){
            wheels[i]->gl_init();
        }
        car->gl_init();
        ground->gl_init();
        alien1->gl_init();

//        wheel->gl_init();
    }

    void draw(tcg::mat4 proj) {
        ground->draw(proj);
        car->draw(proj);
        alien1->draw(proj);
        for (unsigned int i=0; i < wheels.size(); i ++) {
            wheels[i]->draw(proj);
        }
    }

    void update() {
<<<<<<< Updated upstream
        car->update_state(screen_extents);
        alien1->update_state(screen_extents);
        ground->update_state(screen_extents);
        attachWheels();
=======
        if(car->jump_>5){
            car->update_state(screen_extents);
            alien1->update_state(screen_extents);
            
            car->state.cur_location+=vec2(0.0f,0.03f);
            car->state.cur_location-=car->state.velocity;
            alien1->state.cur_location-=car->state.velocity;
            
            attachWheels();
            car->jump_--;
        }else if(car->jump_>0){
            car->update_state(screen_extents);
            alien1->update_state(screen_extents);
            
            car->state.cur_location-=vec2(0.0f,0.03f);
            car->state.cur_location-=car->state.velocity;
            alien1->state.cur_location-=car->state.velocity;
            attachWheels();
            car->jump_--;
        }else{
            car->update_state(screen_extents);
            alien1->update_state(screen_extents);

            
            car->state.cur_location-=car->state.velocity;
            alien1->state.cur_location-=car->state.velocity;
            attachWheels();
        }
    std::vector <tcg::vec2> ground_pos_new;
    std::vector <tcg::vec2> ground_color_new;
//    float loc_x = -1.5;
//    float y_start = -1.0;
//    float x_step1, x_step2, y_step1, y_step2;
//            tcg::vec3 brown = tcg::vec3(0.5,0.35,0.0);
    for (int i=0; i<ground->ground_pos.size()-1; i++) {

//        // Random values to simulate jagged terrain
//        x_step1 = rand() % 10 / 100.;
//        x_step2 = rand() % 10 / 100.;
//        y_step1 = rand() % 10 / 1000. + 0.5;
//        y_step2 = rand() % 10 / 1000. + 0.5;

        // Create a 4 sided polygon for one part of the gorund
        ground_pos_new[i] = ground -> ground_pos[i+1];
//        ground_color_new[i] = ground -> ground_color[i+1];
//        ground -> ground_pos.push_back(tcg::vec2(loc_x, y_start));
//        ground -> ground_pos.push_back(tcg::vec2(loc_x+x_step1, y_start+y_step1));
//        ground -> ground_pos.push_back(tcg::vec2(loc_x +x_step2, y_start));
//        ground -> ground_pos.push_back(tcg::vec2(loc_x+x_step2, y_start+y_step2));

//                ground -> ground_color.push_back(brown);
//                ground -> ground_color.push_back(brown);
//                ground -> ground_color.push_back(brown);
//                ground -> ground_color.push_back(brown);
//        loc_x += x_step1;
    }
        game_over = testIntersections(car,ground);
>>>>>>> Stashed changes
    }

public:

//    void gl_init();
    bool testIntersections(Car *car, Ground *ground);
    void attachWheels();


};
#endif //ASTEROIDS_GAME_H
