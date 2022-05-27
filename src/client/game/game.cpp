#include <std_include.hpp>
#include "game.hpp"

#include <utils/flags.hpp>

namespace game
{
	uint64_t base_address;

	void load_base_address()
	{
		const auto module = GetModuleHandle(NULL);
		base_address = uint64_t(module);
	}

	int Cmd_Argc()
	{
		return cmd_args->argc[cmd_args->nesting];
	}

	const char* Cmd_Argv(const int index)
	{
		return cmd_args->argv[cmd_args->nesting][index];
	}

	int SV_Cmd_Argc()
	{
		return sv_cmd_args->argc[sv_cmd_args->nesting];
	}

	const char* SV_Cmd_Argv(const int index)
	{
		return sv_cmd_args->argv[sv_cmd_args->nesting][index];
	}

	bool VirtualLobby_Loaded()
	{
		return 0; //return *mp::virtualLobby_loaded == 1;
	}

	const char* g_assetNames[ASSET_TYPE_COUNT] =
	{
		"physicslibrary",
		"physicssfxeventasset",
		"physicsvfxeventasset",
		"physicsasset",
		"physicsfxpipeline",
		"physicsfxshape",
		"xanim",
		"xmodelsurfs",
		"xmodel",
		"mayhem", // not confirmed
		"material",
		"computeshader",
		"vertexshader",
		"hullshader",
		"domainshader",
		"pixelshader",
		"vertexdecl",
		"techset",
		"image",
		"soundglobals",
		"soundbank",
		"soundbankpatch",
		"col_map",
		"com_map",
		"glass_map",
		"aipaths",
		"navmesh",
		"map_ents",
		"fx_map",
		"gfx_map",
		"gfx_map_trzone",
		"iesprofile",
		"lightdef",
		"ui_map",
		"animclass",
		"playeranim",
		"gesture",
		"localize",
		"attachment",
		"weapon",
		"vfx",
		"impactfx", // not confirmed
		"surfacefx", // not confirmed
		"aitype", // not confirmed
		"mptype", // not confirmed
		"character", // not confirmed
		"xmodelalias", // not confirmed
		"ASSET_TYPE_UNKNOWN", // not confirmed
		"rawfile",
		"scriptfile",
		"stringtable",
		"leaderboarddef",
		"virtualleaderboarddef",
		"structureddatadef",
		"ddl",
		"tracer",
		"vehicle",
		"addon_map_ents",
		"netconststrings",
		"luafile",
		"scriptable",
		"equipsndtable",
		"vectorfield",
		"particlesimanimation",
		"streaminginfo",
		"laser",
		"ttf",
		"suit",
		"suitanimpackage",
		"spaceshiptarget",
		"rumble",
		"rumblegraph",
		"animpkg",
		"sfxpkg",
		"vfxpkg",
		"behaviortree",
		"animarchetype",
		"proceduralbones",
		"reticle",
		"gfxlightmap",
	};

	const char* DB_GetXAssetName(const XAsset* asset)
	{
		return DB_GetXAssetHeaderName(asset->type, asset->header);
	}

	void DB_EnumXAssets(const std::int32_t type, const std::function<void(XAssetHeader)>& callback)
	{
		DB_EnumXAssets_FastFile(type, static_cast<void(*)(XAssetHeader, void*)>([](XAssetHeader header, void* data)
		{
			const auto& cb = *static_cast<const std::function<void(XAssetHeader)>*>(data);
			cb(header);
		}), &callback);
	}

	namespace environment
	{
		bool is_dedi()
		{
			return utils::flags::has_flag("dedicated");
		}
	}
}

uintptr_t operator"" _b(const uintptr_t ptr)
{
	return game::base_address + ptr;
}