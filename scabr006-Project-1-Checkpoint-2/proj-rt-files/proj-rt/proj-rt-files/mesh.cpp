#include "mesh.h"
#include <fstream>
#include <string>
#include <limits>

// Consider a triangle to intersect a ray if the ray intersects the plane of the
// triangle with barycentric weights in [-weight_tolerance, 1+weight_tolerance]
static const double weight_tolerance = 1e-4;

// Read in a mesh from an obj file.  Populates the bounding box and registers
// one part per triangle (by setting number_parts).
void Mesh::Read_Obj(const char* file)
{
    std::ifstream fin(file);
    if(!fin)
    {
        exit(EXIT_FAILURE);
    }
    std::string line;
    ivec3 e;
    vec3 v;
    box.Make_Empty();
    while(fin)
    {
        getline(fin,line);

        if(sscanf(line.c_str(), "v %lg %lg %lg", &v[0], &v[1], &v[2]) == 3)
        {
            vertices.push_back(v);
            box.Include_Point(v);
        }

        if(sscanf(line.c_str(), "f %d %d %d", &e[0], &e[1], &e[2]) == 3)
        {
            for(int i=0;i<3;i++) e[i]--;
            triangles.push_back(e);
        }
    }
    number_parts=triangles.size();
}

// Check for an intersection against the ray.  See the base class for details.
Hit Mesh::Intersection(const Ray& ray, int part) const
{
    TODO;
    // Consider a triangle to intersect a ray if the ray intersects the plane of the
    // triangle with barycentric weights in [-weight_tolerance, 1+weight_tolerance]

    Hit temp;

    for(unsigned int i = 0; i < triangles.size(); i++){
        for(unsigned int j = 0; j < 3; j++){
            int k = triangles.at(i)[j];
            double l = vertices.at(k)[j];
            if(Intersect_Triangle(ray, k, l)){
                temp = {this, k, part};
            }
        }
    }


    // dist = ; 
    // for (int i = 0; i < triangles.at(i); i++){
    //     if(Intersect_Triangle(ray, part, dist){
    //         if(t < small_t){
    //             temp = {this, t, part};
    //         }
    //     }
    // }
    return temp;
}
// Compute the normal direction for the triangle with index part.
vec3 Mesh::Normal(const vec3& point, int part) const
{
    assert(part>=0);
    vec3 normal =(triangles.at(part), point).normalized();

    TODO;
    return normal;
}

// This is a helper routine whose purpose is to simplify the implementation
// of the Intersection routine.  It should test for an intersection between
// the ray and the triangle with index tri.  If an intersection exists,
// record the distance and return true.  Otherwise, return false.
// This intersection should be computed by determining the intersection of
// the ray and the plane of the triangle.  From this, determine (1) where
// along the ray the intersection point occurs (dist) and (2) the barycentric
// coordinates within the triangle where the intersection occurs.  The
// triangle intersects the ray if dist>small_t and the barycentric weights are
// larger than -weight_tolerance.  The use of small_t avoid the self-shadowing
// bug, and the use of weight_tolerance prevents rays from passing in between
// two triangles.
bool Mesh::Intersect_Triangle(const Ray& ray, int tri, double& dist) const
{
    TODO;
    //ivec3 temp = triangles.at(tri);
    //double j = dot(ray.direction, temp); 
    //(triangle.at(tri)-ray.endpoint);  
    //if(j > 0){

   // }

    //if(dist > small_t && (j > -weight_tolerance) && (j > -weight_tolerance) && (j > -weight_tolerance)){
    //    return true;
    //}
    //else{
        return false;
    //}
    /*
	double d = dot(triangles.at(tri), ray.direction);
	
	if(d == 0){
		//temp = {nullptr, NULL, NULL};
		return false;// = {this, 0, part};
	}
	else{
        double t = (dot(x1, this->normal) - dot(ray.endpoint, this->normal))/d;
		if(t < small_t){
		 return temp;
		}
		else{
			temp = {this, t, part};
		}
    }
    return temp;
    */

}

// Compute the bounding box.  Return the bounding box of only the triangle whose
// index is part.
Box Mesh::Bounding_Box(int part) const
{
    Box b;
    TODO;
    return b;
}
