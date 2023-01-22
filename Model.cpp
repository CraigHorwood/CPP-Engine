#include "Model.h"
#include <string>
#include <iostream>
#include "BinaryStream.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

using namespace std;

void Model::init(string path)
{
	// Open file and check header
    valid = false;
    BinaryStream stream(path);
    if (!stream.open)
    {
        cout << "Could not open model at " << path << endl;
        return;
    }
    unsigned int header;
    stream.readUnsignedInt(&header);
    if (header != 0x4d444c30)
    {
        cout << "Invalid model format at " << path << endl;
		stream.close();
        return;
    }
    valid = true;

	// Get the number of model parts, this determines the size of all chunks of the file
	stream.readUnsignedInt(&modelPartCount);
	modelParts = new ModelPart[modelPartCount];

	for (unsigned int i = 0; i < modelPartCount; i++)
	{
		// Shader ID's, texture ID's
	}

	for (unsigned int i = 0; i < modelPartCount; i++)
	{
		// Load meshes
	}
}

Model::~Model()
{
	if (valid)
	{
		for (unsigned int i = 0; i < modelPartCount; i++)
		{
			delete modelParts[i].geometry;
		}
		delete[] modelParts;
	}
}

void Model::render(float x, float y, float z)
{
	// For each model part, bind the mesh, shader, and texture
	// Apply model matrix transformations as arguments
}