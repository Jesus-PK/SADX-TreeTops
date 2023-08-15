#include "pch.h"

//  Macros:

#define ReplaceTex(pvm, pvr, folder, pngname, gbix, x, y) helperFunctions.ReplaceTexture(pvm, pvr, (std::string(path) + "\\textures\\" folder "\\" pngname ".png").c_str(), gbix, x, y);
#define ReplacePVR(a, b) helperFunctions.ReplaceFile("system\\" a ".PVR", b);


//  Stage Names:

void STAGENAMES_TreeTops(const char* path, const HelperFunctions& helperFunctions)
{
    if (HD_GUI)
    {
        ReplaceTex("AVA_STNAM", "TX_ST11", "StageNames", "HD_SpeedTree", 365041, 128, 16);
        ReplaceTex("AVA_STNAM_E", "TX_ST11_e", "StageNames", "HD_TreeTops", 10000419, 128, 16);
    }
    
    else
    {
        ReplaceTex("AVA_STNAM", "TX_ST11", "StageNames", "SD_SpeedTree", 365041, 128, 16);
        ReplaceTex("AVA_STNAM_E", "TX_ST11_e", "StageNames", "SD_TreeTops", 10000419, 128, 16);
    }
}


//  TitleCards:

void TITLECARDS_TreeTops(const char* path, const HelperFunctions& helperFunctions)
{
    std::string index = path;
    std::string index_cream = path;

    if (HD_GUI)
    {
        index += "\\textures\\TitleCards_HD\\index.txt";
        const char* HD_Index = index.c_str();

        ReplacePVR("S_STAGE08", HD_Index);
        ReplacePVR("S_STAGE08_E", HD_Index);
        ReplacePVR("K_STAGE05", HD_Index);
        ReplacePVR("K_STAGE05_E", HD_Index);

        if (SA1_Cream)
        {
            index_cream += "\\textures\\TitleCards_HD\\Cream_HD\\index.txt";
            const char* CreamHD_Index = index_cream.c_str();

            ReplacePVR("M_STAGE04", CreamHD_Index);
            ReplacePVR("M_STAGE04_E", CreamHD_Index);
        }

        else
        {
            ReplacePVR("M_STAGE04", HD_Index);
            ReplacePVR("M_STAGE04_E", HD_Index);
        }
    }

    else
    {
        index += "\\textures\\TitleCards_SD\\index.txt";
        const char* SD_Index = index.c_str();

        ReplacePVR("S_STAGE08", SD_Index);
        ReplacePVR("S_STAGE08_E", SD_Index);
        ReplacePVR("K_STAGE05", SD_Index);
        ReplacePVR("K_STAGE05_E", SD_Index);

        ReplacePVR("S_STAGE08_DC", SD_Index);
        ReplacePVR("S_STAGE08_E_DC", SD_Index);
        ReplacePVR("K_STAGE05_DC", SD_Index);
        ReplacePVR("K_STAGE05_E_DC", SD_Index);

        if (SA1_Cream)
        {
            index_cream += "\\textures\\TitleCards_SD\\Cream_SD\\index.txt";
            const char* CreamSD_Index = index_cream.c_str();

            ReplacePVR("M_STAGE04", CreamSD_Index);
            ReplacePVR("M_STAGE04_E", CreamSD_Index);

            ReplacePVR("M_STAGE04_DC", CreamSD_Index);
            ReplacePVR("M_STAGE04_E_DC", CreamSD_Index);
        }

        else
        {
            ReplacePVR("M_STAGE04", SD_Index);
            ReplacePVR("M_STAGE04_E", SD_Index);

            ReplacePVR("M_STAGE04_DC", SD_Index);
            ReplacePVR("M_STAGE04_E_DC", SD_Index);
        }
    }
}


//  Multiplayer Thumbnails:

