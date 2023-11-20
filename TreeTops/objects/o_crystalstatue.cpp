#include "pch.h"
#include "o_dragons.h"

//  Models and Collisions:

ModelInfo* MDL_CrystalBase = nullptr;

ModelInfo* MDL_CrystalStatue = nullptr;
ModelInfo* MDL_CSDebris01 = nullptr;
ModelInfo* MDL_CSDebris02 = nullptr;
ModelInfo* MDL_CSDebris03 = nullptr;

CCL_INFO COLLI_CrystalStatue = { 0, CollisionShape_Sphere, 0x77, 0x20, 0x400, { 0.0f, 7.0f, 0.0f }, 11.5f, 0.0f, 0.0f, 0.0f, 0, 0, 0 };


//  Crystal Base - Main:

void DISPLAY_CrystalBase(task* tp)
{
    if (MissedFrames)
        return;

    auto twp = tp->twp;
    
    njSetTexture(&TEXLIST_TreeTops_Objects);
    
    njPushMatrix(0);
    
    njTranslateV(0, &twp->pos);
    njRotateXYZ(0, twp->ang.x, twp->ang.y, twp->ang.z);
    
    dsDrawObject(MDL_CrystalBase->getmodel());
    
    njPopMatrix(1u);
}

void EXEC_CrystalBase(task* tp)
{
    if (CheckRangeOut(tp))
        return;

    auto twp = tp->twp;

    if (!twp->mode)
    {
        auto object = GetMobileLandObject();

        tp->disp = DISPLAY_CrystalBase;
        tp->dest = B_Destructor;

        object->pos[0] = twp->pos.x;
        object->pos[1] = twp->pos.y;
        object->pos[2] = twp->pos.z;

        object->ang[0] = twp->ang.x;
        object->ang[1] = twp->ang.y;
        object->ang[2] = twp->ang.z;

        object->scl[0] = 1.0f;
        object->scl[1] = 1.0f;
        object->scl[2] = 1.0f;

        object->basicdxmodel = MDL_CrystalBase->getmodel()->basicdxmodel;

        RegisterCollisionEntry(ColFlags_Solid, tp, object);

        twp->counter.ptr = object;

        twp->mode++;
    }

    MirenObjCheckCollisionP(twp, 100.0f);

    tp->disp(tp);
}


//  Crystal Statue - Debris Pieces:

void DISPLAY_CSDebris(task* tp)
{
    auto twp = tp->twp;

    njSetTexture(&TEXLIST_TreeTops_Objects);
    
    njPushMatrix(0);
    
    njTranslateV(0, &twp->pos);
    
    if (twp->ang.x)
        njRotateX(0, twp->ang.x);
    
    if (twp->ang.y)
        njRotateY(0, twp->ang.y);

    ds_DrawObjectClip((NJS_OBJECT*)twp->counter.ptr, 1.0f);
    
    njPopMatrix(1);
}

void EXEC_CSDebris(task* tp)
{
    if (!CheckRangeOutWithR(tp, 96100.0))
    {
        auto twp = tp->twp;

        switch (twp->mode)
        {
            case 0:
                
                tp->disp = DISPLAY_CSDebris;
                
                twp->mode = 1;

                twp->scl.x = njRandom() - 0.5f;
                twp->scl.y = njRandom() + 0.5f;
                twp->scl.z = njRandom() - 0.5f;
                
                break;
           
            case 1:
                
                twp->pos.x += twp->scl.x;
                twp->pos.y += twp->scl.y;
                twp->pos.z += twp->scl.z;

                twp->ang.x += 0x80;
                twp->ang.y += 0x100;

                twp->scl.y -= 0.05f;

                if (++twp->wtimer > 120)
                    FreeTask(tp);
                
                break;
        }

        tp->disp(tp);
    }
}

childtaskset CTS_CSDebris[] = {
    { EXEC_CSDebris, 2, 0, {0}, {0}, 0 },
    { EXEC_CSDebris, 2, 0, {0}, {0}, 0 },
    { EXEC_CSDebris, 2, 0, {0}, {0}, 0 },
    { 0 }
};


//  Crystal Statue - Rewards:

void SetDragonRescued()
{
    AddEnemyScore(1000);
    dsPlay_oneshot(SE_BOMB, 0, 0, 0);
    AddNumRing(20);
    DragonCount++;
}


//  Crystal Statue - Checkpoint:

void DisplayCheckpointTime_Statue(task* tp)
{
    //  This if conditions and timer values are kinda messy, how the game does it is to get that "blinking" effect on the sprites. Basically:
    //  The int value increases by 1 every frame via twp->wtimer + 1. Once the int value hits the value we specified (180 for example), it'll stop counting up (returns to 0) and will free the task.
    //  On the else if, it checks if the int value is over 0 and in that case, it'll display the sprites. The other value I'm not 100% sure but basically controls the blink in the sprites, no idea how is dictated nor how to make it a steady blink.
    //  Now if you don't want the blink effect, you can ditch all that mess in the if then on the else if, simply do a ++twp->wtimer < 120 - That'll make it act the same as my CTS killers (It worked fine on test, but doesn't hurt further testing or scrambling that code around to better do FreeTask).
    
    auto twp = tp->twp;

    int TimerDuration = 0;

    CUSTUM_PRINT_NUMBER TimerPosition = { 450.0f, 400.0f, 1.0f, 1.0f, 30.0f, 0.0f };

    TimerPosition.loc_x = 472.0f;
    TimerPosition.loc_y = (HUD_Plus) ? 41.0f : 35.0f; // OCD go brrrrr

    if (HideHud < 0 || EV_CheckCansel() || (TimerDuration = twp->wtimer + 1, twp->wtimer = TimerDuration, TimerDuration > 0xB4))
        FreeTask(tp);
    
    else if ((TimerDuration & 0x98) != 0)
        DisplayCheckpointTime(&TimerPosition, twp->ang.x, twp->ang.y);
}

