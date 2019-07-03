#ifndef __SHADER_H__
#define __SHADER_H__

#include <GL/glew.h>
#include <string>
#include "LibMaths.h"

namespace Resources
{
    typedef Core::Maths::Vec3 Vec3;
    typedef Core::Maths::Vec4 Vec4;

    class Shader
    {
    private:
        #pragma region Attributes
        GLuint m_id;
        #pragma endregion

        #pragma region Functions
        GLuint compileShader(const std::string& path, GLenum shaderType);
        GLuint createProgam (GLuint vertexShader, GLuint fragmentShader);
        char*  readFile     (const std::string& path);
        #pragma endregion

    public:
        #pragma region Constructors
        Shader();
        ~Shader();
        #pragma endregion

        #pragma region Functions
        void    loadShaders(const std::string& vertex, const std::string& fragment);
        GLuint  getLocation(const std::string& elem)                  const noexcept;
        void	setInt     (const std::string& name, GLint value)     const noexcept;
        void	setUint    (const std::string& name, GLuint value)    const noexcept;
        void    setBool    (const std::string& name, GLboolean value) const noexcept;
        void	setFloat   (const std::string& name, GLfloat value)   const noexcept;
        void	setMatrix4 (const std::string& name, float* elem)     const noexcept;
        void	setMatrix3 (const std::string& name, float* elem)     const noexcept;
        void	setVec3    (const std::string& name, const Vec3& vec) const noexcept;
        void	setVec4    (const std::string& name, const Vec4& vec) const noexcept;
        void    use()                                                 noexcept;
        void    unuse()                                               noexcept;
        #pragma endregion

        #pragma region Accessors
        GLuint& id()        { return m_id; };
        GLuint  id()  const { return m_id; };
        #pragma endregion
    };
} /* Resources */

#endif//__SHADER_H__
