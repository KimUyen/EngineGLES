precision mediump float;

uniform sampler2D FireDisp;
uniform sampler2D FireTexture;
uniform sampler2D FireMask;
uniform float u_Time;
uniform float dMax;

varying vec2 v_uv;

void main()
{
	vec2 disp = texture2D(FireDisp, vec2(v_uv.x, v_uv.y + u_Time)).rg;

	vec2 offset = (2.0 * disp - 1.0) * dMax;
	vec2 uv_displaced = v_uv + offset;
	vec4 fire_color = texture2D (FireTexture, uv_displaced);

	vec4 AlphaValue = texture2D(FireMask, v_uv);
	gl_FragColor = fire_color * (1.0, 1.0, 1.0, AlphaValue.r);
}