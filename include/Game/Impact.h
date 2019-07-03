#ifndef __IMPACT_H__
#define __IMPACT_H__

#include "GameObject.h"
#include "Transform.h"
#include "Model.h"
#include "Shader.h"

namespace Game
{
    #pragma region Typedefs
        typedef LowRenderer::GameObject     GameObject;
        typedef Resources::ResourcesManager ResourcesManager;
        typedef Resources::Model            Model;
        typedef Resources::Shader           Shader;
        typedef Physics::Transform          Transform;
    #pragma endregion

    class Impact : public GameObject
    {
        public:
            #pragma region Constructors
            Impact();
            Impact(const Impact& type);
            Impact(const std::string& name, Model* m, Shader* s, const Transform& tr);
            ~Impact() = default;
            #pragma endregion
    
            #pragma region Operators
            Impact& operator=(const Impact& type);
            #pragma endregion
    
            #pragma region Functions
                GameObject& save(std::ofstream& fs, ResourcesManager& resourcesManager, std::string folderPath) noexcept override;
            #pragma endregion
    };
} // namespace Game


#endif //__IMPACT_H__