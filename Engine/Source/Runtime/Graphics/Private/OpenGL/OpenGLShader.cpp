/**
 * OpenGLShader.cpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#if ENGINE_GRAPHICS_OPENGL

#include "OpenGL/OpenGLShader.hpp"

namespace seedengine {

    OpenGLShader::OpenGLShader() {
        m_initialized = false;
    }

    OpenGLShader::~OpenGLShader() {
        
    }

    void OpenGLShader::bind() {
        glUseProgram(m_program_id);
        m_running = true;
    }
    
    void OpenGLShader::unbind() {
        if (m_running) glUseProgram(0);
        else ENGINE_WARN("Shader is not currently running, therefore cannot stop.");
    }

    bool OpenGLShader::init(const String& filepath) {
        // pass: shader path(s), ordered attribute names ?, uniform names ?

        //TODO: Process monolithic shader into shader components

        ENGINE_WARN("Monolithic GLSL shaders are not yet supported. Initialization failed.");
        return false;

        /*m_vertex_shader_id = loadShader(vertex_shader_path, GL_VERTEX_SHADER);
        if (m_vertex_shader_id == 0) {
            ENGINE_WARN("Failed to load fragment shader, Shader will not initialize.");
            return false;
        }
        else {
            m_fragment_shader_id = loadShader(fragment_shader_path, GL_FRAGMENT_SHADER);
            if (m_fragment_shader_id == 0) {
                ENGINE_WARN("Failed to load fragment shader, Shader will not initialize.");
                glDeleteShader(vertex_shader_id_);
                return false;
            }
            else {
                m_program_id = glCreateProgram();
                glAttachShader(m_program_id, m_vertex_shader_id);
                glAttachShader(m_program_id, m_fragment_shader_id);
                //bindAttributes(attributes);
                glLinkProgram(m_program_id);
                glValidateProgram(m_program_id);
                //getAllUniformLocations(uniforms);
                return true;
            }
        }*/
    }
    
    bool OpenGLShader::init(const String& name, const String& vs_filepath, const String& fs_filepath) {
        // pass: shader path(s), ordered attribute names ?, uniform names ?
        m_vertex_shader_id = loadShader(vs_filepath, GL_VERTEX_SHADER);
        if (m_vertex_shader_id == 0) {
            ENGINE_WARN("Failed to load fragment shader, Shader will not initialize.");
            return false;
        }
        else {
            m_fragment_shader_id = loadShader(fs_filepath, GL_FRAGMENT_SHADER);
            if (m_fragment_shader_id == 0) {
                ENGINE_WARN("Failed to load fragment shader, Shader will not initialize.");
                glDeleteShader(m_vertex_shader_id);
                return false;
            }
            else {
                m_program_id = glCreateProgram();
                glAttachShader(m_program_id, m_vertex_shader_id);
                glAttachShader(m_program_id, m_fragment_shader_id);
                //bindAttributes(attributes);
                glLinkProgram(m_program_id);
                glValidateProgram(m_program_id);
                //getAllUniformLocations(uniforms);
                m_initialized = true;
                return true;
            }
        }
    }
    
    void OpenGLShader::cleanUp() {
        unbind();
        glDetachShader(m_program_id, m_vertex_shader_id);
        glDetachShader(m_program_id, m_fragment_shader_id);
        glDeleteShader(m_vertex_shader_id);
        glDeleteShader(m_fragment_shader_id);
        glDeleteProgram(m_program_id);
    }

    GLint OpenGLShader::getUniformLocation(const String& name) const {
        return glGetUniformLocation(m_program_id, name.c_str());
    }

    void OpenGLShader::bindAttribute(const GLuint& attribute, const String& name) const {
        //TODO: Study https://www.opengl.org/sdk/docs/tutorials/ClockworkCoders/attributes.php
        glBindAttribLocation(m_program_id, attribute, name.c_str());
    }

// Load Scalar Parameters

    void OpenGLShader::setParameter(const String& name, bool value) {
        glUniform1i(getUniformLocation(name), value);
    }

    void OpenGLShader::setParameter(const String& name, int32_t value) {
        glUniform1i(getUniformLocation(name), value);
    }
    void OpenGLShader::setParameter(const String& name, uint32_t value) {
        glUniform1ui(getUniformLocation(name), value);
    }

    void OpenGLShader::setParameter(const String& name, float value) {
        glUniform1f(getUniformLocation(name), value);
    }

