#ifndef RENDERABLE_H
#define RENDERABLE_H

#define GLEW_STATIC
#include <glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtx\string_cast.hpp>

#include <iostream>

class Renderable
{
private:
	enum RenderMode {
		VERTICES = 0,
		ELEMENTS
	};
	GLuint		m_vao, m_vbo, m_ebo;
	GLint		m_model;
	RenderMode	m_renderMode;
	GLint		m_numElems, m_numVerts;
	GLboolean	m_valid;
	GLenum		m_elementType;

protected:
	glm::mat4 m_matrix;

	void bufferObject(GLenum elementType, GLfloat* vertexArray, int vertexLength, GLuint *elementArray, int elementLength){
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);
		
		m_valid = false;
		if (vertexLength == 0 || elementLength == 0) return;
		m_valid = true;

		m_numElems = elementLength;
		m_numVerts = vertexLength;
		m_elementType = elementType;
		m_renderMode = ELEMENTS;

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, vertexLength * sizeof(*vertexArray), vertexArray, GL_STATIC_DRAW);

		glGenBuffers(1, &m_ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementLength * sizeof(*elementArray), elementArray, GL_STATIC_DRAW);

		GLint shaderProgram;
		glGetIntegerv(GL_CURRENT_PROGRAM, &shaderProgram);

		m_model = glGetUniformLocation(shaderProgram, "model");

		// Vert in attributes
		GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

		GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
		glEnableVertexAttribArray(colAttrib);
		glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glBindVertexArray(0);
	}

	~Renderable() {
		glDeleteBuffers(1, &m_vbo);
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_ebo);
	}

public:
	void render(void) {
		if (m_valid) {
			glBindVertexArray(m_vao);
			glUniformMatrix4fv(m_model, 1, GL_FALSE, glm::value_ptr(m_matrix));
			switch (m_renderMode) {
				case ELEMENTS: glDrawElements(m_elementType, m_numElems, GL_UNSIGNED_INT, 0); break;
				case VERTICES: glDrawArrays(m_elementType, 0, 3); break;
			}
			glBindVertexArray(0);
		}
	}

	glm::mat4 & getMatrix() {
		return m_matrix;
	}

	void setMatrix(glm::mat4 & new_matrix) {
		m_matrix = new_matrix;
	}
};
#endif