uniform sampler2D texture;
uniform vec3 ambient;

varying vec3 frag_tex_coords;

void main()
{
	gl_FragColor = texture2D(texture, frag_tex_coords);
}
