#pragma once

//	Macros:

#define ReplaceTEX(pvm, tex_name, folder, png_name, gbix, width, height) HelperFunctionsGlobal.ReplaceTexture(pvm, tex_name, (std::string(ModPath) + "\\textures\\" folder "\\" png_name ".png").c_str(), gbix, width, height);
#define ReplaceBIN(a, b) HelperFunctionsGlobal.ReplaceFile("system\\" a ".BIN", "system\\" b ".BIN");
#define ReplacePVR(a, b) HelperFunctionsGlobal.ReplaceFile("system\\" a ".PVR", b);


//	Counters:

extern bool HasKey;
extern uint8_t DragonCount;


//	Bools and code to check if certain mods are enabled / disabled & Mod Loader API version check:

extern bool HD_GUI;
extern bool DC_Conversion;
extern bool HUD_Plus;
extern bool Lantern_Engine;

extern bool DC_HudTweaks;

void CheckActiveMods();


//	Expand Draw Queue Memory Pool (Applies to the entire game):

void ExpandDrawQueueMemoryPool();


//	Functions to load/replace models and animations:

ModelInfo* LoadBasicModel(const char* name);

void LoadLandTable(LandTableInfo** info, const char* name, NJS_TEXLIST* texlist);

ModelInfo* LoadChunkModel(const char* name);

inline AnimationFile* LoadANM(const char* type, const char* name);
AnimationFile* LoadObjectAnim(const char* name);


//	Chunk-display related functions:

void SetupWorldMatrix();
void SetupChunkModelRender();
void ResetChunkModelRender();

void njCnkAction(NJS_ACTION* action, float frame);


//	Sprite-rendering related functions:

void SetSpriteParam();
void ResetSpriteParam();
void ScaleUI(uiscale::Align type);
void ResetScaleUI();


//	CollisionShapes enum to be able to write the name of the collision instead of the HEX number:

enum CollisionShapes
{
	CollisionShape_Sphere,		// A		|	(Radius)
	CollisionShape_Cylinder,	// A, B		|	(Radius, Height)
	CollisionShape_Cylinder2,	// A, B		|	(Radius, Height)
	CollisionShape_Cube,		// A, B, C	|	(XYZ Scale)
	CollisionShape_Cube2,		// A, B, C	|	(XYZ Scale - Support YZ rotation)
	CollisionShape_Capsule = 6,	// A, B		|	(Radius, Height - Support XYZ rotation - Cylinder with rounded ends that can't be walked on),
	CollisionShape_PushWall = 9	// A, B, C	|	(Width, Height, Power - A wall that pushes the player - Support Y rotation)
};


//	ChildTaskSet (CTS) struct and FunctionPointer for custom CTS and replacements:

struct childtaskset
{
	void(__cdecl* exec)(task*);
	Uint16 initmode;
	Sint16 flag;
	Angle3 ang_offset;
	NJS_POINT3 pos_offset;
	void* ptr;
};

FunctionPointer(void, CreateChildrenTask, (childtaskset* ctsp, task* tp), 0x40B9D0);


//	FunctionPointer for IsThisTaskPlayer function:

FunctionPointer(Bool, IsThisTaskPlayer, (task* tp), 0x441AD0);


//	DataArray for all the entries in Sound Test - Action Stage:

DataArray(SoundTestEntry, Soundtest_ActionStage, 0x7EFBE0, 40);