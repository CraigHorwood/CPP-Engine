#include "Assets.h"
#include <string>
#include <map>

using namespace std;

map<string, Model*> Assets::models;
map<string, Shader*> Assets::shaders;
map<string, Texture*> Assets::textures;

void Assets::loadAll()
{
	Assets::lightingShader.init("assets/shaders/lighting.vsh", "assets/shaders/lighting.fsh");
	Assets::skyShader.init("assets/shaders/sky.vsh", "assets/shaders/sky.fsh");
	Assets::shaders.insert(pair<string, Shader*>("SDR_LGHT", &lightingShader));
	Assets::shaders.insert(pair<string, Shader*>("SDR_SKYB", &skyShader));

	Assets::skyTexture.init("assets/textures/sky0.png", true);
	Assets::floorTexture.init("assets/textures/floor.png");
	Assets::grassTexture.init("assets/textures/grass.png");
	Assets::textures.insert(pair<string, Texture*>("TEX_SKYB", &skyTexture));
	Assets::textures.insert(pair<string, Texture*>("TEX_FLOR", &floorTexture));
	Assets::textures.insert(pair<string, Texture*>("TEX_GRAS", &grassTexture));
}

void Assets::unloadAll()
{
	// Delete all assets
}