#ifndef DRAGONESS_ESSENTIAL_VARS_H
#define DRAGONESS_ESSENTIAL_VARS_H
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
extern char* dragonessDebugLogPrefix;
extern bool dragonessBoolShaderCompilationFailed;
extern GLuint programID;
extern GLuint matrixID;
extern GLFWwindow *window;
extern int antialiasing;
extern int windowLength;
extern int windowHeight;
extern GLuint vertexArrayID;
extern int nbFrames;
extern float deltaTime;
extern float horizontalAngle;
extern float verticalAngle;
extern float initialFOV;
extern float keyboardSpeed;
extern float mouseSpeed;
extern double currentTime;
extern double lastTime;
extern double deltaLastTime;
extern mat4 viewMatrix;
extern mat4 projectionMatrix;
extern mat4 modelMatrix;
extern vec3 position;
extern mat4 mvp;
extern float dragonessDebugColorCounter;
extern GLuint vertexBuffer;
extern GLuint colorBuffer;
extern GLuint textureBuffer;
#endif
