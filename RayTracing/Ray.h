#ifndef RAY_H
#define RAY_H
#include <glm/glm.hpp>
using namespace glm;

class Ray
{
public:
	Ray(vec3 o, vec3 d);
	~Ray();
	vec3 origin;
	vec3 direction;
};

#endif // RAY_H
