#include "ResourcesManager.h"
#include "Log.h"
#include "Assert.h"

namespace Resources
{
	#pragma region Constructors
    ResourcesManager::ResourcesManager()
    {}

    ResourcesManager::~ResourcesManager()
    {
        clear();
    }
	#pragma endregion

	#pragma region Functions
    Model* ResourcesManager::getModel(const std::string& path) noexcept
    {
        // Check if the resources manager has already created the resource
        MapModel::iterator it = _models.find(path);
        // If it doesn't exists create it and add the indice
        if (it == _models.end())
        {
            LOG(DEBUG, "ResourcesManager: " + path + " : does not exist.");
            return insertModel(path);
        }
        else
        {
            LOG(DEBUG, "ResourcesManager: " + path + " : already exists.");
            return it->second;
        }
    }

    Model* ResourcesManager::insertModel(const std::string& path) noexcept
    {
        // Create the pointer of the model
        Model* model = new Model();
        try
        {
            // Load the model
            model->loadOBJ(path, this);
            // Insert the model in the resource manager
            _models.insert(std::pair<std::string, Model*>(path, model));

            return model;
        }
        catch (const std::string& err)
        {
            // In case the model does not load
            LOG(ERROR, "Could not create the model");
            // Delete the model
            delete model;

            return nullptr;
        }
    }

    Shader* ResourcesManager::getShader(const std::string& pathV,
                                        const std::string& pathF) noexcept
    {
        // Check if the resources manager has already created the resource
        MapShader::iterator it = _shaders.find(std::make_pair(pathV, pathF));
        // If it doesn't exists create it and add the indice
        if (it == _shaders.end())
        {
            LOG(DEBUG, "ResourcesManager: " + pathV
                       + " ; " + pathF + " : does not exist.");
            return insertShader(pathV, pathF);
        }
        else
        {
            LOG(DEBUG, "ResourcesManager: " + pathV
                       + " ; " + pathF + " : already exists.");
            return it->second;
        }
    }

    Shader* ResourcesManager::insertShader(const std::string& pathV,
                                           const std::string& pathF) noexcept
    {
        Shader* shader = new Shader();
        try
        {
            // Load the shader
            shader->loadShaders(pathV, pathF);
            // Insert the shader in the resource manager
            _shaders.insert(
                std::pair<StrPair, Shader*>(StrPair(pathV, pathF), shader)
            );

            return shader;
        }
        catch (const std::string& err)
        {
            // In case the shader does not load
            LOG(ERROR, "Could not create the shader "
                       + pathV + " ; " + pathF + " :\n" + err);
            // Delete the shader
            delete shader;

            return nullptr;
        }
    }

    Texture* ResourcesManager::getTexture(const std::string& path) noexcept
    {
        // Check if the resources manager has already created the resource
        MapTexture::iterator it = _textures.find(path);
        // If it doesn't exists create it and add the indice
        if (it == _textures.end())
        {
            LOG(DEBUG, "ResourcesManager: " + path + " : does not exist.");
            return insertTexture(path);
        }
        else
        {
            LOG(DEBUG, "ResourcesManager: " + path + " : already exists.");
            return it->second;
        }
    }

    Texture* ResourcesManager::insertTexture(const std::string& path) noexcept
    {
        Texture* texture = new Texture();
        try
        {
            // Load the texture
            texture->loadImage(path);

            // Insert the texture in the resource manager
            _textures.insert(std::pair<std::string, Texture*>(path, texture));

            return texture;
        }
        catch (const std::string& err)
        {
            // In case the texture does not load
            LOG(WARNING, "Could not create the texture " + path + " : " + err);
            // Delete the texture
            delete texture;

            // Give the unknown texture if it doesn't exist
            if (path != PATH_UNKNOWN)
                return getTexture(PATH_UNKNOWN);
            else
                return nullptr;
        }
    }

    Font* ResourcesManager::getFont(const std::string& path) noexcept
    {
        // Check if the resources manager has already created the resource
        MapFont::iterator it = _fonts.find(path);
        // If it doesn't exists create it and add the indice
        if (it == _fonts.end())
        {
            LOG(DEBUG, "ResourcesManager: " + path + " : does not exist.");
            return insertFont(path);
        }
        else
        {
            LOG(DEBUG, "ResourcesManager: " + path + " : already exists.");
            return it->second;
        }
    }

    Font* ResourcesManager::insertFont(const std::string& path) noexcept
    {
        Font* font = new Font();
        try
        {
            // Load the texture
            font->init(path);

            // Insert the texture in the resource manager
            _fonts.insert(std::pair<std::string, Font*>(path, font));

            return font;
        }
        catch (const std::string& err)
        {
            // In case the texture does not load
            LOG(WARNING, "Could not create the font " + path + " : " + err);
            // Delete the texture
            delete font;
            return nullptr;
        }
    }

    std::string ResourcesManager::findModelPathByValue(Model* m) noexcept
    {
        for (MapModel::iterator it = _models.begin(); it != _models.end(); ++it)
            if (it->second == m)
                return it->first;
        return "";
    }

    void ResourcesManager::clear() noexcept
    {
        for (MapModel::iterator it = _models.begin(); it != _models.end(); ++it)
            if (it->second)
                delete it->second;
        _models.clear();

        for (MapShader::iterator it = _shaders.begin(); it != _shaders.end(); ++it)
            if (it->second)
                delete it->second;
        _shaders.clear();

        for (MapTexture::iterator it = _textures.begin(); it != _textures.end(); ++it)
            if (it->second)
                delete it->second;
        _textures.clear();

        for (MapFont::iterator it = _fonts.begin(); it != _fonts.end(); ++it)
            if (it->second)
                delete it->second;
        _fonts.clear();
    }
	#pragma endregion
} /* Resources */