void MULTITHUMBNAILS_TreeTops(const char* path, const HelperFunctions& helperFunctions)
{
	ReplaceTex("AVA_MULTI", "multistg0600", "MultiThumbnails", "Multi_HillTopS", 54926007, 128, 72);
	ReplaceTex("AVA_MULTI", "multistg0602", "MultiThumbnails", "Multi_HillTopK", 71757015, 128, 72);
}


//  Stage Credits:

void STAGECREDITS_TreeTops(const char* path, const HelperFunctions& helperFunctions)
{
    if (HD_GUI)
    {
        ReplaceTex("ENDBG_SUPERSONIC_0_HD", "ss_ev006", "StageCredits", "HD_TreeTops-S00", 366154, 256, 256);
        ReplaceTex("ENDBG_SUPERSONIC_0_HD", "ss_ev007", "StageCredits", "HD_TreeTops-S01", 366155, 256, 256);
        ReplaceTex("ENDBG_TAILS_1_HD", "t_ev015", "StageCredits", "HD_TreeTops-T00", 366141, 256, 256);
        ReplaceTex("ENDBG_KNUCKLES_2_HD", "k_ev021", "StageCredits", "HD_TreeTops-K00", 366070, 256, 256);
        ReplaceTex("ENDBG_KNUCKLES_2_HD", "k_ev022", "StageCredits", "HD_TreeTops-K01", 366071, 256, 256);
    }

    else if (DC_Conversion)
    {
        ReplaceTex("ENDBG_SUPERSONIC_0_HD", "ss_ev006", "StageCredits", "DC_TreeTops-S00", 366154, 256, 256);
        ReplaceTex("ENDBG_SUPERSONIC_0_HD", "ss_ev007", "StageCredits", "DC_TreeTops-S01", 366155, 256, 256);
        ReplaceTex("ENDBG_TAILS_1_HD", "t_ev015", "StageCredits", "DC_TreeTops-T00", 366141, 256, 256);
        ReplaceTex("ENDBG_KNUCKLES_2_HD", "k_ev021", "StageCredits", "DC_TreeTops-K00", 366070, 256, 256);
        ReplaceTex("ENDBG_KNUCKLES_2_HD", "k_ev022", "StageCredits", "DC_TreeTops-K01", 366071, 256, 256);
    }

    else
    {
        ReplaceTex("ENDBG_SONIC_2", "sonic_22", "StageCredits", "DX_TreeTops-S00", 366021, 512, 512);
        ReplaceTex("ENDBG_TAILS_1", "tails_19", "StageCredits", "DX_TreeTops-T00", 366145, 512, 512);
        ReplaceTex("ENDBG_KNUCKLES_2", "knuckles_24", "StageCredits", "DX_TreeTops-K00", 366073, 512, 512);
    }
}


//	Mission Cards:

NJS_TEXNAME TEX_TTMission[12] = { 0 };

DataPointer(NJS_TEXANIM, MissionSpriteAnim, 0x917784);

FunctionHook<void> MissionCard_Result_t(0x457BB0);
FunctionHook<void> LoadMissionImage_t(0x457450);


void HD_MissionTypeCheck()
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

void SD_MissionTypeCheck()
{
    if (Language != JAPANESE)
    {
        switch (CurrentCharacter)
        {
            case Characters_Sonic:
            default:                
                MissionSpriteAnim.texid = 6;
                break;
            
            case Characters_Tails:                
                MissionSpriteAnim.texid = 7;               
                break;
            
            case Characters_Knuckles:                
                MissionSpriteAnim.texid = 8;               
                break;
        }
    }

    else
    {
        switch (CurrentCharacter)
        {
            case Characters_Sonic:            
            default:                
                MissionSpriteAnim.texid = 9;                
                break;
            
            case Characters_Tails:                
                MissionSpriteAnim.texid = 10;                
                break;
            
            case Characters_Knuckles:                
                MissionSpriteAnim.texid = 11;               
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
    
    if (HD_GUI)
        HD_MissionTypeCheck();

    else
        SD_MissionTypeCheck();

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
    
    if (HD_GUI)
        HD_MissionTypeCheck();

    else
        SD_MissionTypeCheck();

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