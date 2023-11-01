#include "pch.h"
#include "deathzones.h"
#include "paths.h"

//	Custom FogData, DrawDistance and SkyboxDrawDistance values - Due to creating a custom level task, it's necessary to setup these values via ___stcFog / ___stcClip:

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
	LoadLandTable(&MDL_TTLandtable, "Landtable_TreeTops", HelperFunctionsGlobal, &TEXLIST_TreeTops);

	GeoLists[LevelIDs_SkyDeck * 8] = MDL_TTLandtable->getlandtable();
	GeoLists[LevelIDs_SkyDeck * 8 + 1] = MDL_TTLandtable->getlandtable();
	GeoLists[LevelIDs_SkyDeck * 8 + 2] = MDL_TTLandtable->getlandtable();
}


//	Load Deathzones:

void DEATHZONES_TreeTops()
{
	KillingCollisionModelsListList[LevelIDs_SkyDeck][0] = DEATHZONES_TreeTops00;
	KillingCollisionModelsListList[LevelIDs_SkyDeck][1] = DEATHZONES_TreeTops00;
	KillingCollisionModelsListList[LevelIDs_SkyDeck][2] = DEATHZONES_TreeTops01;
}


//	Start Positions:

StartPosition STARTPOS_TreeTops00 = { LevelIDs_SkyDeck, 0, { 707.124f, 75.0f, 861.509f }, 0x9500 };
StartPosition STARTPOS_TreeTops01 = { LevelIDs_SkyDeck, 1, { 707.124f, 75.0f, 861.509f }, 0x9500 };
StartPosition STARTPOS_TreeTops02 = { LevelIDs_SkyDeck, 2, { 707.124f, 75.0f, 861.509f }, 0x9500 };

void STARTPOSITIONS_TreeTops()
{
	for (unsigned char i = 0; i < Characters_MetalSonic; ++i)
	{
		HelperFunctionsGlobal.RegisterStartPosition(i, STARTPOS_TreeTops00);
		HelperFunctionsGlobal.RegisterStartPosition(i, STARTPOS_TreeTops01);
		HelperFunctionsGlobal.RegisterStartPosition(i, STARTPOS_TreeTops02);
	}
}


//	Paths:

void PATHS_TreeTops()
{
	HelperFunctionsGlobal.RegisterPathList(PATHDATA_TreeTops00);
	HelperFunctionsGlobal.RegisterPathList(PATHDATA_TreeTops01);
	HelperFunctionsGlobal.RegisterPathList(PATHDATA_TreeTops02);
}


//	File Replacements:

void FILES_TreeTops()
{
	// SET Replacement:

	ReplaceBIN("SET0600S", "SET_TreeTops-S"); // Target
	ReplaceBIN("SET0601S", "SET_TreeTops-S");
	ReplaceBIN("SET0602S", "SET_TreeTops-S");

	ReplaceBIN("SET0600M", "SET_TreeTops-M"); // Target
	ReplaceBIN("SET0601M", "SET_TreeTops-M");
	ReplaceBIN("SET0602M", "SET_TreeTops-M");

	ReplaceBIN("SET0600K", "SET_TreeTops-K");
	ReplaceBIN("SET0601K", "SET_TreeTops-K");
	ReplaceBIN("SET0602K", "SET_TreeTops-K"); // Target


	// CAM Replacement:

	ReplaceBIN("CAM0600S", "CAM_TreeTops-S"); // Target
	ReplaceBIN("CAM0601S", "CAM_TreeTops-S");
	ReplaceBIN("CAM0602S", "CAM_TreeTops-S");

	ReplaceBIN("CAM0600M", "CAM_TreeTops-M"); // Target
	ReplaceBIN("CAM0601M", "CAM_TreeTops-M");
	ReplaceBIN("CAM0602M", "CAM_TreeTops-M");

	ReplaceBIN("CAM0600K", "CAM_TreeTops-K");
	ReplaceBIN("CAM0601K", "CAM_TreeTops-K");
	ReplaceBIN("CAM0602K", "CAM_TreeTops-K"); // Target


	//	PL Replacement:

	ReplaceBIN("PL_60B", "PL_TreeTops");
	ReplaceBIN("PL_61B", "PL_TreeTops");
	
	ReplaceBIN("SL_60B", "SL_TreeTops");


	// OST Replacement:

	HelperFunctionsGlobal.ReplaceFile("system\\sounddata\\bgm\\wma\\skydeck1.wma", "system\\OST_TreeTops.adx");
}


//	Init Level:

void INIT_Level()
{
	WriteData<5>((void*)0x422D84, 0x90); // Disable DC Conversion Sky Deck
	
	LANDTABLE_TreeTops();
	DEATHZONES_TreeTops();
	STARTPOSITIONS_TreeTops();
	PATHS_TreeTops();
	FILES_TreeTops();
}