precision mediump float;
uniform samplerCube u_cube_tex;
uniform vec3 u_camPosition; // the camera position is already in world space
varying vec3 v_posW;
varying vec3 v_normW;

uniform vec3 u_lightPos;
uniform vec3 u_eyePos;
uniform float u_weight;
uniform vec4 u_ambLight;
uniform vec4 u_diffLight;
uniform vec4 u_specLight;

varying mat4 v_model;

void main()
{
	vec3 lightPosW = vec3(v_model * vec4(u_lightPos, 1.0));
	vec3 eyePosW = vec3(v_model * vec4(u_eyePos, 1.0));

    vec3 toEye = u_camPosition - v_posW;
    vec3 reflectDir = reflect(normalize(-toEye), normalize(v_normW));  // reflect() in non linear
    vec4 objColor = textureCube(u_cube_tex, reflectDir);
    
    vec3 lightDirect = v_posW - lightPosW;
    vec3 toEyeLight = normalize(eyePosW - v_posW);
    vec3 normal = objColor.xyz;
    vec3 reflectVec = normalize(reflect(lightDirect, normal));
  
    vec4 ambComp = vec4(1.0, 1.0, 1.0, 1.0);
    vec4 diffComp = max(dot(normal, -lightDirect), 0.0) * u_diffLight;
    vec4 specComp = pow(max(dot(reflectVec, toEye), 0.0), 20.0) * u_specLight;
  
    gl_FragColor = vec4(((ambComp * u_weight + (1.0 - u_weight) * diffComp) * objColor + specComp).xyz, objColor.w);
}
