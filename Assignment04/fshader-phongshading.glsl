#version 150

in vec4 ambientDiffuseColor;
in vec4 specularColor;
in float specularExponent;
in vec3 N;
in vec3 V;
in vec3 L;
in vec3 H; 

uniform vec4 uLightColor;
uniform vec4 uAmbientLight;

out vec4 fColor;

void main()
{
	vec3 fN = normalize(N);
	vec3 fV = normalize(V);
	vec3 fL = normalize(L);
	vec3 fH = normalize(H);

	vec4 amb = ambientDiffuseColor * uAmbientLight;
	vec4 diff = max(0, dot(fN, fL)) * ambientDiffuseColor * uLightColor;
	vec4 spec = pow(max(0, dot(fN, fH)), specularExponent) * specularColor * uLightColor;

    fColor = amb + diff + spec;
//    fColor = vec4(fN, 1);
}