#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Imports the current position from the Vertex Shader
in vec3 crntPos;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the color from the Vertex Shader
in vec3 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;



// Gets the Texture Units from the main function
uniform sampler2D diffuse0;
uniform sampler2D specular0;
// Gets the color of the light from the main function
uniform vec3 lightColor;
uniform vec3 lightColor2;
// Gets the position of the light from the main function
uniform vec3 lightPosition;
uniform vec3 lightPosition2;
// Gets the position of the camera from the main function
uniform vec3 camPos;

// ambient lighting
float ambient = 0.25f;

vec4 getColor(float diffuse, float specular, vec3 color)
{
	return ((texture(diffuse0, texCoord) * (diffuse + ambient) + 0.3 * specular) * vec4(color,1.0));
}

vec4 direcLight()
{

	vec3 lightVec = -lightPosition; // lightDirection sun
	vec3 lightVec2 = -lightPosition2;

	// intensity of light with respect to distance
	// float dist = length(lightVec);
	// float a = 3.0;
	// float b = 0.7;
	// float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	vec3 lightDirection2 = normalize(lightVec2);
	float diffuse = max(dot(normal, lightDirection), 0.0f);
	float diffuse2 = max(dot(normal, lightDirection2), 0.0f);

	// specular lighting
	float specularLight = 0.25f;
	vec3 viewDirection = normalize(abs(camPos + crntPos));
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	vec3 reflectionDirection2 = reflect(-lightDirection2, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specAmount2 = pow(max(dot(viewDirection, reflectionDirection2), 0.0f), 16);
	float specular = specAmount * specularLight;
	float specular2 = specAmount2 * specularLight;

	// return ((texture(diffuse0, texCoord) * (diffuse + ambient) + 0.3 * specular) * vec4(lightColor,1.0)) + ((texture(diffuse0, texCoord) * (diffuse2 + ambient) + 0.3 *specular2) * vec4(lightColor2, 1.0));
	return getColor(diffuse, specular, lightColor) + getColor(diffuse2, specular2, lightColor2);
}

void main() {
	// outputs final color
	FragColor = direcLight();
}