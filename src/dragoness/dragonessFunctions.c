#include "dragonessFunctions.h"
#include "dragonessShaderCode.h"
#include "dragonessTestModels.h"
GLuint dragonessCompileShaders(const char* eCS_vertexShaderCode,const char* eCS_fragmentShaderCode) {
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	GLint result = GL_FALSE;
        int infoLogLength;
        printf("%sCompiling vertex shader...\n",dragonessDebugLogPrefix);
        char const* vertexSourcePointer = vertexShaderCode;
        glShaderSource(vertexShaderID,1,&vertexSourcePointer,NULL);
        glCompileShader(vertexShaderID);
        glGetShaderiv(vertexShaderID,GL_COMPILE_STATUS,&result);
        glGetShaderiv(vertexShaderID,GL_INFO_LOG_LENGTH,&infoLogLength);
        if(infoLogLength > 0) {
                char vertexShaderErrorMessage[infoLogLength+1];
                glGetShaderInfoLog(vertexShaderID,infoLogLength,NULL,&vertexShaderErrorMessage[0]);
                printf("%s\n",&vertexShaderErrorMessage[0]);
		dragonessBoolShaderCompilationFailed = true;
        }
	printf("%sCompiling fragment shader...\n",dragonessDebugLogPrefix);
        char const* fragmentSourcePointer = fragmentShaderCode;
        glShaderSource(fragmentShaderID,1,&fragmentSourcePointer,NULL);
        glCompileShader(fragmentShaderID);
        glGetShaderiv(fragmentShaderID,GL_COMPILE_STATUS,&result);
        glGetShaderiv(fragmentShaderID,GL_INFO_LOG_LENGTH,&infoLogLength);
        if(infoLogLength > 0) {
                char fragmentShaderErrorMessage[infoLogLength+1];
                glGetShaderInfoLog(fragmentShaderID,infoLogLength,NULL,&fragmentShaderErrorMessage[0]);
                printf("%s\n",&fragmentShaderErrorMessage[0]);
		dragonessBoolShaderCompilationFailed = true;
        }
	printf("%sLinking shaders...\n",dragonessDebugLogPrefix);
	GLuint eCS_programID = glCreateProgram();
        glAttachShader(eCS_programID,vertexShaderID);
        glAttachShader(eCS_programID,fragmentShaderID);
        glLinkProgram(eCS_programID);
	glGetProgramiv(eCS_programID, GL_LINK_STATUS, &result);
        glGetProgramiv(eCS_programID,GL_INFO_LOG_LENGTH,&infoLogLength);
        if (infoLogLength > 0) {
                char programErrorMessage[infoLogLength+1];
                glGetProgramInfoLog(eCS_programID,infoLogLength,NULL,&programErrorMessage[0]);
                printf("%s\n",&programErrorMessage[0]);
		dragonessBoolShaderCompilationFailed = true;
        }
	glDetachShader(eCS_programID,vertexShaderID);
        glDetachShader(eCS_programID,fragmentShaderID);
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
	if(infoLogLength < 1) {
		printf("%sShaders have been compiled and linked\n",dragonessDebugLogPrefix);
	}
	return eCS_programID;
}
int dragonessCreateProgramIDs() {
	programID = dragonessCompileShaders(vertexShaderCode,fragmentShaderCode);
	if(dragonessBoolShaderCompilationFailed == true) {
		return -1;
	}
	matrixID = glGetUniformLocation(programID,"mvp");
	return 0;
}
int dragonessInit(const char* vertexShaderPath,const char* fragmentShaderPath) {
	glewExperimental = true;
	if(!glfwInit()) {
                fprintf(stderr,"GLFW failed to initialize!\n");
        	return -1;
	}
	glfwWindowHint(GLFW_SAMPLES,antialiasing);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
        glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
        window = glfwCreateWindow(windowLength,windowHeight,"Tower of the Dead",glfwGetPrimaryMonitor(),NULL);
        if(window==NULL) {
                fprintf(stderr, "GLFW could not create a window!\n");
                glfwTerminate();
                return -1;
        }
	glfwMakeContextCurrent(window);
        glewExperimental=true;
        if(glewInit()!=GLEW_OK) {
                fprintf(stderr,"GLEW could not be initialized!\n");
                return -1;
	}
	printf("OpenGL has been initialized\n");
        glfwSetInputMode(window,GLFW_STICKY_KEYS,GL_TRUE);
        glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_HIDDEN);
	glClearColor(0.2f,0.7f,0.3f,1.0f);
	glGenVertexArrays(1,&vertexArrayID);
	glBindVertexArray(vertexArrayID);
	if(dragonessCreateProgramIDs() != 0) {
		glfwTerminate();
        	printf("%sGLFW closed\n",dragonessDebugLogPrefix);
		return -1;
	}
	//DEBUG MODEL
        glGenBuffers(1,&vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER,sizeof(testVertex),testVertex,GL_STATIC_DRAW);
        glGenBuffers(1, &colorBuffer);
        glBindBuffer(GL_ARRAY_BUFFER,colorBuffer);
        glBufferData(GL_ARRAY_BUFFER,sizeof(testColor),testColor,GL_STATIC_DRAW);
	//END DEBUG MODEL
	glfwSetCursorPos(window,(windowLength/2),(windowHeight/2));
	lastTime = glfwGetTime();
	deltaLastTime = lastTime;
	return 0;
}
typedef void(*dragonessDynamicScriptFunctionAssign_t)(void);
dragonessDynamicScriptFunctionAssign_t dragonessAssignedScriptFunctionPointer = NULL;
void dragonessSetScriptExecFunction(dragonessDynamicScriptFunctionAssign_t PassedScriptFunction) {
	dragonessAssignedScriptFunctionPointer = PassedScriptFunction;
}
void* dragonessScriptFunction(void*) {
	pthread_detach(pthread_self());
	if(dragonessAssignedScriptFunctionPointer != NULL) {
		dragonessAssignedScriptFunctionPointer();
	} else {
		printf("%sScript Function was not assigned!\n",dragonessDebugLogPrefix);
	}
	pthread_exit(NULL);
}
pthread_t scriptThread;
void dragonessCreateScriptThread() {
	pthread_create(&scriptThread,NULL,&dragonessScriptFunction,NULL);
}
void dragonessBatchVertices() {

}
void dragonessBatchColors() {

}
void dragonessBatchTextures() {

}
void dragonessDebugMovement() {
	double xpos,ypos;
        glfwGetCursorPos(window,&xpos,&ypos);
	glfwSetCursorPos(window,windowHeight/2,windowLength/2);
	horizontalAngle += mouseSpeed * deltaTime * (float)((float)windowHeight/2 - xpos);
	verticalAngle += mouseSpeed * deltaTime * (float)((float)windowLength/2 - ypos);
	//DEBUG
	//printf("%sAngles (Horizontal,Vertical): [%f],[%f]\n",dragonessDebugLogPrefix,horizontalAngle,verticalAngle);
	//END DEBUG
	// fucking cursor crap
        if(verticalAngle > 4.0f) {
		verticalAngle = 0.0f;
	}
	if(verticalAngle < -4.0f) {
		verticalAngle = 0.0f;
	}
	// end fucking cursor crap
	if(verticalAngle < -1.6f) {
                verticalAngle = -1.6f;
        }
        if(verticalAngle > 1.6f) {
                verticalAngle = 1.6f;
        }
	if(horizontalAngle >= 360.0f || horizontalAngle <= -360.0f) {
                horizontalAngle = 0.0f;
        }
	vec3 direction = {(cos(verticalAngle) * sin(horizontalAngle)),(sin(verticalAngle)),(cos(verticalAngle) * cos(horizontalAngle))};
	vec3 sideways = {sin(horizontalAngle-3.14f/2.0f),0,cos(horizontalAngle-3.14f/2.0f)};
	vec3 frontal = {cos(horizontalAngle-3.14f/2.0f),0,sin(horizontalAngle+3.14f/2.0f)};
	vec3 upwards = {0,(float)(keyboardSpeed/3.0f),0};
	vec3 cameraFront;
	glm_vec3_cross(sideways,direction,cameraFront);
	void dragonessProcessPositionFromFloats(vec3 vec) {
		for(int i = 0; i < 3; i++) {
			vec[i] *= deltaTime;
		}
		for(int i = 0; i < 3; i++) {
			vec[i] *= keyboardSpeed;
		}
	}
	if(glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS) {
		dragonessProcessPositionFromFloats(upwards);
		glm_vec3_add(position,upwards,position);
        }
        if(glfwGetKey(window,GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		dragonessProcessPositionFromFloats(upwards);
		glm_vec3_sub(position,upwards,position);
        }
        if(glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS) {
		keyboardSpeed *= 2.0f;
		dragonessProcessPositionFromFloats(direction);
                glm_vec3_add(position,direction,position);
		keyboardSpeed /= 2.0f;
        }
        else if (glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS) {
		dragonessProcessPositionFromFloats(frontal);
                glm_vec3_add(position,frontal,position);
        }
        if (glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS) {
		dragonessProcessPositionFromFloats(frontal);
                glm_vec3_sub(position,frontal,position);
        }
        if (glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS) {
		dragonessProcessPositionFromFloats(sideways);
                glm_vec3_add(position,sideways,position);
        }
        if (glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS) {
		dragonessProcessPositionFromFloats(sideways);
                glm_vec3_sub(position,sideways,position);
        }
        float FOV = initialFOV * 3.1415f / 180.0f;
	vec3 posDir;
	glm_vec3_add(position,direction,posDir);
	glm_mat4_identity(viewMatrix);
	glm_mat4_identity(projectionMatrix);
	glm_mat4_identity(modelMatrix);
	glm_perspective(FOV,(float)windowLength/(float)windowHeight,0.1f,100.0f,projectionMatrix);
	glm_lookat(position,posDir,cameraFront,viewMatrix);
	glm_mat4_mulN((mat4* []){&projectionMatrix,&viewMatrix,&modelMatrix},3,mvp);
}
void dragonessBeforeEveryFrame() {
	deltaLastTime = glfwGetTime();
	deltaTime = (float)(deltaLastTime - currentTime);
	currentTime = glfwGetTime();
	nbFrames++;
	if (currentTime - lastTime >= 1.0) {
		nbFrames = 0;
		lastTime += 1.0;
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
}
void dragonessEnableBuffersForRender() {
	dragonessBatchVertices();
	dragonessBatchColors();
	dragonessBatchTextures();
}
void dragonessOnEveryFrame() {
	dragonessBeforeEveryFrame();
	dragonessDebugMovement();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(programID);
	glUniformMatrix4fv(matrixID,1,GL_FALSE,(float*)mvp);
	dragonessEnableBuffersForRender();
	//DEBUG MODEL
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,(void*)0);
	
	glDrawArrays(GL_TRIANGLES,0,(12*3)+(2*3));
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	//END DEBUG MODEL
	glfwSwapBuffers(window);
        glfwPollEvents(); 
}
void dragonessRender() {
        do {
                dragonessOnEveryFrame();
        }
        while (glfwGetKey(window,GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}
void dragonessExit() {
	glDeleteBuffers(1,&vertexBuffer);
	glDeleteVertexArrays(1,&vertexArrayID);
	glDeleteProgram(programID);
	pthread_join(scriptThread,NULL);
	glfwTerminate();
	printf("GLFW closed\n");
	pthread_exit(NULL);
}
