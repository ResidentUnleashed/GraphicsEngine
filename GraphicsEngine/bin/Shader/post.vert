//Simple post-processing vertex shader

#version 410

layout ( location 0 ) in vec2 Position;

out vec2 vTexCoord;

void main(){
//Generate texture coordinates
vTexCoord = Position * 0.5f + 0.5f;
gl_position = vec4(Position, 0, 1);
}
