precision mediump float;
varying vec2 v_uv;
varying vec3 v_normW;
varying vec3 v_tgtW;
varying vec3 v_binormW;

uniform sampler2D u_tex;
uniform sampler2D u_norm_tex;

varying vec3 v_posW;
uniform vec3 u_lightPos;
uniform vec3 u_eyePos;
uniform float u_weight;
uniform vec4 u_ambLight;
uniform vec4 u_diffLight;
uniform vec4 u_specLight;

varying mat4 v_model;

void main()
{
	vec3 normal = texture2D(u_tex, v_uv).xyz;
	mat3 TBN = mat3(normalize(v_tgtW), normalize(v_binormW), normalize(v_normW));
	vec3 normalW = normalize(TBN * (2.0 * normal - 1.0));

	vec3 lightPosW = vec3(v_model * vec4(u_lightPos, 1.0));
	vec3 eyePosW = vec3(v_model * vec4(u_eyePos, 1.0));

	vec4 objColor = texture2D(u_tex, v_uv);
	vec3 lightDirect = v_posW - lightPosW;
	vec3 toEye = normalize(eyePosW - v_posW);
	vec3 reflectVec = normalize(reflect(lightDirect, normalW));

	vec4 ambComp = vec4(1.0, 1.0, 1.0, 1.0);
	vec4 diffComp = max(dot(normalW, -lightDirect), 0.0) * u_diffLight;
	vec4 specComp = pow(max(dot(reflectVec, toEye), 0.0), 20.0) * u_specLight;

	//gl_FragColor = vec4(((ambComp * u_weight + (1.0 - u_weight) * diffComp) * objColor + specComp).xyz, objColor.w);
	gl_FragColor = vec4(objColor);
} 