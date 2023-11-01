#include "pch.h"

//	Mod Version: v1.1.0 (WIP)

HelperFunctions HelperFunctionsGlobal;

extern "C"
{
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		HelperFunctionsGlobal = helperFunctions;

		CheckActiveMods();


		//	Expand Draw Queue Memory Pool (Applies to the entire game):
		
		WriteData((Uint32*)0x408643, 0x100000ui32);
		WriteData((Uint32*)0x40864D, 0x100000ui32);
		WriteData((Uint32*)0x40866B, 0x100000ui32);

		
		//	Init Mod:

		INIT_Level();
		INIT_LevelTask();
		INIT_LevelRanks();
		INIT_Objects(helperFunctions);
		INIT_Graphics(path);
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}