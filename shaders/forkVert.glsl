#version 410

// The modelview and projection matrices are no longer given in OpenGL 4.2
uniform mat4 MV;
uniform mat4 MVP;
uniform mat3 N; // This is the inverse transpose of the MV matrix

// The vertex position attribute
layout (location=0) in vec3 VertexPosition;

// The texture coordinate attribute
layout (location=1) in vec2 inUV;

// The vertex normal attribute
layout (location=2) in vec3 VertexNormal;

smooth out vec3 fragWorldPos;

smooth out vec3 fragNormal;

smooth out vec2 fragmentTexCoord;

/************************************************************************************/
void main() {
    // Set the position of the current vertex
    gl_Position = MVP * vec4(VertexPosition, 1.0);


    fragWorldPos = vec3(MV * vec4(VertexPosition, 1.0f));

    fragmentTexCoord = inUV;

    fragNormal   = N  * VertexNormal;

}
