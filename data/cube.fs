precision mediump float;
varying vec3 v_pos;
uniform samplerCube u_cube_tex;

void main()
{
	gl_FragColor = textureCube(u_cube_tex, v_pos);
	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}