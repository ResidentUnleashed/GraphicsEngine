//A simple textured shader
#version 410

layout( location = 0 ) in vec4 Position;
layout( location = 2 ) in vec2 TextCoord;

out vec2 vTextCoord;

uniform mat4 ProjectionViewModel;

void main()
{
   vTextCoord = TextCoord;
   gl_Position = ProjectionViewModel * Position;
}