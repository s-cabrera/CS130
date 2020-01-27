#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    TODO;
    //we have a center and a radius as Sphere components
    //vec3 sphereDir(1,1,1);
    //vec3 sphereEndpoint = center + radius*sphereDir;
    Hit temp;
    double a, b, c, discriminant;
    
    //These are the constant for the quadratic equation
    a = dot(ray.direction, ray.direction);
    b = dot((ray.endpoint - center),ray.direction)*2;
    c = dot((ray.endpoint - center), (ray.endpoint - center)) - (radius * radius);
    discriminant = std::pow(b,2)-(4*a*c);

    //Set the part of the Hit temp
    temp.part = part;

    //If the discriminant (b^2 -4ac) is < 0, there is no solution
    if(discriminant < 0){
        temp.object = NULL;
    }
    
    //If the discriminant (b^2 -4ac) is = 0, there is one solution
    if(discriminant == 0){
        temp.object = this;
        temp.part = ((-b)/(2*a)); // t = (-b/2a)
    }
    
    
    else{
        temp.part = part;
        temp.object = this;
        temp.part = ((-b - sqrt(discriminant))/(2*a)); 
    }
    return temp;
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    TODO; // compute the normal direction
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
