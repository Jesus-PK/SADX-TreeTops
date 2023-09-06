#include "pch.h"

HelperFunctions HelperFunctionsGlobal;

extern "C"
{
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		//	HelperFunctions pointer for external use - Check Active Mods and Mod Loader API Version:

		HelperFunctionsGlobal = helperFunctions;

		CheckActiveMods(helperFunctions);
		CheckModLoaderVersion(helperFunctions);

		
		//	Init Mod:

		INIT_Level(helperFunctions);
		INIT_LevelTask();
		INIT_LevelRanks();
		INIT_Objects(helperFunctions);
		INIT_Graphics(path, helperFunctions);
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}