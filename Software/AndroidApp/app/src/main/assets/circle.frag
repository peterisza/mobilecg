#ifdef GL_ES
precision mediump float;
#endif

varying vec2 pos;
uniform vec3 color;

void main(){
    float distance=pos.x*pos.x+pos.y*pos.y;
    gl_FragColor = vec4(color, 1.0-smoothstep(0.9, 0.95, distance));
}
