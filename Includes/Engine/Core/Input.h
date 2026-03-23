#pragma once

#include "Core/Common.h"
#include "Math/Vector2.h"

namespace Craft
{
	struct KeyState
	{
		bool isKeyDown = false, isKeyUp = false, isKey = false;

		void SetKeyUpDown(bool isKeyUp, bool isKeyDown)
		{
			this->isKeyDown = isKeyDown;
			this->isKeyUp = isKeyUp;
			isKey = isKeyDown && !isKeyUp;
		}
	};

	struct MouseState
	{
		bool isButtonDown = false, isButtonUp = false, isButton = false;

		void SetButtonUpDown(bool isButtonUp, bool isButtonDown)
		{
			this->isButtonUp = isButtonUp;
			this->isButtonDown = isButtonDown;
			isButton = isButtonDown && !isButtonUp;
		}
	};

	class CRAFT_API Input
	{
	public:
		Input();
		~Input();

		bool IsKeyDown(unsigned int keyCode);
		bool IsKeyUp(unsigned int keyCode);
		bool IsKey(unsigned int keyCode);

		bool IsButtonDown(unsigned int button);
		bool IsButtonUp(unsigned int button);
		bool IsButton(unsigned int button);

		void ResetInputs();

		Vector2 GetMousePosition();
		float GetMouseDeltaX();		// 이전 프레임 대비 이동한 거리(X).
		float GetMouseDeltaY();		// 이전 프레임 대비 이동한 거리(Y).

		void SetKeyUpDown(unsigned int keyCode, bool isKeyUp, bool isKeyDown);
		void SetButtonUpDown(unsigned int button, bool isButtonUp, bool isButtonDown);
		void SetMousePosition(int x, int y);

		static Input& Get();
		static bool IsValid();

	private:
		KeyState keyStates[256] = {};
		MouseState mouseStates[3] = {};
		Vector2 mousePosition;
		Vector2 mousePreviousPosition;
		static Input* instance;
	};
}

