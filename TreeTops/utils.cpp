#include "pch.h"

//	Bools and code to check if certain mods are enabled / disabled:

bool HD_GUI = false;
bool DC_Conversion = false;
bool Lantern_Engine = false;
bool SA1_Cream = false;

void CheckActiveMods(const HelperFunctions& helperFunctions)
{
	HD_GUI = helperFunctions.Mods->find("sadx-hd-gui") != nullptr; // This needs to be called in the Init (or in a function that will be called in the Init like this), "Find" checks if the modID is present - Remember that != means "Not equal" (If HD_GUI is not nullptr)
	DC_Conversion = helperFunctions.Mods->find("sadx-dreamcast-conversion") != nullptr;
	
	Lantern_Engine = GetModuleHandle(L"sadx-dc-lighting") != nullptr;
	SA1_Cream = GetModuleHandle(L"CreamtheRabbit(SA1-Style)") != nullptr;
}

//	Necessary functions to make LoadBasicModel work - You need to have an extern "HelperFunctions HelperFunctionsGlobal;" in a header and also #include ModelInfo.h to this current file (or in pch.h) and add ModelInfo.cpp to your source files:

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


//  Necessary functions to make LoadLandTable work - You need to have an extern "HelperFunctions HelperFunctionsGlobal;" in a header, #include LandTableInfo.h to this current file (or in pch.h) and add LandTableInfo.cpp to your source files:

void LoadLandTable(LandTableInfo** info, const char* name, const HelperFunctions& helperFunctions, NJS_TEXLIST* texlist)
{
	std::string fullPath = "system\\landtables\\";
	fullPath = fullPath + name + ".sa1lvl";

	LandTableInfo* land = new LandTableInfo(helperFunctions.GetReplaceablePath(fullPath.c_str()));

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


//	Neccesary functions to make LoadChunkModel work and display-related chunk functions that are neeeded to correctly write a display code for the chunk object:

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


//	Necessary functions to make LoadObjectAnim work - You need to have an extern "HelperFunctions HelperFunctionsGlobal;" in a header and also #include AnimationFile.h to this current file (or in pch.h) and add AnimationFile.cpp to your source files:

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


//	Functions to make sprites render correctly:

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