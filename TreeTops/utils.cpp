#include "pch.h"

//	Counters:

bool HasKey = 0;
uint8_t DragonCount{ 0 };


//	Bools and code to check if certain mods or config options are enabled:

bool HD_GUI = false;
bool Lantern_Engine = false;
bool DC_Conversion = false;
bool HUD_Plus = false;

bool DC_HudTweaks = false; // Checks if Dreamcast Conversion "Adjust HUD Position" config option is enabled.

void CheckDCConfig()
{
	// To not check for DC Conv twice, I use a different identifier via auto (due to the bool I had not being compatible with reading the config) and then after I check for the mod, I simply return "true" to my original bool if the game finds it enabled.
	
	auto DC_Mod = HelperFunctionsGlobal.Mods->find("sadx-dreamcast-conversion");

	if (DC_Mod)
	{
		DC_Conversion = true;

		const IniFile* DC_Config = new IniFile(std::string(DC_Mod->Folder) + "\\config.ini"); // Allocates the .ini file, we search for it from DC Conv folder.

		DC_HudTweaks = DC_Config->getBool("Branding", "HUDTweak", true); // We specify the bool we want to check from the config.ini.

		delete DC_Config; // Since we don't need the .ini anymore, we delete it - Basically if you ever use "new", you will have to use "delete" too.
	}
}

void CheckActiveMods()
{
	HD_GUI = HelperFunctionsGlobal.Mods->find("sadx-hd-gui") != nullptr; // This needs to be called in the Init (or in a function that will be called in the Init like this), "Find" checks if the modID is present - Remember that != means "Not equal" (If HD_GUI is not nullptr)
	Lantern_Engine = HelperFunctionsGlobal.Mods->find("sadx.sf94.lantern-engine") != nullptr;
	CheckDCConfig(); // I call here the DC Conversion check + it's config option check to group it alongside everything else.
	
	HUD_Plus = GetModuleHandle(L"sadx-hud-plus") != nullptr;
}

void CheckBASS()
{
	if (HelperFunctionsGlobal.LoaderSettings->EnableBassMusic == false)
	{
		MessageBox(WindowHandle,
			L"ERROR! BASS for Music is turned off.\n\nThe music of this level won't play correctly.\n\nPlease exit the game, enable BASS for Music, then try again.",
			L"Tree Tops: BASS Error", MB_OK | MB_ICONERROR);
	}
}


//	Expand Draw Queue Memory Pool (Applies to the entire game):

void ExpandDrawQueueMemoryPool()
{
	WriteData((Uint32*)0x408643, 0x100000ui32);
	WriteData((Uint32*)0x40864D, 0x100000ui32);
	WriteData((Uint32*)0x40866B, 0x100000ui32);
}


//	Function for loading Basic Models - You need to have an extern "HelperFunctions HelperFunctionsGlobal;" in a header and also #include ModelInfo.h to this current file (or in pch.h) and add ModelInfo.cpp to your source files:

ModelInfo* LoadBasicModel(const char* name)
{
    PrintDebug("[TreeTops] Loading basic model: %s... ", name);

    std::string fullPath = "system\\models\\";
    fullPath = fullPath + name + ".sa1mdl";

    ModelInfo* mdl = new ModelInfo(HelperFunctionsGlobal.GetReplaceablePath(fullPath.c_str()));

    if (mdl->getformat() != ModelFormat_Basic)
    {
        PrintDebug("Failed!\n");

        delete mdl;
        return nullptr;
    }

    PrintDebug("Done!\n");

    return mdl;
}


//  Function for loading LandTables - You need to have an extern "HelperFunctions HelperFunctionsGlobal;" in a header, #include LandTableInfo.h to this current file (or in pch.h) and add LandTableInfo.cpp to your source files:

