#include "BlockRenderer.h"
#include "../game/registry/GameRegistry.h"

#define TEXTURE(x, y) ((x + y) / 6.f)

GLfloat cubeVertices[] = {
	// Positions          // Texture Coords

	//back
	-0.5f, -0.5f, -0.5f,  TEXTURE(0.0f, 3), 1.0f,
	0.5f, -0.5f, -0.5f,   TEXTURE(1.0f, 3), 1.0f,
	0.5f,  0.5f, -0.5f,   TEXTURE(1.0f, 3), 0.0f,
	0.5f,  0.5f, -0.5f,   TEXTURE(1.0f, 3), 0.0f,
	-0.5f,  0.5f, -0.5f,  TEXTURE(0.0f, 3), 0.0f,
	-0.5f, -0.5f, -0.5f,  TEXTURE(0.0f, 3), 1.0f,

	//front
	-0.5f, -0.5f,  0.5f, TEXTURE(0.0f, 1), 1.0f,
	0.5f, -0.5f,  0.5f,  TEXTURE(1.0f, 1), 1.0f,
	0.5f,  0.5f,  0.5f,  TEXTURE(1.0f, 1), 0.0f,
	0.5f,  0.5f,  0.5f,  TEXTURE(1.0f, 1), 0.0f,
	-0.5f,  0.5f,  0.5f, TEXTURE(0.0f, 1), 0.0f,
	-0.5f, -0.5f,  0.5f, TEXTURE(0.0f, 1), 1.0f,

	//left nc
	-0.5f,  0.5f,  0.5f,  TEXTURE(1.0f, 4), 0.0f,
	-0.5f,  0.5f, -0.5f,  TEXTURE(0.0f, 4), 0.0f,
	-0.5f, -0.5f, -0.5f,  TEXTURE(0.0f, 4), 1.0f,
	-0.5f, -0.5f, -0.5f,  TEXTURE(0.0f, 4), 1.0f,
	-0.5f, -0.5f,  0.5f,  TEXTURE(1.0f, 4), 1.0f,
	-0.5f,  0.5f,  0.5f,  TEXTURE(1.0f, 4), 0.0f,

	//right nc
	0.5f,  0.5f,  0.5f,  TEXTURE(1.0f, 2), 0.0f,
	0.5f,  0.5f, -0.5f,  TEXTURE(0.0f, 2), 0.0f,
	0.5f, -0.5f, -0.5f,  TEXTURE(0.0f, 2), 1.0f,
	0.5f, -0.5f, -0.5f,  TEXTURE(0.0f, 2), 1.0f,
	0.5f, -0.5f,  0.5f,  TEXTURE(1.0f, 2), 1.0f,
	0.5f,  0.5f,  0.5f,  TEXTURE(1.0f, 2), 0.0f,

	//bottom nc
	-0.5f, -0.5f, -0.5f, TEXTURE(1.0f, 0), 0.0f,
	0.5f, -0.5f, -0.5f,  TEXTURE(0.0f, 0), 0.0f,
	0.5f, -0.5f,  0.5f,  TEXTURE(0.0f, 0), 1.0f,
	0.5f, -0.5f,  0.5f,  TEXTURE(0.0f, 0), 1.0f,
	-0.5f, -0.5f,  0.5f, TEXTURE(1.0f, 0), 1.0f,
	-0.5f, -0.5f, -0.5f, TEXTURE(1.0f, 0), 0.0f,

	//top nc
	-0.5f,  0.5f, -0.5f, TEXTURE(0.0f, 5), 0.0f,
	0.5f,  0.5f, -0.5f,  TEXTURE(1.0f, 5), 0.0f,
	0.5f,  0.5f,  0.5f,  TEXTURE(1.0f, 5), 1.0f,
	0.5f,  0.5f,  0.5f,  TEXTURE(1.0f, 5), 1.0f,
	-0.5f,  0.5f,  0.5f, TEXTURE(0.0f, 5), 1.0f,
	-0.5f,  0.5f, -0.5f, TEXTURE(0.0f, 5), 0.0f
};

