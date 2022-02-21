#pragma once

#include "Utils/String.h"
#include "SaturnEngine/Events/EventSender.h"
#include "SaturnEngine/Events/WindowEvents.h"

namespace SaturnEngine
{
	//Window class, used to create and show a window. Doesn't include a window procedure.
	class SATURN_API Window
	{
	public:
		//Title, width and height by default are set to `Application Window`, 1366 and 768 respectively.
		Window() = delete;
		//Width and height by default are set to 1366 and 768 respectively.
		explicit Window(String title);
		Window(String title, U16 width, U16 height);
		~Window();

		//Returns the title of the window.
		inline String GetTitle() const;
		//Sets the title of the window.
		void SetTitle(const String& title);
		//Returns the width of the window.
		inline U16 GetWidth() const;
		//Returns the height of the window.
		inline U16 GetHeight() const;
		//Returns the window handle.
		inline HWND GetWindowHandle() const;
		//Returns a reference to the window's `EventDispatcher`.
		inline EventSender& EventDispatcher();

		/**
		 * Creates a window class being used by all the windows
		 *
		 * Should only be used once,
		 */
		static void RegisterWindowClass();

	private:
		//Window procedure with member access
		LRESULT WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM  lParam);

		//Window procedure used to set `ActualMessageProc` as the procedure.
		static LRESULT CALLBACK SetupMessageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM  lParam);
		//The actual window procedure used to execute the actual one, which can access window members.
		static LRESULT CALLBACK ActualMessageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM  lParam);

	private:
		HWND m_windowHandle;
		String m_title;
		U16 m_width;
		U16 m_height;
		EventSender m_windowEventSender;
	};
}
