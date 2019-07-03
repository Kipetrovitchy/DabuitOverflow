#include "Texture.h"
#include "SOIL.h"
#include "Assert.h"
#include "Log.h"
#include <climits>

namespace Resources
{
    #pragma region Constructors
    Texture::Texture():
        _id { UINT_MAX }
    {}

    Texture::~Texture()
    {
        if (_id != UINT_MAX)
            glDeleteTextures(1, &_id);
    }
    #pragma endregion

    #pragma region Functions
    void Texture::loadImage(const std::string& path)
    {
        LOG(INFO, "Texture:\tLOADING\t\t" + path);

        initId();
        setParameters();

        // Load the image
        int width, height, channel;
        unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, &channel, SOIL_LOAD_AUTO);

        // Check that the image has been successfuly loeaded
        if (image)
        {
            setTexImage(image, width, height, channel);
            LOG(INFO, "Texture:\tDONE\t\t" + path);
        }
        else
        {
            SOIL_free_image_data(image);
            throw std::string(SOIL_last_result());
        }

        // Free the image
        SOIL_free_image_data(image);
    }

    void Texture::initId() noexcept
    {
        // Generate the id of the texture
        glGenTextures(1, &_id);
        glBindTexture(GL_TEXTURE_2D, _id);
    }

    void Texture::setParameters() noexcept
    {
        // Set the parameters repeat
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Set the linear filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    void Texture::setTexImage(unsigned char* image, int w, int h,
                              int channel) noexcept
    {
        if (channel == 3)
        {
            LOG(DEBUG, "The image has a RGB channel");
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB,
                GL_UNSIGNED_BYTE, image);
        }
        else if (channel == 4)
        {
            LOG(DEBUG, "The image has a RGBA channel");
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,
                GL_UNSIGNED_BYTE, image);
        }

        LOG(DEBUG, "Width : "  + std::to_string(w));
        LOG(DEBUG, "Height : " + std::to_string(h));
    }

    void Texture::bind(int i) noexcept
    {
        // Activate the texture
        glActiveTexture(GL_TEXTURE0 + i);

        // Bind the texture to GL
        glBindTexture(GL_TEXTURE_2D, _id);
    }

    void Texture::unbind() noexcept
    {
        // Bind the texture to GL
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    #pragma endregion

} /* Resources */
