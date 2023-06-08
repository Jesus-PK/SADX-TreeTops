#include "pch.h"

//  Models, Collisions and Text Messages:

ModelInfo* MDL_ChestKey = nullptr;

ModelInfo* MDL_LockedChest = nullptr;
ModelInfo* MDL_ChestLid = nullptr;
ModelInfo* MDL_LCKDebris01 = nullptr;
ModelInfo* MDL_LCKDebris02 = nullptr;
ModelInfo* MDL_LCKDebris03 = nullptr;
ModelInfo* MDL_LCKDebris04 = nullptr;
ModelInfo* MDL_Number25 = nullptr;

ModelInfo* MDL_LCKColli01 = nullptr;

CCL_INFO COLLI_ChestKey = { 0, CollisionShape_Sphere, 0xF0, 0, 0, { 0.0f, 4.625f, 0.0f }, 4.625f, 0.0f, 0.0f, 0.0f, 0, 0, 0 };

NJS_VECTOR POS_LCKTrigger = { 0, 0, 0 };

const char* MSG_LockedChest[] = {
    "You need a key to open this chest!",
    NULL,
};


//  Chest Key - Main:

void KeyPickup()
{
    uint16_t score = 100;
    AddEnemyScore(score);

    HasKey = 1;
}

void DISPLAY_ChestKey(task* obj)
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
    
    dsDrawObject(MDL_ChestKey->getmodel());
    
    njPopMatrix(1u);
}

void EXEC_ChestKey(task* tp)
{
    auto twp = tp->twp;

    if (CheckRangeOut(tp))
        return;

    switch (twp->mode)
    {
        case 0:

            SetFlagNoRespawn(tp);
            
            tp->disp = DISPLAY_ChestKey;
            CCL_Init(tp, &COLLI_ChestKey, 1, 4u);

            twp->mode++;

            break;

        case 1:

            twp->ang.y += 750;
            
            if (twp->flag & Status_ObjectInteract && twp->cwp->hit_cwp)
            {
                task* hit_tp = twp->cwp->hit_cwp->mytask;

                if (hit_tp && IsThisTaskPlayer(hit_tp) != -1)
                {
                    KeyPickup();

                    Dead(tp);

                    twp->mode++;
                }
            }

            EntryColliList(twp);

            break;

        case 2:

            if (++twp->wtimer > 120)
                FreeTask(tp);

            break;
    }

    tp->disp(tp);
}


//  Locked Chest - Main:

void DISPLAY_LockedChest(task* obj)
{
    if (MissedFrames)
        return;

    taskwk* twp = obj->twp;

    njSetTexture(&TEXLIST_TTObjects);
    
    njPushMatrix(0);
    
    njTranslateV(0, &twp->pos);
    njRotateXYZ(0, twp->ang.x, twp->ang.y, twp->ang.z);
    
    dsDrawObject(MDL_LockedChest->getmodel());
    
    njPopMatrix(1u);
}

