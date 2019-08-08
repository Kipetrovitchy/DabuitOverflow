#include "Image.h"
#include "VertexUI.h"

namespace UI
{
    #pragma region Constructors / Destructors
    Image::Image() : 
        BaseUIComponent(),
        Colorable()
    {}

    Image::Image(const Image& i) :
        BaseUIComponent(i),
        Colorable(i),
        _texture { i._texture },
        _shader { i._shader },
        _VAO { i._VAO },
        _VBO { i._VBO },
        _EBO { i._EBO }
    {}

    Image::Image(Resources::Texture* texture, Resources::Shader* shader) :
        BaseUIComponent(),
        Colorable(),
        _texture { texture },
        _shader { shader }
    {
        initBuffers().resetGLBuffers();
    }
    #pragma endregion

    #pragma region Operators
    Image& Image::operator=(const Image& i)
    {
        BaseUIComponent::operator=(i);
        Colorable::operator=(i);
        _texture = i._texture;
        _shader = i._shader;
        _VAO = i._VAO;
        _VBO = i._VBO;
        _EBO = i._EBO;

        return *this;
    }
    #pragma endregion

    #pragma region Methods
    Image& Image::init(Resources::Texture* texture, Resources::Shader* shader) noexcept
    {
        _texture = texture;
        _shader = shader;
           
        return *this;
    }

    BaseUIComponent& Image::render(Core::Maths::Mat viewProj) noexcept
    {
        //We don't render the object and its children if it is disabled
        if (!_enabled)
            return *this;
        
        viewProj = viewProj * _transform.globalTRS();
        _shader->use();
        _shader->setMatrix4("projection", viewProj.elements);
        setColorShader(_shader);
        glBindVertexArray(_VAO);
        

        _texture->bind(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        _texture->unbind();;

        return *this;
    }
    #pragma endregion

    #pragma region Private Methods
    Image& Image::initBuffers() noexcept
    {
        GLuint indices[6]
        {
            0, 1, 2,
            0, 2, 3
        };

        glGenVertexArrays(1, &_VAO);
        glGenBuffers(1, &_VBO);
        glGenBuffers(1, &_EBO);

        glBindVertexArray(_VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(VertexUI) * 4, nullptr, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexUI), 0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexUI),
                              (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        return *this;
    }

    Image& Image::resetGLBuffers() noexcept
    {
        Vec3 pos { Vec3::zero };
        pos.x = -(_transform.width() / 2.f);
        pos.y = -(_transform.height() / 2.f);
        pos.z = _transform.position().z;
        VertexUI vertices[4]
        {
            { { pos.x, pos.y + _transform.height(), pos.z } ,                       { 0.0, 0.0 } },            
            { { pos.x, pos.y, pos.z },                                              { 0.0, 1.0 } },
            { { pos.x + _transform.width(), pos.y, pos.z },                         { 1.0, 1.0 } },
            { { pos.x + _transform.width(), pos.y + _transform.height(), pos.z },   { 1.0, 0.0 } }
        };

        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(VertexUI) * 4, vertices, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        return *this;
    }
    #pragma endregion

    #pragma region Accessors
    BaseUIComponent& Image::setWidth(GLuint width) noexcept
    {
        _transform.setWidth(width);
        resetGLBuffers();
        updateChildrenTransform();

        return *this;
    }
    BaseUIComponent& Image::setHeight(GLuint height) noexcept
    {
        _transform.setHeight(height);
        resetGLBuffers();
        updateChildrenTransform();

        return *this;
    }
    #pragma endregion
} // namespace UI
