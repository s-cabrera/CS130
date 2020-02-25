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

    std::cout<<"TODO: allocate and initialize state.image_color and state.image_depth."<<std::endl;    
    
    state.image_width=width;
    state.image_height=height;
    
    //Allocate and initialize the arrays that store color and depth
      
    state.image_color= new pixel[width*height];
	for(int i = 0; i < (width*height); i++){state.image_color[i] = make_pixel(0x00,0x00,0x00);}
    state.image_depth= new float[width*height];
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
        //std::cout << "triangles num = " << state.num_vertices/3 << std::endl; 
        //for every triangle make a data_geometry array of size three
        data_geometry y[3];
        const data_geometry * in[3] = {&y[0], &y[1], &y[2]};
        for(unsigned int j = 0; j < 3; j++){
            //for each data_geometry in the data_geometry array (each vertex)
            
            float temp[state.floats_per_vertex];
            for(int k = 0; k < state.floats_per_vertex; k++){
                temp[k] = *(state.vertex_data + 
                (state.floats_per_vertex * 3 * x) + 
                (state.floats_per_vertex * j)+  k);
            //    std::cout << "temp[" << k << "] = " << temp[k] << std::endl; 
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

// Area function that returns the area of the triangle formed by the three points you used as parameters
float calcArea(vec4& a, vec4 &b, vec4& c, driver_state& state);

// Rasterize the triangle defined by the three vertices in the "in" array.  This
// function is responsible for rasterization, interpolation of data to
// fragments, calling the fragment shader, and z-buffering.
void rasterize_triangle(driver_state& state, const data_geometry* in[3])
{
    std::cout<<"TODO: implement rasterization"<<std::endl;
   
   
    //state.vertex_shader();
    //Pass each vertex 
    // Divide the position by w (vec4 gl_Position has (x,y,z,w))
    //vec4 tempPos;
   
    
    vec4 tempPosArr[3];
    float w  = 0;
    //float i = 0; 
    //float j = 0;
     
    for(int index = 0; index < 3; index++){
        w = in[index]->gl_Position[3];
        
        vec4 tempPos = {(in[index]->gl_Position[0]/w), (in[index]->gl_Position[1]/w), 
        (in[index]->gl_Position[2]/w), (in[index]->gl_Position[3]/w)};
        tempPos[0] = ((tempPos[0] + 1)*(0.5*state.image_width)) - (0.5);
        tempPos[1] = ((tempPos[1] + 1)*(0.5*state.image_height)) - (0.5);
        tempPosArr[index] = tempPos;
    //    int image_index = (state.image_width*j) + i;
    //    state.image_color[image_index] = make_pixel(0xFF,0xFF,0xFF);
    }
    
    float alpha = 0; float beta = 0; float omega = 0;
    vec4 P = {0,0,0,1};
    //const data_geometry * P_ptr = &P; 

    //Iterate through the pixels, calculate the barycentric coordinates, 
    //determine if in triangle area. If so change color to triangle color
    int image_index = 0;
    float abc = calcArea(tempPosArr[2], tempPosArr[0], tempPosArr[1], state);
    for(int i = 0; i < state.image_height; i++){
        for(int j = 0; j < state.image_width; j++){
            image_index = (state.image_width * i) + j;
            P[0] = j;// - 0.5;
            P[1] = i;// - 0.5;
           // P.gl_Position[2] = 0;
           // P.gl_Position[3] = 1;
            

            alpha = calcArea(P, tempPosArr[0], tempPosArr[1], state)/abc;
            beta  = calcArea(tempPosArr[2], P, tempPosArr[1], state)/abc;
            omega = calcArea(tempPosArr[2], tempPosArr[0], P, state)/abc;

            if((alpha >= 0 && alpha <= 1)  
            && (beta >= 0 && beta <= 1) 
            && (omega >= 0 && omega <= 1)){
                // if all barycentric coordinates are >= 0, color is white  
                state.image_color[image_index] = make_pixel(0xFF,0xFF,0xFF);
            }
            //else{
                // else set the color to 
            //    state.image_color[image_index] = make_pixel(0x00, 0x00, 0x00);
            //}
            //image_index++;
        }
    }

    // Calculate the x and y 
    //vec4 is a float vector

    //float x = tempPos[0];

    // Calculate the triangle area = 0.5*((bxcy - cxby) - (axcy - cxay) + (axby - bxay))
    // a(1st vertex in the data_geometry array), b(2nd vertex), and c(3rd vertex)
    // float ax,ay,bx,by,cx,cy, alpha, beta, omega;
    // ax = in[0]->gl_Position[0];
    // ay = in[0]->gl_Position[1];
    // bx = in[1]->gl_Position[0];
    // by = in[1]->gl_Position[1];
    // cx = in[2]->gl_Position[0];
    // cy = in[2]->gl_Position[1];
    // float area = 0.5 * (((bx*cy) - (cx*by)) - ((ax*cy) - (cx*ay)) + ((ax*by) - (bx*ay)));
    
    

}

float calcArea(vec4& a, vec4& b, vec4& c, driver_state& state){
    
    float ax,ay,bx,by,cx,cy;
    // i = ((tempPos[0] + 1)*(0.5*state.image_width)) - (0.5);
    // j = ((tempPos[1] + 1)*(0.5*state.image_height)) - (0.5);

    //Make the equation easier
    ax = a[0]; //((a[0] + 1)*0.5*state.image_width)-0.5;
    ay = a[1]; //((a[1] + 1)*0.5*state.image_height)-0.5;
    bx = b[0]; //((b[0] + 1)*0.5*state.image_width)-0.5;
    by = b[1]; //((b[1] + 1)*0.5*state.image_height)-0.5;
    cx = c[0]; //((c[0] + 1)*0.5*state.image_width)-0.5;
    cy = c[1];//((c[1] + 1)*0.5*state.image_height)-0.5;
    
    return 0.5 * (((bx*cy) - (cx*by)) - ((ax*cy) - (cx*ay)) + ((ax*by) - (bx*ay)));
}
