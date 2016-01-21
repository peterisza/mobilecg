#ifdef GL_ES
precision mediump float;
#endif

//uniform sampler2D texture;
varying vec2 v_texcoord;

void main(){
   // gl_FragColor = texture2D(texture, v_texcoord);
   gl_FragColor = vec4(1,0.5,0.5,1);
}