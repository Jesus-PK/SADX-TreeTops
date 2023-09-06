#pragma once

//	Bools and code to check if certain mods are enabled / disabled & Mod Loader API version check:

extern bool HD_GUI;
extern bool DC_Conversion;
extern bool HUD_Plus;
extern bool Lantern_Engine;

extern bool DC_HudTweaks;

void CheckActiveMods(const HelperFunctions& helperFunctions);

void CheckModLoaderVersion(const HelperFunctions& helperFunctions);


//	Functions to load/replace models and animations:

ModelInfo* LoadBasicModel(const char* name);

void LoadLandTable(LandTableInfo** info, const char* name, const HelperFunctions& helperFunctions, NJS_TEXLIST* texlist);

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


//	Init modes for the first field of an object in the custom objectlist:

enum INITMODEMD : Sint8
{
	IM_MWK = 0x1,
	IM_TWK = 0x2,
	IM_FWK = 0x4,
	IM_AWK = 0x8
};


//	ssAtributes for the third field of an object in the custom objectlist:

enum ITEMATTR
{
	ITEM_ATTR_DIST = 0x1,
	ITEM_ATTR_LOAD = 0x2,
	ITEM_ATTR_ONCE = 0x4,
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