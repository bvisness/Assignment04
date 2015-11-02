#version 150

#define MAX_LIGHTS 6

in vec4 ambientDiffuseColor;
in vec4 specularColor;
in float diffuseAmount;
in float specularAmount;
in float specularExponent;
in vec3 N[MAX_LIGHTS];
in vec3 L[MAX_LIGHTS];
in vec3 H[MAX_LIGHTS];

uniform int uLightType[MAX_LIGHTS];
uniform vec4 uLightDirection[MAX_LIGHTS];
uniform vec4 uLightColor[MAX_LIGHTS];
uniform vec4 uAmbientLight;

out vec4 fColor;

void main()
{
    vec4 amb = ambientDiffuseColor * uAmbientLight;
    vec4 diff = vec4(0, 0, 0, 0);
    vec4 spec = vec4(0, 0, 0, 0);
    
    for (int i = 0; i < MAX_LIGHTS; i++) {
        if (uLightType[i] == 0) {
            continue;
        }
        
        vec3 fN = N[i];
        vec3 fL = L[i];
        vec3 fH = H[i];

        diff += max(0, dot(fN, fL)) * diffuseAmount * ambientDiffuseColor * uLightColor[i];
        spec += pow(max(0, dot(fN, fH)), specularExponent) * specularAmount * specularColor * uLightColor[i];
    }
    
    fColor = amb + diff + spec;
    //fColor = amb;
    //fColor = diff;
    //fColor = spec;
    //fColor = vec4(fN, 1);
    //fColor = vec4(diffuseAmount, diffuseAmount, diffuseAmount, 1);
    //fColor = vec4(specularAmount, specularAmount, specularAmount, 1);
    //fColor = vec4(specularExponent, specularExponent, specularExponent, 1);
}
