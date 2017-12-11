precision mediump float;
varying vec2 v_uv;
varying vec3 v_normW;
varying vec3 v_tgtW;
varying vec3 v_binormW;

uniform sampler2D u_tex;
uniform sampler2D u_norm_tex;
uniform float u_Time;
uniform float dMax;

varying vec3 v_posL;
uniform vec3 u_lightPos;
uniform vec3 u_eyePos;
uniform float u_weight;
uniform vec4 u_ambLight;
uniform vec4 u_diffLight;
uniform vec4 u_specLight;

varying mat4 v_model;

void main()
{
	float dMaxChange = dMax + (v_uv.x * 0.1);
	vec2 dispNorm = texture2D(u_norm_tex, vec2(v_uv.x + u_Time, v_uv.y)).rg;
	vec2 offset = (2.0 * dispNorm - 1.0) * dMaxChange;
	vec2 uv_displaced = v_uv  + offset;

	vec3 normal = texture2D(u_norm_tex, uv_displaced).xyz;
	mat3 TBN = mat3(normalize(v_tgtW), normalize(v_binormW), normalize(v_normW));
	vec3 normalW = normalize(TBN * (2.0 * normal - 1.0));

	//vec3 lightDirect = normalize((v_posL - u_lightPos));

	vec4 objColor = texture2D(u_tex, uv_displaced);
	//float diffuse = max(dot(normalW, -lightDirect), 0.0);
	float diffuse = max(dot(normalW, vec3(1.0)), 0.0);
	gl_FragColor = vec4(diffuse * objColor.xyz, objColor.a);
	gl_FragColor.b += (v_uv.x * 0.06);
		//gl_FragColor = vec4(normalW, 1.0);
} 