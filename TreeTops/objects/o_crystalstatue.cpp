#include "pch.h"

//  Models and Collisions:

ModelInfo* MDL_CrystalBase = nullptr;

ModelInfo* MDL_CrystalStatue = nullptr;
ModelInfo* MDL_CSDebris01 = nullptr;
ModelInfo* MDL_CSDebris02 = nullptr;
ModelInfo* MDL_CSDebris03 = nullptr;

#define SPEED_Dragon twp->scl.x
NJS_VECTOR SCALE_Dragon = { -0.04f, 0.04, 0.04 };

ModelInfo* MDL_Isaak = nullptr;
ModelInfo* MDL_Lyle = nullptr;
ModelInfo* MDL_Jed = nullptr;
ModelInfo* MDL_Bruno = nullptr;
ModelInfo* MDL_Cleetus = nullptr;

AnimationFile* ANIM_Isaak = nullptr;
AnimationFile* ANIM_Lyle = nullptr;
AnimationFile* ANIM_Jed = nullptr;
AnimationFile* ANIM_Bruno = nullptr;
AnimationFile* ANIM_Cleetus = nullptr;

CCL_INFO COLLI_CrystalStatue = { 0, CollisionShape_Sphere, 0x77, 0x20, 0x400, { 0.0f, 5.25f, 0.0f }, 8.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0 };

CCL_INFO COLLI_Isaak = { 0, CollisionShape_Cylinder, 0x77, 0, 0, { 0.0f, 9.0f, 0.0f }, 7.65f, 8.0f, 0.0f, 0.0f, 0, 0, 0 };


//  Crystal Base - Main:

void DISPLAY_CrystalBase(task* obj)
{
    if (MissedFrames)
        return;

    taskwk* twp = obj->twp;

    njSetTexture(&TEXLIST_TTObjects);
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

    switch (twp->mode)
    {
        case 0:
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

            break;
        }

        case 1:
        {
            MirenObjCheckCollisionP(twp, 100.0f);

            break;
        }
    }

    tp->disp(tp);
}


//  Crystal Statue - Debris Pieces:

void DISPLAY_CSDebris(task* tp)
{
    taskwk* twp = tp->twp;

    njSetTexture(&TEXLIST_TTObjects);
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
                
                break;
        }

        DISPLAY_CSDebris(tp);
    }
}

childtaskset CTS_CSDebris[] = {
    { EXEC_CSDebris, 2, 0, {0}, {0}, 0 },
    { EXEC_CSDebris, 2, 0, {0}, {0}, 0 },
    { EXEC_CSDebris, 2, 0, {0}, {0}, 0 },
    { 0 }
};


//  Crystal Statue - Dragons:

void SetDragonRescued()
{
    uint16_t score = 1000;
    AddEnemyScore(score);
    
    DragonCount++;
}

void DISPLAY_Isaak(task* tp)
{
    if (MissedFrames)
        return;

    auto twp = tp->twp;

    NJS_ACTION ACTION_Isaak = { MDL_Isaak->getmodel(), ANIM_Isaak->getmotion() };

    njSetTexture(&TEXLIST_TTDragons);
    
    njPushMatrix(0);
    
    njTranslate(0, twp->pos.x, twp->pos.y + 2.0f, twp->pos.z);
    njRotateXYZ(0, twp->ang.x, twp->ang.y, twp->ang.z);
    njScaleV(0, &SCALE_Dragon);

    SetupChunkModelRender();
    njCnkAction(&ACTION_Isaak, SPEED_Dragon);
    ResetChunkModelRender();

    njPopMatrix(1u);
}

void DISPLAY_Lyle(task* tp)
{
    if (MissedFrames)
        return;

    auto twp = tp->twp;

    NJS_ACTION ACTION_Lyle = { MDL_Lyle->getmodel(), ANIM_Lyle->getmotion() };

    njSetTexture(&TEXLIST_TTDragons);

    njPushMatrix(0);

    njTranslate(0, twp->pos.x, twp->pos.y + 2.0f, twp->pos.z);
    njRotateXYZ(0, twp->ang.x, twp->ang.y, twp->ang.z);
    njScaleV(0, &SCALE_Dragon);

    SetupChunkModelRender();
    njCnkAction(&ACTION_Lyle, SPEED_Dragon);
    ResetChunkModelRender();

    njPopMatrix(1u);
}

void DISPLAY_Jed(task* tp)
{
    if (MissedFrames)
        return;

    auto twp = tp->twp;

    NJS_ACTION ACTION_Jed = { MDL_Jed->getmodel(), ANIM_Jed->getmotion() };

    njSetTexture(&TEXLIST_TTDragons);

    njPushMatrix(0);

    njTranslate(0, twp->pos.x, twp->pos.y + 2.0f, twp->pos.z);
    njRotateXYZ(0, twp->ang.x, twp->ang.y, twp->ang.z);
    njScaleV(0, &SCALE_Dragon);

    SetupChunkModelRender();
    njCnkAction(&ACTION_Jed, SPEED_Dragon);
    ResetChunkModelRender();

    njPopMatrix(1u);
}

