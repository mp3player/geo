#version 330 core  
precision mediump float;  

uniform mat3 transform;

uniform float width; 
uniform float height; 

layout(location=0) in vec2 position;  

void main(){  
    vec3 pos = vec3( position / vec2( width , height ) , 0.0f );
    pos = transform * pos;
    gl_Position = vec4( pos , 1.0f );   
} 