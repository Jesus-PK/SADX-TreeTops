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
	GeoLists[LevelIDs_SkyDeck * 8 + 1] = MDL_TTLandtable->getlandtable();
	GeoLists[LevelIDs_SkyDeck * 8 + 2] = MDL_TTLandtable->getlandtable();
}


//	Load Deathzones:

void DEATHZONES_TreeTops()
{
	KillingCollisionModelsListList[LevelIDs_SkyDeck][0] = TTDeathzones00;
	KillingCollisionModelsListList[LevelIDs_SkyDeck][1] = TTDeathzones00;
	KillingCollisionModelsListList[LevelIDs_SkyDeck][2] = TTDeathzones01;
}


//	Start Positions:

StartPosition TreeTops00 = { LevelIDs_SkyDeck, 0, { 707.124f, 75.0f, 861.509f }, 0x9500 };
StartPosition TreeTops01 = { LevelIDs_SkyDeck, 1, { 707.124f, 75.0f, 861.509f }, 0x9500 };
StartPosition TreeTops02 = { LevelIDs_SkyDeck, 2, { 707.124f, 75.0f, 861.509f }, 0x9500 };

void STARTPOSITIONS_TreeTops(const HelperFunctions& helperFunctions)
{
	for (unsigned char i = 0; i < Characters_MetalSonic; ++i)
	{
		helperFunctions.RegisterStartPosition(i, TreeTops00);
		helperFunctions.RegisterStartPosition(i, TreeTops01);
		helperFunctions.RegisterStartPosition(i, TreeTops02);
	}
}


//	Paths:

void PATHS_TreeTops(const HelperFunctions& helperFunctions)
{
	helperFunctions.RegisterPathList(PATHDATA_TreeTops00);
	helperFunctions.RegisterPathList(PATHDATA_TreeTops01);
	helperFunctions.RegisterPathList(PATHDATA_TreeTops02);
}


//	File Replacements:

#define ReplaceBIN(a, b) helperFunctions.ReplaceFile("system\\" a ".BIN", "system\\" b ".BIN");

void FILES_TreeTops(const HelperFunctions& helperFunctions)
{
	// SET Replacement:

	ReplaceBIN("SET0600S", "SET_TreeTops-S");
	ReplaceBIN("SET0600M", "SET_TreeTops-M");
	ReplaceBIN("SET0602K", "SET_TreeTops-K");


	// CAM Replacement:

	ReplaceBIN("CAM0600S", "CAM_TreeTops-S");
	ReplaceBIN("CAM0600M", "CAM_TreeTops-M");
	ReplaceBIN("CAM0602K", "CAM_TreeTops-K");


	// OST Replacement:

	helperFunctions.ReplaceFile("system\\sounddata\\bgm\\wma\\skydeck1.wma", "system\\OST_TreeTops.adx");
}


//	Init Level:

void INIT_Level(const HelperFunctions& helperFunctions)
{
	WriteData<5>((void*)0x422D84, 0x90); // Disable DC Conversion Sky Deck
	
	LANDTABLE_TreeTops();
	DEATHZONES_TreeTops();
	STARTPOSITIONS_TreeTops(helperFunctions);
	PATHS_TreeTops(helperFunctions);
	FILES_TreeTops(helperFunctions);
}