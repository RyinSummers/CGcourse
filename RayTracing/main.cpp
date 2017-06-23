#include "./Ray.h"
#include "./IntersectResult.h"
#include "./Scene.h"
#include "./Camera.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <time.h>
#include <math.h>
using namespace glm;

const int WIDTH=800;
const int HEIGHT=600;

void printv(const vec4& v) {
    std::cout << v[0] << " " << v[1] << " " << v[2] << " " << v[3] << std::endl;
}

void printm(const mat4& m) {
    printv(m[0]);
    printv(m[1]);
    printv(m[2]);
    printv(m[3]);
}

vec3 raytracing(Ray ray,int weight,Scene scene,vec3 lightPos,vec3 lightColor)
{
	vec3 resultcolor;
	if(weight<=0)
	{
		resultcolor=vec3(0,0,0);
	}
	else
	{
		//寻找场景中zbuffer最小的点
		int num_item=scene.findPrimitive(ray);
		if(num_item>=0)
		{
			//得到该物体
			Primitive* item=scene.getPrimitive(num_item);
			IntersectResult ir;
			vec3 itemNormal;
			float itemDiffuse;
			vec3 itemColor;
			float itemSpec;
			bool hasRefraction=false;
			if(item->getType()==Primitive::SPHERE)
			{
				Sphere* ball=(Sphere*)item;
				ir=ball->getIntersection(ray);
				itemNormal=ball->getNormal(ir.point);
				itemDiffuse=ball->material.diffuse;
				itemColor=ball->material.color;
				itemSpec=ball->material.reflect;
				if(ball->material.alpha<1)
					hasRefraction=true;
			}
			else if(item->getType()==Primitive::PLANE)
			{
				Plane* p=(Plane*)item;
				ir=p->getIntersection(ray);
				itemNormal=p->getNormal();
				itemDiffuse=p->material.diffuse;
				itemColor=p->material.color;
				itemSpec=p->material.reflect;
			}
			else
			{
				//如果是光源
				return vec3(1,1,1);
			}
			//如果该物体与光源直接接触，就计算色彩
			//生成一个从光源往该点方向投射的ray，对场景求交，看看交到的point是不是该point
			//如果物体与光源没有直接接触，计算反光
			vec3 localcolor=vec3(0,0,0);
			vec3 lightDir=normalize(lightPos-ir.point);
			Ray lightray(lightPos,ir.point-lightPos);
			float para=1;
			vec3 lightpoint=scene.findIntersection(lightray,para,ir.point).point;
			if(distance(lightpoint,ir.point)<0.01)
			{
				
				float temp=dot(itemNormal,lightDir);
				if(temp<0)
					temp=0;
				float diffuse=temp*itemDiffuse;
				localcolor=para*diffuse*lightColor*itemColor;
			}
			//反射光线
			//表面法向量n，相机方向v，光源方向l，反射方向r=2(l.n)n-l
			vec3 reflectDirection=-reflect(lightDir,itemNormal);
			Ray r_ray(ir.point,reflectDirection);
			vec3 r_color=raytracing(r_ray,weight-1,scene,lightPos,lightColor);
			r_color=0.2f*r_color;
			//折射光线，说明物体是透明的，需要把透明物体背后的东西也加进来
			//假设只有球有这种效果，平面没有
			//计算光经过物体内部再从外部出去之后的ray
			vec3 t_color=vec3(0,0,0);
			if(hasRefraction)
			{
				Sphere* ball=(Sphere*)item;
				Ray t_ray=ball->getRefraction(ray,ir.point);
				t_color=raytracing(t_ray,weight-1,scene,lightPos,lightColor);
				t_color=(1-ball->material.alpha)*t_color;
			}
			resultcolor=localcolor+r_color+t_color;
		}
		else
		{
			resultcolor=vec3(0,0,0);
		}
	}
	return resultcolor;
}

int main(int argc, char **argv)
{
	if(!glfwInit())
	{
		return -1;
	}
	GLFWwindow* window;
	glfwWindowHint(GLFW_RESIZABLE , GL_FALSE);//窗口尺寸不可变
	glfwWindowHint(GLFW_SAMPLES, 4);
	window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//GLEW初始化
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, WIDTH, HEIGHT);
	//glClearColor(1.0, 1.0, 1.0, 1.0);//指定默认背景的颜色为白色
	
	//测试样例
//	Ray testray(vec3(2,0,0),vec3(-1,1,0));
//	Sphere testqiu(vec3(0,0,0),1.5);
//	std::cout<<testqiu.getIntersection(testray).isIntersect<<std::endl;
//	std::cout<<testqiu.getIntersection(testray).point.x<<std::endl;
	//vec3 position,vec3 destination,vec3 up,float fov,float ra 4.0f/3.0f
