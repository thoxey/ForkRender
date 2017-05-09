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

void main()
{

    // Transform your input normal
    vec3 n = normalize(fragNormal);
    // Calculate the light vector
    vec3 s = normalize( vec3(Light.Position) - fragWorldPos );
    // Calculate the vertex position
    vec3 v = normalize(-fragWorldPos);
    // Reflect the light about the surface normal
    vec3 r = reflect(s, n);
    //The half vector
    vec3 h = normalize(v+s);
    //Dot product of the surface normal and the half angle
    float NdotH = dot(n, h);
    NdotH = max(NdotH, 0.0001); //Stops NdotH giving a 0 value
    //Dot of the vertex position and the half vector, used for fresnel
    float c = dot(v,h);

#define FULLFRESNEL
#ifdef FULLFRESNEL
    float g = sqrt((IOR*IOR)+(c*c)-1);
    //Fresnel term one
    float F1 = ((g-c)*(g-c))/
            (2*((g+c)+(g+c)));
    //Fresnel term two
    float F2 = 1+((c*(g+c)-1)*(c*(g+c)-1))
            /    ((c*(g-c)-1)*(c*(g-c)+1));
    //full fresnel
    float fresnel = F1 * F2;
#else
    //Schlick approximation
    float F0 = 0.8;
    float fresnel = pow(1.0f - c, 5.0) * (1.0f - F0) + F0;
#endif

    //The shininess squared
    float mSquared = .8f;//Material.Shininess * Material.Shininess;

    //Beckman distribution funcion
    float r1 = 1.0f / (4.0f * mSquared * pow(NdotH, 4.0f));
    float r2 = (NdotH * NdotH - 1.0f) / (mSquared * NdotH * NdotH);
    float Beckman = r1 * exp(r2);


    vec3 beckmanDist = vec3(Beckman, Beckman, Beckman);

    vec3 specular = Light.Ls * pow( max( dot(r,v), 0.0001 ), Beckman) * fresnel;

    // Compute the light from the ambient, diffuse and specular components
    vec3 LightIntensity = (
                Light.La * Material.Ka +
                Light.Ld * Material.Kd * max( dot(s, n), 0.0 ) +
                specular);

    float smudge = texture(glossMap, fragmentTexCoord).r * 8;
    float roughness = clamp(smudge,0,8);
    vec4 envColour = textureLod(envMap, reflect(v, n), roughness)*2;

    // Set the output color of our current pixel
    vec4 mainColour = vec4(LightIntensity,1.0);

    FragColor = envColour * mainColour;
}
