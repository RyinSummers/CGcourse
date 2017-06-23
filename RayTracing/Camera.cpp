#include "Camera.h"

Camera::Camera(vec3 position,vec3 destination,vec3 up,float fov,float ra)
{
	camera_position=position;
	camera_look=normalize(destination-position);
	camera_up=normalize(up);
	camera_right=normalize(cross(camera_look,camera_up));
	FOV=fov*M_PI/180;
	ratio=ra;
}

Camera::~Camera()
{
}

Ray Camera::getRay(float x,float y)
{
	float temp=tan(FOV/2);
	vec3 u=y*camera_up*temp;
	vec3 r=x*camera_right*ratio*temp;
	vec3 d=camera_look+r+u;
	Ray result(camera_position,d);
	return result;
}