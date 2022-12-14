//
// Created by Tulane on 12/9/22.
//

#include "Game.h"

using namespace tcg;

bool Game::WheelGroundCollision(Wheel *w, Ground *g) {
//    std::cout<< "ground pos: " << g->relative_pos[0] << ", " << g->relative_pos[5] << "\n";
    for (int idx=1, increment=1; idx < g->ground_pos.size(); idx+=increment) {
//        std::cout << "wheel loc: " << w->state.cur_location.x << "vs. ground loc: " <<
//        g->ground_pos[idx].x << "\n";
        if (abs(w->state.cur_location.x - g->relative_pos[idx].x) < 0.04    ) {
//            std::cout << "YAY" << "\n";
            w->state.cur_location.y = g->relative_pos[idx].y;
            if (w->state.cur_location.y > -0.5) {
//                std::cout << "wheel above: (" << w->state.cur_location.x << ", " << w->state.cur_location.y << ")\n";
//                std::cout << "ground pos: (" << g->relative_pos[idx].x << ", " << g->relative_pos[idx].y << ")\n";
            }
        }
    }
}
bool Game::testIntersections(Car *c_inter, Ground *g_inter) {
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
    c_p2 = vec2(c_inter->state.cur_location.x+c_width, c_inter->state.cur_location.y);
    c_p3 = vec2(c_inter->state.cur_location.x+c_width, c_inter->state.cur_location.y + c_height);

    g_p0 = vec2(g_inter->state.cur_location.x, g_inter->state.cur_location.y);
    g_p1 = vec2(g_inter->state.cur_location.x, g_inter->state.cur_location.y + g_height);
    g_p2 = vec2(g_inter->state.cur_location.x+g_width, g_inter->state.cur_location.y);
    g_p3 = vec2(g_inter->state.cur_location.x+g_width, g_inter->state.cur_location.y + g_height);

    bool in_x = false;
    bool in_y = false;

    if (c_p0.x < g_p2.x && c_p2.x > g_p0.x) {
        in_x = true;
    }

    if (c_p0.y < g_p1.y && c_p1.y > c_p0.y) {
        in_y = true;
    }

    if (in_y && in_x) {
//        std::cout << "True" << std::endl;
        return true;
    }
    else {
//        std::cout << "False" << std::endl;
        return false;
    }

//    std::cout<<"car min"<<car_min<<"\ncar max"<<car_max<<"\nground min"<<ground_min<<"\nground max"<<ground_max<<std::endl;
//    std::cout<<"car pos ("<<c_inter->state.cur_location.x<<", "<<c_inter->state.cur_location.y << ")\n";

}

void Game::attachWheels() {
    for (unsigned int i=0; i < wheels.size(); i ++){
        wheels[i]->gl_init();
    }
    float y_change = 0.05;
    wheels[0]->state.cur_location = vec2(car->state.cur_location.x - 0.05, wheels[0]->state.cur_location.y);
    wheels[1]->state.cur_location = vec2(car->state.cur_location.x, wheels[1]->state.cur_location.y);
    wheels[2]->state.cur_location = vec2(car->state.cur_location.x + 0.05, wheels[1]->state.cur_location.y);


//    wheels[0]->state.cur_location = cur_location
//    wheel->state.cur_location = car->state.cur_location;
}


Game::Game() {
    car = new Car();
    ground = new Ground();
    alien1 = new Alien1();
    wheels.resize(3);
    wheelCheck = new WheelCheck();
    wheels[0] = new Wheel(1);
    wheels[1] = new Wheel(2);
    wheels[2] = new Wheel(3);
}
