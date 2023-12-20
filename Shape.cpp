#include "Shape.h"

Shape::Shape() : 
    position(glm::vec3(0.0f, 0.0f, 0.0f)), 
    color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
    model(glm::translate(glm::mat4(1.0f), position))
{
    initializeShaders();
}


void Shape::setPosition(float x, float y, float z) {
    const glm::vec3& newPosition = glm::vec3(x, y, z);
    position = newPosition;
    model = glm::translate(glm::mat4(1.0f), position);
}

void Shape::rotateAtAngle(float x, float y, float z, float angle)
{
    model = glm::rotate(model, angle/100, glm::vec3(x, y, z));
}

void Shape::rotate(float x, float y, float z, float speed)
{
    float time = glfwGetTime();
    model = glm::rotate(model, time*speed, glm::vec3(x, y, z));
}

void Shape::move(float x, float y, float z, float deltaTime) {
    glm::vec3 displacement = glm::vec3(x, y, z) * deltaTime;
    position += displacement;
    model = glm::translate(glm::mat4(1.0f), position);
}

void Shape::setColor(float R, float G, float B, float A)
{
    const glm::vec4& newColor = glm::vec4(R, G, B, A);
    color = newColor;
}

void Shape::initializeShaders()
{
	const char* vertexShaderSource = R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            out vec4 vertexColor; // Dodane dla przekazania koloru do fragment shadera

            uniform mat4 model;
            uniform mat4 view;
            uniform mat4 projection;

            void main()
            {
                gl_Position = projection * view * model * vec4(aPos, 1.0);
                vertexColor = vec4(1.0, 1.0, 1.0, 1.0); // Kolor wierzchołka, możesz go przekazywać z aplikacji
            }
        )";

	const char* fragmentShaderSource = R"(
            #version 330 core
            in vec4 vertexColor; // Dodane dla odbioru koloru od vertex shadera
            out vec4 FragColor;

            uniform vec4 objectColor; // Dodane dla ustawiania koloru obiektu

            void main()
            {
                FragColor = objectColor * vertexColor; // Zmieniono na mnożenie kolorów
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

void Shape::initializeVAOVBO(float* vertices, size_t size)
{
    // VAO, VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Shape::~Shape()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}