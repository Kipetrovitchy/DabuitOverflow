#ifndef __RESOURCES_MANAGER_H__
#define __RESOURCES_MANAGER_H__

#include <unordered_map>

#include "Model.h"
#include "Texture.h"
#include "Shader.h"
#include "Font.h"

#define PATH_UNKNOWN "resources/unknown.png"

namespace Resources
{
    // Structure to hash-able pairs
    struct PairHash
    {
        template <class T1, class T2>
        size_t operator() (const std::pair<T1, T2> &p) const
        {
            auto h1 = std::hash<T1>{}(p.first);
            auto h2 = std::hash<T1>{}(p.second);

            return h1 ^ h2;
        }
    };

	#pragma region typedefs
    typedef std::pair<std::string, std::string>             StrPair;
    typedef std::unordered_map<std::string, Model*>         MapModel;
    typedef std::unordered_map<std::string, Texture*>       MapTexture;
    typedef std::unordered_map<std::string, Font*>          MapFont;
    typedef std::unordered_map<StrPair, Shader*, PairHash>  MapShader;
	#pragma endregion

    class ResourcesManager
    {
    private:

	#pragma region Attributes
        MapModel   _models;
        MapShader  _shaders;
        MapTexture _textures;
        MapFont    _fonts;
	#pragma endregion
	#pragma region Functions
        Model*      insertModel  (const std::string& path)  noexcept;
        Shader*     insertShader (const std::string& pathV, 
                                  const std::string& pathF) noexcept;
        Texture*    insertTexture(const std::string& path)  noexcept;
        Font*       insertFont   (const std::string& path)  noexcept;
	#pragma endregion

    public:
	#pragma region Constructors
        ResourcesManager();
        ~ResourcesManager();
	#pragma endregion

    #pragma region Accessors
        MapModel& models()      { return _models; };
        MapShader& shaders()    { return _shaders; };
        MapTexture& textures()  { return _textures; };
    #pragma endregion

	#pragma region Functions
        Model*      getModel    (const std::string& path)   noexcept;
        Shader*     getShader   (const std::string& pathV, 
                                 const std::string& pathF)  noexcept;
        Texture*    getTexture  (const std::string& path)   noexcept;
        Font*       getFont     (const std::string& path)   noexcept;

        std::string findModelPathByValue(Model* m) noexcept;
        
        void	    clear() noexcept;
	#pragma endregion
    };
} /* Resources */

#endif//__RESOURCES_MANAGER_H__
