#include "pch.h"

//  HD GUI check for sprites:

//  I basically declare a integer, then create a simple function with a ternary operator that will check for HD GUI then return either 0 or 1.
//  Then on both icons DrawSprite calls, instead of specifing the texID, I just specify my int "ArrayID" and call the function I made above.
//  This will fill that with the result of the function above: Either Array 0 or 1 of my TEXANIM array. The TexID assigned to these two will vary depending if it is the Dragon or Key counter.

int ArrayID;
float SpriteHeight_Dragon;
float SpriteHeight_Counter;
float SpriteHeight_Key;

void SetSpriteSettings()
{ 
    //  Set Array ID:
    
    HD_GUI ? ArrayID = 1 : ArrayID = 0;


    //  Set Sprite Height Positions:
    
    if (HUD_Plus) // Currently HUD+ hardcodes the lifeicon to the same pos as vanilla and overrides DC Conv options, so I check it first.
    {
        SpriteHeight_Dragon = 416.0f;
        SpriteHeight_Counter = 424.0f;
        
        SpriteHeight_Key = (CurrentCharacter == Characters_Tails) ? 376.0f : 416.0f; // If current characters is Tails, set SpriteHeight_Key to 376.0f, else to 416.0f
    }

    else if (DC_Conversion) // If HUD+ isn't enabled, check for DC Conversion.
    {
        SpriteHeight_Dragon = (DC_HudTweaks) ? 400.0f : 416.0f; // If DC_HudTweaks is enabled, set SpriteHeight_Dragon to 400.0f, else to 416.0f
        SpriteHeight_Counter = (DC_HudTweaks) ? 416.0f : 424.0f;

        if (DC_HudTweaks) // This checks if the "Adjust HUD Position" config option from DC Conv is enabled.
            SpriteHeight_Key = (CurrentCharacter == Characters_Tails) ? 360.0f : 400.0f;

        else
            SpriteHeight_Key = (CurrentCharacter == Characters_Tails) ? 376.0f : 416.0f;
    }

    else // If neither HUD+ or DC Conv is enabled.
    {
        SpriteHeight_Dragon = 416.0f;
        SpriteHeight_Counter = 424.0f;
        
        SpriteHeight_Key = (CurrentCharacter == Characters_Tails) ? 376.0f : 416.0f;
    }
}


//  Dragon HUD:

static NJS_TEXANIM TEXANIM_DragonIcon[] = {
    { 0x20, 0x20, 0, 0, 0, 0, 0x100, 0x100, 28, 0x20 }, // ID 0 - TexID 28
    { 0x20, 0x20, 0, 0, 0, 0, 0x100, 0x100, 29, 0x20 }, // ID 1 - TexID 29
};

static NJS_SPRITE SPRITE_DragonIcon = { { 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 0, &TEXLIST_TTObjects, TEXANIM_DragonIcon };


static NJS_TEXANIM TEXANIM_DragonCounter[] = {
    { 0x10, 0x10, 0, 0, 0, 0, 0x100, 0x100, 0, 0x20 }, // ID 0 - TexID 0
    { 0x10, 0x10, 0, 0, 0, 0, 0x100, 0x100, 1, 0x20 }, // ID 1 - TexID 1
    { 0x10, 0x10, 0, 0, 0, 0, 0x100, 0x100, 2, 0x20 }, // ID 2 - TexID 2
    { 0x10, 0x10, 0, 0, 0, 0, 0x100, 0x100, 3, 0x20 }, // ID 3 - TexID 3
    { 0x10, 0x10, 0, 0, 0, 0, 0x100, 0x100, 4, 0x20 }, // ID 4 - TexID 4
    { 0x10, 0x10, 0, 0, 0, 0, 0x100, 0x100, 5, 0x20 }, // ID 5 - TexID 5
    { 0x10, 0x10, 0, 0, 0, 0, 0x100, 0x100, 73, 0x20 }, // ID 6 - TexID 73
};

static NJS_SPRITE SPRITE_DragonCounter = { { 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 0, &CON_REGULAR_TEXLIST, TEXANIM_DragonCounter }; // Instead of having a custom .PVMX, we just take the number UI from CON_REGULAR and use my custom TEXANIM array - This makes the font consistent when not using HD GUI or using custom UI.

void DrawDragonCountHUD()
{   
    SetSpriteSettings();
    
    SPRITE_DragonIcon.p.x = 592.0f;
    SPRITE_DragonIcon.p.y = SpriteHeight_Dragon;
    late_DrawSprite2D(&SPRITE_DragonIcon, ArrayID, 22046.496f, NJD_SPRITE_ALPHA, LATE_LIG); // This draws the custom dragon icon.

    if (DragonCount >= 5) // This changes the sprite color to green when the condition is met (wrote if equal or greater than the value as a failsafe) - The sprite needs to have the NJD_SPRITE_COLOR flag.
        SetMaterial(1.0f, 0.0f, 1.0f, 0.0f);
    
    SPRITE_DragonCounter.p.x = 576.0f;
    SPRITE_DragonCounter.p.y = SpriteHeight_Counter; // It's enough calling the height once unless we need a different height for the other sprites.
    late_DrawSprite2D(&SPRITE_DragonCounter, 5, 22046.496f, NJD_SPRITE_ALPHA, LATE_LIG); // This draws the right number - Static, put manual ID from the array (In this case 5 since the max amount is gonna be 5 dragons).
    
    SPRITE_DragonCounter.p.x -= 16.0f; // Doing "-=" makes it so it uses the substracted value from the one that was used previously (SPRITE_DragonCounter.p.x at the very top).
    late_DrawSprite2D(&SPRITE_DragonCounter, 6, 22046.496f, NJD_SPRITE_ALPHA, LATE_LIG); // This draws the slash character - ID 6 from the array.

    SPRITE_DragonCounter.p.x -= 16.0f;
    late_DrawSprite2D(&SPRITE_DragonCounter, DragonCount, 22046.496f, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR, LATE_LIG); // This draws the left number - It's texID changes depending of the counter.
}

void DrawDragonHUD()
{
    ScaleUI(uiscale::Align_Automatic);
    SetSpriteParam();

    DrawDragonCountHUD();

    ResetSpriteParam();
    ResetScaleUI();
}


//  Key HUD:

static NJS_TEXANIM TEXANIM_ChestKey[] = {
    { 0x20, 0x20, 0, 0, 0, 0, 0x100, 0x100, 26, 0x20 }, // ID 0 - TexID 26
    { 0x20, 0x20, 0, 0, 0, 0, 0x100, 0x100, 27, 0x20 }, // ID 1 - TexID 27
};

static NJS_SPRITE SPRITE_ChestKey = { { 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 0, &TEXLIST_TTObjects, TEXANIM_ChestKey };

void DrawKeyCountHUD()
{
    SetSpriteSettings();
    
    SPRITE_ChestKey.p.x = 592.0f;
    SPRITE_ChestKey.p.y = SpriteHeight_Key;
    
    if (HasKey == 0)
        return;
    
    else
        late_DrawSprite2D(&SPRITE_ChestKey, ArrayID, 22046.496f, NJD_SPRITE_ALPHA, LATE_LIG);
}

void DrawKeyHUD()
{
    ScaleUI(uiscale::Align_Automatic);
    SetSpriteParam();

    DrawKeyCountHUD();

    ResetSpriteParam();
    ResetScaleUI();
}