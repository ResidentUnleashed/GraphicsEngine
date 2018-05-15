#pragma once
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>

#pragma warning( push )
#pragma warning( disable : 4201 )
#pragma warning( disable : 4310 )
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#pragma warning ( pop )

class Mesh
{
public:
	Mesh() : triCount(0), vao(0), vbo(0), ibo(0) {}
	virtual ~Mesh();

	struct Vertex
	{
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec4 texCoord;
	};

	//Initialises the quad
	void initialiseQuad();

	void initialise(unsigned int vertexCount, const Vertex* vertices, unsigned int indexCount = 0, unsigned int* indices = nullptr);

	//For custom drawing
	virtual void draw();

protected:

	unsigned int triCount; /* Total amount of triangles */
	unsigned int vao = 0; /* Vertex array object */
	unsigned int vbo = 0; /* Vertex buffer objects */
	unsigned int ibo = 0; /* Index buffer object */

};

