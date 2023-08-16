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

NJS_TEXNAME TEX_TTMission[36] = { 0 };

DataPointer(NJS_TEXANIM, MissionSpriteAnim, 0x917784);

FunctionHook<void> MissionCard_Result_t(0x457BB0);
FunctionHook<void> LoadMissionImage_t(0x457450);

//  This function is the one that will check for the current character and Rank you are playing, so they can show the proper MissionCard. It's separated into two functions (HD and SD) that I call via a HD_GUI check. There's also a language check inside each one to show EN or JP cards.
//  GetLevelEmblemCollected checks the SaveData, CurrentChar, Level and the current Mission Rank, it's used on the GetMissionType(0x4575D0) function - Originally I tried using the int results of this function but I wasn't able to get it working as I wanted, so I ended doing my custom one following how the original function was made in IDA.
//  Might be worth looking into why that didn't worked, but tbh I think it's better that I created a custom one since this lets me show a MissionCard when every rank is completed (Vanilla just returns a negative value to not show any card).

static int character;

void HD_MissionTypeCheck(int character)
{
    character = GetPlayerNumber();
    
    if (Language != JAPANESE) // Use an "if it isn't JP" so the EN MissionCards work if other languages are selected.
    {
        switch (CurrentCharacter) // Sets the value to be compared, it's the X in a (if (X == Y)) for example.
        {
            case Characters_Sonic: // Case is to be compared to, it's the Y in a (if (X == Y)) for example. The way this is written also means Sonic and the Default match.
            
                if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 0)) // After A-Rank Completion.
                    MissionSpriteAnim.texid = 0;

                else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 1)) // A-Rank Card.
                    MissionSpriteAnim.texid = 2;

                else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 2)) // B-Rank Card.
                    MissionSpriteAnim.texid = 1;

                else // C-Rank Card.
                    MissionSpriteAnim.texid = 0;

                break;

            case Characters_Tails:

                if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 0))
                    MissionSpriteAnim.texid = 3;

                else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 1))
                    MissionSpriteAnim.texid = 5;

                else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 2))
                    MissionSpriteAnim.texid = 4;

                else
                    MissionSpriteAnim.texid = 3;

                break;

            case Characters_Knuckles:

                if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 0))
                    MissionSpriteAnim.texid = 6;

                else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 1))
                    MissionSpriteAnim.texid = 8;

                else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 2))
                    MissionSpriteAnim.texid = 7;

                else
                    MissionSpriteAnim.texid = 6;

                break;
        }
    }

    else
    {
        switch (CurrentCharacter)
        {
            case Characters_Sonic:
            
                if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 0))
                    MissionSpriteAnim.texid = 9;

                else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 1))
                    MissionSpriteAnim.texid = 11;

                else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 2))
                    MissionSpriteAnim.texid = 10;

                else
                    MissionSpriteAnim.texid = 9;

                break;

            case Characters_Tails:

                if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 0))
                    MissionSpriteAnim.texid = 12;

                else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 1))
                    MissionSpriteAnim.texid = 14;

                else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 2))
                    MissionSpriteAnim.texid = 13;

                else
                    MissionSpriteAnim.texid = 12;

                break;

            case Characters_Knuckles:

                if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 0))
                    MissionSpriteAnim.texid = 15;

                else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 1))
                    MissionSpriteAnim.texid = 17;

                else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 2))
                    MissionSpriteAnim.texid = 16;

                else
                    MissionSpriteAnim.texid = 15;

                break;
        }
    }
}

void SD_MissionTypeCheck(int character)
{
    character = GetPlayerNumber();
    
    if (Language != JAPANESE)
    {
        switch (CurrentCharacter)
        {
            case Characters_Sonic:
            
                if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 0))
                    MissionSpriteAnim.texid = 18;

                else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 1))
                    MissionSpriteAnim.texid = 20;

                else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 2))
                    MissionSpriteAnim.texid = 19;

                else
                    MissionSpriteAnim.texid = 18;

                break;

            case Characters_Tails:

                if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 0))
                    MissionSpriteAnim.texid = 21;

                else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 1))
                    MissionSpriteAnim.texid = 23;

                else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 2))
                    MissionSpriteAnim.texid = 22;

                else
                    MissionSpriteAnim.texid = 21;

                break;

            case Characters_Knuckles:

                if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 0))
                    MissionSpriteAnim.texid = 24;

                else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 1))
                    MissionSpriteAnim.texid = 26;

                else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 2))
                    MissionSpriteAnim.texid = 25;

                else
                    MissionSpriteAnim.texid = 24;

                break;
        }
    }

    else
    {
        switch (CurrentCharacter)
        {
            case Characters_Sonic:
            
                if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 0))
                    MissionSpriteAnim.texid = 27;

                else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 1))
                    MissionSpriteAnim.texid = 29;

                else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 2))
                    MissionSpriteAnim.texid = 28;

                else
                    MissionSpriteAnim.texid = 27;

                break;

            case Characters_Tails:

                if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 0))
                    MissionSpriteAnim.texid = 30;

                else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 1))
                    MissionSpriteAnim.texid = 32;

                else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 2))
                    MissionSpriteAnim.texid = 31;

                else
                    MissionSpriteAnim.texid = 30;

                break;

            case Characters_Knuckles:

                if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 0))
                    MissionSpriteAnim.texid = 33;

                else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 1))
                    MissionSpriteAnim.texid = 35;

                else if (GetLevelEmblemCollected((SaveFileData*)&SaveData, character, LevelIDs_SkyDeck, 2))
                    MissionSpriteAnim.texid = 34;

                else
                    MissionSpriteAnim.texid = 33;

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
        HD_MissionTypeCheck(character);

    else
        SD_MissionTypeCheck(character);

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
        HD_MissionTypeCheck(character);

    else
        SD_MissionTypeCheck(character);

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