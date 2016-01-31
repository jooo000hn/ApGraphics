#pragma once

#include "core/core.h"
#include "utils/timer.h"

namespace apanoo {
	class ApGraphics
	{
	protected:
		ApGraphics()
			: m_FramesPerSecond(0), m_UpdatesPerSecond(0)
		{}
		virtual ~ApGraphics()
		{
			delete m_Window;
			delete m_Timer;
		}

		Window* createWindow(const char* title, int width, int height)
		{
			m_Window = new Window(title, width, height);
			return m_Window;
		}
	public:
		void start() {
			init();
			run();
		}

	protected:

		// 初始化 
		virtual void init() = 0;

		// 每秒执行一次
		virtual void tick() {}

		// 每60秒执行一次
		virtual void update() {}

		// (不打开垂直同步情况下) 不限制帧率
		virtual void render() = 0;

		const unsigned int getFPS() const { return m_FramesPerSecond; }
		const unsigned int getUPS() const { return m_UpdatesPerSecond; }

	private:
		void run()
		{
			float timer = 0.0f;
			float updateTimer = 0.0f;
			float updateTick = 1.0f / 60.0f;
			m_Timer = new Timer();
			unsigned int frames = 0;
			unsigned int updates = 0;

			while (!m_Window->closed())
			{
				m_Window->clear();

				if (m_Timer->elapsed() - updateTimer > updateTick)
				{
					update();
					updates++;
					updateTimer += updateTick;
				}

				render();    // 快速渲染
				frames++;
				m_Window->update();
				if (m_Timer->elapsed() - timer > 1.0f)
				{
					tick();  // 每秒执行一次
					timer += 1.0f;
					m_FramesPerSecond = frames;   // fps
					m_UpdatesPerSecond = updates; // ups
					frames = 0;
					updates = 0;
				}
			}
		}
	public:
		inline Window* getWindow() const { return m_Window; }

	private:
		Window* m_Window;
		Timer* m_Timer;
		unsigned int m_FramesPerSecond;
		unsigned int m_UpdatesPerSecond;
	};
}