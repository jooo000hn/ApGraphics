#include "Window.h"
#include "../../log/Log.h"

namespace apanoo {
	void window_resize(GLFWwindow* window, int width, int height);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	Window::Window(const char *title, int width, int height)
	{
		m_Title = title;
		m_Width = width;
		m_Height = height;
		m_CursorHide = false;
		if (!init())
		{
			glfwTerminate();
		}

		for (int i = 0; i < MAX_KEYS; i++)
		{
			m_Keys[i] = false;
			m_KeyState[i] = false;
			m_KeyTyped[i] = false;
		}

		for (int i = 0; i < MAX_BUTTONS; i++)
		{
			m_MouseButtons[i] = false;
			m_MouseState[i] = false;
			m_MouseClicked[i] = false;
		}
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	bool Window::init()
	{
		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW!" << std::endl;
			Log::Instance()->OutputError("Failed to initialize GLFW!");
			return false;
		}
		Log::Instance()->OutputSuccess("GLFW init success!");
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		if (!m_Window)
		{
			std::cout << "Failed to create GLFW window!" << std::endl;
			Log::Instance()->OutputError("Failed to create GLFW window!");
			return false;
		}
		Log::Instance()->OutputSuccess("GLFW window create success!");
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetFramebufferSizeCallback(m_Window, window_resize);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glfwSwapInterval(0); // 关闭垂直同步

		if (glewInit() != GLEW_OK)
		{
			std::cout << "Could not initialize GLEW!" << std::endl;
			Log::Instance()->OutputError("Could not initialize GLEW!");
			return false;
		}
		Log::Instance()->OutputSuccess("GLEW init success!");

		// 开启 blend 
		glEnable(GL_BLEND); 
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);

		// 背面剔除
		glFrontFace(GL_CW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);

		std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
		Log::Instance()->OutputMisc("OpenGL %s", glGetString(GL_VERSION));
		return true;
	}

	bool Window::isKeyPressed(unsigned int keycode) const
	{
		if (keycode >= MAX_KEYS)
		{
			return false;
		}

		return m_Keys[keycode];
	}

	bool Window::isKeyTyped(unsigned int keycode) const
	{
		if (keycode >= MAX_KEYS)
		{
			return false;
		}

		return m_KeyTyped[keycode];
	}

	bool Window::isMouseButtonPressed(unsigned int button) const
	{
		if (button >= MAX_BUTTONS)
		{
			return false;
		}

		return m_MouseButtons[button];
	}

	bool Window::isMouseButtonClicked(unsigned int button) const
	{
		if (button >= MAX_BUTTONS)
		{
			return false;
		}

		return m_MouseClicked[button];
	}

	void Window::setCursorPosition(double x, double y)
	{
		glfwSetCursorPos(m_Window, x, y);
	}

	void Window::setCursorVisible(bool visible)
	{
		if (visible && m_CursorHide)
		{
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			m_CursorHide = false;
		}
		if (!visible && !m_CursorHide)
		{
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			m_CursorHide = true;
		}
	}

	void Window::setCenterCursor()
	{
		setCursorPosition(getCenter().getX(), getCenter().getY());
	}

	void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::update()
	{
		for (int i = 0; i < MAX_KEYS; i++)
		{
			// 保证只按下一次
			m_KeyTyped[i] = m_Keys[i] && !m_KeyState[i];
		}

		for (int i = 0; i < MAX_BUTTONS; i++)
		{
			// 保证只点击一次
			m_MouseClicked[i] = m_MouseButtons[i] && !m_MouseState[i];
		}

		memcpy(m_KeyState, m_Keys, MAX_KEYS);
		memcpy(m_MouseState, m_MouseButtons, MAX_BUTTONS);

		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			std::cout << "OpenGL Error: " << error << std::endl;
			Log::Instance()->OutputError("OpenGL Error: %d", error);
		}

		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	bool Window::closed() const
	{
		return glfwWindowShouldClose(m_Window) == 1;
	}

	void window_resize(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_Width = width;
		win->m_Height = height;
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_Keys[key] = action != GLFW_RELEASE;
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_MouseButtons[button] = action != GLFW_RELEASE;
	}

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->mx = xpos;
		win->my = ypos;
	}
}