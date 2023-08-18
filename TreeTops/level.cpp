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


//	Level Ranks:

UsercallFunc(_BOOL1, CheckMissionRequirements_t, (int mission, int character, int level), (mission, character, level), 0x426AA0, rAL, rEAX, rEDX, rECX);

_BOOL1 CheckMissionRequirements_r(int mission, int character, int level)
{
	if (CurrentLevel != LevelIDs_SkyDeck)
		return CheckMissionRequirements_t.Original(mission, character, level);
    
	int time;
	time = TimeFrames + 60 * (TimeSeconds + 60 * TimeMinutes);

	switch (CurrentCharacter)
	{
		case Characters_Sonic:

			if (GetLevelEmblemCollected((SaveFileData*)&SaveData, Characters_Sonic, LevelIDs_SkyDeck, 1)) // Rank A
				return Rings >= 250 && time < 10800 ? 1 : 0; //	Finish in less than 3 minutes while having at least 250 rings.

			else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, Characters_Sonic, LevelIDs_SkyDeck, 2)) // Rank B
				return Rings >= 250 ? 1 : 0; // if Rings >= 250 -> return 1 : else return 0

			else // Rank C
				return 1;

			break;

		case Characters_Tails:

			if (GetLevelEmblemCollected((SaveFileData*)&SaveData, Characters_Tails, LevelIDs_SkyDeck, 1)) // Rank A
				return time < 3600 ? 1 : 0; // Finish in less than 1 minute.

			else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, Characters_Tails, LevelIDs_SkyDeck, 2)) // Rank B
				return Rings >= 250 ? 1 : 0; // Have at least 250 rings.

			else // Rank C
				return 1;

			break;

		case Characters_Knuckles:

			if (GetLevelEmblemCollected((SaveFileData*)&SaveData, Characters_Knuckles, LevelIDs_SkyDeck, 1)) // Rank A
				return time < 7200 ? 1 : 0; // Finish in less than 2 minutes.

			else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, Characters_Knuckles, LevelIDs_SkyDeck, 2)) // Rank B
				return Rings >= 250 ? 1 : 0; // Have at least 250 rings.

			else // Rank C
				return 1;

			break;
	}
}

void INIT_LevelRanks()
{
    CheckMissionRequirements_t.Hook(CheckMissionRequirements_r);
}