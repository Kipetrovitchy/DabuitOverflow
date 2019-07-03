#ifndef __SKYBOX_H__
#define __SKYBOX_H__

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

    class Skybox : public GameObject
    {
        public:
            #pragma region Constructors
            Skybox();
            Skybox(const Skybox& type);
            Skybox(const std::string& name, Model* m, Shader* s, const Transform& tr);
            ~Skybox() = default;
            #pragma endregion
    
            #pragma region Operators
            Skybox& operator=(const Skybox& type);
            #pragma endregion
    
            #pragma region Functions
                GameObject& save(std::ofstream& fs, ResourcesManager& resourcesManager, std::string folderPath) noexcept override;
            #pragma endregion
    };
} // namespace Game


#endif //__SKYBOX_H__