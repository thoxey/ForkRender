#version 410

#define IOR 1.45

// This is passed on from the vertex shader

in vec3 fragWorldPos;

in vec3 fragNormal;

in vec2 fragmentTexCoord;

uniform samplerCube envMap;

uniform sampler2D glossMap;

// This is no longer a built-in variable
layout (location=0) out vec4 FragColor;

// Structure for holding light parameters
struct LightInfo {
    vec4 Position; // Light position in eye coords.
    vec3 La; // Ambient light intensity
    vec3 Ld; // Diffuse light intensity
    vec3 Ls; // Specular light intensity
};

// We'll have a single light in the scene with some default values
LightInfo Light = LightInfo(
            vec4(5.0, 15.0, 10.0, 1.0),  // position
            vec3(0.2, 0.2, 0.2),        // La
            vec3(1.0, 1.0, 1.0),        // Ld
            vec3(1.0, 1.0, 1.0)         // Ls
            );

// The material properties of our object
struct MaterialInfo {
    vec3 Ka; // Ambient reflectivity
    vec3 Kd; // Diffuse reflectivity
    vec3 Ks; // Specular reflectivity
    float Shininess; // Specular shininess factor
};

// The object has a material
uniform MaterialInfo Material = MaterialInfo(
            vec3(0.1, 0.1, 0.1),    // Ka
            vec3(1.0, 1.0, 1.0),    // Kd
            vec3(1.0, 1.0, 1.0),    // Ks
            1.0                    // Shininess
            );

float fresnel(float _VdotH)
{
#define FULLFRESNEL
#ifdef FULLFRESNEL
    float g = sqrt((IOR*IOR)+(_VdotH*_VdotH)-1);
    //Fresnel term one
    float F1 = ((g-_VdotH)*(g-_VdotH))/
            (2*((g+_VdotH)+(g+_VdotH)));
    //Fresnel term two
    float F2 = 1+((_VdotH*(g+_VdotH)-1)*(_VdotH*(g+_VdotH)-1))
            /    ((_VdotH*(g-_VdotH)-1)*(_VdotH*(g-_VdotH)+1));
    //full fresnel
    return F1 * F2;
#else
    //Schlick approximation
    float F0 = 0.8;
    return pow(1.0f - _VdotH, 5.0) * (1.0f - F0) + F0;
#endif
}

float beckmanRoughness(float _NdotH)
{
    //The shininess squared
    float mSquared = 1.8f;//Material.Shininess * Material.Shininess;

    //Beckman distribution funcion
    float r1 = 1.0f / (4.0f * mSquared * pow(_NdotH, 4.0f));
    float r2 = _NdotH * _NdotH - 1.0f;
    float r3 = mSquared * _NdotH * _NdotH;
    return r1 * exp(r2/r3);
}

//https://github.com/kamil-kolaczynski/synthclipse-demos/blob/master/src/jsx-demos/lighting-models/shaders/model/cook-torrance.glsl
float geoTerm(float _NdotH, float _VdotH, float _NdotL, float _NdotV)
{
    float geo_numerator = 2.0 * _NdotH;
    float geo_denominator = _VdotH;

    float geo_b = (geo_numerator * _NdotV) / geo_denominator;
    float geo_c = (geo_numerator * _NdotL) / geo_denominator;
    return min(1.0, min(geo_b, geo_c));
}

vec4 envColour(vec3 _v, vec3 _n)
{

    float smudge = texture(glossMap, fragmentTexCoord).r * 8;
    float roughness = clamp(smudge,0,8);
    return textureLod(envMap, reflect(_v, _n), roughness)*2;

}

void main()
{
    // Transform your input normal
    vec3 n = normalize(fragNormal);
    // Calculate the light vector
    vec3 l = normalize( vec3(Light.Position) - fragWorldPos );
    // Calculate the vertex position
    vec3 v = normalize(-fragWorldPos);
    // Reflect the light about the surface normal
    vec3 r = reflect(l, n);
    //The half vector
    vec3 h = normalize(v+l);
    //Dot product of the surface normal and the half angle
    float NdotH = clamp(dot(n, h), 0.0, 1.0);
    //Dot of the light and the normal vectors
    float NdotL = clamp(dot(n,l), 0.0,1.0);
    //Dot of the normal and the and the view vector
    float NdotV = clamp(dot(n,v),0.0,1.0);
    //Dot of the vertex position and the half vector, used for fresnel
    float VdotH = clamp(dot(v,h), 0.0, 1.0);

    //https://github.com/kamil-kolaczynski/synthclipse-demos/blob/master/src/jsx-demos/lighting-models/shaders/model/cook-torrance.glsl
    vec3 Rs_numerator = vec3(fresnel(VdotH)
                             * geoTerm(NdotH, VdotH, NdotL, NdotV)
                             * beckmanRoughness(NdotH));
    float Rs_denominator = NdotV * NdotL;
    vec3 Rs = Rs_numerator / Rs_denominator;

    vec3 final = max(0.0, NdotL) * (vec3(1.0)*Rs + vec3(0.9));

    FragColor = /*envColour(v, n) **/ vec4(final, 1.0);
}
