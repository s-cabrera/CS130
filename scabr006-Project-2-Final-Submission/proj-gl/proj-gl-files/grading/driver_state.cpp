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

   // std::cout<<"TODO: allocate and initialize state.image_color and state.image_depth."<<std::endl;    
    
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

    //std::cout<<"TODO: implement rendering."<<std::endl;
    
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
        //rasterize_triangle(state, in);
        clip_triangle(state, in, 0);
    }
  
}

float interpolate(driver_state & state, const data_geometry* in[3], int sign, int axis, int index, int other_index);

// This function clips a triangle (defined by the three vertices in the "in" array).
// It will be called recursively, once for each clipping face (face=0, 1, ..., 5) to
// clip against each of the clipping faces in turn.  When face=6, clip_triangle should
// simply pass the call on to rasterize_triangle.
void clip_triangle(driver_state& state, const data_geometry* in[3],int face)
{
    if(face==6)
    {
        std :: cout << "Rasterized triangle" << std :: endl;
        rasterize_triangle(state, in);
        return;
    }
 //   std::cout<<"TODO: implement clipping. (The current code passes the triangle through without clipping them.)"<<std::endl;
    

    /*
    /////////////////////////////////////////////////////////////////
    GENERAL HINT by Kris on the whiteboard
    Note: Make copies of the data before passing in !!!!!!
    Faces:
         0 & 1 = x
         2 & 3 = y
         4 & 5 = z
        
        Face /2 = ?
        Face %2 = ? 
         -w <= x <= w 
         x <= w
         x > = -w  =>  -x <= w
         
        Use this one;
        This is for choosing what face.
    //////////////////////////////////////////////////////////////////

    Cases for clipping: 
    
    Case #1: All vertices are "inside": no clipping -> pass to next face 
    
    Case #2: All vertices are "outside": do not draw triangle
    
    Case #3: 1 vertice is "inside": Pass triangle made by the vertice on the inside and the "border" and discard the rest.
    
    Case #4: 2 vertices are "inside": Pass in two triangles (call the clipping function twice) and discard the rest.
    
    How to check what case to use:
    Step 1: Loop through the vertices(positions) and check if they are inside (x < w) or outside (x > w) 
    */
 
    int caseNum = 0;
    data_geometry temp[3];    
    const data_geometry *inTemp[3] = {&temp[0], &temp[1], &temp[2]};
    int axis = (face/2);
    int sign = (face % 2) ? -1: 1;
    std :: cout << "axis: " << axis << ", sign: " << sign << std:: endl;  
    for(int i = 0; i < 3; i++){
        temp[i].data = new float[state.floats_per_vertex];
        for(int j = 0 ; j < state.floats_per_vertex; j++){temp[i].data[j] = in[i]->data[j];}
        for(int j = 0; j < 4; j++){temp[i].gl_Position[j] = in[i]->gl_Position[j];}

        //for(int j = 0; j < state.floats_per_vertex; j++){std :: cout << "temp[" << i << "].data["<< j << "] = " << temp[i].data[j] << "  ";}
        //std :: cout << std :: endl;
        //for(int j = 0; j < 4; j++){std :: cout << "temp[" << i << "].glPosition["<< j <<"] = " << temp[j].gl_Position[j] << "  ";} 
        //std :: cout << std :: endl;
        std :: cout << "For " << i << ", X or -X: " << (sign*in[i]->gl_Position[axis]) << ";  W: " << in[i]->gl_Position[3] << std :: endl; 
        if((sign*in[i]->gl_Position[axis]) <= in[i]->gl_Position[3]){caseNum++;}
    }

    if(caseNum == 3){
        //This is Case #1 from above
        std :: cout << "This is case 1" << std :: endl;
       // std :: cout << std :: endl;
        clip_triangle(state,inTemp,face+1);
    }
        
    else if(caseNum == 0){
        // This is Case #2 from above
        std :: cout << "This is case 2" << std :: endl;
        //return;
        //clip_triangle(state,in,face+1);
    }

    else if(caseNum == 1){
        // This is Case #3 from above
        std :: cout << "This is case 3" << std :: endl;
        int indx = 0;
        for(int i = 0; i < 3; i++){if((sign*in[i]->gl_Position[axis]) <= in[i]->gl_Position[3]){indx = i;}}
        //temp[i] stays the same;
        //float alpha = 0; float beta = 0;
        
        if(indx == 0){
            // Calculating M
            float lambda = interpolate(state, in, sign, axis, indx, 1);   
            for(int i = 0; i < 4; i++){temp[1].gl_Position[i] = 
                ((1 -lambda) * in[indx]->gl_Position[i]) + (lambda * in[1]->gl_Position[i]);}
            for(int i = 0; i < state.floats_per_vertex; i++){
                temp[1].data[i] = ((1-lambda) * in[indx]->data[i]) + (lambda * in[1]->data[i]);
            }

            //Calculating N    
            lambda = interpolate(state, in, sign, axis, indx, 2);   
            for(int i = 0; i < 4; i++){temp[2].gl_Position[i] = 
                ((1 -lambda) * in[indx]->gl_Position[i]) + (lambda * in[2]->gl_Position[i]);}
            for(int i = 0; i < state.floats_per_vertex; i++){
                temp[2].data[i] = ((1-lambda) * in[indx]->data[i]) + (lambda * in[2]->data[i]);
            }

        } 
        else if(indx == 1){
            // Calculating M
            float lambda = interpolate(state, in, sign, axis, indx, 0);   
            for(int i = 0; i < 4; i++){temp[0].gl_Position[i] = 
                ((1 -lambda) * in[indx]->gl_Position[i]) + (lambda * in[0]->gl_Position[i]);}
            for(int i = 0; i < state.floats_per_vertex; i++){
                temp[0].data[i] = ((1-lambda) * in[indx]->data[i]) + (lambda * in[0]->data[i]);
            }

            // Calculating N
            lambda = interpolate(state, in, sign, axis, indx, 2);   
            for(int i = 0; i < 4; i++){temp[2].gl_Position[i] = 
                ((1 -lambda) * in[indx]->gl_Position[i]) + (lambda * in[2]->gl_Position[i]);}
            for(int i = 0; i < state.floats_per_vertex; i++){
                temp[2].data[i] = ((1-lambda) * in[indx]->data[i]) + (lambda * in[2]->data[i]);
            }
        }
        else if(indx == 2){
            float lambda = interpolate(state, in, sign, axis, indx, 0);   

            for(int i = 0; i < 4; i++){temp[0].gl_Position[i] = 
                ((1 -lambda) * in[indx]->gl_Position[i]) + (lambda * in[0]->gl_Position[i]);}
            for(int i = 0; i < state.floats_per_vertex; i++){
                temp[0].data[i] = ((1-lambda) * in[indx]->data[i]) + (lambda * in[0]->data[i]);
            }

            lambda = interpolate(state, in, sign, axis, indx, 1);   
            for(int i = 0; i < 4; i++){temp[1].gl_Position[i] = 
                ((1 -lambda) * in[indx]->gl_Position[i]) + (lambda * in[1]->gl_Position[i]);}
            for(int i = 0; i < state.floats_per_vertex; i++){
                temp[1].data[i] = ((1-lambda) * in[indx]->data[i]) + (lambda * in[1]->data[i]);
            }
        }   
        //    std :: cout << std :: endl;
            clip_triangle(state,inTemp,face+1);
    }

    else if(caseNum == 2){
        //This is Case #4 from above
        std :: cout << "This is case 4" << std :: endl;
        
        ivec2 indxs = {0,0};
        int indexes = 0;
        int not_index = 0;
        for(int i = 0; i < 3; i++){
            if((sign*in[i]->gl_Position[axis]) <= in[i]->gl_Position[3]){
                indxs[indexes] = i;
            //    std :: cout << "indexes = " << indxs[indexes] << std::endl;
                indexes++;
            }
            else{
                not_index = i;
            //    std :: cout << "not_index = " << not_index << std::endl;
            }
        }
        


        float lambda = interpolate(state, in, sign, axis, indxs[0], not_index);  
        //std :: cout << "Lambda for M: " << lambda << std :: endl;
        data_geometry M;
        //Calculating M
        
        // for(int i = 0; i < 4; i++){
        //     //temp[indxs[0]].gl_Position[i] = 
        //     M.gl_Position[i] = ((1-lambda) * in[indxs[0]]->gl_Position[i] ) + (lambda * in[not_index]->gl_Position[i]);
        //     std :: cout << "M.Pos[" << i <<"]." << M.gl_Position[i] << "  ";  
        // }
        // std :: cout << std :: endl;
        
        
        M.data = new float [state.floats_per_vertex];
        for(int i = 0; i < state.floats_per_vertex; i++){
            M.data[i] = ((1-lambda) * in[indxs[0]]->data[i]) + (lambda * in[not_index]->data[i]);
        //    std :: cout << "M.data[" << i << "] = " << M.data[i] << "  ";
        }
        //std :: cout << std :: endl;
        data_vertex z;
        z.data = M.data;
        state.vertex_shader(z, M, state.uniform_data);

         for(int i = 0; i < 4; i++){
        //     //temp[indxs[0]].gl_Position[i] = 
        //     M.gl_Position[i] = ((1-lambda) * in[indxs[0]]->gl_Position[i] ) + (lambda * in[not_index]->gl_Position[i]);
        //     std :: cout << "M.Pos[" << i <<"]: " << M.gl_Position[i] << "  ";  
        }
        //std :: cout << std :: endl;

        data_geometry N;
        lambda = interpolate(state, in, sign, axis, indxs[1], not_index);
        //std :: cout << "Lambda for N: " << lambda << std :: endl;
        //Calculating N
        // for(int i = 0; i < 4; i++){
        //     //temp[indxs[1]].gl_Position[i] = 
        //     N.gl_Position[i] = 
        //     ((1-lambda) * in[indxs[1]]->gl_Position[i] ) + (lambda * in[not_index]->gl_Position[i]);
        //     std :: cout << "N[" << i <<"]" << N.gl_Position[i] << "  ";  
        // }
        // std :: cout << std :: endl;
        
        N.data = new float [state.floats_per_vertex];
        for(int i = 0; i < state.floats_per_vertex; i++){
            N.data[i] = ((1-lambda) * in[indxs[1]]->data[i]) + (lambda * in[not_index]->data[i]);
        //    std :: cout << "N.data[" << i << "] = " << N.data[i] << "  ";
        }
        //std :: cout << std :: endl;

        z.data = N.data;
        state.vertex_shader(z, N, state.uniform_data);
        
        for(int i = 0; i < 4; i++){
        //     //temp[indxs[0]].gl_Position[i] = 
        //     M.gl_Position[i] = ((1-lambda) * in[indxs[0]]->gl_Position[i] ) + (lambda * in[not_index]->gl_Position[i]);
        //     std :: cout << "N.Pos[" << i <<"]: " << N.gl_Position[i] << "  ";  
        }
        //std :: cout << std :: endl;

        const data_geometry *ABM[3] = {&temp[indxs[0]], &temp[indxs[1]] , &M };
        const data_geometry *MBN[3] = {&M, &temp[indxs[1]], &N};
        
        //std :: cout << "Clipping #1" << std :: endl;
        clip_triangle(state, ABM, face + 1);
        //std :: cout << "Clipping #2" << std :: endl;
        clip_triangle(state, MBN, face + 1);        
        //clip_triangle(state,in,face+1);
        //clip_triangle(state,in,face+1);
    }
    
    //clip_triangle(state,in,face+1);
}

// Area function that returns the area of the triangle formed by the three points you used as parameters
float calcArea(vec4& a, vec4 &b, vec4& c);

// Rasterize the triangle defined by the three vertices in the "in" array.  This
// function is responsible for rasterization, interpolation of data to
// fragments, calling the fragment shader, and z-buffering.
void rasterize_triangle(driver_state& state, const data_geometry* in[3])
{
    //std::cout<<"TODO: implement rasterization"<<std::endl;
   
    
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



                if(depth < state.image_depth[image_index]){
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

float interpolate(driver_state & state, const data_geometry* in[3], int sign, int axis, int index, int other_index){
    float xa = in[index]->gl_Position[axis];
    float wa = sign * in[index]->gl_Position[3];
    float xb = in[other_index]->gl_Position[axis];
    float wb = sign *in[other_index]->gl_Position[3];
    return (xa - wa)/((xa - wa) + (wb - xb));
}
