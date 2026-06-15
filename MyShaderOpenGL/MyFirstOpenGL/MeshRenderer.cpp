#include "MeshRenderer.h"
#include <gtc/type_ptr.hpp>

void MeshRenderer::Init(float* vertices, int byteSize)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, byteSize, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void MeshRenderer::Draw(GLuint shaderProgram, const glm::mat4& translation, const glm::mat4& rotation, const glm::mat4& scale, const glm::mat4& view, const glm::mat4& projection, int vertexCount)
{
	glUseProgram(shaderProgram);

	// Enviamos las matrices como uniforms
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "translationMatrix"), 1, GL_FALSE, glm::value_ptr(translation));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotation));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(scale));
	
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glBindVertexArray(0);
}
