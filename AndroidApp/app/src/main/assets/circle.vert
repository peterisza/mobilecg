#ifdef GL_ES
precision mediump float;
#endif

attribute vec2 a_Position;

uniform mat4 mvpMatrix;
uniform float x;
uniform float y;
uniform float r;


varying vec3 v_Color;
varying vec2 pos;

void main(){
   pos=a_Position;
   gl_Position=mvpMatrix*vec4(a_Position.x*r+x, a_Position.y*r+y, -1, 1);
}