// Load Vector Parameters

    void OpenGLShader::setParameter(const String& name, const Vector2& value) {
        glUniform2fv(getUniformLocation(name), 2, &value[0]);
    }
    void OpenGLShader::setParameter(const String& name, const Vector3& value) {
        glUniform3fv(getUniformLocation(name), 3, &value[0]);
    }
    void OpenGLShader::setParameter(const String& name, const Vector4& value) {
        glUniform4fv(getUniformLocation(name), 4, &value[0]);
    }

    void OpenGLShader::setParameter(const String& name, const Vector2Int& value) {
        glUniform2iv(getUniformLocation(name), 2, &value[0]);
    }
    void OpenGLShader::setParameter(const String& name, const Vector3Int& value) {
        glUniform3iv(getUniformLocation(name), 3, &value[0]);
    }
    void OpenGLShader::setParameter(const String& name, const Vector4Int& value) {
        glUniform4iv(getUniformLocation(name), 4, &value[0]);
    }

// Load Matrix Parameters

     //NOTE: Be aware of transpose from row major to column major

    void OpenGLShader::setParameter(const String& name, const Matrix2x2& value) {
        glUniformMatrix2fv(getUniformLocation(name), 1, true, &value(0, 0));
    }
    void OpenGLShader::setParameter(const String& name, const Matrix2x3& value) {
        glUniformMatrix2x3fv(getUniformLocation(name), 1, true, &value(0, 0));
    }
    void OpenGLShader::setParameter(const String& name, const Matrix2x4& value) {
        glUniformMatrix2x4fv(getUniformLocation(name), 1, true, &value(0, 0));
    }

    void OpenGLShader::setParameter(const String& name, const Matrix3x2& value) {
        glUniformMatrix3x2fv(getUniformLocation(name), 1, true, &value(0, 0));
    }
    void OpenGLShader::setParameter(const String& name, const Matrix3x3& value) {
        glUniformMatrix3fv(getUniformLocation(name), 1, true, &value(0, 0));
    }
    void OpenGLShader::setParameter(const String& name, const Matrix3x4& value) {
        glUniformMatrix3x4fv(getUniformLocation(name), 1, true, &value(0, 0));
    }

    void OpenGLShader::setParameter(const String& name, const Matrix4x2& value) {
        glUniformMatrix4x2fv(getUniformLocation(name), 1, true, &value(0, 0));
    }
    void OpenGLShader::setParameter(const String& name, const Matrix4x3& value) {
        glUniformMatrix4x3fv(getUniformLocation(name), 1, true, &value(0, 0));
    }
    void OpenGLShader::setParameter(const String& name, const Matrix4x4& value) {
        glUniformMatrix4fv(getUniformLocation(name), 1, true, &value(0, 0));
    }

// Load Texture Parameters

    void OpenGLShader::setParameter(const String& name, const Texture& value) {}

// Load Shader

    GLuint OpenGLShader::loadShader(const String& filepath, const GLenum& shader_type) {
            
        // Read the passed file
        std::ifstream file(filepath, std::ifstream::in);

        String line;
        int line_num = 1;

        String buffer = "";

        if (file.is_open()) {
            while (std::getline(file, line)) {
                buffer += line;
                buffer += "\n";
            }
            file.close();
        }

        GLuint shader_id = glCreateShader(shader_type);
        GLchar const* files[] = { buffer.c_str() };
        GLint lengths[] = { (GLint)buffer.size() };

        //TODO: Create common shader code that can be written in prior to each source file
        glShaderSource(shader_id, 1, files, lengths);
        glCompileShader(shader_id);

        GLint compiled = 0;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled);
        if (compiled == GL_FALSE) {

            GLint max_length = 0;
            glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &max_length);

            std::vector<char> error_log(max_length);

            glGetShaderInfoLog(shader_id, max_length, &max_length, &error_log[0]);

            String msg(error_log.begin(), error_log.end());
            ENGINE_ERROR(msg);

            glDeleteShader(shader_id);

            return 0;
        }
        return shader_id;
    }

// Cast Operators

    OpenGLShader::operator bool() const noexcept {
        return m_initialized;
    }

}

#endif