#include "Mesh.h"
#include <assert.h>

Mesh::~Mesh()
{
	//Cleanup
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Mesh::initialiseQuad()
{
	//Check that the mesh is not initialised already
	assert(vao == 0);

	//Generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	//Bind vertex array aka a mesh wrapper
	glBindVertexArray(vao);

	//Bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Define 6 vertices for 2 triangles
	Vertex vertices[6];

	//Positions of verts
	vertices[0].position = { -0.5f, 0, 0.5f, 1 };
	vertices[1].position = { 0.5f, 0, 0.5f, 1 };
	vertices[2].position = { -0.5f, 0, -0.5f, 1 };
	vertices[3].position = { -0.5f, 0, -0.5f, 1 };
	vertices[4].position = { 0.5f, 0, 0.5f, 1 };
	vertices[5].position = { 0.5f, 0, -0.5f, 1 };

	//Normals
	vertices[0].normal = { 0, 1, 0, 0 };
	vertices[1].normal = { 0, 1, 0, 0 };
	vertices[2].normal = { 0, 1, 0, 0 };
	vertices[3].normal = { 0, 1, 0, 0 };
	vertices[4].normal = { 0, 1, 0, 0 };
	vertices[5].normal = { 0, 1, 0, 0 };

	//Coords of textures
	vertices[0].texCoord = { 0, 1 }; // bottom left
	vertices[1].texCoord = { 1, 1 }; // bottom right
	vertices[2].texCoord = { 0, 0 }; // top left
	vertices[3].texCoord = { 0, 0 }; // top left
	vertices[4].texCoord = { 1, 1 }; // bottom right
	vertices[5].texCoord = { 1, 0 }; // top right
    
	//Fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	//Enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);


	//Enable second element as normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)16);

    //Enable third element as texture
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);

	//Unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Quad has 2 triangles
	triCount = 2;
}

void Mesh::initialise(unsigned int vertexCount, const Vertex * vertices, unsigned int indexCount, unsigned int * indices)
{
	assert(vao == 0);
	//Generate buffers 
	glGenBuffers(1, &vbo); glGenVertexArrays(1, &vao);

	//Bind vertex array aka a mesh wrapper 
	glBindVertexArray(vao);

	//Bind vertex buffer 
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Fill vertex buffer 
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	//Enable first element as position 
	glEnableVertexAttribArray(0); 
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	//Bind indices if there are any
	if (indexCount != 0)
	{
		glGenBuffers(1, &ibo);

		//Bind vertex buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		//Fill vertex buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		triCount = indexCount / 3;
	}
	else
	{
		triCount = vertexCount / 3;
	}

	//Unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::initialiseFullscreenQuad()
{
	assert(vao == 0);

	//Generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	//Bind vertex array aka a mesh wrapper
	glBindVertexArray(vao);

	//Bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Define vertices
	float vertices[] = {
		-1,1, //Left top
		-1,-1, //Left bottom
		1,1, //Right top
		-1,-1, //Left bottom
		1,-1, //Right bottom
		1, 1 //Right top
	};
	//Fill vertex buffer 
	glBufferData(GL_BUFFER, 12 * sizeof(float), vertices, GL_STATIC_DRAW);

	//Enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8, 0);

	//Unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Quad has 2 triangles
	triCount = 2;
}

void Mesh::draw()
{
	//Bind vertex array aka a mesh wrapper
	glBindVertexArray(vao);

	//Using indices or just vertices?
	if (ibo != 0)
	{
		glDrawElements(GL_TRIANGLES, 3 * triCount, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);
	}
}
