#include "SaturnEngine/Window.h"

#include "Management/ErrorManager.h"
#include "Management/LogManager.h"

namespace SaturnEngine
{
	Window::Window(String title)
		: m_width(1366), m_height(768), m_title(std::move(title))
	{
		RECT size;
		size.top = 100;
		size.left = 100;
		size.right = m_width + size.left;
		size.bottom = m_height + size.top;
		if(!AdjustWindowRect(&size, WS_OVERLAPPEDWINDOW, FALSE))
		{
			ST_THROW_ERROR(SaturnError::CouldNotStartUp);
			return;
		}

		//Passing class pointer as an extra parameter, so we can later retrieve it and do some magic.
		m_windowHandle = CreateWindowW(L"SaturnEngineClass", m_title.Pointer(), WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT, size.right - size.left, size.bottom - size.top, nullptr, nullptr,
				GetModuleHandleW(nullptr), this);

		if(m_windowHandle == nullptr)
		{
			ST_THROW_ERROR(SaturnError::CouldNotStartUp);
			return;
		}

		ShowWindow(m_windowHandle, SW_SHOW);
		UpdateWindow(m_windowHandle);
	}

	Window::Window(String title, U16 width, U16 height)
			: m_width(width), m_height(height), m_title(std::move(title))
	{
		RECT size;
		size.top = 100;
		size.left = 100;
		size.right = m_width + size.left;
		size.bottom = m_height + size.top;
		if(!AdjustWindowRect(&size, WS_OVERLAPPEDWINDOW, FALSE))
		{
			ST_THROW_ERROR(SaturnError::CouldNotStartUp);
			return;
		}

		//Passing class pointer as an extra parameter, so we can later retrieve it and do some magic.
		m_windowHandle = CreateWindowW(L"SaturnEngineClass", m_title.Pointer(), WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT, size.right - size.left, size.bottom - size.top, nullptr, nullptr,
				GetModuleHandleW(nullptr), this);

		if(m_windowHandle == nullptr)
		{
			ST_THROW_ERROR(SaturnError::CouldNotStartUp);
			return;
		}

		ShowWindow(m_windowHandle, SW_SHOW);
		UpdateWindow(m_windowHandle);
	}

	Window::~Window()
	{
		DestroyWindow(m_windowHandle);
	}

	String Window::GetTitle() const
	{
		return m_title;
	}

	void Window::SetTitle(const String& title)
	{
		if(!SetWindowTextW(m_windowHandle, title.Pointer()))
		{
			ST_THROW_ERROR(SaturnError::InvalidArgument);
			return;
		}

		m_title = title;
	}

	U16 Window::GetWidth() const
	{
		return m_width;
	}

	U16 Window::GetHeight() const
	{
		return m_height;
	}

	HWND Window::GetWindowHandle() const
	{
		return m_windowHandle;
	}

	EventSender& Window::EventDispatcher()
	{
		return m_windowEventSender;
	}

	void Window::RegisterWindowClass()
	{
		WNDCLASSW wc;
		wc.style = 0;
		wc.lpszMenuName = nullptr;
		wc.lpfnWndProc = SetupMessageProc;
		wc.hbrBackground = nullptr;
		wc.hInstance = GetModuleHandleW(nullptr);
		wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.cbWndExtra = 0;
		wc.cbClsExtra = 0;
		wc.lpszClassName = L"SaturnEngineClass";

		if(!RegisterClassW(&wc))
			ST_THROW_ERROR(SaturnError::CouldNotStartUp);
	}

	LRESULT Window::WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch(msg)
		{
		case WM_MOUSEMOVE:
			{
				MouseMoveEvent e;
				e.X = GET_X_LPARAM(lParam);
				e.Y = GET_Y_LPARAM(lParam);
				e.Modifier = static_cast<Modifier>(wParam);
				m_windowEventSender.Invoke(e);
			}
			break;
		case WM_MOUSEWHEEL:
			{
				MouseScrollEvent e;
				e.X = GET_X_LPARAM(lParam);
				e.Y = GET_Y_LPARAM(lParam);
				e.Modifier = static_cast<Modifier>(GET_KEYSTATE_WPARAM(wParam));
				e.Delta = GET_WHEEL_DELTA_WPARAM(wParam);
				m_windowEventSender.Invoke(e);
			}
			break;
		case WM_LBUTTONUP:
			{
				LeftMouseButtonUpEvent e;
				e.X = GET_X_LPARAM(lParam);
				e.Y = GET_Y_LPARAM(lParam);
				e.Modifier = static_cast<Modifier>(wParam);
				m_windowEventSender.Invoke(e);
			}
			break;
		case WM_LBUTTONDOWN:
			{
				LeftMouseButtonDownEvent e;
				e.X = GET_X_LPARAM(lParam);
				e.Y = GET_Y_LPARAM(lParam);
				e.Modifier = static_cast<Modifier>(wParam);
				m_windowEventSender.Invoke(e);
			}
			break;
		case WM_RBUTTONUP:
			{
				RightMouseButtonUpEvent e;
				e.X = GET_X_LPARAM(lParam);
				e.Y = GET_Y_LPARAM(lParam);
				e.Modifier = static_cast<Modifier>(wParam);
				m_windowEventSender.Invoke(e);
			}
			break;
		case WM_RBUTTONDOWN:
			{
				RightMouseButtonDownEvent e;
				e.X = GET_X_LPARAM(lParam);
				e.Y = GET_Y_LPARAM(lParam);
				e.Modifier = static_cast<Modifier>(wParam);
				m_windowEventSender.Invoke(e);
			}
			break;
		case WM_KEYDOWN:
			{
				KeyDownEvent e;
				e.PressedKey = static_cast<KeyCode>(wParam);
				e.RepeatCount = lParam & 0xFF;
				m_windowEventSender.Invoke(e);
			}
			break;
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProcW(hWnd, msg, wParam, lParam);
		}

		return 0;
	}

	LRESULT Window::SetupMessageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		//If the window hasn't been created yet, set the user window data as the class pointer and `ActualMessageProc`
		//as the current message procedure.
		if(msg == WM_NCCREATE)
		{
			auto* createStruct = reinterpret_cast<CREATESTRUCTW*>(lParam);
			auto* classPointer = reinterpret_cast<Window*>(createStruct->lpCreateParams);

			SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(classPointer));
			SetWindowLongPtrW(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::ActualMessageProc));

			return classPointer->WindowProcedure(hWnd, msg, wParam, lParam);
		}

		return DefWindowProcW(hWnd, msg, wParam, lParam);
	}

	LRESULT Window::ActualMessageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		//We execute the member window procedure
		auto* classPointer = reinterpret_cast<Window*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));

		return classPointer->WindowProcedure(hWnd, msg, wParam, lParam);
	}
}
