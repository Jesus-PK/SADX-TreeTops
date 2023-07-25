#include "pch.h"

HelperFunctions HelperFunctionsGlobal;

extern "C"
{
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		//	HelperFunctions pointer for external use:

		HelperFunctionsGlobal = helperFunctions;


		//	Disable DC Conversion Sky Deck:

		WriteData<5>((void*)0x422D84, 0x90);
		
		
		//	Custom LevelOBJ:

		RoundMasterList[LevelIDs_SkyDeck] = OBJ_TreeTops;
		
		
		//	Custom Skybox:

		WriteJump((void*)0x5F0340, EXEC_TTSkybox);


		//	Load Level Stuff:

		LANDTABLE_TreeTops();
		DEATHZONES_TreeTops();
		STARTPOSITIONS_TreeTops(helperFunctions);
		PATHS_TreeTops(helperFunctions);
		//FILES_TreeTops(helperFunctions);


		//	Load Object Assets - Load Object List and Texture List:

		LOADOBJECTS_TreeTops();
		INITOBJECTS_TreeTops();


		//	Load Lantern Engine Custom Files:

		LANTERN_TreeTops();
		
		
		//	Load TitleCards and Mission Cards:

		TITLECARDS_TreeTops(path, helperFunctions);
		MISSIONCARDS_TreeTops();

		
		//	Level Destructor Trampoline:
		
		INIT_LevelDestructor();
	}

	__declspec(dllexport) void __cdecl OnFrame()
	{
		//	Lantern Engine .dll Check:

		LANTERNERROR_TreeTops();
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}