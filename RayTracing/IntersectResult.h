#ifndef INTERSECTRESULT_H
#define INTERSECTRESULT_H
#include <glm/glm.hpp>
class IntersectResult
{
public:
	IntersectResult();
	~IntersectResult();
	bool isIntersect;
	glm::vec3 point;
	float k;
};

#endif // INTERSECTRESULT_H
