# SADX - Tree Tops

A level port of Tree Tops from Spyro 1.

## Overview:

This repository only hosts the code I used for this mod. If you are looking for the latest playable release, you can download it from [GameBanana - Tree Tops](https://youtu.be/TxK2Sj5fj_c).

The purpose of this repository is to backup my code on the cloud and to serve as public resource for other modders, I think some of this code might serve as helpful examples for other people working on level mods.

## Repository Notes:

Cloning this repository should result in a buildable .dll project of this mod without any additional tweaks needed, though there's a few things worth noting:

* Make sure that you are compiling in **x86 mode**.
* The project uses custom include paths, the project settings already have setup the necessary additional include directories in **Project > Properties > C/C++ > General > Additional Include Directories** for both **Release - x86** and **Debug - x86** (All Configurations - Win32) - These are the include directories:

  * `$(ProjectDir)`
  * `$(ProjectDir)objects`
  * `$(ProjectDir)programming`
  * `$(ProjectDir)lantern`

* The files in the `programming` folder are the same ones encountered in the `programming` folder that is shipped with the SADX Mod Loader. I copy these files manually at the time of creating my project, so remember that you might need to replace them with "fresh" ones from the latest Mod Loader release.
* The files in the `lantern` folder are the Lantern Engine API necessary files (`lanternapi.h` and `sadx-dc-lighting.lib`)

  * Adding to this: `AnimationFile.cpp`, `LandTableInfo.cpp`, `ModelInfo.cpp` and `Trampoline.cpp` have been edited (changed `#include "stdafx.h"` for `#include "pch.h"`) since I needed to add them to the **Source Files** of this project for some specific functions I used (**Source Files > Right Click > Add Existing Item**).

* Regarding the Lantern API, these are the few extra settings that have been applied to the project to make everything work correctly:
  * **Linker > General > Additional Library Directories:**
    * `$(ProjectDir)lantern`
  * **Linker > Input > Additional Dependencies:**
    * `sadx-dc-lighting.lib`
  * **Linker > Input > Delay Loaded DLLs**
    * `sadx-dc-lighting.dll`

* As an extra, I have the project set it up so it automatically copies the new .DLLs on the mod folder (so no need to copypaste manually) - The target path needs to be adjusted depending on your game's path:
  * **Build Events > Post-Build Event > Command Line**
    * `xcopy "$(SolutionDir)Release\*.dll" "D:\Juegos\Retail\SADX\SonicAdventureDX\mods\Tree Tops\*.dll" /Y`

If you are starting out, it's recommendable making your own project from scratch and use these functions and annotations as a guide / example to learn what they do instead of cloning the repository (since a lot of things are tailored in particular for my mod, so they might not apply on a general way).

It's also recommended to check out the [X-Hax Discord](https://discord.gg/gqJCF47) if you are looking for further help and troubleshooting.
