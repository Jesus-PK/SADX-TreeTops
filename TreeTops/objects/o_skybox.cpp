#include "pch.h"

//  Model:

ModelInfo* MDL_TTSkybox = nullptr;


//  Skybox - Main:

//  I create a entiretely custom BG task with the same format the game does it (disp, exec, init) then slap the init (bg) in ScrollMasterList:

void DISP_TTSkybox(task* tp)
{
    auto twp = tp->twp;
    
    Direct3D_SetNearFarPlanes(SkyboxDrawDistance.Minimum, SkyboxDrawDistance.Maximum);

    DisableFog();
    njPushMatrix(0);

    njTranslate(0, 0.0f, 0.0f, 0.0f);
    njScale(0, 20.0f, 20.0f, 20.0f);

    DrawModel(MDL_TTSkybox->getmodel()->basicdxmodel);

    njPopMatrix(1u);
    ToggleStageFog();

    Direct3D_SetNearFarPlanes(LevelDrawDistance.Minimum, LevelDrawDistance.Maximum);
}

void EXEC_TTSkybox(task* tp)
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
    tp->exec = EXEC_TTSkybox;
    tp->disp = DISP_TTSkybox;
}


//  Skybox - Load Assets:

void LOAD_TTSkybox()
{
    MDL_TTSkybox = LoadBasicModel("TreeTops_Skybox");
}