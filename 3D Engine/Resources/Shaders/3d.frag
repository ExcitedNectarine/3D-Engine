uniform sampler2D texture;
uniform vec3 ambient;

varying vec4 frag_tex_coords;
varying vec3 frag_pos;

#define MAX_LIGHT_SOURCES 128
#define CONSTANT 1.0f
#define LINEAR 0.0f
#define QUADRATIC 0.5f

struct Light
{
	vec3 position;
	vec3 colour;
	float radius;
};

uniform Light lights[MAX_LIGHT_SOURCES];

void main()
{
	float distance = 0.0f;
	float attenuation = 0.0f;
	vec3 total_light = ambient;
	vec3 diffuse;
	vec4 tex = texture2D(texture, frag_tex_coords);
	
	for (int i = 0; i < MAX_LIGHT_SOURCES; i++)
	{
		distance = length(lights[i].position - frag_pos);
		attenuation = max(1.0 / (CONSTANT + LINEAR * distance + QUADRATIC * (distance * distance)) - 1.0f / (lights[i].radius * lights[i].radius), 0.0f);
		diffuse = vec3(tex) * lights[i].colour;
		diffuse *= attenuation;
		total_light += diffuse;
	}
	
	gl_FragColor = tex * vec4(total_light, 1.0);
}