GLfloat testquad[] = {
	-1.0, -1.0, 0.0, 0.0, 0.0,
	1.0, -1.0, 0.0, 0.0, 0.0,
	1.0, 1.0, 0.0, 0.0, 0.0,
};

BlockRenderer::BlockRenderer()
{
}

BlockRenderer* BlockRenderer::instance()
{
	static BlockRenderer *instance = new BlockRenderer;
	return instance;
}

BlockRenderer::~BlockRenderer()
{
}

void BlockRenderer::init()
{
	m_Shader = std::make_unique<Shader>("./res/shader/BlockRenderer.vert", "./res/shader/BlockRenderer.frag");

	uint BlockVBO;
	GLCall(glCreateVertexArrays(1, &m_ChunkVao));

	GLCall(glCreateBuffers(1, &BlockVBO));
	GLCall(glCreateBuffers(1, &m_ChunkVBO));

	GLCall(glBindVertexArray(m_ChunkVao));

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, BlockVBO));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW));
		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0));
		GLCall(glEnableVertexAttribArray(1));
		GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))));

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ChunkVBO));
		GLCall(glBufferData(GL_ARRAY_BUFFER, CHUNK_VBO_MAX_SIZE, nullptr, GL_STREAM_DRAW));
		GLCall(glEnableVertexAttribArray(2));
		GLCall(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat) + 4, 0));
		GLCall(glEnableVertexAttribArray(3));
		GLCall(glVertexAttribPointer(3, 1, GL_INT, GL_FALSE, 3 * sizeof(GLfloat) + 4, (GLvoid*)(3 * sizeof(GLfloat))));

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		GLCall(glVertexAttribDivisor(2, 1));
		GLCall(glVertexAttribDivisor(3, 1));

	GLCall(glBindVertexArray(0));

	std::vector<std::string> paths;
	for (auto &block : GameRegistry::instance().m_RegisteredBlocks)
	{
		paths.push_back("./res/textures/blocks/" + block.regName + ".jpg");
	}
	paths.shrink_to_fit();

	TextureProperties prop;
	prop.FilterMag = GL_LINEAR;
	prop.FilterMin = GL_NEAREST_MIPMAP_LINEAR;
	prop.Wrapping_S = GL_CLAMP_TO_EDGE;
	prop.Wrapping_T = GL_CLAMP_TO_EDGE;
	prop.height = 32;
	prop.width = 192;


	std::cout << "5" << std::endl;

	m_BlockTextures.loadFromFiles(paths, prop);

	std::cout << "6" << std::endl;
	std::cout << "BlockRenderer Initialized!" << std::endl;
}

void BlockRenderer::begin()
{
	GLCall(glActiveTexture(GL_TEXTURE0));
	m_BlockTextures.bind();

	m_Shader->Use();
	m_Shader->setUniform1i("textures", 0);
	glm::mat4 vp = GameRegistry::instance().getPlayer().m_Camera.getVPMatrix();
	m_Shader->setUniformMat4("vp", vp);

	GLCall(glBindVertexArray(m_ChunkVao));
}

struct ShaderBlock
{
	glm::vec3 position;
	int id;
};

void BlockRenderer::render(const Chunk &chunk)
{
	ShaderBlock *block = (ShaderBlock *) glMapNamedBuffer(m_ChunkVBO, GL_WRITE_ONLY);

	for (const Block &bl : chunk.m_Blocks)
	{
		int xoff = ((int)chunk.x) << 4;
		int zoff = ((int)chunk.z) << 4;
		block->position = bl.position + glm::vec3(xoff, 0 , zoff);
		block->id = bl.ID;
		block++;
	}

	GLCall(glUnmapNamedBuffer(m_ChunkVBO));
	GLCall(glDrawArraysInstanced(GL_TRIANGLES, 0, 36, chunk.m_Blocks.size()));
}
