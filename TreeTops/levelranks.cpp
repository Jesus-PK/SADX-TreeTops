#include "pch.h"

//	Mission Cards:

NJS_TEXNAME TEX_TTMission[36] = { 0 };

DataPointer(NJS_TEXANIM, MissionSpriteAnim, 0x917784);

FunctionHook<void> LoadStageMissionImage_t(0x457450);
FunctionHook<void> LoadMissionCardResult_t(0x457BB0);

//  Basically on this function I made, I check the result value of the game's GetMissionType function with int missionType to know which mission card the game is gonna use. Just like the game does it.
//  By doing this, I can set up the TexID of my custom .PVMX accordingly - So for example value 47 of GetMissionType is Sonic's A-Rank card for Sky Deck. If my functions detects that value, it will set up MissionSpriteAnim.texid to use the TexID 2 of my .PVMX (which is my custom A-Rank card texture)
//  To further optimize the function, instead of doing the main language check and then the switch (one per language); I used a ternary operator in each MissionSpriteAnim.texid instance which will check for the current language and in the case of the current language NOT being Japanese, it will setup the English card TexID and if the current language IS Japanese, it will setup the Japanese card TexID - This saved me a lot of unnecesarily repeating code.
//  The main difference between this method and the previous manual one I was doing with GetLevelEmblemCollected, is that this one is now fully compatible with Metal Sonic and overall it's just better since it's pretty much how the game does it to decide which TexID to use from the hardcoded texlist of the vanilla mission cards PVRs

void HD_GetMissionTypeCheck()
{
	int character = GetPlayerNumber();
	int level = ((__int16)ssActNumber | (ssStageNumber << 8)) >> 8;
	int missionType = GetMissionType(character, level); // With this, the value of missionType will be the result value of the GetMissionType function. This will let me check if a certain value is being used.

    switch (CurrentCharacter)
    {
	    case Characters_Sonic:

            if (missionType == 47) // Rank A Card
                MissionSpriteAnim.texid = (Language != JAPANESE) ? 2 : 11; // if Language isn't Japanese, return TexID 2 (EN Card) : else, return TexID 11 (JP Card)

            else if (missionType == 1) // Rank B Card
                MissionSpriteAnim.texid = (Language != JAPANESE) ? 1 : 10;

            else // Rank C Card - LevelClear
                MissionSpriteAnim.texid = (Language != JAPANESE) ? 0 : 9;

            break;

        case Characters_Tails:

            if (missionType == 5)
                MissionSpriteAnim.texid = (Language != JAPANESE) ? 5 : 14;

            else if (missionType == 4)
                MissionSpriteAnim.texid = (Language != JAPANESE) ? 4 : 13;

            else
                MissionSpriteAnim.texid = (Language != JAPANESE) ? 3 : 12;

            break;

        case Characters_Knuckles:

            if (missionType == 48)
                MissionSpriteAnim.texid = (Language != JAPANESE) ? 8 : 17;

            else if (missionType == 7)
                MissionSpriteAnim.texid = (Language != JAPANESE) ? 7 : 16;

            else
                MissionSpriteAnim.texid = (Language != JAPANESE) ? 6 : 15;

            break;

        default:               
            MissionSpriteAnim.texid = (Language != JAPANESE) ? 0 : 9;
            break;
	}
}

void SD_GetMissionTypeCheck()
{
	int character = GetPlayerNumber();
	int level = ((__int16)ssActNumber | (ssStageNumber << 8)) >> 8;
	int missionType = GetMissionType(character, level);

    switch (CurrentCharacter)
    {
	    case Characters_Sonic:

            if (missionType == 47) // Rank A Card
                MissionSpriteAnim.texid = (Language != JAPANESE) ? 20 : 29;

            else if (missionType == 1) // Rank B Card
                MissionSpriteAnim.texid = (Language != JAPANESE) ? 19 : 28;

            else // Rank C Card - LevelClear
                MissionSpriteAnim.texid = (Language != JAPANESE) ? 18 : 27;

            break;

        case Characters_Tails:

            if (missionType == 5)
                MissionSpriteAnim.texid = (Language != JAPANESE) ? 23 : 32;

            else if (missionType == 4)
                MissionSpriteAnim.texid = (Language != JAPANESE) ? 22 : 31;

            else
                MissionSpriteAnim.texid = (Language != JAPANESE) ? 21 : 30;

            break;

        case Characters_Knuckles:

            if (missionType == 48)
                MissionSpriteAnim.texid = (Language != JAPANESE) ? 26 : 35;

            else if (missionType == 7)
                MissionSpriteAnim.texid = (Language != JAPANESE) ? 25 : 34;

            else
                MissionSpriteAnim.texid = (Language != JAPANESE) ? 24 : 33;

            break;

        default:               
            MissionSpriteAnim.texid = (Language != JAPANESE) ? 18 : 27;
            break;
	}
}

