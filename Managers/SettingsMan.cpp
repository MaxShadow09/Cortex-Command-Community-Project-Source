#include "SettingsMan.h"
#include "ConsoleMan.h"
#include "PostProcessMan.h"
#include "RTEManagers.h"

extern bool g_ResetActivity;

namespace RTE {

	const std::string SettingsMan::m_ClassName = "Settings";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void SettingsMan::Clear() {
		m_SettingsNeedOverwrite = false;

		m_ForceVirtualFullScreenGfxDriver = false;
		m_ForceOverlayedWindowGfxDriver = false;
		m_ForceNonOverlayedWindowGfxDriver = false;

		m_SoundPanningEffectStrength = 0.6F;
		//////////////////////////////////////////////////
		//TODO These need to be removed when our soundscape is sorted out. They're only here temporarily to allow for easier tweaking by pawnis.
		m_ListenerZOffset = 0;
		m_MinimumDistanceForPanning = 50.0F;
		//////////////////////////////////////////////////

		m_FlashOnBrainDamage = true;
		m_BlipOnRevealUnseen = true;
		m_EndlessMode = false;
		m_EnableHats = false;

		m_NetworkServerName = "127.0.0.1:8000";
		m_PlayerNetworkName = "Dummy";
		m_UseNATService = false;
		m_NATServiceAddress = "127.0.0.1:61111";
		m_NATServerName = "DefaultServerName";
		m_NATServerPassword = "DefaultServerPassword";
		m_ClientInputFps = 30;
		m_ServerTransmitAsBoxes = true;
		m_ServerBoxWidth = 32;
		m_ServerBoxHeight = 44;
		m_ServerUseHighCompression = true;
		m_ServerUseFastCompression = false;
		m_ServerHighCompressionLevel = 10;
		m_ServerFastAccelerationFactor = 1;
		m_ServerUseInterlacing = false;
		m_ServerEncodingFps = 30;
		m_ServerSleepWhenIdle = false;
		m_ServerSimSleepWhenIdle = false;

		m_AllowSavingToBase = false;
		m_ShowForeignItems = true;
		m_ShowMetaScenes = false;

		m_RecommendedMOIDCount = 240;
		m_PreciseCollisions = true;

		m_PlayIntro = true;
		m_ToolTips = true;
		m_DisableLoadingScreen = true;
		m_LoadingScreenReportPrecision = 100;
		m_PrintDebugInfo = false;
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int SettingsMan::Create(Reader &reader, bool checkType, bool doCreate) {
		if (reader.IsOK()) {
			return Serializable::Create(reader, checkType);
		}

		// Couldn't find the settings file, so create a new one with all the good defaults!
		Writer writer("Base.rte/Settings.ini");
		RTEAssert(writer.WriterOK(), "After failing to open the Base.rte/Settings.ini, could not then even create a new one to save settings to! Are you trying to run the game from a read-only disk? You need to install the game to a writable area before running it!");

		WriteDefaultSettings(writer);
		// Close the newly created default file, we're opening it again to read from
		writer.Destroy();

		Reader settings("Base.rte/Settings.ini");
		// Now read from that same file
		return Serializable::Create(settings, true, doCreate);
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int SettingsMan::ReadProperty(std::string propName, Reader &reader) {
		if (propName == "PaletteFile") {
			g_FrameMan.ReadProperty(propName, reader);
		} else if (propName == "ResolutionX") {
			g_FrameMan.ReadProperty(propName, reader);
		} else if (propName == "ResolutionY") {
			g_FrameMan.ReadProperty(propName, reader);
		} else if (propName == "ResolutionMultiplier") {
			g_FrameMan.ReadProperty(propName, reader);
		} else if (propName == "HSplitScreen") {
			g_FrameMan.ReadProperty(propName, reader);
		} else if (propName == "VSplitScreen") {
			g_FrameMan.ReadProperty(propName, reader);
		} else if (propName == "ForceVirtualFullScreenGfxDriver") {
			reader >> m_ForceVirtualFullScreenGfxDriver;
		} else if (propName == "ForceOverlayedWindowGfxDriver") {
			reader >> m_ForceOverlayedWindowGfxDriver;
		} else if (propName == "ForceNonOverlayedWindowGfxDriver") {
			reader >> m_ForceNonOverlayedWindowGfxDriver;
		} else if (propName == "SoundVolume") {
			g_AudioMan.SetSoundsVolume(std::stod(reader.ReadPropValue()) / 100.0);
		} else if (propName == "MusicVolume") {
			g_AudioMan.SetMusicVolume(std::stod(reader.ReadPropValue()) / 100.0);
		} else if (propName == "SoundPanningEffectStrength") {
			reader >> m_SoundPanningEffectStrength;

		//////////////////////////////////////////////////
		//TODO These need to be removed when our soundscape is sorted out. They're only here temporarily to allow for easier tweaking by pawnis.
		} else if (propName == "ListenerZOffset") {
			reader >> m_ListenerZOffset;
		} else if (propName == "MinimumDistanceForPanning") {
			reader >> m_MinimumDistanceForPanning;
		//////////////////////////////////////////////////

		} else if (propName == "ShowForeignItems") {
			reader >> m_ShowForeignItems;
		} else if (propName == "FlashOnBrainDamage") {
			reader >> m_FlashOnBrainDamage;
		} else if (propName == "BlipOnRevealUnseen") {
			reader >> m_BlipOnRevealUnseen;
		} else if (propName == "MaxUnheldItems") {
			g_MovableMan.ReadProperty(propName, reader);
		} else if (propName == "SloMoThreshold") {
			g_MovableMan.ReadProperty(propName, reader);
		} else if (propName == "SloMoDurationMS") {
			g_MovableMan.ReadProperty(propName, reader);
		} else if (propName == "EndlessMode") {
			reader >> m_EndlessMode;
		} else if (propName == "EnableHats") {
			reader >> m_EnableHats;
		} else if (propName == "DefaultActivityType") {
			g_ActivityMan.SetDefaultActivityType(reader.ReadPropValue());
		} else if (propName == "DefaultActivityName") {
			g_ActivityMan.SetDefaultActivityName(reader.ReadPropValue());
		} else if (propName == "DefaultSceneName") {
			g_SceneMan.SetDefaultSceneName(reader.ReadPropValue());
		} else if (propName == "PlayerNetworkName") {
			reader >> m_PlayerNetworkName;
		} else if (propName == "NetworkServerName") {
			reader >> m_NetworkServerName;
		} else if (propName == "UseNATService") {
			reader >> m_UseNATService;
		} else if (propName == "NATServiceAddress") {
			reader >> m_NATServiceAddress;
		} else if (propName == "NATServerName") {
			reader >> m_NATServerName;
		} else if (propName == "NATServerPassword") {
			reader >> m_NATServerPassword;
		} else if (propName == "ClientInputFps") {
			reader >> m_ClientInputFps;
		} else if (propName == "ServerTransmitAsBoxes") {
			reader >> m_ServerTransmitAsBoxes;
		} else if (propName == "ServerBoxWidth") {
			reader >> m_ServerBoxWidth;
		} else if (propName == "ServerBoxHeight") {
			reader >> m_ServerBoxHeight;
		} else if (propName == "ServerUseHighCompression") {
			reader >> m_ServerUseHighCompression;
		} else if (propName == "ServerUseFastCompression") {
			reader >> m_ServerUseFastCompression;
		} else if (propName == "ServerHighCompressionLevel") {
			reader >> m_ServerHighCompressionLevel;
		} else if (propName == "ServerFastAccelerationFactor") {
			reader >> m_ServerFastAccelerationFactor;
		} else if (propName == "ServerUseInterlacing") {
			reader >> m_ServerUseInterlacing;
		} else if (propName == "ServerEncodingFps") {
			reader >> m_ServerEncodingFps;
		} else if (propName == "ServerSleepWhenIdle") {
			reader >> m_ServerSleepWhenIdle;
		} else if (propName == "ServerSimSleepWhenIdle") {
			reader >> m_ServerSimSleepWhenIdle;
		} else if (propName == "AllowSavingToBase") {
			reader >> m_AllowSavingToBase;
		} else if (propName == "ShowMetaScenes") {
			reader >> m_ShowMetaScenes;
		} else if (propName == "RecommendedMOIDCount") {
			reader >> m_RecommendedMOIDCount;
		} else if (propName == "PixelsPerMeter") {
			g_FrameMan.ReadProperty(propName, reader);
		} else if (propName == "PreciseCollisions") {
			reader >> m_PreciseCollisions;
		} else if (propName == "EnableParticleSettling") {
			g_MovableMan.ReadProperty(propName, reader);
		} else if (propName == "EnableMOSubtraction") {
			g_MovableMan.ReadProperty(propName, reader);
		} else if (propName == "DeltaTime") {
			g_TimerMan.SetDeltaTimeSecs(std::stof(reader.ReadPropValue()));
		} else if (propName == "RealToSimCap") {
			g_TimerMan.SetRealToSimCap(std::stof(reader.ReadPropValue()));
		} else if (propName == "PlayIntro") {
			reader >> m_PlayIntro;
		} else if (propName == "ToolTips") {
			reader >> m_ToolTips;
		} else if (propName == "DisableLoadingScreen") {
			reader >> m_DisableLoadingScreen;
		} else if (propName == "LoadingScreenReportPrecision") {
			reader >> m_LoadingScreenReportPrecision;
		} else if (propName == "ConsoleScreenRatio") {
			g_ConsoleMan.SetConsoleScreenSize(std::stof(reader.ReadPropValue()));
		} else if (propName == "AdvancedPerformanceStats") {
			g_PerformanceMan.ShowAdvancedPerformanceStats(std::stoi(reader.ReadPropValue()));
		} else if (propName == "PrintDebugInfo") {
			reader >> m_PrintDebugInfo;
		} else if (propName == "VisibleAssemblyGroup") {
			m_VisibleAssemblyGroupsList.push_back(reader.ReadPropValue());
		} else if (propName == "DisableMod") {
			std::string mod = reader.ReadPropValue();
			std::transform(mod.begin(), mod.end(), mod.begin(), ::tolower);
			DisableMod(mod);
		} else if (propName == "EnableScript") {
			std::string mod = reader.ReadPropValue();
			std::transform(mod.begin(), mod.end(), mod.begin(), ::tolower);
			EnableScript(mod);
		} else if (propName == "MouseSensitivity") {
			g_UInputMan.ReadProperty(propName, reader);
		} else if (propName == "P1Scheme" || propName == "P2Scheme" || propName == "P3Scheme" || propName == "P4Scheme") {
			g_UInputMan.ReadProperty(propName, reader);
		} else {
			// See if the base class(es) can find a match instead
			return Serializable::ReadProperty(propName, reader);
		}
		return 0;
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int SettingsMan::Save(Writer &writer) const {
		Serializable::Save(writer);

		writer.NewDivider(false);
		writer.NewLineString("// Display Settings", false);
		writer.NewLine(false);
		writer.NewProperty("PaletteFile");
		writer << g_FrameMan.GetPaletteFile();
		writer.NewProperty("ResolutionX");
		writer << g_FrameMan.GetNewResX();
		writer.NewProperty("ResolutionY");
		writer << g_FrameMan.GetNewResY();
		writer.NewProperty("ResolutionMultiplier");
		writer << g_FrameMan.ResolutionMultiplier();
		writer.NewProperty("HSplitScreen");
		writer << g_FrameMan.GetHSplit();
		writer.NewProperty("VSplitScreen");
		writer << g_FrameMan.GetVSplit();
		writer.NewProperty("ForceVirtualFullScreenGfxDriver");
		writer << m_ForceVirtualFullScreenGfxDriver;
		writer.NewProperty("ForceOverlayedWindowGfxDriver");
		writer << m_ForceOverlayedWindowGfxDriver;
		writer.NewProperty("ForceNonOverlayedWindowGfxDriver");
		writer << m_ForceNonOverlayedWindowGfxDriver;

		writer.NewLine(false, 2);
		writer.NewDivider(false);
		writer.NewLineString("// Audio Settings", false);
		writer.NewLine(false);
		writer.NewProperty("SoundVolume");
		writer << g_AudioMan.GetSoundsVolume() * 100;
		writer.NewProperty("MusicVolume");
		writer << g_AudioMan.GetMusicVolume() * 100;
		writer.NewProperty("SoundPanningEffectStrength");
		writer << m_SoundPanningEffectStrength;
		//////////////////////////////////////////////////
		//TODO These need to be removed when our soundscape is sorted out. They're only here temporarily to allow for easier tweaking by pawnis.
		writer.NewProperty("ListenerZOffset");
		writer << m_ListenerZOffset;
		writer.NewProperty("MinimumDistanceForPanning");
		writer << m_MinimumDistanceForPanning;
		//////////////////////////////////////////////////

		writer.NewLine(false, 2);
		writer.NewDivider(false);
		writer.NewLineString("// Gameplay Settings", false);
		writer.NewLine(false);
		writer.NewProperty("ShowForeignItems");
		writer << m_ShowForeignItems;
		writer.NewProperty("FlashOnBrainDamage");
		writer << m_FlashOnBrainDamage;
		writer.NewProperty("BlipOnRevealUnseen");
		writer << m_BlipOnRevealUnseen;
		writer.NewProperty("MaxUnheldItems");
		writer << g_MovableMan.GetMaxDroppedItems();
		writer.NewProperty("SloMoThreshold");
		writer << g_MovableMan.GetSloMoThreshold();
		writer.NewProperty("SloMoDurationMS");
		writer << g_MovableMan.GetSloMoDuration();
		writer.NewProperty("EndlessMode");
		writer << m_EndlessMode;
		writer.NewProperty("EnableHats");
		writer << m_EnableHats;

		writer.NewLine(false, 2);
		writer.NewDivider(false);
		writer.NewLineString("// Default Activity Settings", false);
		writer.NewLine(false);
		writer.NewProperty("DefaultActivityType");
		writer << g_ActivityMan.GetDefaultActivityType();
		writer.NewProperty("DefaultActivityName");
		writer << g_ActivityMan.GetDefaultActivityName();
		writer.NewProperty("DefaultSceneName");
		writer << g_SceneMan.GetDefaultSceneName();

		writer.NewLine(false, 2);
		writer.NewDivider(false);
		writer.NewLineString("// Network Settings", false);
		writer.NewLine(false);
		writer.NewProperty("PlayerNetworkName");
		writer << m_PlayerNetworkName;
		writer.NewProperty("NetworkServerName");
		writer << m_NetworkServerName;
		writer.NewProperty("UseNATService");
		writer << m_UseNATService;
		writer.NewProperty("NATServiceAddress");
		writer << m_NATServiceAddress;
		writer.NewProperty("NATServerName");
		writer << m_NATServerName;
		writer.NewProperty("NATServerPassword");
		writer << m_NATServerPassword;

		writer.NewLine(false, 2);
		writer.NewDivider(false);
		writer.NewLineString("// Advanced Network Settings", false);
		writer.NewLine(false);
		writer.NewProperty("ClientInputFps");
		writer << m_ClientInputFps;
		writer.NewProperty("ServerTransmitAsBoxes");
		writer << m_ServerTransmitAsBoxes;
		writer.NewProperty("ServerBoxWidth");
		writer << m_ServerBoxWidth;
		writer.NewProperty("ServerBoxHeight");
		writer << m_ServerBoxHeight;
		writer.NewProperty("ServerUseHighCompression");
		writer << m_ServerUseHighCompression;
		writer.NewProperty("ServerUseFastCompression");
		writer << m_ServerUseFastCompression;
		writer.NewProperty("ServerHighCompressionLevel");
		writer << m_ServerHighCompressionLevel;
		writer.NewProperty("ServerFastAccelerationFactor");
		writer << m_ServerFastAccelerationFactor;
		writer.NewProperty("ServerUseInterlacing");
		writer << m_ServerUseInterlacing;
		writer.NewProperty("ServerEncodingFps");
		writer << m_ServerEncodingFps;
		writer.NewProperty("ServerSleepWhenIdle");
		writer << m_ServerSleepWhenIdle;
		writer.NewProperty("ServerSimSleepWhenIdle");
		writer << m_ServerSimSleepWhenIdle;

		writer.NewLine(false, 2);
		writer.NewDivider(false);
		writer.NewLineString("// Editor Settings", false);
		writer.NewLine(false);
		writer.NewProperty("AllowSavingToBase");
		writer << m_AllowSavingToBase;
		writer.NewProperty("ShowMetaScenes");
		writer << m_ShowMetaScenes;

		writer.NewLine(false, 2);
		writer.NewDivider(false);
		writer.NewLineString("// Engine Settings", false);
		writer.NewLine(false);
		writer.NewProperty("RecommendedMOIDCount");
		writer << m_RecommendedMOIDCount;
		writer.NewProperty("PixelsPerMeter");
		writer << g_FrameMan.GetPPM();
		writer.NewProperty("PreciseCollisions");
		writer << m_PreciseCollisions;
		writer.NewProperty("EnableParticleSettling");
		writer << g_MovableMan.IsParticleSettlingEnabled();
		writer.NewProperty("EnableMOSubtraction");
		writer << g_MovableMan.IsMOSubtractionEnabled();
		writer.NewProperty("DeltaTime");
		writer << g_TimerMan.GetDeltaTimeSecs();
		writer.NewProperty("RealToSimCap");
		writer << g_TimerMan.GetRealToSimCap();

		writer.NewLine(false, 2);
		writer.NewDivider(false);
		writer.NewLineString("// Misc Settings", false);
		writer.NewLine(false);
		writer.NewProperty("PlayIntro");
		writer << m_PlayIntro;
		writer.NewProperty("ToolTips");
		writer << m_ToolTips;
		writer.NewProperty("DisableLoadingScreen");
		writer << m_DisableLoadingScreen;
		writer.NewProperty("LoadingScreenReportPrecision");
		writer << m_LoadingScreenReportPrecision;
		writer.NewProperty("ConsoleScreenRatio");
		writer << g_ConsoleMan.GetConsoleScreenSize();
		writer.NewProperty("AdvancedPerformanceStats");
		writer << g_PerformanceMan.AdvancedPerformanceStatsEnabled();
		writer.NewProperty("PrintDebugInfo");
		writer << m_PrintDebugInfo;

		if (!m_VisibleAssemblyGroupsList.empty()) {
			writer.NewLine(false, 2);
			writer.NewDivider(false);
			writer.NewLineString("// Enabled Bunker Assembly Groups", false);
			writer.NewLine(false);
			for (const std::string &visibleAssembly : m_VisibleAssemblyGroupsList) {
				writer.NewProperty("VisibleAssemblyGroup");
				writer << visibleAssembly;
			}
		}

		if (!m_DisabledMods.empty()) {
			writer.NewLine(false, 2);
			writer.NewDivider(false);
			writer.NewLineString("// Disabled Mods", false);
			writer.NewLine(false);
			for (const std::pair<std::string, bool> &disabledMod : m_DisabledMods) {
				if (disabledMod.second) {
					writer.NewProperty("DisableMod");
					writer << disabledMod.first;
				}
			}
		}

		if (!m_EnabledScripts.empty()) {
			writer.NewLine(false, 2);
			writer.NewDivider(false);
			writer.NewLineString("// Enabled Global Scripts", false);
			writer.NewLine(false);

			for (const std::pair<std::string, bool> &enabledScript : m_EnabledScripts) {
				if (enabledScript.second) {
					writer.NewProperty("EnableScript");
					writer << enabledScript.first;
				}
			}
		}

		writer << g_UInputMan;

		return 0;
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int SettingsMan::WriteDefaultSettings(Writer &writer) {
		if (!writer.WriterOK()) {
			return -1;
		}
		writer.ObjectStart(GetClassName());

		writer.NewProperty("PaletteFile");
		ContentFile paletteFile("Base.rte/palette.bmp");
		writer << paletteFile;
		writer.NewProperty("ResolutionX");
		writer << 960;
		writer.NewProperty("ResolutionY");
		writer << 540;
		writer.NewProperty("ResolutionMultiplier");
		writer << 1;
		writer.NewProperty("SoundVolume");
		writer << 40;
		writer.NewProperty("MusicVolume");
		writer << 60;
		writer.NewProperty("PixelsPerMeter");
		writer << 20;

		writer.ObjectEnd();

		m_SettingsNeedOverwrite = true;

		return 0;
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool SettingsMan::IsModDisabled(string modModule) {
		std::transform(modModule.begin(), modModule.end(), modModule.begin(), ::tolower);
		if (m_DisabledMods.find(modModule) != m_DisabledMods.end()) {
			return m_DisabledMods[modModule];
		}
		return false;
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool SettingsMan::IsScriptEnabled(string scriptName) {
		std::transform(scriptName.begin(), scriptName.end(), scriptName.begin(), ::tolower);
		if (m_EnabledScripts.find(scriptName) != m_EnabledScripts.end()) {
			return m_EnabledScripts[scriptName];
		}
		return false;
	}
}