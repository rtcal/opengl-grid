#version 450 core

layout (location = 0) in vec3 in_pos;

uniform mat4 m_model;
uniform mat4 m_view;
uniform mat4 m_proj;

void main()
{
    gl_Position = m_proj * m_view * m_model * vec4(in_pos, 1.0);
}