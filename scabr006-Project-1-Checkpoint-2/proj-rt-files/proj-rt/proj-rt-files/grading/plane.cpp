#include "plane.h"
#include "ray.h"
#include <cfloat>
#include <limits>

// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
Hit Plane::Intersection(const Ray& ray, int part) const
{
    TODO;

	Hit temp;
	double d = dot(this->normal, ray.direction);
	double t = (dot(x1, this->normal) - dot(ray.endpoint, this->normal))/d;
	if(d == 0){
		//temp = {nullptr, NULL, NULL};
		return temp;// = {this, 0, part};
	}
	else{
		if(t < small_t){
		 return temp;
		}
		else{
			temp = {this, t, part};
		}
    }
    return temp;
}

vec3 Plane::Normal(const vec3& point, int part) const
{
	vec3 normal = this->normal; //(x1 - point).normalized();
    TODO; // compute the normal direction
    return normal;//.normalized();
}

// There is not a good answer for the bounding box of an infinite object.
// The safe thing to do is to return a box that contains everything.
Box Plane::Bounding_Box(int part) const
{
    Box b;
    b.hi.fill(std::numeric_limits<double>::max());
    b.lo=-b.hi;
    return b;
}
