#pragma once

#define  GLEW_STATIC
#include "gl/glew.h"
#include "glfw/glfw3.h"
#include "../../maths/Maths.h"
#include <iostream> 

namespace apanoo {
#define MAX_KEYS	1024
#define MAX_BUTTONS	32

	class Window
	{
	public:
		Window(const char *name, int width, int height);
		~Window();
		void clear() const;
		void update();
		bool closed() const;

		inline const int getWidth() const { return m_Width; }
		inline const int getHeight() const { return m_Height; }
		inline const double getCursorX() const { return mx; }
		inline const double getCursorY() const { return my; }
		inline const Vector2 getCursorPosition() const { return Vector2((float)mx, (float)my); }
		inline const Vector2 getCenter() const { return Vector2(m_Width / 2.0f, m_Height / 2.0f); }
		
		// 是否处于按下状态
		bool isKeyPressed(unsigned int keycode) const;
		
		// 键盘按下一次
		bool isKeyTyped(unsigned int keycode) const;
		
		// 鼠标按下状态
		bool isMouseButtonPressed(unsigned int button) const;

		// 鼠标点击
		bool isMouseButtonClicked(unsigned int button) const;

		// 设置光标位置
		void setCursorPosition(double x, double y);

		// 设置光标模式
		void setCursorVisible(bool visible);

		// 设置光标居中
		void setCenterCursor();
	private:
		bool init();
		friend void window_resize(GLFWwindow* window, int width, int height);
		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	private:
		const char*  m_Title;
		int m_Width, m_Height;
		GLFWwindow*  m_Window;
		bool		 m_Closed;
		bool	     m_CursorHide;

		bool m_Keys[MAX_KEYS];
		bool m_KeyState[MAX_KEYS];
		bool m_KeyTyped[MAX_KEYS];
		bool m_MouseButtons[MAX_BUTTONS];
		bool m_MouseState[MAX_BUTTONS];
		bool m_MouseClicked[MAX_BUTTONS];
		double mx, my;
	};
}