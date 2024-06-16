#version 450 core

out vec4 out_frag_colour;

in vec3 v_colour;

void main()
{
    out_frag_colour = vec4(v_colour, 1.0);
}