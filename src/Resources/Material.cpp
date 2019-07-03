#include "Material.h"
#include "ResourcesManager.h"
#include "Log.h"
#include "Assert.h"

#include <sstream>

namespace Resources
{
	#pragma region Constructors
	Material::Material() :
		_ambient{ AMBIENT },
		_diffuse{ DIFFUSE },
		_specular{ SPECULAR },
		_shininess{ SHININESS },
		_map_kd{ nullptr },
		_map_ka{ nullptr },
		_map_ks{ nullptr },
		_map_ns{ nullptr },
		_map_bump{ nullptr }
	{}

	Material::Material(const std::string& name) :
		_name{ name },
		_ambient{ AMBIENT },
		_diffuse{ DIFFUSE },
		_specular{ SPECULAR },
		_shininess{ SHININESS },
		_map_kd{ nullptr },
		_map_ka{ nullptr },
		_map_ks{ nullptr },
		_map_ns{ nullptr },
		_map_bump{ nullptr }
	{}

	Material::Material(const Vec3& amb, const Vec3& diff, const Vec3& spec,
		float shine) :
		_ambient{ amb },
		_diffuse{ diff },
		_specular{ spec },
		_shininess{ shine },
		_map_kd{ nullptr },
		_map_ka{ nullptr },
		_map_ks{ nullptr },
		_map_ns{ nullptr },
		_map_bump{ nullptr }
	{}

	Material::Material(const Material& m) :
		_name{ m._name },
		_ambient{ m._ambient },
		_diffuse{ m._diffuse },
		_specular{ m._specular },
		_shininess{ m._shininess },
		_map_kd{ m._map_kd },
		_map_ka{ m._map_ka },
		_map_ks{ m._map_ks },
		_map_ns{ m._map_ns },
		_map_bump{ m._map_bump }
	{}
	#pragma endregion

	#pragma region Operators
	Material& Material::operator= (const Material& m)
	{
		_name = m._name;
		_ambient = m._ambient;
		_diffuse = m._diffuse;
		_specular = m._specular;
		_shininess = m._shininess;
		_map_kd = m._map_kd;
		_map_ka = m._map_ka;
		_map_ks = m._map_ks;
		_map_ns = m._map_ns;
		_map_bump = m._map_bump;

		return *this;
	}

	bool Material::operator==(const Material& m)
	{
		return _name == m._name;
	}
	#pragma endregion

	#pragma region Functions
	void Material::setValuesToShader(const Shader& shader) const noexcept
	{
		setMapKd(shader, 0);
		setMapKs(shader, 1);
		setMapKa(shader, 2);

		// Set the shininess of the material
		shader.setFloat("material.shininess", _shininess);
	}

	void    Material::setMapKd(const Shader& s, int i) const noexcept
	{
		s.setInt("material.diffuseMap", i);

		if (!_map_kd)
		{
			s.setVec3("material.diffuse", _diffuse);
			s.setBool("material.isDiffuseMap", false);
		}
		// If the map exists use the map
		else
		{
			_map_kd->bind(i);
			// glActiveTexture(GL_TEXTURE0 + i);
			// glBindTexture(GL_TEXTURE_2D, _map_kd->id());
			s.setBool("material.isDiffuseMap", true);
		}
	}

	void    Material::setMapKs(const Shader& s, int i) const noexcept
	{
		s.setInt("material.specularMap", i);

		if (!_map_ks)
		{
			s.setVec3("material.specular", _specular);
			s.setBool("material.isSpecularMap", false);
		}
		// If the map exists use the map
		else
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, _map_ks->id());
			s.setBool("material.isSpecularMap", true);
		}
	}

	void    Material::setMapKa(const Shader& s, int i) const noexcept
	{
		s.setInt("material.ambientMap", i);

		if (!_map_ka)
		{
			s.setVec3("material.ambient", _ambient);
			s.setBool("material.isAmbientMap", false);
		}
		// If the map exists use the map
		else
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, _map_ka->id());
			s.setBool("material.isAmbientMap", true);
		}
	}

	void Material::unbind() const noexcept
	{
		if (_map_kd)
			_map_kd->unbind();

		if (_map_ka)
			_map_ka->unbind();

		if (_map_ks)
			_map_ks->unbind();

		if (_map_ns)
			_map_ns->unbind();

		if (_map_bump)
			_map_bump->unbind();
	}

	void Material::parseFile(std::ifstream& file, const std::string& folder,
		ResourcesManager* rm)
	{
		_resourcesManager = rm;
		_folderPath = folder;

		// Store the current position
		std::streampos lineStart = file.tellg();
		// Retrieve each line
		std::string line;
		while (std::getline(file, line))
		{
			// Parse the line and if we are done reading the current material
			if (parseLine(line))
			{
				// Go back to the start of the line so the current line is still newmtl
				file.seekg(lineStart);
				// Leave the parsing of the model
				break;
			}
			// Store the current position
			lineStart = file.tellg();
		}
		_resourcesManager = nullptr;

		LOG(DEBUG, "\tAmbient : " + _ambient.to_string());
		LOG(DEBUG, "\tDiffuse : " + _diffuse.to_string());
		LOG(DEBUG, "\tSpecular : " + _specular.to_string());
		LOG(DEBUG, "\tShininess : " + std::to_string(_shininess));
	}

	bool Material::parseLine(std::string& line)
	{
		std::istringstream data(line);
		std::string lineHeader;
		data >> lineHeader;

		if (lineHeader == "newmtl")
			return true;
		else if (lineHeader == "Ns")
			parseShininess(data);
		else if (lineHeader == "Ka")
			parseVec3(data, _ambient);
		else if (lineHeader == "Kd")
			parseVec3(data, _diffuse);
		else if (lineHeader == "Ks")
			parseVec3(data, _specular);
		else if (lineHeader == "map_Kd")
			parseTextureMap(data, _map_kd);
		else if (lineHeader == "map_Ka")
			parseTextureMap(data, _map_ka);
		else if (lineHeader == "map_Ks")
			parseTextureMap(data, _map_ks);
		else if (lineHeader == "map_Ns")
			parseTextureMap(data, _map_ns);
		else if (lineHeader == "map_Bump")
			parseTextureMap(data, _map_bump);

		return false;
	}

	void Material::parseShininess(std::istringstream& data)
	{
		// Get the Vector3 elements
		data >> _shininess;
	}

	void Material::parseVec3(std::istringstream& data, Vec3& vec)
	{
		// Get the Vector3 elements
		data >> vec.x;
		data >> vec.y;
		data >> vec.z;
	}

	void Material::parseTextureMap(std::istringstream& data, Texture*& texture)
	{
		if (!ASSERT_OUT_MSG(_resourcesManager, "No ResourcesManager"))
			return;

		// Get the name of the texture
		std::string texturePath;
		data >> texturePath;
		texturePath = _folderPath + texturePath;

		// Load the texture
		texture = _resourcesManager->getTexture(texturePath);
	}
	#pragma endregion
}
