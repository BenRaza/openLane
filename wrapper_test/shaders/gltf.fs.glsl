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
// Gets the position of the light from the main function
uniform vec3 lightPosition;
// Gets the position of the camera from the main function
uniform vec3 camPos;

vec4 direcLight()
{

	vec3 lightVec = lightPosition - vec3(0); // lightDirection sun

	// ambient lighting
	float ambient = 0.25f;

	// intensity of light with respect to distance
	// float dist = length(lightVec);
	// float a = 3.0;
	// float b = 0.7;
	// float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * (diffuse + ambient) + 1.0 * specular) * vec4(lightColor,1.0);
	// return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor;
}

void main() {
	// outputs final color
	FragColor = direcLight();
}