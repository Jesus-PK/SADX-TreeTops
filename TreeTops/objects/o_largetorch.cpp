#include "pch.h"

#define SPEED_LargeTorch twp->scl.x

//  Models, Animations and Collisions:

ModelInfo* MDL_LargeTorch = nullptr;
AnimationFile* ANIM_LargeTorch = nullptr;

CCL_INFO COL_LargeTorch[] = {
    { 0, CollisionShape_Cylinder2, 0x77, 0, 0, { 0.0f, 17.0f, 0.0f }, 2.0f, 17.0f, 0.0f, 0.0f, 0, 0, 0 },
    { 0, CollisionShape_Cylinder2, 0x70, 0x2F, 0, { 0.0f, 39.0f, 0.0f }, 2.0f, 5.0f, 0.0f, 0.0f, 0, 0, 0 }
};


//  LargeTorch - Main:

void DISPLAY_LargeTorch(task* tp)
{
    if (MissedFrames)
        return;

    auto twp = tp->twp;
    
    NJS_MOTION* MOTION_LargeTorch = ANIM_LargeTorch->getmotion();

    njSetTexture(&TEXLIST_TreeTops_Objects);
    
    njPushMatrix(0);
    
    njTranslateV(0, &twp->pos);
    njRotateXYZ(0, twp->ang.x, twp->ang.y, twp->ang.z);
    njScale(0, 2.0f, 2.0f, 2.0f);

    dsDrawShapeMotion(MDL_LargeTorch->getmodel(), MOTION_LargeTorch, MOTION_LargeTorch, SPEED_LargeTorch);
    
    njPopMatrix(1u);
}

void EXEC_LargeTorch(task* tp)
{
    if (CheckRangeOut(tp))
        return;
    
    auto twp = tp->twp;

    switch (twp->mode)
    {
        case 0:

            CCL_Init(tp, arrayptrandlength(COL_LargeTorch), 4u);

            twp->mode++;

            break;

        case 1:

            SPEED_LargeTorch += 0.33f; // VELOCIDAD TOTAL, WOW

            break;
    }

    EntryColliList(twp);

    tp->disp(tp);
}

void INIT_LargeTorch(task* tp)
{
    auto twp = tp->twp;

    twp->scl.x = rand();

    tp->exec = EXEC_LargeTorch;
    tp->disp = DISPLAY_LargeTorch;
}


//  LargeTorch - Load Assets:

void LOAD_LargeTorch()
{
    MDL_LargeTorch = LoadBasicModel("TreeTops_LargeTorch");
    ANIM_LargeTorch = LoadObjectAnim("TreeTops_LargeTorch");
}