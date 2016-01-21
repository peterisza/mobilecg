#ifdef GL_ES
precision mediump float;
#endif

attribute vec2 a_Position;
uniform vec2 screenSize;
uniform vec3 position;

varying vec2 v_texcoord;

void main(){
   float scale=2.0;
   float aspect=screenSize.x/screenSize.y;
   v_texcoord=(a_Position*vec2(aspect,1)+vec2(0.5, 0.5));
   gl_Position=vec4((a_Position.x)*aspect*scale+position.x, (a_Position.y)*scale+position.y, position.z, 1);
}
