#include "pch.h"

//  Models, Animations and Collisions:

#define SPEED_Dragon twp->scl.x

NJS_POINT3 POS_Smoke = { 0, 0, 0 };
NJS_POINT3 VELO_Smoke = { 0, 0, 0 };
NJS_POINT3 SCALE_Dragon = { -0.04f, 0.04f, 0.04f };

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

CCL_INFO COLLI_Isaak = { 0, CollisionShape_Cylinder, 0x77, 0, 0, { 0.0f, 9.0f, 0.0f }, 7.65f, 8.0f, 0.0f, 0.0f, 0, 0, 0 };
CCL_INFO COLLI_Lyle = { 0, CollisionShape_Cylinder, 0x77, 0, 0, { 0.0f, 9.0f, 0.0f }, 7.65f, 8.0f, 0.0f, 0.0f, 0, 0, 0 };
CCL_INFO COLLI_Jed = { 0, CollisionShape_Cylinder, 0x77, 0, 0, { 0.0f, 9.0f, 0.0f }, 7.65f, 8.0f, 0.0f, 0.0f, 0, 0, 0 };
CCL_INFO COLLI_Bruno = { 0, CollisionShape_Cylinder, 0x77, 0, 0, { 0.0f, 9.0f, 0.0f }, 7.65f, 8.0f, 0.0f, 0.0f, 0, 0, 0 };
CCL_INFO COLLI_Cleetus = { 0, CollisionShape_Cylinder, 0x77, 0, 0, { 0.0f, 9.0f, 0.0f }, 7.65f, 8.0f, 0.0f, 0.0f, 0, 0, 0 };


//  Dragons - Display Functions:

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


//  Dragons - Exec Functions:

//  NOTE: Since these are child tasks and not SET objects, I use CheckRangeOutWithR to set up a custom range.
//  In this case if (!CheckRangeOutWithR(tp, range)) whichs means: "If the object is not gonna be deleted, do what's in the condition".
//  I don't use CheckRangeOut because this one picks up the range set in the object list, this is not the case for child objects since they are created manually and not part of the object list.

void EXEC_Isaak(task* tp)
{
    if (!CheckRangeOutWithR(tp, 96100.0f))
    {
        auto twp = tp->twp;

        switch (twp->mode)
        {
            case 0:

                tp->disp = DISPLAY_Isaak;
                CCL_Init(tp, &COLLI_Isaak, 1, 4u);

                POS_Smoke.x = twp->pos.x;
                POS_Smoke.y = twp->pos.y + 10.25f;
                POS_Smoke.z = twp->pos.z;

                twp->mode++;

                break;

            case 1:

                SPEED_Dragon += 0.33f;

                if (++twp->wtimer > 3300)
                {
                    CreateSmoke(&POS_Smoke, &VELO_Smoke, 5.0f);
                    FreeTask(tp);
                }

                break;
        }

        EntryColliList(twp);

        tp->disp(tp);
    }
}

void EXEC_Lyle(task* tp)
{
    if (!CheckRangeOutWithR(tp, 96100.0f))
    {
        auto twp = tp->twp;

        switch (twp->mode)
        {
            case 0:

                tp->disp = DISPLAY_Lyle;
                CCL_Init(tp, &COLLI_Lyle, 1, 4u);

                twp->mode++;

                break;

            case 1:

                SPEED_Dragon += 0.33f;

                if (++twp->wtimer > 3300)
                    FreeTask(tp);

                break;
        }

        EntryColliList(twp);

        tp->disp(tp);
    }
}

void EXEC_Jed(task* tp)
{
    if (!CheckRangeOutWithR(tp, 96100.0f))
    {
        auto twp = tp->twp;

        switch (twp->mode)
        {
            case 0:

                tp->disp = DISPLAY_Jed;
                CCL_Init(tp, &COLLI_Jed, 1, 4u);

                twp->mode++;

                break;

            case 1:

                SPEED_Dragon += 0.33f;

                if (++twp->wtimer > 3300)
                    FreeTask(tp);

                break;
        }

        EntryColliList(twp);

        tp->disp(tp);
    }
}

void EXEC_Bruno(task* tp)
{
    if (!CheckRangeOutWithR(tp, 96100.0f))
    {
        auto twp = tp->twp;

        switch (twp->mode)
        {
            case 0:

                tp->disp = DISPLAY_Bruno;
                CCL_Init(tp, &COLLI_Bruno, 1, 4u);

                twp->mode++;

                break;

            case 1:

                SPEED_Dragon += 0.33f;

                if (++twp->wtimer > 3300)
                    FreeTask(tp);

                break;
        }

        EntryColliList(twp);

        tp->disp(tp);
    }
}

void EXEC_Cleetus(task* tp)
{
    if (!CheckRangeOutWithR(tp, 96100.0f))
    {
        auto twp = tp->twp;

        switch (twp->mode)
        {
            case 0:

                tp->disp = DISPLAY_Cleetus;
                CCL_Init(tp, &COLLI_Cleetus, 1, 4u);

                twp->mode++;

                break;

            case 1:

                SPEED_Dragon += 0.33f;

                if (++twp->wtimer > 3300)
                    FreeTask(tp);

                break;
        }

        EntryColliList(twp);

        tp->disp(tp);
    }
}


//  Dragons - ChildTaskSet:

childtaskset CTS_Isaak[] = {
    { EXEC_Isaak, 2, 0, {0}, {0}, 0 },
    { 0 }
};

childtaskset CTS_Lyle[] = {
    { EXEC_Lyle, 2, 0, {0}, {0}, 0 },
    { 0 }
};

childtaskset CTS_Jed[] = {
    { EXEC_Jed, 2, 0, {0}, {0}, 0 },
    { 0 }
};

childtaskset CTS_Bruno[] = {
    { EXEC_Bruno, 2, 0, {0}, {0}, 0 },
    { 0 }
};

childtaskset CTS_Cleetus[] = {
    { EXEC_Cleetus, 2, 0, {0}, {0}, 0 },
    { 0 }
};


//  Dragons - Load Assets:

void LOAD_Dragons()
{
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
}