#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"

extern bool disable_hierarchy;

Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find and return the Hit structure for the closest intersection.  Be careful
// to ensure that hit.dist>=small_t.
Hit Render_World::Closest_Intersection(const Ray& ray)
{
    TODO;
    /*
    Set min_t to a large value (google std numeric_limits)
    For each object* in objects: 
        use object -> Intersect to get the hit with the object
        If hit is the closest so far and larger than small_t 
        (i.e. with smallest t, that is larger than small_t)
            then store the hit as the closest hit
    return closest hit
    */
   
    //int min_t;
    //min_t = min_t.max();
    //Hit temp ; 
   // if (ray->Intersect < )
    return {};
    
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    TODO; // set up the initial view ray here
    /*
    //end_point: camera position (from camera class)
    //direction: a unit vector from the camera position to the world position of 
    //the pixel. 
        //vec3 class has normalized() function that returns the normalized vector;


    */

    Ray ray;
    vec3 color=Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    if(!disable_hierarchy)
        Initialize_Hierarchy();

    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    /*
    Get the closest hit with an objedt using Closest_Intersection
    If there is am intersection:
        Set color using the object Shade_Surface function which calculates and
        returns the color of the ray/object intersection point. 
        Shade_Surface receives as parameters: ray, intersection point, normal at
        the intersection point and recursion_depth. You can get the intersection
        point using the ray object and the normal using the object pointer
        inside the hit object.
    Else (if there is no intersection)
        Use background_shader of the render_world class. The background shader 
        is a flat_shader so you can use any 3d vector as parameters
    */
    vec3 color;
    TODO; // determine the color here

    return color;
}

void Render_World::Initialize_Hierarchy()
{
    TODO; // Fill in hierarchy.entries; there should be one entry for
    // each part of each object.

    hierarchy.Reorder_Entries();
    hierarchy.Build_Tree();
}
