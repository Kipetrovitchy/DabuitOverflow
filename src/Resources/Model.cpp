#include "Model.h"

#include <cstring>
#include <sstream>
#include <fstream>
#include <climits>
#include <algorithm>
#include <regex>
#include "Log.h"
#include "Assert.h"
#include "ResourcesManager.h"
#include "LibMaths.h"


namespace Resources
{
	#pragma region Constructors
    Model::Model():
        _VAO { UINT_MAX }
    {}

    Model::~Model()
    {
        if (_VAO != UINT_MAX)
            glDeleteVertexArrays(1, &_VAO);
    }
	#pragma endregion

	#pragma region Functions
    void Model::loadOBJ(const std::string& path, ResourcesManager* rm)
    {
        _resourcesManager = rm;

        // Get the path to the folder
        _folderPath = path.substr(0, path.find_last_of('/') + 1);

        // Open the file
        std::ifstream file(path, std::ios::in);

        // If the file doesn't open
        ASSERT_THROW_MSG(file, "Cannot open the file " + path);

        // Read the file
        LOG(INFO, "Model:\tEXTRACTING\t" + path);
        parseFile(file);
        LOG(INFO, "Model:\tEXTRACTED\t" + path);

        // Close the file
        file.close();

        _resourcesManager = nullptr;

        initModel();
    }

    void Model::parseFile(std::ifstream& file)
    {
        std::string line;
        // Retrieve each line
        while (std::getline(file, line))
        {
            // Parse the line
            parseLine(line);
        }

        // Log all the informations about the file extracted
        LOG(DEBUG, std::to_string(_positions.size()) + " positions");
        LOG(DEBUG, std::to_string(_uvs.size())       + " uvs");
        LOG(DEBUG, std::to_string(_normals.size())   + " normals");
        LOG(DEBUG, std::to_string(_indices.size())   + " indices");
        LOG(DEBUG, std::to_string(_vertices.size())  + " vertices");
    }

    void Model::parseLine(std::string& line)
    {
        // Get the header of the line
        std::istringstream data(line);
        std::string lineHeader;
        data >> lineHeader;

        if      (lineHeader == "mtllib")
            parseMTL(data);
        else if (lineHeader == "usemtl")
            changeCurrentMat(data);
        else if (lineHeader == "v")
            getCurrentVertex(data);
        else if (lineHeader == "vt")
            getCurrentUV(data);
        else if (lineHeader == "vn")
            getCurrentNormal(data);
        else if (lineHeader == "f")
            getCurrentFace(data);
    }

    void Model::parseMTL(std::istringstream& data)
    {
        // Get the mtl file
        std::string modelPath;
        data >> modelPath;
        modelPath = _folderPath + modelPath;

        // Open the file
        std::ifstream file(modelPath, std::ios::in);
        ASSERT_THROW_MSG(file, "Cannot open the file " + modelPath);

        LOG(INFO, "MTL:\t\tEXTRACTING\t" + modelPath);
        std::string line;
        // Retrieve each line
        while (std::getline(file, line))
        {
            // Get the header of the line
            std::istringstream dataMat(line);
            std::string lineHeader;
            dataMat >> lineHeader;
            if (lineHeader == "newmtl")
                parseNextMTL(file, dataMat);
        }
        LOG(INFO, "MTL:\t\tEXTRACTED\t" + modelPath);

        // Close the file
        file.close();
    }

    void Model::parseNextMTL(std::ifstream& file, std::istringstream& data)
    {
        // Extract the name of the material
        std::string matName;
        data >> matName;

        LOG(DEBUG, "Material : EXTRACTING\t" + matName);
        Material mat(matName);
        mat.parseFile(file, _folderPath, _resourcesManager);
        LOG(DEBUG, "Material : EXTRACTED\t" + matName);

        _materials.push_back(mat);
    }

    void Model::changeCurrentMat(std::istringstream& data)
    {
        // Extract the name of the material
        std::string matName;
        data >> matName;

        uint index = findMaterial(matName);

        _indicesMaterial.push_back(std::pair<uint, uint>(_indices.size(), index));
    }

    uint Model::findMaterial(std::string& matName)
    {
        uint index = 0;
        // Go through all the materials
        std::vector<Material>::iterator it = _materials.begin();
        for (; it != _materials.end(); ++it)
        {
            if (matName == (*it).name())
                return index;

            // Increment the index
            index++;
        }

        return UINT_MAX;
    }

