# SADX - Tree Tops

![TreeTops_Thumbnail](https://images.gamebanana.com/img/ss/mods/64fb56666155f.jpg)

## Overview:

This mod brings a fully fledged level port of Tree Tops from Spyro 1 into SADX, replacing Sky Deck.

You can find more details about this mod in [**GameBanana**](https://gamebanana.com/mods/467594).

**Features:**
* The original level geometry, skybox and objects with their vertex colors directly ripped from the game by me. With many touch-ups added to improve the overall gameplay experience.
* Complete SET and CAM layouts for every character featured in the level, all of them including the same amount of Rings in each level layout as amount of Gems there are to collect on their original counterparts. Just like in the original Spyro game!
* A lot of custom coded objects! Breakable chest, the exit portal, a buckload amount of dragons...
* Custom palette lightning, so it's recommended to use Lantern Engine alongside this mod.
* Custom A / B / C mission requirements, perfect if you want to fully complete these levels from a fresh savefile.
* Custom GUI elements such as titlecards, stage nameplates, mission cards, credits images and multiplayer thumbnails! All of them having full English and Japanese support alongside SD and HD quality textures depending if you are using HD GUI or not.
* A lot of work and care to ensure the best posible gameplay experience, alongside tons of tweaks through code to improve compatibility alongside other mods.

## Compatibility Notes:
* This mod automatically disables Sky Deck in Dreamcast Conversion, so you don't need to manually disable anything from that mod.
* There's a minor mod order issue with Hill Top, so if you play with it enabled, be sure that you load Spyro Triple Pack **under** Hill Top. That'll fix it and not affect either of the mods negatively.
* There's a minor graphic issue with Character Select that only happens Tails version of this level, if you play with this mod enabled you'll see the Sonic race AI spawn (which is disabled). This won't affect gameplay.
* Multiplayer support is currently limited. It can be playable but some things might not work as intended for the time being.
* For any other issues, it's always recommended to load this mod on the bottom of the list. If that doesn't help, you can also use the [**Issues**](https://github.com/Jesus-PK/SADX-TreeTops/issues) tab or [**GameBanana**](https://gamebanana.com/mods/467594) page to report any issues.

## Repository Notes:

This repository hosts both the code and playable versions of this mod. You can find them in the [**Releases**](https://github.com/Jesus-PK/SADX-TreeTops/releases) tab or [**GameBanana**](https://gamebanana.com/mods/467594) page.

Cloning this repository should result in a buildable .dll project of this mod without any additional tweaks needed, though there's a few things worth noting:

* Make sure that you are compiling in **x86 mode**.
* The project uses custom include paths, the project settings already have setup the necessary additional include directories in **Project > Properties > C/C++ > General > Additional Include Directories** for both **Release - x86** and **Debug - x86** (All Configurations - Win32) - These are the include directories:

  * `$(ProjectDir)`
  * `$(ProjectDir)config`
  * `$(ProjectDir)lantern`
  * `$(ProjectDir)objects`
  * `$(ProjectDir)programming`

* The files in the `config` folder are the neccesary files to read a configuration form (`IniFile.cpp`, `IniFile.hpp`, `TextConv.cpp`, `TextConv.h`, `Utils.hpp`) - You can get them [**HERE**](https://github.com/sonicretro/mod-loader-common/tree/master/ModLoaderCommon).

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

If you are looking for further help and troubleshooting, feel free to check out the [**X-Hax Discord**](https://discord.gg/gqJCF47).
