#include <stdio.h>
#include <ft2build.h>
#include FT_CONFIG_OPTIONS_H

#include "freetype-gl.h"
#include "vertex-buffer.h"
#include "text-buffer.h"
#include "markup.h"
#include "shader.h"
#include "mat4.h"

#include <GLFW/glfw3.h>


// ------------------------------------------------------- typedef & struct ---
typedef struct {
	float x, y, z;
	float r, g, b, a;
} vertex_t;


// ------------------------------------------------------- global variables ---
text_buffer_t *text_buffer;
vertex_buffer_t *buffer;
GLuint shader;
mat4 model, view, projection;

void init()
{
	buffer = vertex_buffer_new("vertex:3f,color:4f");
	vertex_t vertices[4 * 2] = { { 15,  0,0, 0,0,0,1 },
	{ 15,330,0, 0,0,0,1 },
	{ 245,  0,0, 0,0,0,1 },
	{ 245,330,0, 0,0,0,1 } };
	GLuint indices[4 * 3] = { 0,1,2,3, };
	vertex_buffer_push_back(buffer, vertices, 4, indices, 4);

	text_buffer = text_buffer_new(LCD_FILTERING_ON,
		"../media/shaders/text.vert",
		"../media/shaders/text.frag");
	vec4 black = { { 0.0, 0.0, 0.0, 1.0 } };
	text_buffer->base_color = black;

	vec4 none = { { 1.0, 1.0, 1.0, 0.0 } };
	markup_t markup;
	markup.family = "../media/fonts/Vera.ttf";
	markup.size = 9.0;
	markup.bold = 0;
	markup.italic = 0;
	markup.rise = 0.0;
	markup.spacing = 0.0;
	markup.gamma = 1.0;
	markup.foreground_color = black;
	markup.background_color = none;
	markup.underline = 0;
	markup.underline_color = black;
	markup.overline = 0;
	markup.overline_color = black;
	markup.strikethrough = 0;
	markup.strikethrough_color = black;
	markup.font = 0;

	size_t i;
	vec2 pen = { { 20, 320 } };
	char *text = "| A Quick Brown Fox Jumps Over The Lazy Dog\n";
	for (i = 0; i < 30; ++i)
	{
		text_buffer_add_text(text_buffer, &pen, &markup, text, 0);
		pen.x += i*0.1;
	}

	shader = shader_load("../media/shaders/v3f-c4f.vert",
		"../media/shaders/v3f-c4f.frag");
	mat4_set_identity(&projection);
	mat4_set_identity(&model);
	mat4_set_identity(&view);
}


// ---------------------------------------------------------------- display ---
void display(GLFWwindow* window)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(text_buffer->shader);
	{
		glUniformMatrix4fv(glGetUniformLocation(text_buffer->shader, "model"),
			1, 0, model.data);
		glUniformMatrix4fv(glGetUniformLocation(text_buffer->shader, "view"),
			1, 0, view.data);
		glUniformMatrix4fv(glGetUniformLocation(text_buffer->shader, "projection"),
			1, 0, projection.data);
		text_buffer_render(text_buffer);
	}
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glBlendColor(1.0, 1.0, 1.0, 1.0);
	glUseProgram(shader);
	{
		glUniformMatrix4fv(glGetUniformLocation(shader, "model"),
			1, 0, model.data);
		glUniformMatrix4fv(glGetUniformLocation(shader, "view"),
			1, 0, view.data);
		glUniformMatrix4fv(glGetUniformLocation(shader, "projection"),
			1, 0, projection.data);
		vertex_buffer_render(buffer, GL_LINES);
	}

	glfwSwapBuffers(window);
}


// ---------------------------------------------------------------- reshape ---
void reshape(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	mat4_set_orthographic(&projection, 0, width, 0, height, -1, 1);
}


// --------------------------------------------------------------- keyboard ---
void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}


// --------------------------------------------------------- error-callback ---
void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}


// ------------------------------------------------------------------- main ---
int main(int argc, char **argv)
{
	GLFWwindow* window;
#define FT_CONFIG_OPTION_SUBPIXEL_RENDERING
#ifndef FT_CONFIG_OPTION_SUBPIXEL_RENDERING
	fprintf(stderr,
		"This demo requires freetype to be compiled "
		"with subpixel rendering.\n");
	exit(EXIT_FAILURE);
#endif

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(1, 1, argv[0], NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glfwSetFramebufferSizeCallback(window, reshape);
	glfwSetWindowRefreshCallback(window, display);
	glfwSetKeyCallback(window, keyboard);

#ifndef __APPLE__
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}
	fprintf(stderr, "Using GLEW %s\n", glewGetString(GLEW_VERSION));
#endif

	init();

	glfwSetWindowSize(window, 260, 330);
	glfwShowWindow(window);

	while (!glfwWindowShouldClose(window))
	{
		display(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return EXIT_SUCCESS;
}
