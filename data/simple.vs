attribute vec3 a_posL;
attribute vec2 a_uvL;
attribute vec3 a_binormL;
attribute vec3 a_tgtL;
attribute vec3 a_normL;

varying vec2 v_uv;
varying vec3 v_normW;
varying vec3 v_tgtW;
varying vec3 v_binormW;
uniform mat4 u_mvp;
uniform mat4 u_model;

varying vec3 v_posW;
uniform mat4 u_TransInvModel;
varying mat4 v_model;

void main()
{
	gl_Position = u_mvp * vec4(a_posL, 1.0);
	v_normW = normalize((u_model * vec4(a_normL, 0.0)).xyz);
	v_tgtW = normalize((u_model * vec4(a_tgtL, 0.0)).xyz);
	v_binormW = normalize((u_model * vec4(a_binormL, 0.0)).xyz);
	v_uv = a_uvL;

	v_model = u_model;

	
	v_posW = vec3(u_model * vec4(a_posL, 1.0));
}
   