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

		static Input& Get();

	private:
		KeyState keyState[256] = {};
		MouseState MouseState[3] = {};
		Vector2 mousePosition;
		Vector2 mousePreviousPosition;
		static Input* instance;
	};
}

