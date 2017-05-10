#version 410

#define IOR 1.45

// This is passed on from the vertex shader

in vec3 fragWorldPos;

in vec3 fragNormal;

in vec2 fragmentTexCoord;

uniform sampler2D textureMap;

// This is no longer a built-in variable
layout (location=0) out vec4 FragColor;


void main()
{
    FragColor = texture(textureMap, fragmentTexCoord);
}
