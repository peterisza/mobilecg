#ifdef GL_ES
precision mediump float;
#endif

attribute vec2 a_Position;
uniform vec2 screenSize;
uniform vec2 size;
uniform vec3 position;

varying vec2 v_texcoord;

void main(){
   vec2 scale=2.0*size/screenSize;
   float aspect=screenSize.x/screenSize.y;
   v_texcoord=a_Position+vec2(0.5, 0.5);

   //vec2 pos2=-position.xy - screenSize*vec2(1,-1)/2.0;
   //gl_Position=vec4((a_Position.x)*scale.x+pos2.x/screenSize.x*2.0, (a_Position.y)*scale.y+pos2.y/screenSize.y*2.0, position.z, 1);

   gl_Position =vec4( ((a_Position+vec2(0.5,0.5))*size + position.xy) / screenSize * 2.0 - vec2(1.0,1.0), position.z, 1) * vec4(1,-1,1,1);
}