void LoadStageMissionImage_r()
{
    if (CurrentLevel != LevelIDs_SkyDeck)
    {
        MissionSpriteAnim.texid = 0;
        return LoadStageMissionImage_t.Original();
    }

    StageMissionTexlist.textures = TEX_TTMission;
    StageMissionTexlist.nbTexture = 1;
    
    LoadPVM("TreeTops_MissionCards", &StageMissionTexlist);
    
    if (HD_GUI)
        HD_GetMissionTypeCheck();

    else
        SD_GetMissionTypeCheck();

    task* task = CreateElementalTask(LoadObj_Data1, 6, (TaskFuncPtr)0x457B60);
    
    task->twp->mode = 0;
    task->twp->counter.b[1] = GetPlayerNumber();
    task->twp->wtimer = 120;
    task->twp->pos.x = 320.0f;
    task->twp->pos.y = 360.0f;
    
    task->dest = (TaskFuncPtr)FreeStageMissionImage;
}

void LoadMissionCardResult_r()
{
    if (CurrentLevel != LevelIDs_SkyDeck)
    {
        MissionSpriteAnim.texid = 0;
        return LoadMissionCardResult_t.Original();
    }

    StageMissionTexlist.textures = TEX_TTMission;
    StageMissionTexlist.nbTexture = 1;
    
    LoadPVM("TreeTops_MissionCards", &StageMissionTexlist);
    
    if (HD_GUI)
        HD_GetMissionTypeCheck();

    else
        SD_GetMissionTypeCheck();

    task* tp = CreateElementalTask(LoadObj_Data1, 6, (TaskFuncPtr)0x457B60);
    
    tp->twp->mode = 0;
    tp->twp->counter.b[1] = GetPlayerNumber();
    tp->twp->wtimer = (MissedFrames_B * 72);
    tp->twp->pos.x = 320.0f;
    tp->twp->pos.y = 240.0f;
    
    tp->dest = (TaskFuncPtr)FreeStageMissionImage;
}

void MISSIONCARDS_TreeTops()
{
    LoadStageMissionImage_t.Hook(LoadStageMissionImage_r);
    LoadMissionCardResult_t.Hook(LoadMissionCardResult_r);
}


//  Level Ranks:

UsercallFunc(BOOL, CheckMissionRequirements_t, (int mission, int character, int level), (mission, character, level), 0x426AA0, rAL, rEAX, rEDX, rECX);

//  This is a more "faithful" decompilation of the CheckMissionRequirements function. Now instead of the "v3 / missionBool" calculation to check for a particular rank, it just boils down to a simple switch statement that will check for the current mission value (LevelClear and A-Rank = 0 / B-Rank = 1 / C-Rank = 2) - Fully compatible with Metal Sonic ranks.
//  Worth nothing: For C-Rank I opted to call it as the default case of the switch rather than case 2, doing this fixed a "Not all control paths return a value" compiler warning.

BOOL CheckMissionRequirements_r(int mission, int character, int level)
{
    if (CurrentLevel != LevelIDs_SkyDeck)
        return CheckMissionRequirements_t.Original(mission, character, level);

    switch (mission)
    {
        case 0: // Rank A - LevelClear
        {
            int time = TimeFrames + 60 * (TimeSeconds + 60 * TimeMinutes); // Due to declaring the "int time" inside the switch case, curly braces are needed at case 0 with braces due to the "Initialization of 'time' is skipped by 'case' label" error.
            switch (character)
            {
                case Characters_Sonic:
                    return (Rings >= 1 && time < 180) ? 1 : 0;
                    break;

                case Characters_Tails:
                    return (time < 240) ? 1 : 0;
                    break;

                case Characters_Knuckles:
                    return (time < 300) ? 1 : 0;
                    break;

                default:
                    return 1;
                    break;
            }
            break;
        }
        case 1: // Rank B
            return (Rings >= 5) ? 1 : 0;
            break;

        default: // Rank C
            return 1;
            break;
    }
}

void INIT_LevelRanks()
{
    CheckMissionRequirements_t.Hook(CheckMissionRequirements_r);
}