void SetCheckpointData(task* tp)
{
    auto twp = tp->twp;

    updateContinueData(&twp->pos, &twp->ang); // This sets the checkpoint data (pos, ang, time) to the object.

    task* TASK_DisplayTimer = CreateElementalTask(2u, 6, DisplayCheckpointTime_Statue); // I load this task to store the minutes and seconds in the task data (ang x, ang y).

    if (TASK_DisplayTimer)
    {
        TASK_DisplayTimer->twp->ang.x = TimeMinutes;
        TASK_DisplayTimer->twp->ang.y = TimeSeconds;
    }
}


//  Crystal Statue - Main:

void DISPLAY_CrystalStatue(task* tp)
{
    if (MissedFrames)
        return;
    
    auto twp = tp->twp;

    if (twp->mode == 3)
        return;

    njSetTexture(&TEXLIST_TreeTops_Objects);
    
    njPushMatrix(0);
    
    njTranslateV(0, &twp->pos);
    njRotateXYZ(0, twp->ang.x, twp->ang.y, twp->ang.z);
    
    dsDrawObject(MDL_CrystalStatue->getmodel());
    
    njPopMatrix(1u);
}

void EXEC_CrystalStatue(task* tp)
{
    if (CheckRangeOut(tp))
        return;
    
    auto twp = tp->twp;

    switch (twp->mode)
    {
        case 0:

            SetNoRevive(tp); // Enabling this flag makes it so the object won't respawn after is destroyed (if you destroyed the object and you die, the one you collected won't respawn) - Previously known as SetFlagNoRespawn(tp);
            
            tp->disp = DISPLAY_CrystalStatue;
            CCL_Init(tp, &COLLI_CrystalStatue, 1, 2u);

            twp->mode++;

            break;

        case 1:

            if (twp->flag & Status_Hurt && twp->cwp->hit_cwp)
            {
                task* hit_tp = twp->cwp->hit_cwp->mytask;

                if (hit_tp && IsThisTaskPlayer(hit_tp) != -1)
                {
                    EnemyBounceAndRumble(hit_tp->twp->counter.b[0]);
                    
                    SetDragonRescued();
                    
                    if (CurrentCharacter != Characters_Knuckles)
                        SetCheckpointData(tp);
                    
                    Knuckles_KakeraGame_Set_PutEme(twp->ang.z, &twp->pos); // This gives an emerald shard upon destroying the object, the emerald ID is dictated by the Z Angle value.
                    
                    Dead(tp); // This sets the "No Respawn" flag on the object, requiring you to manually delete it later. DeadOut on the other hand, sets this same flag alongside destroying the object - In this case, I use Dead since I need to run more code afterwards (the Child Tasks). So I manually delete the object later with FreeTask.
                    
                    CreateChildrenTask(CTS_CSDebris, tp);

                    twp->mode++;
                }
            }

            EntryColliList(twp);

            break;

        case 2:

            switch (DragonCount) // If DragonCount == 1, 2, 3...
            {
                case 1:
                    CreateChildrenTask(CTS_Isaak, tp);
                    break;

                case 2:
                    CreateChildrenTask(CTS_Lyle, tp);
                    break;

                case 3:
                    CreateChildrenTask(CTS_Jed, tp);
                    break;

                case 4:
                    CreateChildrenTask(CTS_Bruno, tp);
                    break;

                case 5:
                    CreateChildrenTask(CTS_Cleetus, tp);
                    break;
            }

            twp->mode++;

            break;

        case 3:

            LoopTaskC(tp);

            break;
    }

    Knuckles_KakeraGame_Set_CheckEme(twp->ang.z, &twp->pos); // This checks if the emerald ID exists and let's the radar track it, needs to be called every frame.

    tp->disp(tp);
}


//  Crystal Statue - Load Assets:

void LOAD_CrystalStatue()
{
    MDL_CrystalBase = LoadBasicModel("TreeTops_CrystalBase");
    
    MDL_CrystalStatue = LoadBasicModel("TreeTops_CrystalStatue");
    MDL_CSDebris01 = LoadBasicModel("TreeTops_CSDebris01");
    MDL_CSDebris02 = LoadBasicModel("TreeTops_CSDebris02");
    MDL_CSDebris03 = LoadBasicModel("TreeTops_CSDebris03");

    CTS_CSDebris[0].ptr = MDL_CSDebris01->getmodel();
    CTS_CSDebris[1].ptr = MDL_CSDebris02->getmodel();
    CTS_CSDebris[2].ptr = MDL_CSDebris03->getmodel();
}