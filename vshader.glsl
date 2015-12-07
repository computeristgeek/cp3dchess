#version 330
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;
layout(location = 2) in vec4 vIndex;
uniform float THangle;
uniform vec4 offset;

out vec4 interColor;
void main()
{
    float angle=THangle*3.14159/180;vec4 off=offset;
    if (vIndex==vec4(0,0,0,0)) {angle=0;off=vec4(0,0,0,0);}
    mat4 trans=mat4(vec4(cos(angle),-sin(angle),0,0),vec4(sin(angle),cos(angle),0,0),vec4(0,0,1,0),vec4(0,0,0,1));
    gl_Position = trans*vPosition+off;
    interColor=vColor;
}
