attribute vec3 a_posL;
attribute vec2 a_uvL;
attribute vec3 a_normL;

varying vec3 v_posW;
varying vec3 v_normW;
uniform mat4 u_mvp;
uniform mat4 u_model;
varying vec2 v_uv;
uniform mat4 u_TransInvModel;

varying mat4 v_model;
void main()
{
	vec4 pos = u_mvp * vec4(a_posL, 1.0);
	v_uv = a_uvL;
	gl_Position = pos;
	v_model = u_model;

	v_normW = mat3(u_TransInvModel) * a_normL;
    v_posW = vec3(u_model * vec4(a_posL, 1.0));
}
