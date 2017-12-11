attribute vec3 a_posL;
attribute vec2 a_uvL;

varying vec3 v_pos;
uniform mat4 u_mvp;

void main()
{
	vec4 pos = u_mvp * vec4(a_posL, 1.0);
	gl_Position = pos;
	v_pos = a_posL.xyz;
}
   