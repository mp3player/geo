#version 330 core
precision mediump float;

uniform vec3 color;

// out vec4 fcolor;

void main(){
    gl_FragColor = vec4( color , 1.0f );
}
