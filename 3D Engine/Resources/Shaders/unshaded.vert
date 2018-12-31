attribute vec3 position;
attribute vec4 tex_coords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;

varying vec3 frag_tex_coords;

void main()
{
	gl_Position = projection * view * transform * vec4(position, 1.0);
	frag_tex_coords = tex_coords;
}