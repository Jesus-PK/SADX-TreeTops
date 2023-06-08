#include "pch.h"

//  Model:

ModelInfo* MDL_TTSkybox = nullptr;


//  Skybox - Main:

//  Since Sky Deck is the only level that doesn't have the structure of Skybox_Level_Load -> 3 function calls inside (Main, Display & Delete), seems like Skybox_SkyDeck is the exec and then Skybox_SkyDeck_Display.
//  In the exec there's some hardcoded things such as the gravity gimmick - So what I did in here was writing first a custom display function for the skybox then a custom exec function in were I call my custom display function. Literally same thing I did with my custom objects.
//  Then I WriteJump this custom skybox exec on the address of Skybox_SkyDeck -> WriteJump((void*)0x5F0340, EXEC_TTSkybox);

void DISPLAY_TTSkybox(task* obj)
{
    auto data = obj->twp;
    
    Direct3D_SetNearFarPlanes(SkyboxDrawDistance.Minimum, SkyboxDrawDistance.Maximum);

    DisableFog();
    njPushMatrix(0);

    NJS_VECTOR POS_TTSkybox = { 0, 0, 0 };
    njTranslateV(0, &POS_TTSkybox);
    njScale(0, 20.0f, 20.0f, 20.0f);

    DrawModel(MDL_TTSkybox->getmodel()->basicdxmodel);

    njPopMatrix(1u);
    ToggleStageFog();

    SetGlobalPoint2Col_Colors(0x15201A, 0x15201A, 0x15201A);

    Direct3D_SetNearFarPlanes(LevelDrawDistance.Minimum, LevelDrawDistance.Maximum);
}

//  In here I'm doing a simple if instead the whole switch getup since I'm just writing the display function call, nothing extra besides that:

void EXEC_TTSkybox(task* tp)
{
    auto twp = tp->twp;

    if (!twp->mode)
    {
        tp->disp = DISPLAY_TTSkybox;
        
        twp->mode++;
    }

    tp->disp(tp);
}


//  Skybox - Load Assets:

void LOAD_TTSkybox()
{
    MDL_TTSkybox = LoadBasicModel("TreeTops_Skybox");
}