#version 450 core

layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_colour;

out vec3 v_colour;

uniform mat4 m_model;
uniform mat4 m_view;
uniform mat4 m_proj;

void main()
{
    v_colour = in_colour;
    gl_Position = m_proj * m_view * m_model * vec4(in_pos, 1.0);
}