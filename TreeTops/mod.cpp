#include "pch.h"

//	Mod Version: v1.2.0

std::string ModPath;
HelperFunctions HelperFunctionsGlobal;

extern "C"
{
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		ModPath = path;
		HelperFunctionsGlobal = helperFunctions;

		CheckActiveMods();
		CheckBASS();
		ExpandDrawQueueMemoryPool();

		
		//	Init Mod:

		INIT_Level();
		INIT_LevelTask();
		INIT_LevelRanks();
		INIT_Objects();
		INIT_Graphics();
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}