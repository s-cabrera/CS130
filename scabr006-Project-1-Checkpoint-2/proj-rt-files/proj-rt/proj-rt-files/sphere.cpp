#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    TODO;
    //we have a center and a radius as Sphere components
    Hit temp, null;
    double a, b, c, discriminant;
    
    //These are the constant for the quadratic equation
    a = dot(ray.direction, ray.direction);
    b = dot((ray.endpoint - center),ray.direction)*2;
    c = dot((ray.endpoint - center), (ray.endpoint - center)) - (radius * radius);
    discriminant = std::pow(b,2)-(4*a*c);

    //Set the part of the Hit temp
    //temp.object = this;
    
    //If the discriminant (b^2 -4ac) is < 0, there is no solution
    if(discriminant < 0){
       // std::cout<<"Sphere returns null\n";
        return null;
    }
    //If the discriminant (b^2 -4ac) is = 0, there is one solution
    else if(discriminant == 0){
       // temp.dist = ((-b)/(2*a)); // t = (-b/2a)
       // temp.part = 0;
        temp = {this, ((-b)/(2*a)), 0};

    }
    
    else{
        double t1 = ((-b) - sqrt(discriminant))/(2*a);
        double t2 = ((-b) + sqrt(discriminant))/(2*a);
        if(t1 > t2)
        {
            t1 = t2;
        //    temp = {this,t1,0};
        }
        temp = {this,t1,0};
        /*
        else if((t2 >= 0) && (t2 < t1)){
            temp = {this, t2, 0};
        }
        else if((t1 < 0) && (t2 < 0)){
            return null;
        }
        else{
            temp = {this, t1, 0};
        }
        */
    }

    //std::cout << "Intersection::sphere\n";
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
