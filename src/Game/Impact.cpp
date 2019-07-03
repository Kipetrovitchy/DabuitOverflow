#include "Impact.h"

namespace Game
{
    #pragma region Constructors
    Impact::Impact() : 
        GameObject()
    {}

    Impact::Impact(const Impact& type) :
        GameObject(type)
    {}

    Impact::Impact (const std::string& name,
                    Model* m,
                    Shader* s,
                    const Transform& tr):
        GameObject(name, m, s, tr)
    {}
            
    #pragma endregion
    
    #pragma region Operators
    Impact& Impact::operator=(const Impact& type)
    {
        GameObject::operator=(type);
        return *this;
    }
    #pragma endregion

    #pragma region Functions
    GameObject& Impact::save(std::ofstream& fs, ResourcesManager& resourcesManager, 
                             std::string folderPath) noexcept
    {
        (void)folderPath;
        (void)fs;
        (void)resourcesManager;
        return *this;
    }
    #pragma endregion
} // namespace Game
