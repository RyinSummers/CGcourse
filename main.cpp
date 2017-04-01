#include "shader.h"
#include "texture.h"
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
const GLchar* vertexShaderFile = "/Users/LJY/Documents/CodeLiteWorkspace/CGcourse/ColorArrays.vertexshader";
const GLchar* fragmentShaderFile = "/Users/LJY/Documents/CodeLiteWorkspace/CGcourse/ColorArrays.fragmentshader";

void error_callback(int error, const char* description)
{
	std::cerr << description << std::endl;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, char ** argv)
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
	window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
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
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	//创建VAO，顶点数组对象
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	//绑定至上下文
	glBindVertexArray(VAO);
	
	//着色器加载
	GLuint programID = loadShaders(vertexShaderFile, fragmentShaderFile);
	
	/*
	 * ===================================================================================
	 * 以上都是一些通用的初始化。
	 * 以下开始具体绘图内容。
	 * ===================================================================================
	 */
	
	//VBO顶点缓冲对象，管理顶点数组的内存
	GLuint VBO;
	//EBO索引缓冲对象，管理索引数组的内存
	GLuint EBO;
	static const GLfloat vertices[] = {
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
    };
    static const GLuint indices[] = {
            0, 1, 2,
            1, 2, 3,
            1, 0, 5,
            0, 5, 4,
            5, 6, 7,
            4, 5, 6,
            2, 3, 7,
            6, 2, 7,
            1, 5, 3,
            3, 5, 7,
            0, 2, 4,
            2, 4, 6,
    };
	//产生1个
	glGenBuffers(1, &VBO);
	//绑定到array_buffer上
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//把数组数据设置到buffer里
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	
	//颜色缓冲
	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	//立方体顶点颜色数据
	static GLfloat colors[8*3];
	//srand(time(NULL));
	for (int v = 0; v < 8 ; v++)
	{
		colors[3*v+0] = (float)rand()/RAND_MAX;
		colors[3*v+1] = (float)rand()/RAND_MAX;
		colors[3*v+2] = (float)rand()/RAND_MAX;
	}
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,(void*)0);
	glEnableVertexAttribArray(1);
	
	/*
	// 3nd attribute buffer : UVs
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,(void*)0);
	*/
	
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);
	
	
	/*
	//纹理导入
	//GLuint Texture = loadBMP_custom("/Users/LJY/Documents/CodeLiteWorkspace/CGcourse/uvtemplate.bmp");
	GLuint Texture = loadDDS("/Users/LJY/Documents/CodeLiteWorkspace/CGcourse/uvtemplate.DDS");
	GLuint textureID = glGetUniformLocation(programID, "myTextureSampler");
	
	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	// Two UV coordinatesfor each vertex. They were created withe Blender.
	static const GLfloat uv[] = { 
		0.0f,0.0f,
		1.0f,1.0f,
		0.0f,0.0f,
		1.0f,1.0f,
		0.0f,0.0f,
		1.0f,1.0f,
		0.0f,0.0f,
		1.0f,1.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);
	 */

	//模型矩阵，观察矩阵，投影矩阵，MVP，translate计算矩阵并传给GLSL，scale缩放变换，rotate旋转
	//从着色器获得uniform变量MVP的索引
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	//45°水平视野, 4:3, 展示范围远近截面
	mat4 projection=perspective(45.0f,4.0f/3.0f,0.1f,100.0f);
	// Or, for an ortho camera :正交投影
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
	//相机位置，相机朝向的点的位置，相机头的方向向量
	mat4 view=lookAt(vec3(4,2,0),vec3(0,0,3),vec3(0,1,0));
	mat4 model_head=mat4(1.0f);
	mat4 model_body=mat4(1.0f);
	mat4 model_hand_left=mat4(1.0f);
	mat4 model_hand_right=mat4(1.0f);
	mat4 model_leg_left=mat4(1.0f);
	mat4 model_leg_right=mat4(1.0f);
	mat4 MVP=mat4(1.0f);
	
	//身子
	model_body=translate(model_body, vec3(0.0f,0.5f,0.0f));
	model_body=scale(model_body, vec3(0.2f,0.5f,0.2f));
	
	//地板
	mat4 model_stay=mat4(1.0f);
	model_stay=translate(model_stay, vec3(0.0f,-1.1f,5.0f));
	model_stay=scale(model_stay, vec3(1.0f,0.1f,5.0f));
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清空颜色缓冲变为默认色；清空深度
		//glShadeModel(GL_FLAT);//设置颜色是单色还是默认渐变过度填充
		
		glUseProgram(programID);//使用着色器
		glBindVertexArray(VAO);
		
		/*
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		glUniform1i(textureID, 0);
		*/
		//地板
		MVP=projection*view*model_stay;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_INT, (void*)0);
		
		
		//身子
		//model_body=mat4(1.0f);
		//model_body=translate(model_body,vec3((float)sin(glfwGetTime()/2), 0.0f, 2*(float)sin(glfwGetTime()/4)));
		model_body=translate(model_body, vec3(0.0f,0.0f,0.05f));
		//model_body=rotate(model_body,(float)cos(glfwGetTime()/2)*2.355f,vec3(0.0f,1.0f,0.0f));
		//model_body=scale(model_body, vec3(0.2f,0.5f,0.2f));
		MVP=projection*view*model_body;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_INT, (void*)0);
		
		//脑袋
		vec4 neck(0.0f,1.0f,0.0f,1.0f);
		neck=model_body*neck;
		model_head=mat4(1.0f);
		model_head=translate(model_head,vec3(neck.x,neck.y+0.3,neck.z));
		model_head=rotate(model_head,(float)sin(glfwGetTime()*2)/5,vec3(0.0f,0.0f,1.0f));
		model_head=scale(model_head, vec3(0.1f,0.1f,0.1f));
		MVP=projection*view*model_head;
		//通过索引，往着色器设置Uniform变量的值，类型为float向量
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);//MVP
		glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_INT, (void*)0);
		
		//glDrawArrays(GL_TRIANGLES, 0, 3*12); //从第0个点开始，共3个点
		
		//左手
		vec4 shd_left(1.0f,0.0f,0.0f,1.0f);
		shd_left=model_body*shd_left;
		model_hand_left=mat4(1.0f);
		model_hand_left=translate(model_hand_left,vec3(shd_left.x+0.1,shd_left.y+0.5,shd_left.z));
		model_hand_left=rotate(model_hand_left,(float)sin(glfwGetTime()*2)/3,vec3(1.0f,0.0f,0.5f));
		model_hand_left=translate(model_hand_left,vec3(0.0f,-0.5f,0.0f));
		model_hand_left=scale(model_hand_left, vec3(0.1f,0.5f,0.1f));
		MVP=projection*view*model_hand_left;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_INT, (void*)0);
		
		//右手
		vec4 shd_right(-1.0f,0.0f,0.0f,1.0f);
		shd_right=model_body*shd_right;
		model_hand_right=mat4(1.0f);
		model_hand_right=translate(model_hand_right,vec3(shd_right.x-0.1,shd_right.y+0.5,shd_right.z));
		model_hand_right=rotate(model_hand_right,(float)sin(glfwGetTime()*2)/3,vec3(-1.0f,0.0f,-0.5f));
		model_hand_right=translate(model_hand_right,vec3(0.0f,-0.5f,0.0f));
		model_hand_right=scale(model_hand_right, vec3(0.1f,0.5f,0.1f));
		MVP=projection*view*model_hand_right;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_INT, (void*)0);
		
		//左脚
		vec4 pp_left(0.5f,-1.0f,0.0f,1.0f);
		pp_left=model_body*pp_left;
		model_leg_left=mat4(1.0f);
		model_leg_left=translate(model_leg_left,vec3(pp_left.x+0.05,pp_left.y,pp_left.z));
		model_leg_left=rotate(model_leg_left,(float)sin(glfwGetTime()*2)/3,vec3(-1.0f,0.0f,0.0f));
		model_leg_left=translate(model_leg_left,vec3(0.0f,-0.5f,0.0f));
		model_leg_left=scale(model_leg_left, vec3(0.1f,0.5f,0.1f));
		MVP=projection*view*model_leg_left;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_INT, (void*)0);
		
		//右脚
		vec4 pp_right(-0.5f,-1.0f,0.0f,1.0f);
		pp_right=model_body*pp_right;
		model_leg_right=mat4(1.0f);
		model_leg_right=translate(model_leg_right,vec3(pp_right.x-0.05,pp_right.y,pp_right.z));
		model_leg_right=rotate(model_leg_right,(float)sin(glfwGetTime()*2)/3,vec3(1.0f,0.0f,0.0f));
		model_leg_right=translate(model_leg_right,vec3(0.0f,-0.5f,0.0f));
		model_leg_right=scale(model_leg_right, vec3(0.1f,0.5f,0.1f));
		MVP=projection*view*model_leg_right;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_INT, (void*)0);
		
		glfwSwapBuffers(window);//交换颜色缓冲
		glfwPollEvents();//检查有没有触发什么事件（比如键盘输入、鼠标移动等）
	}

	// Cleanup
	glDeleteBuffers(1, &colorbuffer);
	//glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(programID);
	//glDeleteTextures(1, &textureID);
	glDeleteVertexArrays(1, &VAO);
	//窗口结束
    glfwTerminate();
	return 0;
}