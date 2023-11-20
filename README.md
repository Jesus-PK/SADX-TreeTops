# SADX - Tree Tops

A level port of Tree Tops from Spyro 1, replaces Sky Deck.

This mod features the original level geometry and skybox with vertex colors alongside tons of custom coded objects, but also:
* Fully fledged SET and CAM layouts for Sonic, Tails and Knuckles.
* Full GUI support: Titlecards, stage names, mission cards, credits images, multiplayer thumbnails... All with full EN / JP support and SD / HD variants depending if you are using HD GUI or not.
* Custom level objectives, including new A / B missions requirements.
* For more details, please check the [GameBanana](https://gamebanana.com/mods/467594) page of this mod.

## Overview:

You can find on this repository both the code I wrote for this mod and all playable versions that I've released so far.

The purpose of this repository is to backup my code in the cloud and to serve as public resource for other modders, I think some of this code might serve as helpful examples for other people working on level mods.

This repository also acts as a mean to archive previous releases of this mod since in GameBanana I only offer the latest playable release.

## Repository Notes:

Cloning this repository should result in a buildable .dll project of this mod without any additional tweaks needed, though there's a few things worth noting:

* Make sure that you are compiling in **x86 mode**.
* The project uses custom include paths, the project settings already have setup the necessary additional include directories in **Project > Properties > C/C++ > General > Additional Include Directories** for both **Release - x86** and **Debug - x86** (All Configurations - Win32) - These are the include directories:

  * `$(ProjectDir)`
  * `$(ProjectDir)config`
  * `$(ProjectDir)lantern`
  * `$(ProjectDir)objects`
  * `$(ProjectDir)programming`

* The files in the `config` folder are the neccesary files to read a configuration form (`IniFile.cpp`, `IniFile.hpp`, `TextConv.cpp`, `TextConv.h`, `Utils.hpp`) - You can get them [HERE](https://github.com/sonicretro/mod-loader-common/tree/master/ModLoaderCommon).

* The files in the `lantern` folder are the Lantern Engine API necessary files (`lanternapi.h` and `sadx-dc-lighting.lib`)

* The files in the `programming` folder are the same ones encountered in the `programming` folder that is shipped with the SADX Mod Loader. I copy these files manually at the time of creating my project and I also update them manually, so remember that you might need to replace them with "fresh" ones from the latest Mod Loader release from time to time when those files get updated.

* Adding to this, the following files need to be added to the existing **Source Files** of this project via the Project Properties window (**Source Files > Right Click > Add Existing Item**):
  * `AnimationFile.cpp`
  * `LandTableInfo.cpp`
  * `ModelInfo.cpp`
  * `Trampoline.cpp`
  * `IniFile.cpp`
  * `TextConv.cpp`
    * Remember that you also need to edit them afterwards (change `#include "stdafx.h"` for `#include "pch.h"`)
    * And in the case of `IniFile.cpp`, you also need to add this line below the `#includes` to get rid of some warnings that prevent building the mod: `#pragma warning(disable:4996)`

* Regarding the Lantern API, these are the few extra settings that have been applied to the project to make everything work correctly:
  * **Linker > General > Additional Library Directories:**
    * `$(ProjectDir)lantern`
  * **Linker > Input > Additional Dependencies:**
    * `sadx-dc-lighting.lib`
  * **Linker > Input > Delay Loaded DLLs**
    * `sadx-dc-lighting.dll`

* As an extra, I have the project set it up so it automatically copies the new .DLLs on the mod folder (so no need to copypaste manually) - The target path needs to be adjusted depending on your game's path:
  * **Build Events > Post-Build Event > Command Line**
    * `xcopy "$(SolutionDir)Release\*.dll" "D:\Juegos\Retail\SONICADVENTUREDX\mods\Tree Tops\*.dll" /Y`

As always, it's recommended to make your own project from scratch and just use these functions and annotations you see in here as a guide / example to learn what they do instead of just cloning the repository or copypasting functions. I say this because some of these things might only apply to this mod in particular instead of a general level due to using specific nomenclatures / tweaks or they might just be wrong / obsolete as time goes by.

If you are looking for further help and troubleshooting, feel free to check out the [X-Hax Discord](https://discord.gg/gqJCF47).