    void Model::getCurrentVertex(std::istringstream& data)
    {
        // Create the Vector3 to get the elements of the position
        Vec4 position(0.0f, 0.0f, 0.0f, 1.0f);
        data >> position.x;
        data >> position.y;
        data >> position.z;

        // w is optional so it will be 1 by default
        data >> position.w;

        // Store the positions
        _positions.push_back(std::move(position));
    }

    void Model::getCurrentUV(std::istringstream& data)
    {
        // Create the Vector3 to get the elements of the  vertex
        Vec3 uv(0.0f, 0.0f, 0.0f);
        data >> uv.x;

        // v and w are optional so they will be 0 by default
        data >> uv.y;
        data >> uv.z;

        // Store the positions
        _uvs.push_back(std::move(uv));
    }

    void Model::getCurrentNormal(std::istringstream& data)
    {
        // Create the Vector3 to get the elements of the  vertex
        Vec3 normal;
        data >> normal.x;
        data >> normal.y;
        data >> normal.z;

        // Store the data
        _normals.push_back(std::move(normal));
    }

    void Model::getCurrentFace(std::istringstream& data)
    {
        // Get all the triplets that make up the face
        std::string strIndices;
        std::vector<Triplet> triplets;
        while (data >> strIndices)
            triplets.emplace_back(splitIndices(strIndices));

        // Transform the n-gon to multiple triangles
        GLuint nTriplet = triplets.size();
        for (GLuint i = 0; i < nTriplet - 2; i++)
        {
            addVertex(triplets[0]);
            addVertex(triplets[i + 1]);
            addVertex(triplets[i + 2]);
        }
    }

    Triplet Model::splitIndices(std::string& strIndices)
    {
        // Create the triplet to store the values of the indices
        Triplet triplet;

        try
        {
            GLuint nbSlash = std::count(strIndices.begin(), strIndices.end(), '/');
            switch (nbSlash)
            {
                case 0: readIndiceNoSlash(strIndices, triplet);     break;
                case 1: readIndiceOneSlash(strIndices, triplet);    break;
                case 2: readIndiceTwoSlashes(strIndices, triplet);  break;
                default: throw;                                     break;
            }
        }
        catch (std::invalid_argument e)
        {
            // If we can't read the file
            triplet.indiceP  = UINT_MAX;
            triplet.indiceUV = UINT_MAX;
            triplet.indiceN  = UINT_MAX;
            LOG(WARNING, "Could not read the triplet");
        }

        return triplet;
    }

    void Model::readIndiceNoSlash   (std::string& strIndices, Triplet& triplet)
    {
        // Just parse the position
        triplet.indiceP  = std::stoul(strIndices) - 1;
        triplet.indiceUV = UINT_MAX;
        triplet.indiceN  = UINT_MAX;
    }

    void Model::readIndiceOneSlash  (std::string& strIndices, Triplet& triplet)
    {
        // Create a string stream to split the string depending on the slashes
        std::istringstream iss(strIndices);
        std::string str;

        // Split the first value which is the position
        std::getline(iss, str, '/');
        triplet.indiceP  = std::stoul(str) - 1;

        // Split the second value which is the position of the texture
        std::getline(iss, str, '/');
        triplet.indiceUV = std::stoul(str) - 1;

        triplet.indiceN  = UINT_MAX;
    }

    void Model::readIndiceTwoSlashes(std::string& strIndices, Triplet& triplet)
    {
        // Create a string stream to split the string depending on the slashes
        std::istringstream iss(strIndices);
        std::string str;

        // Split the first value which is the position
        std::getline(iss, str, '/');
        triplet.indiceP  = std::stoul(str) - 1;

        // Split the second value which is the position of the texture (can be empty)
        std::getline(iss, str, '/');
        if (str.length() > 0)
            triplet.indiceUV = std::stoul(str) - 1;
        else
            triplet.indiceUV = UINT_MAX;

        // Split the third value which is the normal
        std::getline(iss, str, '/');
        triplet.indiceN  = std::stoul(str) - 1;
    }

