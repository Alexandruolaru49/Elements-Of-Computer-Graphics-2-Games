#version 330

uniform sampler2D u_texture_0;

// Input
in vec3 fragment_position;
in vec3 fragment_color;
in vec2 fragment_coord;
in vec3 fragment_normal;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    out_color = vec4(fragment_color, 1);

}
