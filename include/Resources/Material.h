#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <fstream>

#include "LibMaths.h"
#include "Shader.h"
#include "Texture.h"

#define AMBIENT Vec3::zero
#define DIFFUSE Vec3::zero
#define SPECULAR Vec3::zero
#define SHININESS 64

namespace Resources
{
	#pragma region typedefs
    typedef Core::Maths::Vec3 Vec3;
    typedef Resources::Shader Shader;
    typedef Resources::Texture Texture;
	#pragma endregion

    class ResourcesManager;

    class Material
    {
    private:
		#pragma region Attributes
        std::string _name;
        std::string _folderPath;

        /* Composition of the material */
        Vec3    _ambient;
        Vec3    _diffuse;
        Vec3    _specular;
        float   _shininess;

        /* Maps */
        Texture*    _map_kd;
        Texture*    _map_ka;
        Texture*    _map_ks;
        Texture*    _map_ns;
        Texture*    _map_bump;

        /* ResourcesManager */
        ResourcesManager* _resourcesManager;
		#pragma endregion

		#pragma region Functions
        /* Return true if the current material is parsed */
        bool    parseLine           (std::string& line);
        /* Parse the line and get the value of the shininess */
        void	parseShininess      (std::istringstream& data);
        /* Parse the data and get the value of the vec3 */
        void	parseVec3           (std::istringstream& data, Vec3& vec);
        /* Parse the data and get the values of the specular */
        void	parseTextureMap     (std::istringstream& data, Texture*& texture);

        /* Set the kd map to the shader */
        void    setMapKd(const Shader& s, int i) const noexcept;
        /* Set the ka map to the shader */
        void    setMapKa(const Shader& s, int i) const noexcept;
        /* Set the ks map to the shader */
        void    setMapKs(const Shader& s, int i) const noexcept;
		#pragma endregion
    public:
		#pragma region Constructors
        Material();
        Material(const std::string& name);
        Material(const Vec3& amb, const Vec3& diff, const Vec3& spec,
                 float shine);
        Material(const Material& m);
        ~Material() = default;
		#pragma endregion

		#pragma region Operators
        Material& operator= (const Material& m);
        bool      operator==(const Material& m);
		#pragma endregion

		#pragma region Functions
        void setValuesToShader  (const Shader& shader) const noexcept;
        void unbind             ()                     const noexcept;
        void parseFile          (std::ifstream& file, const std::string& folder,
                                 ResourcesManager* rm);                                
		#pragma endregion

		#pragma region Accessors
        std::string& name  ()              { return _name; };
        Vec3&   ambient    ()              { return _ambient; };
        Vec3&   diffuse    ()              { return _diffuse; };
        Vec3&   specular   ()              { return _specular; };
        float&  shininess  ()              { return _shininess; };
        void	setMapKd   (Texture* map)  { _map_kd = map; };
        void	setMapKa   (Texture* map)  { _map_ka = map; };
        void	setMapKs   (Texture* map)  { _map_ks = map; };
        void	setMapNs   (Texture* map)  { _map_ns = map; };
        void	setMapBump (Texture* map)  { _map_bump = map; };
		#pragma endregion
    };
} /* Resources */
#endif//__MATERIAL_H__
