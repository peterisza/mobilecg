#ifdef GL_ES
precision mediump float;
#endif

attribute vec2 a_Position;
uniform vec2 screenSize;
uniform float size;
uniform vec3 position;

varying vec2 pos;

void main(){
   float aspect=screenSize.x/screenSize.y;
   pos=a_Position*2.0;

   gl_Position =vec4( (a_Position*size + position.xy) / screenSize * 2.0 - vec2(1.0,1.0), position.z, 1) * vec4(1,-1,1,1);
}
