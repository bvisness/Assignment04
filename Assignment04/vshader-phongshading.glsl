#version 150

in vec4 vPosition;
in vec4 vAmbientDiffuseColor;
in vec3 vNormal;
in float vDiffuseAmount;
in float vSpecularAmount;
in float vSpecularExponent;

vec4 vSpecularColor = vec4(1, 1, 1, 1);

out vec4 posEye;
out vec3 normal;
out vec4 ambientDiffuseColor;
out vec4 specularColor;
out float diffuseAmount;
out float specularAmount;
out float specularExponent;

uniform mat4 uModelView;
uniform mat4 uProjection;

void main()
{
	posEye = uModelView * vPosition;
	normal = (uModelView * vec4(vNormal, 0)).xyz;
	ambientDiffuseColor = vAmbientDiffuseColor;
	specularColor = vSpecularColor;
    diffuseAmount = vDiffuseAmount;
    specularAmount = vSpecularAmount;
    specularExponent = vSpecularExponent;

	gl_Position = uProjection * posEye;
}
