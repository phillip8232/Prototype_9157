#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "GL/glew.h"
#include <iostream>
#include <string>
using std::string;

class Texture2D
{
private:
	GLuint mTexture;

public:
	Texture2D();
	virtual ~Texture2D();

	bool loadTexture(const string& filename, bool generateMipMaps = true);
	void bind(GLuint texUnit = 0);
};

#endif

