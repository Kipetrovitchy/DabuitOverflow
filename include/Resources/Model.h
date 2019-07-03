#ifndef __MODEL_H__
#define __MODEL_H__

#include <cstdio>
#include <GL/glew.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include "Triplet.h"
#include "Vertex.h"
#include "Material.h"
#include "LibMaths.h"

#define CUBE_NOT_TEXTURED_PATH "./resources/cubeNotTextured.obj"

namespace Resources
{
	#pragma region typedefs
    typedef Core::DataStructure::Triplet Triplet;
    typedef Core::Maths::Vec4 Vec4;
    typedef Core::Maths::Vec3 Vec3;
	#pragma endregion

    class ResourcesManager;

    class Model
    {
    private:
		#pragma region Attributes
        /* All the temporary vectors to parse the model */
        ResourcesManager* _resourcesManager;
        std::string       _folderPath;

        std::vector<Vec4> _positions;
        std::vector<Vec3> _uvs;
        std::vector<Vec3> _normals;
        std::map<Triplet, uint> _triplets;

        std::vector<uint>       _indices;
        std::vector<Vertex>     _vertices;

        /* Store the materials */
        std::vector<Material>               _materials;
        /* 1st uint -> indiceCurrentVertex | 2nd uint -> indiceMaterial */
        std::vector<std::pair<uint, uint>>  _indicesMaterial;

        /* Store the VAO and the number of indices */
        GLuint _VAO;
        GLuint _nIndices;
		#pragma endregion

		#pragma region Functions
        /* Parse the current file */
        void    parseFile           (std::ifstream& file);
        /* Parse the current line given */
        void    parseLine           (std::string& line);
        /* Parse the line if it contains a definition of a .mtl */
        void	parseMTL            (std::istringstream& data);
        /* Parse the current material of the .mtl */
        void	parseNextMTL        (std::ifstream& file, std::istringstream& data);
        /* Change the current material used */
        void	changeCurrentMat    (std::istringstream& data);
        /* Give the position of the material in the vertor */
        uint    findMaterial        (std::string& matName);
        /* Parse the current vertex of the line */
        void    getCurrentVertex    (std::istringstream& data);
        /* Parse the current texture coordinates of the line */
        void    getCurrentUV        (std::istringstream& data);
        /* Parse the current normal of the line */
        void    getCurrentNormal    (std::istringstream& data);
        /* Parse the current face of the line */
        void    getCurrentFace      (std::istringstream& data);
        /* Get the triplet of the current line */
        Triplet splitIndices        (std::string& strIndices);
        /* Read the current triplet if it contains no slash */
        void    readIndiceNoSlash   (std::string& strIndices, Triplet& triplet);
        /* Read the current triplet if it contains one slash */
        void    readIndiceOneSlash  (std::string& strIndices, Triplet& triplet);
        /* Read the current triplet if it contains two slashes */
        void    readIndiceTwoSlashes(std::string& strIndices, Triplet& triplet);
        /* Add the triplet to the list of vertices */
        void    addVertex           (Triplet& triplet);

        /* Clear all the maps and the vectors */
        void    clear()                                              noexcept;
        /* Initialize the Model in the GPU */
        void	initModel()                                          noexcept;
        /* Initialize the VAO */
        void	initVAO()                                            noexcept;
        /* Initialize the VBO */
        void	initVBO(GLuint* vbo, GLfloat* vertices, size_t size) noexcept;
        /* Initialize the EBO */
        void	initEBO(GLuint* ebo, GLuint*  indices,  size_t size) noexcept;
        /* Attribe the pointers for the VAO */
        void	attribPointer(GLuint index, GLint size,
                              GLsizei stride, GLsizei offset)        noexcept;
        /* Function that will set only this texture for the Model */
        void    setTexture(ResourcesManager* rm, const std::string path) noexcept;
		#pragma endregion

    public:
		#pragma region Constructors
        Model();
        ~Model();
		#pragma endregion

		#pragma region Functions
        void    loadOBJ(const std::string& path, ResourcesManager* rm);
        void	bindVAO()                                      noexcept;
        void	unbindVAO()                                    noexcept;

        static Model* createCube(ResourcesManager* rm, const std::string& pathTexture) noexcept;
		#pragma endregion

		#pragma region Accessors
        std::vector<Material>& materials()     { return _materials; };
        std::vector<std::pair<uint, uint>>& indicesMaterial()
            { return _indicesMaterial; }
        GLuint&               id()             { return _VAO; };
        GLuint                id()       const { return _VAO; };
        GLuint&               nIndices()       { return _nIndices; };
        GLuint                nIndices() const { return _nIndices; };
		#pragma endregion
    };
} /* Resources */

#endif//__MODEL_H__
