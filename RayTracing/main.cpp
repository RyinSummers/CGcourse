#include "../tool/shader.h"
#include "../tool/texture.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <time.h>
#include <math.h>
using namespace glm;
const int WIDTH=800;
const int HEIGHT=600;
const GLchar* vertexShaderFile = "/Users/LJY/Documents/CodeLiteWorkspace/CGcourse/RayTracing/RT.vertexshader";
const GLchar* fragmentShaderFile = "/Users/LJY/Documents/CodeLiteWorkspace/CGcourse/RayTracing/RT.fragmentshader";
const GLchar* textureFile = "/Users/LJY/Documents/CodeLiteWorkspace/CGcourse/resource/egg.tga";

int main(int argc, char **argv)
{
	glfwSetErrorCallback(error_callback);
	//glfw初始化
	if(!glfwInit())
	{
		return -1;
	}
	GLFWwindow* window;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//使用新版本的核心模式
	glfwWindowHint(GLFW_RESIZABLE , GL_FALSE);//窗口尺寸不可变
	glfwWindowHint(GLFW_SAMPLES, 4);
	window = glfwCreateWindow(WIDTH, HEIGHT, "RayTracing", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	//GLEW初始化
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, WIDTH, HEIGHT);
	glClearColor(1.0, 1.0, 1.0, 1.0);//指定默认背景的颜色为白色
	glEnable(GL_DEPTH_TEST);//自动进行深度缓冲
	glDepthFunc(GL_LESS);
	glEnable(GL_MULTISAMPLE);
	
	//着色器加载
	GLuint programID = loadShaders(vertexShaderFile, fragmentShaderFile);
	
	
	
	//创建VAO，顶点数组对象
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	/*
	 * =============================================================================
	 * 策略：先分别计算MVP矩阵
	 * 算出多个物体的M坐标
	 * =============================================================================
	 */
	
	/*
	 * ==================
	 * MVP
	 * ==================
	 */
	
	//45°水平视野, 4:3, 展示范围远近截面
	mat4 projection=perspective(45.0f,4.0f/3.0f,0.1f,100.0f);
	vec3 cameraview=vec3(4,2,0);
	//相机位置，相机朝向的点的位置，相机头的方向向量
	mat4 view=lookAt(cameraview,vec3(0,0,3),vec3(0,1,0));
	
	mat4 model_1=mat4(1.0f);
	model_1=translate(model_1, vec3(1.0f,0.0f,0.0f));
	mat4 model_2=mat4(1.0f);
	model_2=translate(model_1, vec3(-2.0f,0.0f,0.0f));
	
	//光源位置
	vec3 light_position=vec3(5.0f, 0.0f, 0.0f);
	//光源颜色
	vec3 light_color=vec3(1.0f, 1.0f, 1.0f);
	//从着色器获得uniform变量MVP的索引
	//GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	//GLuint ModelID = glGetUniformLocation(programID, "M");
	
	
	
	return 0;
}