void EXEC_LockedChest(task* tp)
{
    if (CheckRangeOut(tp))
        return;

    auto twp = tp->twp;

    switch (twp->mode)
    {
        case 0:
        {
            auto object = GetMobileLandObject();

            tp->disp = DISPLAY_LockedChest;
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

            object->basicdxmodel = MDL_LCKColli01->getmodel()->basicdxmodel;

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


//  Locked Chest - Debris Pieces:

void DISPLAY_LCKDebris(task* tp)
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

void EXEC_LCKDebris(task* tp)
{
    if (!CheckRangeOutWithR(tp, 96100.0))
    {
        auto twp = tp->twp;

        switch (twp->mode)
        {
            case 0:
                
                tp->disp = DISPLAY_LCKDebris;
                
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

        tp->disp(tp);
    }
}

childtaskset CTS_LCKDebris[] = {
    { EXEC_LCKDebris, 2, 0, {0}, {0}, 0 },
    { EXEC_LCKDebris, 2, 0, {0}, {0}, 0 },
    { EXEC_LCKDebris, 2, 0, {0}, {0}, 0 },
    { EXEC_LCKDebris, 2, 0, {0}, {0}, 0 },
    { 0 }
};


//  Locked Chest - Value Number:

void DISPLAY_Number25(task* obj)
{
    if (MissedFrames)
        return;

    taskwk* twp = obj->twp;

    njSetTexture(&TEXLIST_TTObjects);
    
    njPushMatrix(0);
    
    njTranslateV(0, &twp->pos);
    njRotateXYZ(0, twp->ang.x, twp->ang.y, twp->ang.z);
    
    dsDrawObject(MDL_Number25->getmodel());
    
    njPopMatrix(1u);
}


//  Chest Lid - Main:

void SetChestOpen()
{
    uint16_t score = 1000;
    AddEnemyScore(score);

    dsPlay_oneshot(SE_BOMB, 0, 0, 0);
    
    Rings += 25;
    Lives += 1;
    GiveMagneticBarrier(CurrentCharacter);

    HasKey = 0;
}

void DISPLAY_ChestLid(task* obj)
{
    if (MissedFrames)
        return;
    
    taskwk* twp = obj->twp;

    if (twp->mode == 3)
        return;

    njSetTexture(&TEXLIST_TTObjects);
    
    njPushMatrix(0);
    
    njTranslateV(0, &twp->pos);
    njRotateXYZ(0, twp->ang.x, twp->ang.y, twp->ang.z);
    
    dsDrawObject(MDL_ChestLid->getmodel());
    
    njPopMatrix(1u);
}

void EXEC_ChestLid(task* tp)
{
    auto twp = tp->twp;
    
    if (CheckRangeOut(tp))
        return;

    switch (twp->mode)
    {
        case 0:

            SetFlagNoRespawn(tp);
            
            tp->disp = DISPLAY_ChestLid;

            POS_LCKTrigger.x = twp->pos.x;
            POS_LCKTrigger.y = twp->pos.y + 8.25f;
            POS_LCKTrigger.z = twp->pos.z + 20.0f;

            twp->mode++;

            break;

        case 1:

            if (CheckCollisionP(&POS_LCKTrigger, 10.0f))
            {
                if (HasKey == 0)
                {
                    DisplayHintText(MSG_LockedChest, 100);

                    twp->mode = 2;
                }
                
                else
                {
                    SetChestOpen();
                    
                    Dead(tp);
                    
                    tp->disp = DISPLAY_Number25;
                    
                    CreateChildrenTask(CTS_LCKDebris, tp);

                    twp->mode = 3;
                }
            }

            break;

        case 2:

            if (++twp->wtimer > 150)
            {
                twp->wtimer = 0;

                twp->mode = 1;
            }

            break;     
        
        case 3:

            twp->ang.y += 750;

            if (++twp->wtimer > 120)
                FreeTask(tp);

            LoopTaskC(tp);

            break;
    }
    
    tp->disp(tp);
}


//  Chest Key & Locked Chest - Load Assets:

void LOAD_LockedChest()
{
    MDL_ChestKey = LoadBasicModel("TreeTops_ChestKey");
    MDL_LockedChest = LoadBasicModel("TreeTops_LockedChest");
    MDL_ChestLid = LoadBasicModel("TreeTops_ChestLid");
    MDL_LCKDebris01 = LoadBasicModel("TreeTops_LCKDebris01");
    MDL_LCKDebris02 = LoadBasicModel("TreeTops_LCKDebris02");
    MDL_LCKDebris03 = LoadBasicModel("TreeTops_LCKDebris03");
    MDL_LCKDebris04 = LoadBasicModel("TreeTops_LCKDebris04");
    MDL_Number25 = LoadBasicModel("TreeTops_Number25");
    MDL_LCKColli01 = LoadBasicModel("TreeTops_LCKColli01");

    CTS_LCKDebris[0].ptr = MDL_LCKDebris01->getmodel();
    CTS_LCKDebris[1].ptr = MDL_LCKDebris02->getmodel();
    CTS_LCKDebris[2].ptr = MDL_LCKDebris03->getmodel();
    CTS_LCKDebris[3].ptr = MDL_LCKDebris04->getmodel();
}