    void Model::addVertex(Triplet& triplet)
    {
        // Check if we can insert this triplet
        std::map<Triplet, uint>::iterator it = _triplets.find(triplet);

        // If it doesn't exists create it and add the indice
        if (it == _triplets.end())
        {
            // Get the new indice for the vertex
            GLuint indice = _vertices.size();

            // Create the vertex and add it to the vector
            const Vec4& pos     = (triplet.indiceP  != UINT_MAX) ?
                _positions[triplet.indiceP] : Vec4(0.0f, 0.0f, 0.0f);
            const Vec3& uvs     = (triplet.indiceUV != UINT_MAX) ?
                _uvs[triplet.indiceUV]      : Vec3(0.0f, 0.0f, 0.0f);
            const Vec3& normal  = (triplet.indiceN  != UINT_MAX) ?
                _normals[triplet.indiceN]   : Vec3(0.0f, 0.0f, 0.0f);

            _vertices.emplace_back(pos, uvs, normal);
            // Add the triplet to the list of triplet stored
            _triplets.insert(std::pair<Triplet, uint>(std::move(triplet), indice));
            _indices.push_back(std::move(indice));
        }
        // If it exists only add the indice
        else
            _indices.emplace_back(it->second);
    }

    void Model::clear() noexcept
    {
        _positions.clear();
        _uvs.clear();
        _normals.clear();
        _triplets.clear();
        _indices.clear();
        _vertices.clear();
    }

    void Model::initModel() noexcept
    {
        initVAO();

    	// Get the vertices and the indices
        _nIndices = _indices.size();

        GLuint vbo, ebo;
        // Init the VBO with the vertices
        initVBO(&vbo, (GLfloat*)_vertices.data(), _vertices.size() * sizeof(Vertex));
        // Init the EBO with the array of indices
        initEBO(&ebo, (GLuint*) _indices.data(), _nIndices * sizeof(GLuint));

        clear(); // Clear the model one it is passed

        attribPointer(0, 4, 10, 0); // Pointer of the positions
        attribPointer(1, 3, 10, 4); // Pointer of the UV
        attribPointer(2, 3, 10, 7); // Pointer of the texture

        unbindVAO();

        glDeleteBuffers(1, &ebo);
        glDeleteBuffers(1, &vbo);
    }

    void Model::initVAO() noexcept
    {
        glGenVertexArrays(1, &_VAO);
        glBindVertexArray(_VAO);
    }

    void Model::initVBO(GLuint* vbo, GLfloat* vertices, size_t size) noexcept
    {
        // Generate the VBO
        glGenBuffers(1, vbo);

        // Set the VBO
    	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    	glBufferData(
            GL_ARRAY_BUFFER,
            size,
            vertices,
            GL_STATIC_DRAW
        );
    }

    void Model::initEBO(GLuint* ebo, GLuint* indices, size_t size) noexcept
    {
        // Generate the EBO
        glGenBuffers(1, ebo);

        // Set the EBO
    	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
    	glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            size,
            indices,
            GL_STATIC_DRAW
        );
    }

    void Model::attribPointer(GLuint index, GLint size,
                             GLsizei stride, GLsizei offset) noexcept
    {
        glVertexAttribPointer(
            index,
            size,
            GL_FLOAT,
            GL_FALSE,
            stride * sizeof(GLfloat),
            (GLvoid*) (offset * sizeof(GLfloat))
        );
    	glEnableVertexAttribArray(index);
    }

    void Model::bindVAO() noexcept
    {
        glBindVertexArray(_VAO);
    }

    void Model::unbindVAO() noexcept
    {
        glBindVertexArray(0);
    }

    Model* Model::createCube(ResourcesManager* rm, const std::string& pathTexture) noexcept
    {
        if (!rm)
            return nullptr;

        // Get the model of the untextured cube
        std::string mapString = "Textured_" + pathTexture;
        auto it = rm->models().find(mapString);

        // If it exists return it
        if (it != rm->models().end())
        {
            LOG(DEBUG, std::string("Model : ") + mapString + " exists");
            return it->second;
        }

        // Create it and insert it
        Model* model = new Model();
        try 
        {
            model->loadOBJ(CUBE_NOT_TEXTURED_PATH, rm);
            model->setTexture(rm, pathTexture);
            rm->models().insert(std::pair<std::string, Model*>(mapString, model));
        }
        catch (std::string e)
        {
            delete model;
            return nullptr;
        }

        return model;
    }

    void Model::setTexture(ResourcesManager* rm, const std::string path) noexcept
    {
        // Create the material of the cube using the texture
        Material m;
        m.setMapKd(rm->getTexture(path));

        // Add the only material to the model
        _materials.clear();
        _materials.push_back(m);

        // Set the indice of the only texture to the model
        _indicesMaterial.clear();
        _indicesMaterial.push_back(std::pair<uint, uint>(0, 0));
    }
	#pragma endregion 
} /* Resources */
