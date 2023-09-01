#include "pch.h"

HelperFunctions HelperFunctionsGlobal;

extern "C"
{
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		//	HelperFunctions pointer for external use:

		HelperFunctionsGlobal = helperFunctions;

		
		//	Check Active Mods and Mod Loader API Version:

		CheckActiveMods(helperFunctions);
		CheckModLoaderVersion(helperFunctions);

		//	Disable DC Conversion Sky Deck:

		WriteData<5>((void*)0x422D84, 0x90);
		
		
		//	Custom LevelOBJ:

		RoundMasterList[LevelIDs_SkyDeck] = RD_TreeTops;
		
		
		//	Custom Skybox:

		ScrollMasterList[LevelIDs_SkyDeck] = BG_TreeTops;


		//	Load Level Stuff:

		LANDTABLE_TreeTops();
		DEATHZONES_TreeTops();
		STARTPOSITIONS_TreeTops(helperFunctions);
		PATHS_TreeTops(helperFunctions);
		//FILES_TreeTops(helperFunctions);		

		WriteCall((void*)0x689172, EV0095_PositionFix); // Tweak Knux position in his story mode cutscene.


		//	Load Custom Ranks and Mission Cards:
		
		MISSIONCARDS_TreeTops();
		INIT_LevelRanks();


		//	Load Object Assets - Load Object List and Texture List:

		LOADOBJECTS_TreeTops();
		INITOBJECTS_TreeTops();


		//	Load Lantern Engine Custom Files:

		LANTERN_TreeTops();
		
		
		//	Load StageNames, TitleCards and Mission Cards:

		STAGENAMES_TreeTops(path, helperFunctions);
		TITLECARDS_TreeTops(path, helperFunctions);
		//MULTITHUMBNAILS_TreeTops(path, helperFunctions);
		//STAGECREDITS_TreeTops(path, helperFunctions);
		
		
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