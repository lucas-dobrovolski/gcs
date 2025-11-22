#version 330 core

in vec3 vNormal;
in vec2 vUV;

out vec4 FragColor;

void main(){
    vec3 baseColor = abs(vNormal);  // colorcito según normal
    FragColor = vec4(baseColor, 1.0);
}
