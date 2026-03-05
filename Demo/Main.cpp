#include "Core/Engine.h"
#include "Level/TriangleDemoLevel.h"

using namespace Craft;

// ���� ���� �Լ�.
void LaunchEngineStartup(HINSTANCE instance)
{
	Engine engine;
	engine.Initialize(instance);
	engine.AddNewLevel<TriangleDemoLevel>();
	engine.Run();
}

int main()
{
	LaunchEngineStartup(GetModuleHandle(nullptr));
}