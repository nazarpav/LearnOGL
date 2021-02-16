#version 460 core
uniform float time;
varying vec2 v_pos;
void main(){
    vec4 color;
    vec2 uv_frag = gl_FragCoord.xy/vec2(800.,600.);
    vec2 uv = (v_pos.xy+1.)/2.;
    float r = uv.x*uv.y;
    float g = uv.x*(1.-uv.y);
    float b = uv.y*(1-uv.x);
    color = vec4(r, g, b, 1.0f);
    color.rgb+=vec3(distance(uv,uv_frag));
    gl_FragColor=color;
}