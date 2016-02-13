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
 
#ifndef ANDROIDAPP_SHADERBUILDER_H
#define ANDROIDAPP_SHADERBUILDER_H

#include <vector>
#include <map>
#include <GLES2/gl2.h>

class ShaderBuilder {
    private:
        typedef std::map<std::string, int> NameMap;
        ShaderBuilder();

        std::vector<GLint> shaders;
        NameMap nameMap;

        GLint currShader;
    public:
        static ShaderBuilder& instance();
        int buildShader(const std::string &name, const std::string &vert, const std::string &frag);
        GLint getShader(int shaderId);
        GLint useProgram(int shaderId);

        void reset();
};


#endif //ANDROIDAPP_SHADERBUILDER_H
