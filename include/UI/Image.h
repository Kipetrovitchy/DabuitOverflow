#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "BaseUIComponent.h"
#include "Texture.h"
#include "Shader.h"
#include "Colorable.h"

namespace UI
{
    class Image : public BaseUIComponent, public Colorable
    {
        private:
            #pragma region Attributes
            Resources::Texture* _texture;
            Resources::Shader*  _shader;
            GLuint _VAO;
            GLuint _VBO;
            GLuint _EBO;
            #pragma endregion

            #pragma region Private Methods
            Image& initBuffers() noexcept;
            Image& resetGLBuffers() noexcept;
            #pragma endregion
        public:
            #pragma region Constructors / Destructors
            Image();
            Image(const Image& i);
            Image(Resources::Texture* texture, Resources::Shader* shader);
            ~Image() = default;
            #pragma endregion
    
            #pragma region Operators
            Image& operator=(const Image& i);
            #pragma endregion
    
            #pragma region Methods
            Image& init(Resources::Texture* texture, Resources::Shader* shader) noexcept;
            BaseUIComponent& render(Core::Maths::Mat transformParent)           noexcept;
            #pragma endregion

            #pragma region Accesssors
            BaseUIComponent& setWidth(GLuint width)     noexcept override;
            BaseUIComponent& setHeight(GLuint height)   noexcept override;

            inline Resources::Texture*& texture() { return _texture; }
            #pragma endregion
    };
} // namespace UI

#endif // __IMAGE_H__