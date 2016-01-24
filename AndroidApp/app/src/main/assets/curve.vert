#ifdef GL_ES
precision mediump float;
#endif

attribute float a_Position;
attribute float a_Value;

uniform vec2 scale;
uniform vec3 position;
uniform vec3 color;
uniform vec2 screenSize;

varying vec4 v_Color;

void main(){
    float opacity = ( a_Value == a_Value ) ? 1.0 : 0.0;
    v_Color = vec4(color,opacity);

    vec2 pixelSize=2.0/screenSize;
    gl_Position = vec4(vec2(-1.0,1.0) +  vec2(1.0,-1.0) * (position.xy*pixelSize + vec2(a_Position, -a_Value)*scale*pixelSize) , position.z, 1.0);
}