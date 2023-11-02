#include "pch.h"

//  Stage Names:

void STAGENAMES_TreeTops()
{
    if (HD_GUI)
    {
        ReplaceTEX("AVA_STNAM", "TX_ST11", "StageNames", "HD_StageName_TreeTops-JP", 365041, 128, 16);
        ReplaceTEX("AVA_STNAM_E", "TX_ST11_e", "StageNames", "HD_StageName_TreeTops-EN", 10000419, 128, 16);
    }
    
    else
    {
        ReplaceTEX("AVA_STNAM", "TX_ST11", "StageNames", "SD_StageName_TreeTops-JP", 365041, 128, 16);
        ReplaceTEX("AVA_STNAM_E", "TX_ST11_e", "StageNames", "SD_StageName_TreeTops-EN", 10000419, 128, 16);
    }
}


//  TitleCards:

void TITLECARDS_TreeTops()
{
    std::string index = ModPath;

    if (HD_GUI)
    {
        index += "\\textures\\TitleCards_HD\\index.txt";
        const char* HD_Index = index.c_str();

        ReplacePVR("S_STAGE08", HD_Index);
        ReplacePVR("M_STAGE04", HD_Index);
        ReplacePVR("K_STAGE05", HD_Index);
        
        ReplacePVR("S_STAGE08_E", HD_Index);  
        ReplacePVR("M_STAGE04_E", HD_Index);
        ReplacePVR("K_STAGE05_E", HD_Index);
    }

    else
    {
        index += "\\textures\\TitleCards_SD\\index.txt";
        const char* SD_Index = index.c_str();

        ReplacePVR("S_STAGE08", SD_Index);
        ReplacePVR("M_STAGE04", SD_Index);
        ReplacePVR("K_STAGE05", SD_Index);
        
        ReplacePVR("S_STAGE08_E", SD_Index);       
        ReplacePVR("M_STAGE04_E", SD_Index);       
        ReplacePVR("K_STAGE05_E", SD_Index);

        ReplacePVR("S_STAGE08_DC", SD_Index);
        ReplacePVR("M_STAGE04_DC", SD_Index);
        ReplacePVR("K_STAGE05_DC", SD_Index);
        
        ReplacePVR("S_STAGE08_E_DC", SD_Index);        
        ReplacePVR("M_STAGE04_E_DC", SD_Index);        
        ReplacePVR("K_STAGE05_E_DC", SD_Index);
    }
}


//  Multiplayer Thumbnails:

void MULTITHUMBNAILS_TreeTops()
{
	ReplaceTEX("AVA_MULTI", "multistg0600", "MultiThumbnails", "Multi_TreeTops-S", 54926007, 128, 72);
	ReplaceTEX("AVA_MULTI", "multistg0602", "MultiThumbnails", "Multi_TreeTops-K", 71757015, 128, 72);
}


//  Stage Credits:

void STAGECREDITS_TreeTops()
{
    if (HD_GUI)
    {
        ReplaceTEX("ENDBG_SUPERSONIC_0", "ss_ev006", "StageCredits", "HD_StageCredits_TreeTops-S00", 366154, 256, 256);
        ReplaceTEX("ENDBG_SUPERSONIC_0", "ss_ev007", "StageCredits", "HD_StageCredits_TreeTops-S01", 366155, 256, 256);
        ReplaceTEX("ENDBG_TAILS_1", "t_ev015", "StageCredits", "HD_StageCredits_TreeTops-T00", 366141, 256, 256);
        ReplaceTEX("ENDBG_KNUCKLES_2", "k_ev021", "StageCredits", "HD_StageCredits_TreeTops-K00", 366070, 256, 256);
        ReplaceTEX("ENDBG_KNUCKLES_2", "k_ev022", "StageCredits", "HD_StageCredits_TreeTops-K01", 366071, 256, 256);
    }

    else if (DC_Conversion)
    {
        ReplaceTEX("ENDBG_SUPERSONIC_0", "ss_ev006", "StageCredits", "DC_StageCredits_TreeTops-S00", 366154, 256, 256);
        ReplaceTEX("ENDBG_SUPERSONIC_0", "ss_ev007", "StageCredits", "DC_StageCredits_TreeTops-S01", 366155, 256, 256);
        ReplaceTEX("ENDBG_TAILS_1", "t_ev015", "StageCredits", "DC_StageCredits_TreeTops-T00", 366141, 256, 256);
        ReplaceTEX("ENDBG_KNUCKLES_2", "k_ev021", "StageCredits", "DC_StageCredits_TreeTops-K00", 366070, 256, 256);
        ReplaceTEX("ENDBG_KNUCKLES_2", "k_ev022", "StageCredits", "DC_StageCredits_TreeTops-K01", 366071, 256, 256);
    }

    else
    {
        ReplaceTEX("ENDBG_SONIC_2", "sonic_22", "StageCredits", "DX_StageCredits_TreeTops-S00", 366021, 512, 512);
        ReplaceTEX("ENDBG_TAILS_1", "tails_19", "StageCredits", "DX_StageCredits_TreeTops-T00", 366145, 512, 512);
        ReplaceTEX("ENDBG_KNUCKLES_2", "knuckles_24", "StageCredits", "DX_StageCredits_TreeTops-K00", 366073, 512, 512);
    }
}


//	Sound Test Entries:

SoundTestEntry SoundTestEntry_TreeTops = { "Tree Tops:  Spyro the Dragon", 81 };


//  Init Graphics:

void INIT_Graphics()
{
    STAGENAMES_TreeTops();
    TITLECARDS_TreeTops();
    MULTITHUMBNAILS_TreeTops();
    STAGECREDITS_TreeTops();

    Soundtest_ActionStage[12] = SoundTestEntry_TreeTops;
}