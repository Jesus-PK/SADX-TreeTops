#include "pch.h"

#define SPEED_Firewood twp->scl.x

//  Models, Animations and Collisions:

ModelInfo* MDL_Firewood = nullptr;
AnimationFile* ANIM_Firewood = nullptr;

CCL_INFO COL_Firewood[] = {
    { 0, CollisionShape_Sphere, 0x77, 0, 0, { 0.0f, 2.5f, 0.0f }, 7.5f, 0.0f, 0.0f, 0.0f, 0, 0, 0 },
    { 0, CollisionShape_Cylinder2, 0x70, 0x2F, 0, { 0.0f, 16.0f, 0.0f }, 3.0f, 7.5f, 0.0f, 0.0f, 0, 0, 0 }
};


//  Firewood - Main:

void DISPLAY_Firewood(task* tp)
{
    if (MissedFrames)
        return;

    auto twp = tp->twp;
    
    NJS_MOTION* MOTION_Firewood = ANIM_Firewood->getmotion();

    njSetTexture(&TEXLIST_TreeTops_Objects);
    
    njPushMatrix(0);
    
    njTranslateV(0, &twp->pos);
    njRotateXYZ(0, twp->ang.x, twp->ang.y, twp->ang.z);
    njScale(0, 2.0f, 2.0f, 2.0f);

    dsDrawShapeMotion(MDL_Firewood->getmodel(), MOTION_Firewood, MOTION_Firewood, SPEED_Firewood);
    
    njPopMatrix(1u);
}

void EXEC_Firewood(task* tp)
{
    if (CheckRangeOut(tp))
        return;
    
    auto twp = tp->twp;

    switch (twp->mode)
    {
        case 0:

            CCL_Init(tp, arrayptrandlength(COL_Firewood), 4u);

            twp->mode++;

            break;

        case 1:

            SPEED_Firewood += 0.14f;

            break;
    }

    EntryColliList(twp);

    tp->disp(tp);
}

void INIT_Firewood(task* tp)
{
    auto twp = tp->twp;

    twp->scl.x = rand();

    tp->exec = EXEC_Firewood;
    tp->disp = DISPLAY_Firewood;
}


//  Firewood - Load Assets:

void LOAD_Firewood()
{
    MDL_Firewood = LoadBasicModel("TreeTops_Firewood");
    ANIM_Firewood = LoadObjectAnim("TreeTops_Firewood");
}