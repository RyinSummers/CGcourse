#ifndef CAMERA_H
#define CAMERA_H
#include <./Ray.h>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
class Camera
{
public:
	Camera(vec3 position,vec3 destination,vec3 up,float fov,float ra);
	~Camera();
	Ray getRay(float x,float y);
	vec3 camera_position;//相机位置坐标
	vec3 camera_look;//相机正面的朝向
	vec3 camera_up;
	vec3 camera_right;
	float FOV;//y反向的视角
	float ratio;//x除以y
	//float near;//最近截面的距离
};

#endif // CAMERA_H
