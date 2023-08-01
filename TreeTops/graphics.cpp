#include "pch.h"

//	TitleCards:

#define	ReplaceTitleCard(a) do { \
		_snprintf_s(pathbuf, LengthOfArray(pathbuf), "%s\\textures\\TitleCards\\index.txt", path); \
		helperFunctions.ReplaceFile("system\\" a ".PVR", pathbuf); \
} while (0)

#define	ReplaceTitleCard_Wabbit(a) do { \
		_snprintf_s(pathbuf, LengthOfArray(pathbuf), "%s\\textures\\TitleCards_C\\index.txt", path); \
		helperFunctions.ReplaceFile("system\\" a ".PVR", pathbuf); \
} while (0)

void TITLECARDS_TreeTops(const char* path, const HelperFunctions & helperFunctions)
{
	char pathbuf[MAX_PATH];

	ReplaceTitleCard("S_STAGE08");
	ReplaceTitleCard("S_STAGE08_E");
    
	ReplaceTitleCard("K_STAGE05");
	ReplaceTitleCard("K_STAGE05_E");

    if (!Da_Wabbit)
    {
        ReplaceTitleCard("M_STAGE04");
        ReplaceTitleCard("M_STAGE04_E");
    }

    else
    {
        ReplaceTitleCard_Wabbit("M_STAGE04");
        ReplaceTitleCard_Wabbit("M_STAGE04_E");
    }
}


//	Mission Cards:

NJS_TEXNAME TEX_TTMission[6] = { 0 };

DataPointer(NJS_TEXANIM, MissionSpriteAnim, 0x917784);

FunctionHook<void> MissionCard_Result_t(0x457BB0);
FunctionHook<void> LoadMissionImage_t(0x457450);


void MISSIONTYPE_Check()
{
    if (Language != JAPANESE) // Use an "if it isn't JP" so the EN MissionCards work if other languages are selected.
    {
        switch (CurrentCharacter) // Sets the value to be compared, it's the X in a (if (X == Y)) for example.
        {
            case Characters_Sonic: // Case is to be compared to, it's the Y in a (if (X == Y)) for example. The way this is written also means Sonic and the Default match.
            default: // This is where the checks will default to if it doesn't match any existing values. in this case, anyone who isn't Tails or Knuckles would end up here.                
                MissionSpriteAnim.texid = 0;
                break; // Breaks out of the switch case. You can skip having one of these, and it'll mean it falls into the next case to process more code.
            
            case Characters_Tails:                
                MissionSpriteAnim.texid = 1;               
                break;
            
            case Characters_Knuckles:                
                MissionSpriteAnim.texid = 2;               
                break;
        }
    }

    else
    {
        switch (CurrentCharacter)
        {
            case Characters_Sonic:            
            default:                
                MissionSpriteAnim.texid = 3;                
                break;
            
            case Characters_Tails:                
                MissionSpriteAnim.texid = 4;                
                break;
            
            case Characters_Knuckles:                
                MissionSpriteAnim.texid = 5;               
                break;
        }
    }
}

void MissionCard_Result_r()
{
    if (CurrentLevel != LevelIDs_SkyDeck)
    {
        MissionSpriteAnim.texid = 0;
        
        return MissionCard_Result_t.Original();
    }

    StageMissionTexlist.textures = TEX_TTMission;
    StageMissionTexlist.nbTexture = 1;
    
    LoadPVM("TreeTops_MissionCards", &StageMissionTexlist);
    MISSIONTYPE_Check();

    task* tp = CreateElementalTask(LoadObj_Data1, 6, (TaskFuncPtr)0x457B60);
    
    tp->twp->mode = 0;
    tp->twp->counter.b[1] = GetPlayerNumber();
    tp->twp->wtimer = (MissedFrames_B * 72);
    tp->twp->pos.x = 320.0f;
    tp->twp->pos.y = 240.0f;
    
    tp->dest = (TaskFuncPtr)FreeStageMissionImage;
}

void LoadMissionImage_r()
{
    if (CurrentLevel != LevelIDs_SkyDeck)
    {
        MissionSpriteAnim.texid = 0;
        
        return LoadMissionImage_t.Original();
    }

    StageMissionTexlist.textures = TEX_TTMission;
    StageMissionTexlist.nbTexture = 1;
    
    LoadPVM("TreeTops_MissionCards", &StageMissionTexlist);
    MISSIONTYPE_Check();

    task* task = CreateElementalTask(LoadObj_Data1, 6, (TaskFuncPtr)0x457B60);
    
    task->twp->mode = 0;
    task->twp->counter.b[1] = GetPlayerNumber();
    task->twp->wtimer = 120;
    task->twp->pos.x = 320.0f;
    task->twp->pos.y = 360.0f;
    
    task->dest = (TaskFuncPtr)FreeStageMissionImage;
}

void MISSIONCARDS_TreeTops()
{
    MissionCard_Result_t.Hook(MissionCard_Result_r);
    LoadMissionImage_t.Hook(LoadMissionImage_r);
}