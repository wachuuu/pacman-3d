#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 lpos1;
uniform vec4 lpos2;
uniform vec4 lpos3;
uniform vec4 lpos4;

//Atrybuty
layout (location=0) in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
layout (location=1) in vec4 normal; //wektor normalny w wierzcholku
layout (location=2) in vec2 texCoord; //wspó³rzêdne teksturowania


//Zmienne interpolowane
out vec4 n;
out vec4 v;
out vec4 l1;
out vec4 l2;
out vec4 l3;
out vec4 l4;
out vec2 iTexCoord0;


void main(void) {

    l1 = normalize(V*lpos1 - V*M*vertex);
    l2 = normalize(V*lpos2 - V*M*vertex);
    l3 = normalize(V*lpos3 - V*M*vertex);
    l4 = normalize(V*lpos4 - V*M*vertex);
    
    n = normalize(V*M*normal);
    v = normalize(vec4(0,0,0,1)-V*M*vertex);

    iTexCoord0=texCoord;

    gl_Position=P*V*M*vertex;
}
