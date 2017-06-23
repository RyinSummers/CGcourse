#include "Scene.h"

/*
 *===================== 
 * 物体-平面
 * ====================
 */
IntersectResult Plane::getIntersection(Ray ray)
{
	IntersectResult result;
	float dn=dot(ray.direction,normal);
	if (dn==0.0f)
	{
		result.isIntersect=false;
	}
	else
	{
		float k=a-dot(ray.origin,normal);
		k=k/dn;
		if(k>=0.0f)
		{
			result.isIntersect=true;
			result.point=k*ray.direction+ray.origin;
			result.k=k;
		}
		else
		{
			result.isIntersect=false;
		}
	}
	return result;
}

/*
 *===================== 
 * 物体-球体
 * ====================
 */
IntersectResult Sphere::getIntersection(Ray ray)
{
	IntersectResult result;
	vec3 v=ray.origin-center;
	vec3 d=ray.direction;
	float vd=dot(v,d);
	if (vd<=0.0f)
	{
		float delta=vd*vd-dot(v,v)+radius*radius;
		if(delta>=0.0f)
		{
			float t=-vd-sqrt(delta);
			result.isIntersect=true;
			result.point=ray.origin+t*ray.direction;
			result.k=t;
		}
		else
		{
			result.isIntersect=false;
		}
	}
	else
		result.isIntersect=false;
	return result;
}

Ray Sphere::getRefraction(Ray ray, vec3 p)
{
	vec3 n1=this->getNormal(p);
	vec3 l=ray.direction;
	double costheta1=-dot(n1,normalize(l));
	if(costheta1-1==0.0)
	{
		return ray;
	}
	double sintheta1=sqrt(1-costheta1*costheta1);
	double sintheta2=sintheta1/material.refraction;
	double costheta2=sqrt(1-sintheta2*sintheta2);
	//把n1移到原点，再旋转，再移动回去？
	vec3 n2=rotate(n1,(float)(asin(sintheta2)+M_PI/2.0),cross(l,n1));
	n2=normalize(n2);
	//vec3 result_d=l-2*(sintheta1*costheta2-costheta1*sintheta2)*n2;
	vec3 result_d=normalize(reflect(l,n2));
	vec3 n3=normalize(-reflect(n1,n2));
	Ray findp(center+radius*2*n3,-n3);
	vec3 result_p=this->getIntersection(findp).point;
	Ray result(result_p,result_d);
	return result;
}

/*
 *===================== 
 * 整个场景
 * ====================
 */
Scene::Scene()
{
	number=0;
//	ball=Sphere(vec3(0,0,0),1);
//	ball.material.color=vec3(1.0,0.5,0.31);
//	ball.material.ambientStrength=0.3f;
//	ball.material.diffuse=1.0f;
//	ball.material.specularStrength=0.2f;
//	ball.material.shininess=128;
//	plane=Plane(vec3(0,1,0),vec3(0,0,0));
}

void Scene::addPrimitive(Primitive* p)
{
	itemlist.push_back(p);
	number++;
}
Primitive* Scene::getPrimitive(int i)
{
	return itemlist[i];
}

int Scene::findPrimitive(Ray ray)
{
	int result=-1;
	float k=10000000;
	for(int i=0;i<number;i++)
	{
		IntersectResult ir=itemlist[i]->getIntersection(ray);
		if(ir.isIntersect)
		{
			if(ir.k<k)
			{
				k=ir.k;
				result=i;
			}
		}
	}
	return result;
}

IntersectResult Scene::findIntersection(Ray ray, float &para, vec3 goalp)
{
	IntersectResult result;
	float k=10000000;
	for(int i=0;i<number;i++)
	{
		IntersectResult ir=itemlist[i]->getIntersection(ray);
		if(ir.isIntersect)
		{
			if(itemlist[i]->getType()==Primitive::SPHERE)
			{
				Sphere* ball=(Sphere*)itemlist[i];
				if(ball->material.alpha<1&&distance(goalp,ir.point)>=0.01)
					{
						para=para/2;
						continue;
					}
			}
			if(ir.k<k)
			{
				k=ir.k;
				result=ir;
			}
		}
	}
	return result;
}