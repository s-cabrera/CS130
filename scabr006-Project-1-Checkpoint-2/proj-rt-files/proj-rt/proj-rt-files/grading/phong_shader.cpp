#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
        TODO; //determine the color
    vec3 color = color_ambient*world.ambient_color*world.ambient_intensity;
	for (unsigned int i = 0; i<world.lights.size(); i++){
		double j = dot(normal, (world.lights.at(i)->position - intersection_point).normalized());
		if (j>0){
			color += color_diffuse*world.lights.at(i)->Emitted_Light(world.lights.at(i)->position-intersection_point).magnitude_squared();
		}
	}
	double temp = 0;
	for(unsigned int i = 0; i<world.lights.size(); i++){
		double j = dot((world.lights.at(i)->position-intersection_point).normalized(), normal);
		vec3 myVec = j*2*normal-(world.lights.at(i)->position-intersection_point).normalized();
		temp += (-1)*dot(ray.direction, myVec);
		
		if(temp>0){
			color+= color_specular*world.lights.at(i)->Emitted_Light(world.lights.at(i)->position-intersection_point).magnitude_squared();
		}
	}
	
    return color;
}

