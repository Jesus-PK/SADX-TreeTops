#include "pch.h"

#define SPEED_Spaba twp->scl.x

//  Models, Animations and Collisions:

ModelInfo* MDL_Spaba = nullptr;
AnimationFile* ANIM_Spaba = nullptr;

CCL_INFO COLLI_Spaba = { 0, CollisionShape_Sphere, 0x77, 0, 0, { 0.0f, 0.0f, 0.0f }, 7.5f, 0.0f, 0.0f, 0.0f, 0, 0, 0 };


//  Spaba - Main:

void DISPLAY_Spaba(task* tp)
{
    if (MissedFrames)
        return;

    auto twp = tp->twp;
    
    NJS_POINT3 SCALE_Spaba = { 0.02f, 0.02f, 0.02f };
    NJS_ACTION ACTION_Spaba = { MDL_Spaba->getmodel(), ANIM_Spaba->getmotion() };

    njSetTexture(&TEXLIST_TTSpaba);
    njPushMatrix(0);
    njTranslateV(0, &twp->pos);
    njRotateXYZ(0, twp->ang.x, twp->ang.y, twp->ang.z);
    njScaleV(0, &SCALE_Spaba);
    
    SetupChunkModelRender();
    njCnkAction(&ACTION_Spaba, SPEED_Spaba);
    ResetChunkModelRender();
    
    njPopMatrix(1u);
}

void EXEC_Spaba(task* tp)
{
    if (CheckRangeOut(tp))
        return;
    
    auto twp = tp->twp;

    switch (twp->mode)
    {
        case 0:

            tp->disp = DISPLAY_Spaba;
            CCL_Init(tp, &COLLI_Spaba, 1, 4u);

            twp->mode++;

            break;

        case 1:

            SPEED_Spaba += 0.3f;

            break;
    }

    EntryColliList(twp);

    tp->disp(tp);
}


//  Spaba - Load Assets:

void LOAD_Spaba()
{
    MDL_Spaba = LoadChunkModel("TreeTops_SpabaLEDGE");
    ANIM_Spaba = LoadObjectAnim("TreeTops_SpabaLEDGE");
}