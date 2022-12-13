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
        car->update_state(screen_extents);
        alien1->update_state(screen_extents);
        attachWheels();
    }

public:

//    void gl_init();
    bool testIntersections(Car *car, Ground *ground);
    void attachWheels();


};
#endif //ASTEROIDS_GAME_H
