#version 410

in vec4 vPosition;
in vec3 vNormal;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;

uniform vec3 cameraPosition;

uniform float specularPower;

uniform vec3 Ia;

uniform vec3 Id;
uniform vec3 Id2;
uniform vec3 Is;
uniform vec3 Is2;

uniform vec3 LightDirection;
uniform vec3 LightDirection2;

out vec4 FragColour;

void main() 
{
	vec3 N = normalize(vNormal);
	vec3 L = normalize(LightDirection);
	vec3 L2 = normalize(LightDirection2);

	
	float lambertTerm = max( 0, min( 1, dot( N, -L ) ) );
	float lambertTerm2 = max( 0, min( 1, dot( N, -L2 ) ) );
	
	vec3 V = normalize(cameraPosition - vPosition.xyz);
	vec3 R = reflect( L, N );
	vec3 R2 = reflect( L2, N );
	
	float specularTerm = pow( max( 0, dot( R, V ) ), specularPower );
	float specularTerm2 = pow( max( 0, dot( R2, V ) ), specularPower );
	
	vec3 ambient = Ia * Ka;
	vec3 diffuse = Id * Kd * lambertTerm;
	vec3 diffuse2 = Id2 * Kd * lambertTerm2;
	vec3 specular = Is * Ks * specularTerm;
	vec3 specular2 = Is2 * Ks * specularTerm2;

	FragColour = vec4( ambient + diffuse + diffuse2 + specular + specular2, 1);
}