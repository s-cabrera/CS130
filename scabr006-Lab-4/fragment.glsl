varying vec4 position;
varying vec3 normal;
varying vec3 light_direction;

struct gl_LightSourceParameters{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;  
    vec4 position;
};
uniform gl_LightSourceParameters gl_LightSource[gl_MaxLights];
struct gl_LightMode1Parameters{
    vec4 ambient;
};
uniform gl_LightModeParameters gl_lightModel;

struct gl_MaterialsParameters{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess; // this is the exponent of the specular component
};
uniform gl_MaterialParameters gl_FrontMaterial;


void main()
{
    vec4 ambient = vec4(1, 0, 0, 1);
    vec4 diffuse = vec4(0, 1, 0, 1);
    vec4 specular = vec4(0, 0, 1, 1);
    //double d = dot(normal, light_direction); 
    //vec3 r = light direction - (2(dot(light_direction, normalized(normal)*d) * (normal.normalized * d;
    //diffuse = diffuse * r; 
   // diffuse*(ambient +  )

    gl_FragColor = ambient + diffuse + specular;
	
}