void LoadLandTable(LandTableInfo** info, const char* name, NJS_TEXLIST* texlist)
{
	std::string fullPath = "system\\landtables\\";
	fullPath = fullPath + name + ".sa1lvl";

	LandTableInfo* land = new LandTableInfo(HelperFunctionsGlobal.GetReplaceablePath(fullPath.c_str()));

	if (land->getlandtable() == nullptr)
	{
		delete land;
		*info = nullptr;
	}
	
	else
	{
		if (texlist != nullptr)
		{
			land->getlandtable()->TexList = texlist;
		}

		*info = land;
	}
}


//	Function for loading Chunk Models:

ModelInfo* LoadChunkModel(const char* name)
{
	PrintDebug("[TreeTops] Loading chunk model: %s... ", name);

	std::string fullPath = "system\\models\\";
	fullPath = fullPath + name + ".sa2mdl";

	ModelInfo* mdl = new ModelInfo(HelperFunctionsGlobal.GetReplaceablePath(fullPath.c_str()));

	if (mdl->getformat() != ModelFormat_Chunk)
	{
		PrintDebug("Failed!\n");
		
		delete mdl;
		return nullptr;
	}

	PrintDebug("Done!\n");
	
	return mdl;
}


//	Functions for rendering Chunk Models:

void SetupWorldMatrix() // SetupChunkModelRender calls SetupWorldMatrix, that's why we need this function dependency.
{
    ProjectToWorldSpace();
    Direct3D_SetWorldTransform();
    memcpy(_nj_current_matrix_ptr_, &ViewMatrix, sizeof(NJS_MATRIX));
}

void SetupChunkModelRender()
{
    SetupWorldMatrix();
    Direct3D_SetChunkModelRenderState();
}

void ResetChunkModelRender()
{
    Direct3D_ResetWorldTransform();
    Direct3D_UnsetChunkModelRenderState();

	CnkRestoreSpecular(); // This is needed to fix an issue regarding specular lightning on chunk models messing up other objects lightning (happens when not using Lantern Engine)
}

// FunctionPointer for _njCnkDrawModel, needed for the njCnkAction function which is necessary to correctly write the display code of an animated chunk object:

FunctionPointer(void, _njCnkDrawModel, (NJS_CNK_MODEL* a3), 0x789750);

void njCnkAction(NJS_ACTION* action, float frame)
{
	DisplayAnimationFrame(action, frame, (QueuedModelFlagsB)0, 0, (void(__cdecl*)(NJS_MODEL_SADX*, int, int))_njCnkDrawModel);
}


//	Functions for loading Animations - You need to have an extern "HelperFunctions HelperFunctionsGlobal;" in a header and also #include AnimationFile.h to this current file (or in pch.h) and add AnimationFile.cpp to your source files:

inline AnimationFile* LoadANM(const char* type, const char* name)
{	
	std::string fullPath = "system\\models\\";
	fullPath = fullPath + name + ".saanim";

	AnimationFile* temp = new AnimationFile(HelperFunctionsGlobal.GetReplaceablePath(fullPath.c_str()));

	if (temp->getmodelcount())
	{
		PrintDebug("Done!\n");
		
		return temp;
	}
	
	else
	{
		PrintDebug("Failed!\n");
		
		delete temp;
		return nullptr;
	}
}

AnimationFile* LoadObjectAnim(const char* name)
{
	PrintDebug("[TreeTops] Loading object animation: %s... ", name);
	
	return LoadANM("anims", name);
}


//	Functions for rendering Sprites:

void SetSpriteParam()
{
	njColorBlendingMode(NJD_SOURCE_COLOR, NJD_COLOR_BLENDING_SRCALPHA);
	njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_INVSRCALPHA);
	SetMaterial(1.0f, 1.0, 1.0f, 1.0f);
}

void ResetSpriteParam()
{
	ResetMaterial();
	njColorBlendingMode(NJD_SOURCE_COLOR, NJD_COLOR_BLENDING_SRCALPHA);
	njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_INVSRCALPHA);
}

void ScaleUI(uiscale::Align type)
{
	HelperFunctionsGlobal.PushScaleUI((uiscale::Align)(type), false, 1.0f, 1.0f);
}

void ResetScaleUI()
{
	HelperFunctionsGlobal.PopScaleUI();
}