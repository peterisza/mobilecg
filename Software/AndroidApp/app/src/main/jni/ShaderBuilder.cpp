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
 
#include "ShaderBuilder.h"
#include "Helper.h"

ShaderBuilder::ShaderBuilder(){
    reset();
}

ShaderBuilder& ShaderBuilder::instance(){
    static ShaderBuilder i;
    return i;
}

int ShaderBuilder::buildShader(const std::string &name, const std::string &vert, const std::string &frag){
    NameMap::iterator it = nameMap.find(name);
    if (it!=nameMap.end())
        return it->second;

    shaders.push_back(helper::createGlProgram(vert, frag));
    int shaderIndex=shaders.size()-1;
    nameMap[name]=shaderIndex;

    return shaderIndex;
}

GLint ShaderBuilder::useProgram(int shaderId){
    GLint shader=shaders[shaderId];
    if (currShader!=shader) {
        glUseProgram(shader);
        currShader=shader;
    }
    return shader;
}

GLint ShaderBuilder::getShader(int shaderId){
    return shaders[shaderId];
}

void ShaderBuilder::reset(){
    nameMap.clear();
    shaders.clear();
    currShader=-1;
}