//	Camera camera(vec3(0,0,1),vec3(0,0,0),vec3(0,1,0),45.0f,1.0f);
//	Ray ray=camera.getRay(1,1);
//	printv(vec4(camera.camera_position,0));
//	printv(vec4(camera.camera_look,0));
//	printv(vec4(camera.camera_up,0));
//	printv(vec4(camera.camera_right,0));
//	std::cout<<camera.FOV<<std::endl;
//	printv(vec4(ray.origin,0));
//	printv(vec4(ray.direction,0));
//	vec3 testv=reflect(vec3(-1,-1,0),vec3(0,1,0));
//	printv(vec4(testv,0));
	//物体
	Scene scene;
	Sphere ball(vec3(-2,0,-3),2);
	ball.material.color=vec3(0.3,0.2,0.9);
	ball.material.diffuse=1.0f;
	ball.material.reflect=0.7f;
	ball.material.alpha=1;
	ball.material.refraction=1.1;
	Sphere ball2(vec3(1,0,0),2);
	ball2.material.color=vec3(1,1,1);
	ball2.material.diffuse=1.0f;
	ball2.material.reflect=0.8f;
	ball2.material.alpha=1;
	ball2.material.refraction=0.95f;
	Sphere ball3(vec3(-1,-1,3),1);
	ball3.material.color=vec3(1,0.3,0.2);
	ball3.material.diffuse=1.0f;
	ball3.material.reflect=0.8f;
	ball3.material.alpha=0.8;
	ball3.material.refraction=0.95f;
	Plane plane(vec3(0,1,0),vec3(0,-2,0));
	plane.material.color=vec3(1.0,0.7,0.7);
	plane.material.diffuse=1.0f;
	plane.material.reflect=0.9f;
	Plane plane2(vec3(0,0,1),vec3(0,0,-10));
	plane2.material.color=vec3(1.0,0.7,0.7);
	plane2.material.diffuse=1.0f;
	plane2.material.reflect=0.9f;
	scene.addPrimitive(dynamic_cast<Primitive*>(&ball));
	scene.addPrimitive(dynamic_cast<Primitive*>(&ball2));
	scene.addPrimitive(dynamic_cast<Primitive*>(&ball3));
	scene.addPrimitive(dynamic_cast<Primitive*>(&plane));
	scene.addPrimitive(dynamic_cast<Primitive*>(&plane2));
	
	//还是测试
	//Sphere* testb=(Sphere*)scene.getPrimitive(0);
	//std::cout<<scene.getPrimitive(0)->getType();
	//Ray testray(vec3(5,0,5),vec3(0,0,-1));
	//std::cout<<scene.findPrimitive(testray);
	
	//又一个test
//	Ray testray(vec3(-5,1,0),vec3(1,0,0));
//	Ray testresult=ball2.getRefraction(testray,ball2.getIntersection(testray).point);
//	printv(vec4(testresult.origin,1.0f));
//	printv(vec4(testresult.direction,1.0f));
	
	
	//相机
	Camera camera(vec3(0,0,10),vec3(0,0,0),vec3(0,1,0),45.0f,(float)WIDTH/HEIGHT);
	//光源
	vec3 lightColor=vec3(1,1,1);
	vec3 lightPos=vec3(-5,5,5);
	
	//光线追踪，计算颜色
	float colors[WIDTH*HEIGHT*3];
	for(int i=0;i<WIDTH;i++)
	{
		float x=2*(float)i/WIDTH-1;
		for(int j=0;j<HEIGHT;j++)
		{
			//xy为-1到1
			float y=2*(float)j/HEIGHT-1;
			Ray ray=camera.getRay(x,y);
			vec3 color=raytracing(ray,4,scene,lightPos,lightColor);
			int v=3*(i*HEIGHT+j);
			colors[v+0]=color.x;
			colors[v+1]=color.y;
			colors[v+2]=color.z;
		}
	}
	
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBegin(GL_POINTS);
		for(int i=0;i<WIDTH;i++)
		{
			float x=2*(float)i/WIDTH-1;
			for(int j=0;j<HEIGHT;j++)
			{
				//xy为-1到1
				float y=2*(float)j/HEIGHT-1;
				int v=3*(i*HEIGHT+j);
				glColor3f(colors[v+0],colors[v+1],colors[v+2]);
				glVertex2f(x,y);
			}
		}
		glEnd();
		glfwSwapBuffers(window);//交换颜色缓冲
		glfwPollEvents();//检查有没有触发什么事件（比如键盘输入、鼠标移动等）
	}
	glfwTerminate();
	return 0;
}
