#include "pch.h"

//  Model:

ModelInfo* MDL_TreeTops_Skybox = nullptr;


//  Skybox - Main:

//  I create a entiretely custom BG task with the same format the game does it (disp, exec, init) then slap the init (bg) in ScrollMasterList:

void DISPLAY_TreeTops_Skybox(task* tp)
{
    auto twp = tp->twp;
    
    njSetTexture(&TEXLIST_TreeTops_Objects); // Just setting a texture fix the blinking issue lol, even if I don't really use any visible textures on the model.
    
    Direct3D_SetNearFarPlanes(SkyboxDrawDistance.Minimum, SkyboxDrawDistance.Maximum);

    DisableFog();
    njPushMatrix(0);

    njTranslate(0, 0.0f, 0.0f, 0.0f);
    njScale(0, 20.0f, 20.0f, 20.0f);

    DrawModel(MDL_TreeTops_Skybox->getmodel()->basicdxmodel);

    njPopMatrix(1u);
    ToggleStageFog();

    Direct3D_SetNearFarPlanes(LevelDrawDistance.Minimum, LevelDrawDistance.Maximum);
}

void EXEC_TreeTops_Skybox(task* tp)
{
    auto twp = tp->twp;

    if (!twp->mode)
    {
        SetGlobalPoint2Col_Colors(0x15201A, 0x15201A, 0x15201A);

        twp->mode++;
    }

    tp->disp(tp);
}

void BG_TreeTops(task* tp)
{
    tp->exec = EXEC_TreeTops_Skybox;
    tp->disp = DISPLAY_TreeTops_Skybox;
}


//  Skybox - Load Assets:

void LOAD_TreeTops_Skybox()
{
    MDL_TreeTops_Skybox = LoadBasicModel("TreeTops_Skybox");
}