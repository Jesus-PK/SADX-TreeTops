#include "pch.h"

#define SPEED_SpottedChicken twp->scl.x

//  Models, Animations and Collisions:

ModelInfo* MDL_SpottedChicken = nullptr;
AnimationFile* ANIM_SpottedChicken = nullptr;

CCL_INFO COLLI_SpottedChicken = { 0, CollisionShape_Sphere, 0x77, 0, 0, { 0.0f, 0.0f, 0.0f }, 7.5f, 0.0f, 0.0f, 0.0f, 0, 0, 0 };


//  SpottedChicken - Main:

void DISPLAY_SpottedChicken(task* tp)
{
    if (MissedFrames)
        return;

    auto twp = tp->twp;
    
    NJS_MOTION* MOTION_SpottedChicken = ANIM_SpottedChicken->getmotion();

    njSetTexture(&TEXLIST_TTObjects);
    
    njPushMatrix(0);
    
    njTranslateV(0, &twp->pos);
    njRotateXYZ(0, twp->ang.x, twp->ang.y, twp->ang.z);
    njScale(0, 2.0f, 2.0f, 2.0f);

    dsDrawShapeMotion(MDL_SpottedChicken->getmodel(), MOTION_SpottedChicken, MOTION_SpottedChicken, SPEED_SpottedChicken);
    
    njPopMatrix(1u);
}

void MAIN_SpottedChicken(task* tp)
{
    if (CheckRangeOut(tp))
        return;
    
    auto twp = tp->twp;

    switch (twp->mode)
    {
        case 0:

            //tp->disp = DISPLAY_SpottedChicken;
            CCL_Init(tp, &COLLI_SpottedChicken, 1, 4u);

            twp->mode++;

            break;

        case 1:

            
            SPEED_SpottedChicken += 0.075f;
            

            break;
    }

    EntryColliList(twp);

    tp->disp(tp);
}

void EXEC_SpottedChicken(task* tp)
{
    auto twp = tp->twp;

    twp->scl.x = rand();
    tp->exec = MAIN_SpottedChicken;
    tp->disp = DISPLAY_SpottedChicken;
}


//  SpottedChicken - Load Assets:

void LOAD_SpottedChicken()
{
    MDL_SpottedChicken = LoadBasicModel("TreeTops_SpottedChicken");
    ANIM_SpottedChicken = LoadObjectAnim("TreeTops_SpottedChicken");
}