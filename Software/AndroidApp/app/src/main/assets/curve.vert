/*
 * This file is part of MobilECG, an open source clinical grade Holter
 * ECG. For more information visit http://mobilecg.hu
 *
 * Copyright (C) 2016  Robert Csordas, Peter Isza
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#ifdef GL_ES
precision mediump float;
#endif

attribute float a_Position;
attribute float a_Value;

uniform vec2 scale;
uniform vec3 position;
uniform vec3 color;
uniform vec2 screenSize;
uniform float endOffset;
uniform float pointCount;
uniform float clearWidth;


varying vec4 v_Color;

float sqr(float x){
    return x*x;
}

void main(){
    float opacity = ( a_Value == a_Value ) ? 1.0 : 0.0;

    float end2=endOffset - 1.0;
    if (end2<0.0)
        end2+=pointCount;

    float distance = (a_Position >= end2) ? (a_Position - end2) : pointCount - (end2 - a_Position);
    opacity *= (distance > clearWidth) ? 1.0 : sqr(distance/clearWidth);
    v_Color = vec4(color,opacity);

    vec2 pixelSize=2.0/screenSize;
    gl_Position = vec4(vec2(-1.0,1.0) +  vec2(1.0,-1.0) * (position.xy*pixelSize + vec2(a_Position, -a_Value)*scale*pixelSize) , position.z, 1.0);
}