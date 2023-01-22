#ifndef _ASSETS_H
#define _ASSETS_H

#include <string>
#include <map>
#include "Model.h"
#include "Shader.h"
#include "Texture.h"

class Assets
{
public:
	static void loadAll();
	static void unloadAll();
	static Model skyModel, floorModel, roomModel;
	static Shader lightingShader, skyShader;
	static Texture skyTexture, floorTexture, grassTexture;
	static std::map<std::string, Model*> models;
	static std::map<std::string, Shader*> shaders;
	static std::map<std::string, Texture*> textures;
private:
protected:
};

#endif