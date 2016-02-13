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

attribute vec2 a_Position;
uniform vec2 screenSize;
uniform vec2 size;
uniform vec3 position;

varying vec2 v_texcoord;

void main(){
   float aspect=screenSize.x/screenSize.y;
   v_texcoord=a_Position+vec2(0.5, 0.5);

   gl_Position =vec4( ((a_Position+vec2(0.5,0.5))*size + position.xy) / screenSize * 2.0 - vec2(1.0,1.0), position.z, 1) * vec4(1,-1,1,1);
}