void DISPLAY_Bruno(task* tp)
{
    if (MissedFrames)
        return;

    auto twp = tp->twp;

    NJS_ACTION ACTION_Bruno = { MDL_Bruno->getmodel(), ANIM_Bruno->getmotion() };

    njSetTexture(&TEXLIST_TTDragons);

    njPushMatrix(0);

    njTranslate(0, twp->pos.x, twp->pos.y + 2.0f, twp->pos.z);
    njRotateXYZ(0, twp->ang.x, twp->ang.y, twp->ang.z);
    njScaleV(0, &SCALE_Dragon);

    SetupChunkModelRender();
    njCnkAction(&ACTION_Bruno, SPEED_Dragon);
    ResetChunkModelRender();

    njPopMatrix(1u);
}

void DISPLAY_Cleetus(task* tp)
{
    if (MissedFrames)
        return;

    auto twp = tp->twp;

    NJS_ACTION ACTION_Cleetus = { MDL_Cleetus->getmodel(), ANIM_Cleetus->getmotion() };

    njSetTexture(&TEXLIST_TTDragons);

    njPushMatrix(0);

    njTranslate(0, twp->pos.x, twp->pos.y + 2.0f, twp->pos.z);
    njRotateXYZ(0, twp->ang.x, twp->ang.y, twp->ang.z);
    njScaleV(0, &SCALE_Dragon);

    SetupChunkModelRender();
    njCnkAction(&ACTION_Cleetus, SPEED_Dragon);
    ResetChunkModelRender();

    njPopMatrix(1u);
}


//  Crystal Statue - Main:

void DISPLAY_CrystalStatue(task* obj)
{
    if (MissedFrames)
        return;
    
    taskwk* twp = obj->twp;

    if (twp->mode == 2)
        return;

    njSetTexture(&TEXLIST_TTObjects);
    njPushMatrix(0);
    njTranslateV(0, &twp->pos);
    njRotateXYZ(0, twp->ang.x, twp->ang.y, twp->ang.z);
    dsDrawObject(MDL_CrystalStatue->getmodel());
    njPopMatrix(1u);
}

void EXEC_CrystalStatue(task* tp)
{
    auto twp = tp->twp;

    if (CheckRangeOut(tp))
        return;

    switch (twp->mode)
    {
        case 0:

            SetFlagNoRespawn(tp); // Enabling this flag makes so the object won't respawn after is destroyed (if you destroyed the object and you die, the one you collected won't respawn)
            
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
                    dsPlay_oneshot(SE_BOMB, 0, 0, 0);
                    SetDragonRescued();
                    Dead(tp);
                    
                    CreateChildrenTask(CTS_CSDebris, tp);

                    twp->mode++;
                }
            }

            EntryColliList(twp);

            break;

        case 2:

            if (DragonCount == 1)
                tp->disp = DISPLAY_Isaak;

            else if (DragonCount == 2)
                tp->disp = DISPLAY_Lyle;

            else if (DragonCount == 3)
                tp->disp = DISPLAY_Jed;

            else if (DragonCount == 4)
                tp->disp = DISPLAY_Bruno;

            else if (DragonCount >= 5)
                tp->disp = DISPLAY_Cleetus;

            //CCL_Init(tp, &COLLI_Isaak, 1, 4u);

            twp->mode++;

            break;

        case 3:

            //EntryColliList(twp);

            SPEED_Dragon += 0.3f;

            if (++twp->wtimer > 120)
                FreeTaskC(tp); // This will free ONLY the children of the task (the debris) - I use this one instead of FreeTask so the extra dragon model can stay until the object deloads.

            LoopTaskC(tp);

            break;
    }

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
    
    MDL_Isaak = LoadChunkModel("TreeTops_Isaak");
    MDL_Lyle = LoadChunkModel("TreeTops_Lyle");
    MDL_Jed = LoadChunkModel("TreeTops_Jed");
    MDL_Bruno = LoadChunkModel("TreeTops_Bruno");
    MDL_Cleetus = LoadChunkModel("TreeTops_Cleetus");

    ANIM_Isaak = LoadObjectAnim("TreeTops_Isaak");
    ANIM_Lyle = LoadObjectAnim("TreeTops_Lyle");
    ANIM_Jed = LoadObjectAnim("TreeTops_Jed");
    ANIM_Bruno = LoadObjectAnim("TreeTops_Bruno");
    ANIM_Cleetus = LoadObjectAnim("TreeTops_Cleetus");

    CTS_CSDebris[0].ptr = MDL_CSDebris01->getmodel();
    CTS_CSDebris[1].ptr = MDL_CSDebris02->getmodel();
    CTS_CSDebris[2].ptr = MDL_CSDebris03->getmodel();
}