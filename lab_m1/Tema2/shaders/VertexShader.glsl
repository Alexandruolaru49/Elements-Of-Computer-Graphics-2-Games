#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_color;  
layout(location = 2) in vec2 v_coord;
layout(location = 3) in vec3 v_normal;
 

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 Color;
uniform vec3 CarPosition;

// Output
out vec3 fragment_position;
out vec3 fragment_color;
out vec2 fragment_coord;
out vec3 fragment_normal;

void main()
{
    vec3 world_position = (Model * vec4(v_position, 1)).xyz;
    float scale_factor= 0.005;

    vec3 newVec;
    newVec.x = CarPosition.x - world_position.x;
    newVec.y = CarPosition.y - world_position.y;
    newVec.z = CarPosition.z - world_position.z;

    world_position.y = world_position.y - (pow(newVec.x, 2) + pow(newVec.y, 2) + pow(newVec.z, 2)) * scale_factor;

    fragment_position = world_position;
    fragment_color = Color;
    fragment_coord = v_coord;
	fragment_normal = v_normal;

    gl_Position = Projection * View * vec4(world_position, 1);

}
