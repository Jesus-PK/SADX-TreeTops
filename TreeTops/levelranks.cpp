#include "pch.h"

//	Mission Cards:

NJS_TEXNAME TEX_TTMission[36] = { 0 };

DataPointer(NJS_TEXANIM, MissionSpriteAnim, 0x917784);

FunctionHook<void> LoadStageMissionImage_t(0x457450);
FunctionHook<void> MissionCard_Result_t(0x457BB0);

void HD_GetMissionTypeCheck()
{
	int character;
	int level;
	int missionType;

	character = GetPlayerNumber();
	level = ((__int16)ssActNumber | (ssStageNumber << 8)) >> 8;
	missionType = GetMissionType(character, level);

	if (Language != JAPANESE)
	{
		switch (CurrentCharacter)
		{
			case Characters_Sonic: // Case is to be compared to, it's the Y in a (if (X == Y)) for example. The way this is written also means Sonic and the Default match.
            
                if (missionType == 0) // Level Clear Card.
                    MissionSpriteAnim.texid = 0;

                else if (missionType == 47) // A-Rank Card.
                    MissionSpriteAnim.texid = 2;

                else if (missionType == 1) // B-Rank Card.
                    MissionSpriteAnim.texid = 1;

                else // C-Rank Card.
                    MissionSpriteAnim.texid = 0;

                break;

            case Characters_Tails:

                if (missionType == 3)
                    MissionSpriteAnim.texid = 3;

                else if (missionType == 5)
                    MissionSpriteAnim.texid = 5;

                else if (missionType == 4)
                    MissionSpriteAnim.texid = 4;

                else
                    MissionSpriteAnim.texid = 3;

                break;

            case Characters_Knuckles:

                if (missionType == 6)
                    MissionSpriteAnim.texid = 6;

                else if (missionType == 48)
                    MissionSpriteAnim.texid = 8;

                else if (missionType == 7)
                    MissionSpriteAnim.texid = 7;

                else
                    MissionSpriteAnim.texid = 6;

                break;

            default:
                
                MissionSpriteAnim.texid = 0;
                
                break;
		}
	}

    else
    {
        switch (CurrentCharacter)
		{
			case Characters_Sonic:
            
                if (missionType == 0)
                    MissionSpriteAnim.texid = 9;

                else if (missionType == 47)
                    MissionSpriteAnim.texid = 11;

                else if (missionType == 1)
                    MissionSpriteAnim.texid = 10;

                else
                    MissionSpriteAnim.texid = 9;

                break;

            case Characters_Tails:

                if (missionType == 3)
                    MissionSpriteAnim.texid = 12;

                else if (missionType == 5)
                    MissionSpriteAnim.texid = 14;

                else if (missionType == 4)
                    MissionSpriteAnim.texid = 13;

                else
                    MissionSpriteAnim.texid = 12;

                break;

            case Characters_Knuckles:

                if (missionType == 6)
                    MissionSpriteAnim.texid = 15;

                else if (missionType == 48)
                    MissionSpriteAnim.texid = 17;

                else if (missionType == 7)
                    MissionSpriteAnim.texid = 16;

                else
                    MissionSpriteAnim.texid = 15;

                break;

            default:
                
                MissionSpriteAnim.texid = 9;
                
                break;
		}
    }
}

void SD_GetMissionTypeCheck()
{
	int character;
	int level;
	int missionType;

	character = GetPlayerNumber();
	level = ((__int16)ssActNumber | (ssStageNumber << 8)) >> 8;
	missionType = GetMissionType(character, level);

	if (Language != JAPANESE)
	{
		switch (CurrentCharacter)
		{
			case Characters_Sonic:
            
                if (missionType == 0)
                    MissionSpriteAnim.texid = 18;

                else if (missionType == 47)
                    MissionSpriteAnim.texid = 20;

                else if (missionType == 1)
                    MissionSpriteAnim.texid = 19;

                else
                    MissionSpriteAnim.texid = 18;

                break;

            case Characters_Tails:

                if (missionType == 3)
                    MissionSpriteAnim.texid = 21;

                else if (missionType == 5)
                    MissionSpriteAnim.texid = 23;

                else if (missionType == 4)
                    MissionSpriteAnim.texid = 22;

                else
                    MissionSpriteAnim.texid = 21;

                break;

            case Characters_Knuckles:

                if (missionType == 6)
                    MissionSpriteAnim.texid = 24;

                else if (missionType == 48)
                    MissionSpriteAnim.texid = 26;

                else if (missionType == 7)
                    MissionSpriteAnim.texid = 25;

                else
                    MissionSpriteAnim.texid = 24;

                break;

            default:
                
                MissionSpriteAnim.texid = 18;
                
                break;
		}
	}

    else
    {
        switch (CurrentCharacter)
		{
			case Characters_Sonic:
            
                if (missionType == 0)
                    MissionSpriteAnim.texid = 27;

                else if (missionType == 47)
                    MissionSpriteAnim.texid = 29;

                else if (missionType == 1)
                    MissionSpriteAnim.texid = 28;

                else
                    MissionSpriteAnim.texid = 27;

                break;

            case Characters_Tails:

                if (missionType == 3)
                    MissionSpriteAnim.texid = 30;

                else if (missionType == 5)
                    MissionSpriteAnim.texid = 32;

                else if (missionType == 4)
                    MissionSpriteAnim.texid = 31;

                else
                    MissionSpriteAnim.texid = 30;

                break;

            case Characters_Knuckles:

                if (missionType == 6)
                    MissionSpriteAnim.texid = 33;

                else if (missionType == 48)
                    MissionSpriteAnim.texid = 35;

                else if (missionType == 7)
                    MissionSpriteAnim.texid = 34;

                else
                    MissionSpriteAnim.texid = 33;

                break;

            default:
                
                MissionSpriteAnim.texid = 27;
                
                break;
		}
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
    MissionCard_Result_t.Hook(MissionCard_Result_r);
}


//  Level Ranks:

UsercallFunc(_BOOL1, CheckMissionRequirements_t, (int mission, int character, int level), (mission, character, level), 0x426AA0, rAL, rEAX, rEDX, rECX);

_BOOL1 CheckMissionRequirements_r(int mission, int character, int level)
{
    if (CurrentLevel != LevelIDs_SkyDeck)
        return CheckMissionRequirements_t.Original(mission, character, level);

    int missionBool;
    int time;

    if (mission)
    {
        missionBool = mission - 1;

        if (missionBool)
            return missionBool == 1;

        else
            return Rings >= 5 ? 1 : 0;
    }

    else
    {
        time = TimeFrames + 60 * (TimeSeconds + 60 * TimeMinutes);

        switch (character)
        {
            case Characters_Sonic:
                return Rings >= 1 && time < 180 ? 1 : 0;
                break;

            case Characters_Tails:
                return time < 240 ? 1 : 0;
                break;

            case Characters_Knuckles:
                return time < 300 ? 1 : 0;
                break;

            default:
                return 1;
                break;
        }
    }
}

void INIT_LevelRanks()
{
    CheckMissionRequirements_t.Hook(CheckMissionRequirements_r);
}