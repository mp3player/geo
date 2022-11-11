#version 330 core  
precision mediump float;  

uniform float width; 
uniform float height; 

layout(location=0) in vec2 position;  

void main(){  
    gl_Position = vec4(position / vec2( width , height ) , 0.0f , 1.0f);   
} 