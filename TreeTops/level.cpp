#include "pch.h"
#include "deathzones.h"
#include "paths.h"

//	Counters:

bool HasKey = 0;
uint8_t DragonCount{ 0 };


//	Custom FogData, DrawDistance and SkyboxDrawDistance values - Due to creating a custom LevelOBJ, it's necessary to setup these values via ___stcFog / ___stcClip.

___stcFog FOGDATA_TreeTops[] = {
	{ 100.0f, 1000.0f, 0xFFFFFF, 0 },
	{ 100.0f, 1000.0f, 0xFFFFFF, 0 },
	{ 100.0f, 1000.0f, 0xFFFFFF, 0 }
};

___stcClip DRAWDISTANCE_TreeTops[] = {
	{ -1.0f, -8000.0f },
	{ -1.0f, -8000.0f },
	{ -1.0f, -8000.0f }
};

___stcClip SKYBOXDRAWDISTANCE_TreeTops[] = {
	{ -1.0f, -10000.0f },
	{ -1.0f, -10000.0f },
	{ -1.0f, -10000.0f }
};

void SETVIEWDATA_TreeTops()
{
	gFog = FOGDATA_TreeTops[ssActNumber];
	gClipMap = DRAWDISTANCE_TreeTops[ClipLevel];
	gClipSky = SKYBOXDRAWDISTANCE_TreeTops[ClipLevel];
}


//	Load Landtable:

LandTableInfo* MDL_TTLandtable = nullptr;

void LANDTABLE_TreeTops()
{
	LoadLandTable(&MDL_TTLandtable, "TreeTops_Landtable", HelperFunctionsGlobal, &TEXLIST_TreeTops);

	GeoLists[LevelIDs_SkyDeck * 8] = MDL_TTLandtable->getlandtable();
	GeoLists[LevelIDs_SkyDeck * 8 + 2] = MDL_TTLandtable->getlandtable();
}


//	Load Deathzones:

void DEATHZONES_TreeTops()
{
	KillingCollisionModelsListList[LevelIDs_SkyDeck][0] = TTDeathzones00;
	KillingCollisionModelsListList[LevelIDs_SkyDeck][2] = TTDeathzones01;
}


//	Start Positions:

StartPosition TreeTops00 = { LevelIDs_SkyDeck, 0, { 707.124f, 75.0f, 861.509f }, 0x9500 };
StartPosition TreeTops01 = { LevelIDs_SkyDeck, 2, { 707.124f, 75.0f, 861.509f }, 0x9500 };

void STARTPOSITIONS_TreeTops(const HelperFunctions& helperFunctions)
{
	for (unsigned char i = 0; i < Characters_MetalSonic; ++i)
	{
		helperFunctions.RegisterStartPosition(i, TreeTops00);
		helperFunctions.RegisterStartPosition(i, TreeTops01);
	}
}


//	Paths:

void PATHS_TreeTops(const HelperFunctions& helperFunctions)
{
	helperFunctions.RegisterPathList(PATHDATA_TreeTops00);
	helperFunctions.RegisterPathList(PATHDATA_TreeTops01);
}


//	File Replacements:

#define ReplaceBIN(a, b) helperFunctions.ReplaceFile("system\\" a ".BIN", "system\\" b ".BIN");

void FILES_TreeTops(const HelperFunctions& helperFunctions)
{
	// SET Replacement:

	ReplaceBIN("SET0600S", "SET_TreeTopsS");
	ReplaceBIN("SET0600M", "SET_TreeTopsM");
	ReplaceBIN("SET0602K", "SET_TreeTopsK");


	// CAM Replacement:

	ReplaceBIN("CAM0600S", "CAM_TreeTopsS");
	ReplaceBIN("CAM0600M", "CAM_TreeTopsM");
	ReplaceBIN("CAM0602K", "CAM_TreeTopsK");


	// OST Replacement:

	helperFunctions.ReplaceFile("system\\sounddata\\bgm\\wma\\skydeck1.wma", "system\\OST_TreeTops.adx");
}


//	Rank Requirements:

FunctionHook<bool, int, int, int> CheckMissionRequirements_t(0x426AA0);

bool CheckMissionRequirements_r(int a1, int a2, int a3)
{
	if (CurrentLevel != LevelIDs_SkyDeck)
    {
        return CheckMissionRequirements_t.Original(a1, a2, a3);
    }

	a3 = GetPlayerNumber();
	
	switch (CurrentCharacter)
	{
		case Characters_Sonic:

			if (GetLevelEmblemCollected((SaveFileData*)&SaveData, a3, LevelIDs_SkyDeck, 0)) // After A-Rank Completion.
				return 1;

			else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, a3, LevelIDs_SkyDeck, 1))
			{
				if (Rings >= 20)
					return 1;

				else
					return 0;
			}

			else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, a3, LevelIDs_SkyDeck, 2))
			{
				if (Rings >= 5)
					return 1;

				else
					return 0;
			}

			else
				return 1;

			break;

		case Characters_Tails:

			if (GetLevelEmblemCollected((SaveFileData*)&SaveData, a3, LevelIDs_SkyDeck, 0))
				return 1;

			else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, a3, LevelIDs_SkyDeck, 1))
			{
				if (Rings >= 25)
					return 1;

				else
					return 0;
			}

			else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, a3, LevelIDs_SkyDeck, 2))
			{
				if (Rings >= 10)
					return 1;

				else
					return 0;
			}

			else
				return 1;

			break;

		case Characters_Knuckles:

			if (GetLevelEmblemCollected((SaveFileData*)&SaveData, a3, LevelIDs_SkyDeck, 0))
				return 1;

			else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, a3, LevelIDs_SkyDeck, 1))
			{
				if (Rings >= 30)
					return 1;

				else
					return 0;
			}

			else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, a3, LevelIDs_SkyDeck, 2))
			{
				if (Rings >= 15)
					return 1;

				else
					return 0;
			}

			else
				return 1;

			break;
	}
}

void Ranks()
{
	CheckMissionRequirements_t.Hook(CheckMissionRequirements_r);
}