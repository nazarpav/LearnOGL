#version 460 core

layout (location = 0) in vec3 aPos;
varying vec2 v_pos;
void main()
{
    v_pos=aPos.xy;
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}