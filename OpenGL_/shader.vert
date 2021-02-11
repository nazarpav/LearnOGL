#version 330 core

layout (location = 0) in vec3 aPos;
attribute vec2 position;
varying vec2 v_pos;
void main()
{
    v_pos=position;
    gl_Position = vec4(aPos.x+0.1, aPos.y, aPos.z, 1.0);
}