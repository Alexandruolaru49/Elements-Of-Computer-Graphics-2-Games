#version 330

// Input
// TODO(student): Get values from vertex shader
in vec3 fragment_position;
in vec3 fragment_color;
in vec2 fragment_coord;
in vec3 fragment_normal;


// Output
layout(location = 0) out vec4 out_color;


void main()
{
    // TODO(student): Write pixel out color
    out_color = vec4(fragment_color, 1);

}
