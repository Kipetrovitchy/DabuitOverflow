#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <GL/glew.h>
#include <string>

#include "Shader.h"

namespace Resources
{
    class Texture
    {
    private:
        #pragma region Attributes
        GLuint  _id;
        #pragma endregion

        #pragma region Functions
        void initId()           noexcept;
        void setParameters()    noexcept;
        void setTexImage(unsigned char* image, int w, int h, int channel) noexcept;
        #pragma endregion

    public:
        #pragma region Constructors
        Texture();
        ~Texture();
        #pragma endregion

        #pragma region Functions
        void loadImage(const std::string& path);
        void bind(int i)                        noexcept;
        void unbind()                           noexcept;
        #pragma endregion

        #pragma region Accessors
        GLuint& id()       { return _id; };
        GLuint  id() const { return _id; };
        #pragma endregion
    };
} /* Resources */

#endif//__TEXTURE_H__
