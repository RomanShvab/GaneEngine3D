﻿#include "Pyramid.h"

Pyramid::Pyramid()
{
	initializeShaders();
	initializeGeometry();
}

Pyramid::~Pyramid()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
}

void Pyramid::draw(const glm::mat4& view, const glm::mat4& projection)
{
	glUseProgram(shaderProgram);

	// Rotacja piramidy
	float time = glfwGetTime();
	glm::mat4 model = glm::rotate(glm::mat4(1.0f), time, glm::vec3(0.0f, 1.0f, 0.0f));

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 18);
	glBindVertexArray(0);
}

void Pyramid::initializeShaders()
{
	const char* vertexShaderSource = R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            uniform mat4 model;
            uniform mat4 view;
            uniform mat4 projection;
            void main() {
                gl_Position = projection * view * model * vec4(aPos, 1.0);
            }
        )";

	const char* fragmentShaderSource = R"(
            #version 330 core
            out vec4 FragColor;
            void main() {
                FragColor = vec4(1.0, 1.0, 1.0, 1.0);
            }
        )";

	// Kompilacja shaderów
	unsigned int vertexShader, fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	// Linkowanie programu shaderów
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Pyramid::initializeGeometry() {
	// Definicja wierzchołków piramidy
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.0f,  0.5f,  0.0f,

		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.0f,  0.5f,  0.0f,

		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		 0.0f,  0.5f,  0.0f,

		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
		 0.0f,  0.5f,  0.0f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,

		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f
	};

	// VAO, VBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}