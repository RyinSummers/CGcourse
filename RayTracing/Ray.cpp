#include "Ray.h"

Ray::Ray(vec3 o, vec3 d)
{
	origin=o;
	//方向向量归一化
	direction=normalize(d);
}

Ray::~Ray()
{
}