#pragma once

#include "Event.h"
#include "SaturnEngine/Core.h"

namespace SaturnEngine
{
	//Modifier
	enum Modifier : U8
	{
		ModifierNone = 0,
		ModifierLeftMoseButton = 1,
		ModifierMiddleMouseButton = 10,
		ModifierRightMouseButton = 2,
		ModifierShiftKey = 4,
		ModifierControlKey = 8
	};

	//Key code
	enum class KeyCode : U8
	{
		Unknown = 0,
		Backspace = 8,
		Tab = 9,
		Enter = 13,
		Pause = 19,
		CapsLock = 20,
		Escape = 27,
		Space = 32,
		PageUp = 33,
		PageDown = 34,
		End = 35,
		Home = 36,
		Left = 37,
		Up = 38,
		Right = 39,
		Down = 40,
		PrintScreen = 44,
		Insert = 45,
		Delete = 46,
		Zero = 48,
		One = 49,
		Two = 50,
		Three = 51,
		Four = 52,
		Five = 53,
		Six = 54,
		Seven = 55,
		Eight = 56,
		Nine = 57,
		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,
		LeftWindows = 91,
		RightWindows = 92,
		NumZero = 96,
		NumOne = 97,
		NumTwo = 98,
		NumThree = 99,
		NumFour = 100,
		NumFive = 101,
		NumSix = 102,
		NumSeven = 103,
		NumEight = 104,
		NumNine = 105,
		NumSlash = 111,
		NumMultiply = 106,
		NumSubtract = 109,
		NumAdd = 107,
		F1 = 112,
		F2 = 113,
		F3 = 114,
		F4 = 115,
		F5 = 116,
		F6 = 117,
		F7 = 118,
		F8 = 119,
		F9 = 120,
		F10 = 121,
		F11 = 122,
		F12 = 123,
		NumLock = 144,
		ScrollLock = 145,
		LeftShift = 160,
		RightShift = 161,
		LeftControl = 162,
		RightControl = 163,
		LeftAlt = 164,
		RightAlt = 165,
		Colon = 186,
		Plus = 187,
		Comma = 188,
		Dash = 189,
		Period = 190,
		Slash = 191,
		Tilda = 192,
		SquareBracketOpen = 219,
		Backslash = 220,
		SquareBracketClose = 221,
		Quote = 222
	};

	//Invoked when the mouse moves.
	typedef struct MouseMoveEvent : public Event
	{
		Modifier Modifier = ModifierNone;
		U16 X = 0;
		U16 Y = 0;

		EVENT_METHODS(CoreEventType::MouseMove)
	} MouseMoveEvent;

	//Invoked when the mouse is scrolled.
	typedef struct MouseScrollEvent : public Event
	{
		Modifier Modifier = ModifierNone;
		I16 Delta = 0;
		U16 X = 0;
		U16 Y = 0;

		EVENT_METHODS(CoreEventType::MouseScroll)
	} MouseScrollEvent;


	//Invoked when the left mouse button stops being pressed.
	typedef struct LeftMouseButtonUpEvent : public Event
	{
		Modifier Modifier = ModifierNone;
		U16 X = 0;
		U16 Y = 0;

		EVENT_METHODS(CoreEventType::LeftMouseButtonUp)
	} LeftMouseButtonUpEvent;

	//Invoked when the left mouse button is pressed.
	typedef struct LeftMouseButtonDownEvent : public Event
	{
		Modifier Modifier = ModifierNone;
		U16 X = 0;
		U16 Y = 0;

		EVENT_METHODS(CoreEventType::LeftMouseButtonDown)
	} LeftMouseButtonDownEvent;

	//Invoked when the right mouse button stops being pressed.
	typedef struct RightMouseButtonUpEvent : public Event
	{
		Modifier Modifier = ModifierNone;
		U16 X = 0;
		U16 Y = 0;

		EVENT_METHODS(CoreEventType::RightMouseButtonUp)
	} RightMouseButtonUpEvent;

	//Invoked when the right mouse button is pressed.
	typedef struct RightMouseButtonDownEvent : public Event
	{
		Modifier Modifier = ModifierNone;
		U16 X = 0;
		U16 Y = 0;

		EVENT_METHODS(CoreEventType::RightMouseButtonDown)
	} RightMouseButtonDownEvent;

	//Invoked when a key on the keyboard stops being pressed.
	typedef struct KeyUpEvent : public Event
	{
		KeyCode PressedKey = KeyCode::Unknown;

		EVENT_METHODS(CoreEventType::KeyUp)
	} KeyUpEvent;

	//Invoked when a key on the keyboard is pressed.
	typedef struct KeyDownEvent : public Event
	{
		KeyCode PressedKey = KeyCode::Unknown;
		U16 RepeatCount = 0;

		EVENT_METHODS(CoreEventType::KeyDown)
	} KeyDownEvent;
}
