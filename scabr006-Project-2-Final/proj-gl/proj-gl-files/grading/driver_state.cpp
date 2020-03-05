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
    for(int i = 0; i < (width*height); i++){state.image_depth[i] = 1;}
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
        //std::cout << "x = " << x << std :: endl << std:: endl;
        //std::cout << "triangles num = " << state.num_vertices/3 << std::endl; 
        //for every triangle make a data_geometry array of size three
        data_geometry y[3];
        const data_geometry * in[3] = {&y[0], &y[1], &y[2]};
        for(unsigned int j = 0; j < 3; j++){
            //for each data_geometry in the data_geometry array (each vertex)
            
            y[j].data = new float[state.floats_per_vertex];
            for(int k = 0; k < state.floats_per_vertex; k++){
                y[j].data[k] = *(state.vertex_data + 
                (state.floats_per_vertex * 3 * x) + 
                (state.floats_per_vertex * j)+  k);
                //std::cout << "[" << k << "] = " << temp[k] << std::endl; 
            }
            //y[j].data = temp;
            //for(int k = 0; k < state.floats_per_vertex; k++){ std::cout << "y["<< j <<"].data["<<k<<"] = " << y[j].data[k] << std :: endl;}
           
            data_vertex z;
            z.data = y[j].data;
            //for(int k = 0; k < state.floats_per_vertex; k++){std::cout << "z.data[" << k << "]: " << z.data[k] << std :: endl;}
            
            state.vertex_shader(z, y[j], state.uniform_data);
        } 
        x++;
       // std::cout << "x = " << x << std :: endl << std:: endl;
       // for(int k = 0; k < 3; k++){
       //     for(int l = 0; l < state.floats_per_vertex; l++){
       //         std :: cout << "in[" << k <<  "].data["<< l <<"] = " << in[k]->data[l] << std :: endl;
       //     }
       // }
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
    //std::cout<<"TODO: implement clipping. (The current code passes the triangle through without clipping them.)"<<std::endl;
    clip_triangle(state,in,face+1);
}

// Area function that returns the area of the triangle formed by the three points you used as parameters
float calcArea(vec4& a, vec4 &b, vec4& c);

// Rasterize the triangle defined by the three vertices in the "in" array.  This
// function is responsible for rasterization, interpolation of data to
// fragments, calling the fragment shader, and z-buffering.
void rasterize_triangle(driver_state& state, const data_geometry* in[3])
{
    std::cout<<"TODO: implement rasterization"<<std::endl;
   
    
    vec4 tempPosArr[3];
    float w  = 0;

    for(int index = 0; index < 3; index++){
        w = in[index]->gl_Position[3];
        vec4 tempPos = {(in[index]->gl_Position[0]/w), (in[index]->gl_Position[1]/w), 
        (in[index]->gl_Position[2]/w), (in[index]->gl_Position[3]/w)};
        tempPos[0] = ((tempPos[0] + 1)*(0.5*state.image_width)) - (0.5);
        tempPos[1] = ((tempPos[1] + 1)*(0.5*state.image_height)) - (0.5);
        tempPosArr[index] = tempPos;
    }
    
    //Iterate through the pixels that contain the triangle, calculate the barycentric coordinates, 
    //determine if in triangle area. If so change color to triangle color
    
    //Calculating the x and y min and max
    float xmin, xmax, ymin, ymax;
     xmin = tempPosArr[0][0]; 
     ymin = tempPosArr[0][1];
     xmax = tempPosArr[0][0];
     ymax = tempPosArr[0][1];
     for(int i  = 1; i < 3; i++){
         if(tempPosArr[i][0] > xmax){
             xmax = tempPosArr[i][0];
         }
         if(tempPosArr[i][0] < xmin){
             xmin = tempPosArr[i][0];
         } 
         if(tempPosArr[i][1] > ymax){
             ymax = tempPosArr[i][1];
         }
         if(tempPosArr[i][1] < ymin){
             ymin = tempPosArr[i][1];
         }
        }   

    int image_index = 0;
    float abc = calcArea(tempPosArr[0], tempPosArr[1], tempPosArr[2]);
    

    for(int i = ymin; i < ymax; i++){
        for(int j = xmin; j < xmax; j++){
            image_index = (state.image_width * i) + j;
            vec4 P = {0,0,0,1};
            P[0] = j;
            P[1] = i;
            
            float alpha = calcArea(P, tempPosArr[1], tempPosArr[2])/abc;
            float beta  = calcArea(tempPosArr[0], P, tempPosArr[2])/abc;
            float omega = calcArea(tempPosArr[0], tempPosArr[1], P)/abc;

            //float depth = (alpha*tempPosArr[0][2]) + (beta*tempPosArr[1][2]) + (omega*tempPosArr[2][2]);

            if((alpha >= 0 && alpha <= 1)  
            && (beta >= 0 && beta <= 1) 
            && (omega >= 0 && omega <= 1)){ 

                float depth = (alpha*tempPosArr[0][2]) + (beta*tempPosArr[1][2]) + (omega*tempPosArr[2][2]);



                if(depth <=  state.image_depth[image_index]){
                    state.image_depth[image_index] = depth;

                    data_output output;
                    data_fragment fragTemp; 
                    fragTemp.data = new float [state.floats_per_vertex]; 
                    // if all barycentric coordinates are >= 0, color is white  
                    for(int k = 0; k < state.floats_per_vertex; k++){   
                   
                        if(state.interp_rules[k] ==  interp_type:: flat){
                                fragTemp.data[k] = in[0]->data[k];

                        }

                        else if(state.interp_rules[k] == interp_type::noperspective){
                            fragTemp.data[k] = (alpha*in[0]->data[k]) + (beta*in[1]->data[k]) + (omega*in[2]->data[k]);
                            //std::cout << fragTemp.data[k] << std::endl;
                        }
                       
                        else if(state.interp_rules[k] == interp_type::smooth){}
                        else if(state.interp_rules[k] == interp_type::invalid){}
                    }
                    const data_fragment frag = {fragTemp.data};
                    state.fragment_shader(frag, output, state.uniform_data);

                    state.image_color[image_index] = make_pixel(
                        0xFF * output.output_color[0],
                        0xFF * output.output_color[1],
                        0xFF * output.output_color[2]);
                }  

            }
        }
    }
}

float calcArea(vec4& a, vec4& b, vec4& c){
    
    return 0.5 * (((b[0]*c[1]) - (c[0]*b[1])) - ((a[0]*c[1]) - (c[0]*a[1])) + ((a[0]*b[1]) - (b[0]*a[1])));
}
