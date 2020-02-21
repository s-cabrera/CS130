#include "driver_state.h"
#include <cstring>

driver_state::driver_state()
{
}

driver_state::~driver_state()
{
    delete [] image_color;
    delete [] image_depth;
}

// This function should allocate and initialize the arrays that store color and
// depth.  This is not done during the constructor since the width and height
// are not known when this class is constructed.
void initialize_render(driver_state& state, int width, int height)
{
    state.image_width=width;
    state.image_height=height;
    
    //Allocate and initialize the arrays that store color and depth
      
    state.image_color= new pixel[width*height];
	for(int i = 0; i < (width*height); i++){state.image_color[i] = make_pixel(0xFF,0xFF,0xFF);}
    state.image_depth= new float[width*height];
    std::cout<<"TODO: allocate and initialize state.image_color and state.image_depth."<<std::endl;
}

// This function will be called to render the data that has been stored in this class.
// Valid values of type are:
//   render_type::triangle - Each group of three vertices corresponds to a triangle.
//   render_type::indexed -  Each group of three indices in index_data corresponds
//                           to a triangle.  These numbers are indices into vertex_data.
//   render_type::fan -      The vertices are to be interpreted as a triangle fan.
//   render_type::strip -    The vertices are to be interpreted as a triangle strip.
void render(driver_state& state, render_type type)
{

    std::cout<<"TODO: implement rendering."<<std::endl;
    //data_geometry * xpt; // pointer to each new data_geometry array of size 3
    int x = 0;
   // data_geometry x[3];
    for(int i = 0; i < (state.num_vertices/3); i++){
        //for every triangle make a data_geometry array of size three
        data_geometry y[3];
        const data_geometry * in[3] = {&y[0], &y[1], &y[2]};
        for(unsigned int j = 0; j < 3; j++){
            //for each data_geometry in the data_geometry array
            float temp[state.floats_per_vertex];
            for(int k = 0; k < state.floats_per_vertex; k++){
                temp[k] = *(state.vertex_data + state.floats_per_vertex + x);
            }
            y[j].data = temp;
        }
        x++;
        rasterize_triangle(state, in);
    }
    
    //for(num_triangles)
    
    //for(unsigned int i = 0; i < 3; i++){
	//    for(int j = 0; j < state.floats_per_vertex; j++){
    //        x[index_data].data = state.vertex_data;
            //state(*vertex_shader)(state.vertex_data, x[i], state.uniform_data);
	//    }
    //}
    //rasterize_triangle(state, x); 
    //state.vertex_data = 
   // state.num_vertices = 
   // state.floats_per_vertex = 
   
   //(this)(state.vertex_data, x[i], );
}


// This function clips a triangle (defined by the three vertices in the "in" array).
// It will be called recursively, once for each clipping face (face=0, 1, ..., 5) to
// clip against each of the clipping faces in turn.  When face=6, clip_triangle should
// simply pass the call on to rasterize_triangle.
void clip_triangle(driver_state& state, const data_geometry* in[3],int face)
{
    if(face==6)
    {
        rasterize_triangle(state, in);
        return;
    }
    std::cout<<"TODO: implement clipping. (The current code passes the triangle through without clipping them.)"<<std::endl;
    clip_triangle(state,in,face+1);
}

// Rasterize the triangle defined by the three vertices in the "in" array.  This
// function is responsible for rasterization, interpolation of data to
// fragments, calling the fragment shader, and z-buffering.
void rasterize_triangle(driver_state& state, const data_geometry* in[3])
{
    std::cout<<"TODO: implement rasterization"<<std::endl;
   // for(int i = 0;  i < 3; i++){
//	( , in[i], state.uniform_data);
 //   }

}

