#include "Shader.h"

#include <fstream>
#include <climits>
#include "Log.h"
#include "Assert.h"

namespace Resources
{
    #pragma region Constructors
    Shader::Shader():
        m_id { UINT_MAX }
    {}

    Shader::~Shader()
    {
        if (m_id != UINT_MAX)
            glDeleteProgram(m_id);
    }
    #pragma endregion

    #pragma region Fonctions
    void Shader::loadShaders(const std::string& vertex, const std::string& fragment)
    {
        LOG(INFO, "Shader:\tCOMPILING\t" + vertex + " ; " + fragment);
        // Create the vertex shader
        GLuint vertexShader = compileShader(vertex, GL_VERTEX_SHADER);

        // Create the fragment shader
        GLuint fragmentShader = compileShader(fragment, GL_FRAGMENT_SHADER);

        // Create the shader program
        m_id = createProgam(vertexShader, fragmentShader);
        LOG(INFO, "Shader:\tCOMPILED\t" + vertex + " ; " + fragment);

        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);
    }

    GLuint Shader::compileShader(const std::string& path, GLenum shaderType)
    {
    	// Read the file
    	const GLchar* source = readFile(path);

    	// Compile the shader
    	GLuint shader = glCreateShader(shaderType);
    	glShaderSource (shader, 1, &source, NULL);
    	glCompileShader(shader);

    	delete[] source;

    	// Check if the compiling was succesful
    	GLint status;
    	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    	if (!status)
    	{
    		// Create the buffer to retrieve the error message
    		char buffer[512];
    		glGetShaderInfoLog(shader, 512, NULL, buffer);
    		// throw the error
    		throw std::string(buffer);
    	}

    	return shader;
    }

    GLuint Shader::createProgam(GLuint vertexShader, GLuint fragmentShader)
    {
    	// Instantiate the program
    	GLuint shaderProgram = glCreateProgram();

    	// Attach the shaders
    	glAttachShader(shaderProgram, vertexShader);
    	glAttachShader(shaderProgram, fragmentShader);

    	// Link the program to openGL
    	glLinkProgram(shaderProgram);

    	// Check for errors
    	GLint status;
    	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    	if (!status)
    	{
    		// Create the buffer to retrieve the error message
    		char buffer[512];
    		glGetProgramInfoLog(shaderProgram, 512, NULL, buffer);
    		// throw the error
    		throw std::string(buffer);
    	}

    	return shaderProgram;
    }

    char* Shader::readFile(const std::string& path)
    {
        std::ifstream fileStream (path, std::ios::in);

        // If the file couldn't be opened
        ASSERT_THROW_MSG(fileStream, "Error: Could not open the file " + path);

        // Get length of file
        fileStream.seekg (0, fileStream.end);
        size_t length = fileStream.tellg();
        fileStream.seekg (0, fileStream.beg);

        char* buffer = new char[length + 1];

        // Read data as a block:
        fileStream.read(buffer, length);

        buffer[length] = '\0';

        // Close the file
        fileStream.close();

        return buffer;
    }

    GLuint Shader::getLocation(const std::string& elem) const noexcept
    {
        return glGetUniformLocation(m_id, elem.c_str());
    }

    void Shader::setInt(const std::string& name, GLint value) const noexcept
    {
        // Get the location of the uint
        GLuint intLoc = glGetUniformLocation(m_id, name.c_str());

        // Give the value of the texture to the uint
        glUniform1i(intLoc, value);
    }

    void Shader::setUint(const std::string& name, GLuint value) const noexcept
    {
        // Get the location of the uint
        GLuint uintLoc = glGetUniformLocation(m_id, name.c_str());

        // Give the value of the texture to the uint
        glUniform1ui(uintLoc, value);
    }

    void Shader::setBool(const std::string& name, GLboolean value) const noexcept
    {
        // Get the location of the uint
        GLuint boolLoc = glGetUniformLocation(m_id, name.c_str());

        // Give the value of the texture to the uint
        glUniform1i(boolLoc, value);
    }

    void Shader::setFloat(const std::string& name, GLfloat value) const noexcept
    {
        // Get the location of the texture
        GLuint floatLoc = glGetUniformLocation(m_id, name.c_str());

        // Give the id of the texture to the shader
        glUniform1f(floatLoc, value);
    }

    void Shader::setMatrix4(const std::string& name, float* elem) const noexcept
    {
        // Get the location of the matrix
        GLuint matrixLoc = glGetUniformLocation(m_id, name.c_str());

        // Give the Matrix to the shader
        glUniformMatrix4fv(matrixLoc,  1, GL_TRUE, elem);
    }

    void Shader::setMatrix3(const std::string& name, float* elem) const noexcept
    {
        // Get the location of the matrix
        GLuint matrixLoc = glGetUniformLocation(m_id, name.c_str());

        // Give the Matrix to the shader
        glUniformMatrix3fv(matrixLoc,  1, GL_TRUE, elem);
    }

    void Shader::setVec3(const std::string& name, const Vec3& vec) const noexcept
    {
        // Get the location of the vector3
        GLuint vecLoc = glGetUniformLocation(m_id, name.c_str());

        // Give the vec3 to the shader
        glUniform3f(vecLoc, vec.x, vec.y, vec.z);
    }

    void Shader::setVec4(const std::string& name, const Vec4& vec) const noexcept
    {
        // Get the location of the vector4
        GLuint vecLoc = glGetUniformLocation(m_id, name.c_str());

        // Give the vec4 to the shader
        glUniform4f(vecLoc, vec.x, vec.y, vec.z, vec.w);
    }

    void Shader::use() noexcept
    {
        glUseProgram(m_id);
    }

    void Shader::unuse() noexcept
    {
        glUseProgram(0);
    }
    #pragma endregion
} /* Resources */
