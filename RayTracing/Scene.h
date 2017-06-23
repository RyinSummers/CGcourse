#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "./Ray.h"
#include "./IntersectResult.h"
using namespace std;
using namespace glm;
/*
 *===================== 
 * 材质
 * ====================
 */
class Material
{
public:
	Material(){alpha=1;};
	~Material(){};
	vec3 color;
	float diffuse;//1-diffuse=specular
	float reflect;//反射
	float alpha;//透明度
	float refraction;//物体表面折射率

};

/*
 *===================== 
 * 抽象物体
 * ====================
 */
class Primitive
{
public:
	enum{PLANE = 1, SPHERE = 2, LIGHT= 3};
	Primitive(){};
	~Primitive(){};
	virtual int getType()=0;
	virtual IntersectResult getIntersection(Ray ray){};
};

/*
 *===================== 
 * 物体-平面
 * ====================
 */
class Plane: public Primitive
{
public:
	Plane(){};
	Plane(vec3 n,vec3 p0){normal=n;a=dot(n,p0);};
	~Plane(){};
	int getType(){return PLANE;};
	IntersectResult getIntersection(Ray ray);
	vec3 getNormal(){return normal;};
	
	//变量
	vec3 normal;
	float a;
	Material material;
};

/*
 *===================== 
 * 物体-球体
 * ====================
 */
class Sphere: public Primitive
{
public:
	Sphere(){};
	Sphere(vec3 c, float r){center=c;radius=r;};
	~Sphere(){};
	int getType(){return SPHERE;};
	IntersectResult getIntersection(Ray ray);
	Ray getRefraction(Ray ray, vec3 p);
	vec3 getNormal(vec3 p){return normalize(p-center);};
	
	//变量
	vec3 center;
	float radius;
	Material material;
};

/*
 * ====================
 * 光源
 * ====================
 */
class Light: public Primitive
{
public:
	Light(){};
	Light(vec3 pos,vec3 co){lightPos=pos;lightColor=co;};
	int getType(){return LIGHT;};
	vec3 lightPos;
	vec3 lightColor;
};

/*
 *===================== 
 * 整个场景
 * ====================
 */
class Scene
{
public:
	Scene();
	~Scene(){};
	void addPrimitive(Primitive* p);
	Primitive* getPrimitive(int i);
	int findPrimitive(Ray ray);
	IntersectResult findIntersection(Ray ray,float &para,vec3 goalp);
	int number;
	vector<Primitive*> itemlist;
	//Sphere ball;
	//Plane plane;
};

#endif // SCENE_H
