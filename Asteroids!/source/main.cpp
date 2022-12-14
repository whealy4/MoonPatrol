#include "common.h"
using namespace std;

GLFWwindow* window;
Game *game;

Ship ship;
Asteroid asteroid;
//Car car;
//Ground ground;

//left right bottom top
tcg::vec4 extents;

static void error_callback(int error, const char* description)
{
  fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT)){
//      std::cout << "M: " <<ship.M;
        ship.rotateLeft();}

    if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT)){
//        std::cout << "pointing ";
        game->bullets.add(game->car->fireRight());
        ship.rotateRight();}
  if (key == GLFW_KEY_SPACE){
    if(action == GLFW_PRESS){
//        std::cout << "pointing ";
      asteroid.switch_dir();
      game->alien1->change_angle();
      game->bullets.add(game->car->fireUp());
      // ship.start_thruster();
      
    }
    if(action == GLFW_RELEASE){
      // ship.stop_thruster();
    }
  }
  if (key == GLFW_KEY_Z && action == GLFW_PRESS){
  }
}

void init(){
  
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
  glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);
    
//  ship.gl_init();
  asteroid.gl_init();
//  car.gl_init();
//  ground.gl_init();
    game->init();
  
}

//Call update function 30 times a second
void animate(){
  if(glfwGetTime() > 0.033){
    glfwSetTime(0.0);

//    ship.update_state(extents);
    asteroid.update_state(extents);
//    game->car->update_state(extents);
//    car.drive_on_ground(&ground);
    game->update();
    game->testIntersections(game->car, game->ground);
  }
}

int main(void)
{
  glfwSetErrorCallback(error_callback);
  
  if (!glfwInit())
    exit(EXIT_FAILURE);
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  glfwWindowHint(GLFW_SAMPLES, 10);
  
  window = glfwCreateWindow(1024, 768, "Asteroids!", NULL, NULL);
  game = new Game();
  if (!window){
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  
  glfwSetKeyCallback(window, key_callback);
  
  glfwMakeContextCurrent(window);
  gladLoadGL(glfwGetProcAddress);
  glfwSwapInterval(1);
  
  init();
    
//    std::cout << "pointing ";
  while (!glfwWindowShouldClose(window)){
    
    int FB_width, FB_height;
    glfwGetFramebufferSize(window, &FB_width, &FB_height);
    glViewport(0, 0, FB_width, FB_height);
    
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    game->screen_extents[0] = -1*(float)width/(float)height;
    game->screen_extents[1] = 1*(float)width/(float)height;
    game->screen_extents[2] = -1.0;
    game->screen_extents[3] = 1.0;
    
    //(left, right, bottom, top)        
    tcg::mat4 proj = tcg::Ortho2D(game->screen_extents[0],game->screen_extents[1],
                                  game->screen_extents[2],game->screen_extents[3]);
        
    animate();
    
    glClear(GL_COLOR_BUFFER_BIT);

    game->draw(proj);
    ship.draw(proj);
    asteroid.draw(proj);
//    car.draw(proj);
//    ground.draw(proj);

    glfwSwapBuffers(window);
    glfwPollEvents();
    
  }
  
  glfwDestroyWindow(window);
  
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
