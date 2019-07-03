#include "Skybox.h"

namespace Game
{
    #pragma region Constructors
    Skybox::Skybox() : 
        GameObject()
    {}

    Skybox::Skybox(const Skybox& type) :
        GameObject(type)
    {}

    Skybox::Skybox (const std::string& name,
                    Model* m,
                    Shader* s,
                    const Transform& tr):
        GameObject(name, m, s, tr)
    {}
            
    #pragma endregion
    
    #pragma region Operators
    Skybox& Skybox::operator=(const Skybox& type)
    {
        GameObject::operator=(type);
        return *this;
    }
    #pragma endregion

    #pragma region Functions
    GameObject& Skybox::save(std::ofstream& fs, ResourcesManager& resourcesManager, 
                             std::string folderPath) noexcept
    {
        (void)folderPath;
        (void)fs;
        (void)resourcesManager;
        return *this;
    }
    #pragma endregion
} // namespace Game
