#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Misc/global.h"
#include "Scene/scene.h"


GLFWwindow* window;
GLuint tex_handle;

void setGlfw();
void display(std::unique_ptr<uint8_t[]> & data);

void ErrorCallback(int, const char* err_str)
{
    std::cout << "GLFW Error: " << err_str << std::endl;
}

void setGlfw(){
  glfwSetErrorCallback(ErrorCallback);
  if (!glfwInit()) {
      std::cout<< "Couldn't init GLFW\n";
      exit(-1);
  }
  window = glfwCreateWindow(SCREEN_W, SCREEN_H, "CG", NULL, NULL);
  if (!window) {
      std::cout<<"Couldn't open window\n";
      exit(-1);
  }
  glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);
  glfwMakeContextCurrent(window);
  glfwWaitEventsTimeout(30);

  glGenTextures(1, &tex_handle);
  glBindTexture(GL_TEXTURE_2D, tex_handle);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void display(std::unique_ptr<uint8_t[]> & data){

  glfwMakeContextCurrent(window);
  while (!glfwWindowShouldClose(window)) {
    //glfwMakeContextCurrent(window);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_W, SCREEN_H, 0, GL_RGB, GL_UNSIGNED_BYTE, data.release());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     // Set up orphographic projection
    int window_width, window_height;
    glfwGetFramebufferSize(window, &window_width, &window_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, window_width, 0, window_height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    // Render whatever you want
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex_handle);
    glBegin(GL_QUADS);
      glTexCoord2d(0,1); glVertex2i(0, 0);
      glTexCoord2d(1,1); glVertex2i(SCREEN_W, 0);
      glTexCoord2d(1,0); glVertex2i(SCREEN_W,SCREEN_H);
      glTexCoord2d(0,0); glVertex2i(0, SCREEN_H);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    glfwSwapBuffers(window);
    //glfwPollEvents();
  }
}


int main(){
  std::unique_ptr<uint8_t[]> data(new uint8_t[SCREEN_W*SCREEN_H*3]);
  setGlfw();
  Scene scene;
  scene.sceneBuild();
  scene.render(data);
  
  display(data);
  return 1;
}

