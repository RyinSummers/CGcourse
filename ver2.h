//#define GLEW_STATIC
#include <stdlib.h>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>


//mask可以存成一个bmp文件，使用时读取即可
static GLubyte Mask[128] =
		{
    0x00, 0x00, 0x00, 0x00,     //这是最下面的一行
    0x00, 0x00, 0x00, 0x00,
    0x03, 0x80, 0x01, 0xC0,     //麻
    0x06, 0xC0, 0x03, 0x60,     //烦
    0x04, 0x60, 0x06, 0x20,     //的
    0x04, 0x30, 0x0C, 0x20,     //初
    0x04, 0x18, 0x18, 0x20,     //始
    0x04, 0x0C, 0x30, 0x20,     //化
    0x04, 0x06, 0x60, 0x20,     //，
    0x44, 0x03, 0xC0, 0x22,     //不
    0x44, 0x01, 0x80, 0x22,     //建
    0x44, 0x01, 0x80, 0x22,     //议
    0x44, 0x01, 0x80, 0x22,     //使
    0x44, 0x01, 0x80, 0x22,     //用
    0x44, 0x01, 0x80, 0x22,
    0x44, 0x01, 0x80, 0x22,
    0x66, 0x01, 0x80, 0x66,
    0x33, 0x01, 0x80, 0xCC,
    0x19, 0x81, 0x81, 0x98,
    0x0C, 0xC1, 0x83, 0x30,
    0x07, 0xE1, 0x87, 0xE0,
    0x03, 0x3F, 0xFC, 0xC0,
    0x03, 0x31, 0x8C, 0xC0,
    0x03, 0x3F, 0xFC, 0xC0,
    0x06, 0x64, 0x26, 0x60,
    0x0C, 0xCC, 0x33, 0x30,
    0x18, 0xCC, 0x33, 0x18,
    0x10, 0xC4, 0x23, 0x08,
    0x10, 0x63, 0xC6, 0x08,
    0x10, 0x30, 0x0C, 0x08,
    0x10, 0x18, 0x18, 0x08,
    0x10, 0x00, 0x00, 0x08    //这是最上面的一行
};

void drawStipple()
{
		//镂空多边形
		glEnable(GL_POLYGON_STIPPLE);//开启镂空
		glPolygonStipple(Mask);
		glRectf(-0.5f, -0.5f, 0.5f, 0.5f);//画矩形，四个参数分别表示了位于对角线上的两个点的横、纵坐标
		glDisable(GL_POLYGON_STIPPLE);//关闭镂空
}

void drawTirangle()
{
		glBegin(GL_TRIANGLES);
		
		glColor3f(1.0, 0.0, 0.0);//     Red
		glVertex3f(1.0, 1.0, 0.0);//坐标范围为-1~1

		glColor3f(0.0, 1.0, 0.0);//     Green
		glVertex3f(0.0, -1.0, 0.0);
		
		glColor3f(0.0, 0.0, 1.0);//     Blue
		glVertex3f(-1.0, -1.0, 0.0);

		glEnd();
}

void drawPolygon()
{
		glBegin(GL_POLYGON);
		int i;
		int n = 100;
		GLfloat R = 0.5f;
		GLfloat Pi = 3.1415926536f;
		for(i=0;i<n;i++)
			glVertex2f(R*cos(2*Pi/n*i), R*sin(2*Pi/n*i));
		glEnd();
}