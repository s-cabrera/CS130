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
    //e + ut
    // P(t) = (x - x0) • n = 0
    // P(t) = ((e + ut) - x0) • n = 0

    Hit temp, null; 
    temp.object = this;
    temp.part = part;

    vec3 diff = ray.endpoint - x1;
    double min = -1;
    for(int i = 0; i < part; i++){
        if(dot((diff + (ray.direction * i)), normal) == 0){
            min = i;
            break;
        }
    }

    if(min < 0){
        return null;
    }
    else{
        temp.dist = min;
    }

    // double a, b, c; 
    // a = dot(ray.direction, ray.direction)*dot(normal, normal);
    // b = ray.direction* ray.direction * diff *normal;
    // c = dot(normal, normal) * dot(diff, diff);

    // Hit temp, null; 
    // temp.object = this;
    // temp.part = part;

    //  double discriminant = std::pow(b,2)-(4*a*c);

    // //Set the part of the Hit temp
    // //temp.object = this;
    
    // //If the discriminant (b^2 -4ac) is < 0, there is no solution
    // if(discriminant < 0){
    //    // std::cout<<"Sphere returns null\n";
    //     return null;
    // }
    // //If the discriminant (b^2 -4ac) is = 0, there is one solution
    // else if(discriminant == 0){
    //    // temp.dist = ((-b)/(2*a)); // t = (-b/2a)
    //    // temp.part = 0;
    //     temp = {this, ((-b)/(2*a)), 0};

    // }
    
    // else if(discriminant > 0){
    //     double t1 = ((-b) - sqrt(discriminant))/(2*a);
    //     double t2 = ((-b) + sqrt(discriminant))/(2*a);
    //     if((t1 >= 0) && (t1 < t2)){
    //         temp = {this,t1,0};
    //     }
    //     else if((t2 >= 0) && (t2 < t1)){
    //         temp = {this, t2, 0};
    //     }
    //     else if((t1 < 0) && (t2 < 0)){
    //         return null;
    //     }
    //     else{
    //         temp = {this, t1, 0};
    //     }
    // }

    return temp;
}

vec3 Plane::Normal(const vec3& point, int part) const
{
    return normal;
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
