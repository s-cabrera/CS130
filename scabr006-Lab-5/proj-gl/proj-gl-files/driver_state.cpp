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
    int x = 0;
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
            data_vertex z;
            z.data = y[j].data;
            state.vertex_shader(z, y[j], state.uniform_data);
        }
        x++;
        rasterize_triangle(state, in);
    }
    
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
    //state.vertex_shader();
    //Pass each vertex 
    // Divide the position by w (vec4 gl_Position has (x,y,z,w))
    vec4 tempPos;
    vec4 tempPosArr[3];
    float w  = 0;
    float i, j; 
    for(int index = 0; index < 3; index++){
        w = in[index]->gl_Position[3];
        tempPos = {(in[index]->gl_Position[0]/w), (in[index]->gl_Position[1]/w), (in[index]->gl_Position[2]/w), (in[index]->gl_Position[3]/w)};
        tempPosArr[index] = tempPos;
        i = ((tempPos[0] + 1)*(0.5*state.image_width)) - (0.5);
        j = ((tempPos[1] + 1)*(0.5*state.image_height)) - (0.5);
    }

    //Iterate through the pixels
    for(int j = 0; j < state.image_height; j++){
        for(int k = 0; k < state.image_width; k ++){

        }
       // state.image_color[j]  = ;
    }

    // Calculate the x and y 
    //vec4 is a float vector

    //float x = tempPos[0];

    // Calculate the area of the triangle
    float area = 0.5*
    // Calculate the barycentric coordinates
    
}

