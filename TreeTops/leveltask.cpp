#include "pch.h"
#include "hud.h"
#include "ramps.h"
#include "o_skybox.h"

//	Custom LevelTask - Custom code for Sky Deck leveltask function (0x5F02E0).
//	As a workaround for the Lantern Engine API issues, I trampoline the original leveltask and then if Lantern is active > I call the original function once and disable blending (not needed but just in case).
//	This lets Lantern load the PL / SL files (since in Sky Deck it does it through the leveltask), and then I can just replace those files like I usually do.

static Trampoline* Rd_Skydeck_t = nullptr;

void RD_TreeTops(task* tp)
{
	auto twp = tp->twp;

	if (!twp->mode)
	{
		if (Lantern_Engine)
		{
			((decltype(RD_TreeTops)*)Rd_Skydeck_t->Target())(tp); // This will call the original function once, I do this only if Lantern is enabled so Lantern can apply it's Trampoline to load the PL / SL files for Sky Deck.
			set_shader_flags(ShaderFlags_Blend, false); // Since this above would've activated blending (though with a factor of 0, no so visual changes) - Just in case I desactive it via a function of the Lantern API.
		}
		
		ADXTaskInit();
		PlayMusic(MusicIDs_skydeck1);

		CreateElementalTask(2, 2, ANIM_WoodenRamp);
		CreateElementalTask(2, 2, ANIM_GrassRamp);

		SETVIEWDATA_TreeTops(); // I think I don't need to call this every frame anymore, I believe the problem I used to have in Gnorc Cove was the Skybox task setting up their own values and overriding mine. This shouldn't be an issue anymore since I do custom RD and BG tasks.

		twp->mode++;
	}

	if (CurrentCharacter == Characters_Tails)
		DrawDragonHUD();

	DrawKeyHUD();
}


//	Level Destructor - I funchook the level destructor function so I can reset the rescued dragons counter and other counters only when exiting, completing the level or SA2Restarting, this saves the counter when dying or SA1Restarting.

static FunctionHook<void, int>RunLevelDestructor_t(RunLevelDestructor);

void __cdecl RunLevelDestructor_r(int heap)
{
	if (heap == 0 && CurrentLevel == LevelIDs_SkyDeck)
	{
		DragonCount = 0;
		HasKey = 0;
	}

	return RunLevelDestructor_t.Original(heap);
}


//	Disable Tails AI Race (Currently not compatible with CharSel mod, using BetterTailsAI does override that and makes it work again though):

FunctionHook<void, __int16, __int16, __int16> LoadTailsOpponent_t(0x47D940);

void LoadTailsOpponent_r(__int16 character, __int16 loop, __int16 level)
{
	if (CurrentLevel == LevelIDs_SkyDeck)
		return;

    else
		return LoadTailsOpponent_t.Original(character, loop, level);
}


//	Disable Tails flight camera adjustment:

//	Basically this function is called on every Tails level except Casinopolis, what it does is that when you fly as Tails, it will swap the CAM mode for a Relative3 Knuckles CAM (and it will stick afterwards if there was no collider).
//	This overrides current CAM mode / collider you are in, so making this function not run in Sky Deck makes it so Tails still follows the current CAM mode while flying.
//	Currently this is only a hack with WriteCall, it doesn't work in Multiplayer and other mod can't do the same for other level - So this is pending an update.
//	I basically make the "original" code run if the level ISN'T Sky Deck, else it will return (making the function not run and getting rid of that):

void CameraSetEventCameraFunc_Hack(CamFuncPtr fnCamera, Sint8 ucAdjustType, Sint8 scCameraDirect)
{
	if (CurrentLevel != LevelIDs_SkyDeck)
		CameraSetEventCameraFunc(fnCamera, ucAdjustType, scCameraDirect);
}


//	Event Cutscene Fixes:

//	I discovered that Knux cutscene after finishing Sky Deck for the first time results in him dying (if you don't skip it) and literally softlocking the game + breaking your savefile...
//	So yeah, this is just a simple WriteCall with this function below to set a particular position for Knux at the start of the event (so he doesn't fall to the void). On this particular one, the CAM works great, so no need for tweaking that for now.

void EV0095_PositionFix(task* tp, float x, float y, float z) // The arguments in here need to be the same as EV_SetPos (check them on IDA)
{
    EV_SetPos(tp, 1228.0f, 12.0f, -692.0f); // Just mentioning the task as tp is enough in here, since we are just replacing the line that does this in the event. So the rest of the vanilla code handles the rest.
}


//	Init LevelTask:

void INIT_LevelTask()
{
	Rd_Skydeck_t = new Trampoline(0x005F02E0, 0x005F02E5, RD_TreeTops); // Init Level Task Trampoline.
	ScrollMasterList[LevelIDs_SkyDeck] = BG_TreeTops; // Skybox Task.
	
	RunLevelDestructor_t.Hook(RunLevelDestructor_r); // Init Level Destructor Trampoline.
	
	LoadTailsOpponent_t.Hook(LoadTailsOpponent_r); // Remove Tails Race AI.
	
	WriteCall((void*)0x45EE82, CameraSetEventCameraFunc_Hack); // Remove Tails flight CAM adjustment.
	
	WriteCall((void*)0x689172, EV0095_PositionFix); // Fix Knuckles Sky Deck cutscene.
}