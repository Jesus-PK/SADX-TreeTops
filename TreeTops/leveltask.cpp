#include "pch.h"
#include "hud.h"
#include "ramps.h"

//	Custom LevelTask - Custom code for Sky Deck leveltask function (0x5F02E0).
//	Due to Lantern Engine hooking SkyDeck leveltask for the special effects in this level, I used RoundMasterList instead of WriteJump to call my custom OBJ, this made my changes always work regardless of mod order:

void RD_TreeTops(task* tp)
{
	auto twp = tp->twp;

	if (!twp->mode)
	{
		ADXTaskInit();
		PlayMusic(MusicIDs_skydeck1);

		CreateElementalTask(2, 2, ANIM_WoodenRamp);
		CreateElementalTask(2, 2, ANIM_GrassRamp);

		SETVIEWDATA_TreeTops(); // I think I don't need to call this every frame anymore, I believe the problem I used to have in Gnorc Cove was the Skybox task setting up their own values and overriding mine. This shouldn't be an issue anymore since I do custom RD and BG tasks.
		
		EnableFreeCamera(1); // Forces FreeCam on level start, pending removal.

		twp->mode++;
	}

	if (CurrentCharacter == Characters_Tails)
		DrawDragonHUD();

	DrawKeyHUD();
}


//	Event Cutscene Fixes:

//	I discovered that Knux cutscene after finishing Sky Deck for the first time results in him dying (if you don't skip it) and literally softlocking the game + breaking your savefile...
//	So yeah, this is just a simple WriteCall with this function below to set a particular position for Knux at the start of the event (so he doesn't fall to the void). On this particular one, the CAM works great, so no need for tweaking that for now.

void EV0095_PositionFix(task* tp, float x, float y, float z) // The arguments in here need to be the same as EV_SetPos (check them on IDA)
{
    EV_SetPos(tp, 1228.0f, 12.0f, -692.0f); // Just mentioning the task as tp is enough in here, since we are just replacing the line that does this in the event. So the rest of the vanilla code handles the rest.
}


//	Lantern Engine API - Custom Palette and Light files.
//	These functions are custom (any name works), we need to make an individual function for every file we are gonna register down below on the Lantern API:

const char* RegisterLevelPalette(int32_t level, int32_t act)
{
	if (level == LevelIDs_SkyDeck)
		return HelperFunctionsGlobal.GetReplaceablePath("system\\PL_TreeTops.BIN"); // This will override the name used by Lantern Engine.
	
	else
		return nullptr; // Returning null will let Lantern Engine choose the name.
}

const char* RegisterLevelLight(int32_t level, int32_t act)
{
	if (level == LevelIDs_SkyDeck)
		return HelperFunctionsGlobal.GetReplaceablePath("system\\SL_TreeTops.BIN");
	
	else
		return nullptr;
}


//	Load custom Lantern Engine files and error message:

static int LanternErrorMessageTimer = 500;

void LANTERN_TreeTops()
{
	if (Lantern_Engine) // We check if Lantern Engine is loaded, this is important because if we try to call an API function without doing this check, the game will crash.
	{
		pl_load_register(RegisterLevelPalette); // This is an API function from Lantern Engine, it registers a custom PL file we specified in the function we made (RegisterLevelPalette)
		sl_load_register(RegisterLevelLight); // This is an API function from Lantern Engine, it registers a custom SL file we specified in the function we made (RegisterLevelLight)
	}
}

void LANTERNERROR_TreeTops()
{
	if (CurrentLevel == LevelIDs_SkyDeck && !Lantern_Engine && LanternErrorMessageTimer)
	{
		SetDebugFontSize(Uint16(10.0f * (float)VerticalResolution / 480.0f));
		SetDebugFontColor(0xFFBFBFBF);

		DisplayDebugString(NJM_LOCATION(2, 1), "Failed to detect Lantern Engine mod.");
		DisplayDebugString(NJM_LOCATION(2, 2), "The objects in this level will have no lighting.");
		DisplayDebugString(NJM_LOCATION(2, 3), "Please install and enable Lantern Engine for correct visuals.");

		LanternErrorMessageTimer--;
	}
}


//	Level Destructor - I trampoline the level destructor function so I can reset the rescued dragons counter and other counters only when exiting, completing the level or SA2Restarting, this saves the counter when dying or SA1Restarting.
//	Originally I funchooked this, but doing that causes a weird texture issue with DC Conversion in Hot Shelter and made this mod crash with Jet Set Sonk (since it did the same workaround).
//	Basically funchook can rarely not work correctly for some functions, this seems to be one of them so it's better to just trampoline it.

//	To make these functions work correctly, it's necessary to #include "Trampoline.h" to this current file (or in pch.h) and to add "Trampoline.cpp" to your source files.
//	Also remember to change #include "stdafx.h" for #include "pch.h" and to change #include <MemAccess.h> for #include "MemAccess.h" (if you have your programming folder files alongside the others, shouldn't be necessary if you have them on another include location:

static Trampoline* RunLevelDestructor_t = nullptr;

void __cdecl RunLevelDestructor_r(int heap)
{
	if (heap == 0 && CurrentLevel == LevelIDs_SkyDeck)
	{
		DragonCount = 0;
		HasKey = 0;
	}

	FunctionPointer(void, origin, (int heap), RunLevelDestructor_t->Target());
	origin(heap);
}

void INIT_LevelDestructor()
{
	RunLevelDestructor_t = new Trampoline((intptr_t)RunLevelDestructor, (intptr_t)RunLevelDestructor + 0x6, RunLevelDestructor_r);
}


//	Disable Tails AI Race:

void LoadTailsOpponent_r(__int16 character, __int16 loop, __int16 level);
FunctionHook <void, __int16, __int16, __int16> LoadTailsOpponent_t(0x47D940, LoadTailsOpponent_r);

void LoadTailsOpponent_r(__int16 character, __int16 loop, __int16 level)
{
	if (CurrentLevel == LevelIDs_SkyDeck)
		return;

    else
		return LoadTailsOpponent_t.Original(character, loop, level);
}