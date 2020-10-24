#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

Texture::Texture(const std::string Texture_path)
{
	const char * path = Texture_path.c_str();
	Imagedata = stbi_load(path, &width, &height, &components, 0);
	if (!Imagedata) {
		std::cout << "Texture failed to load: " << Texture_path << std::endl;
		exit(0);
	}
}

Texture::~Texture()
{
	/*delete Imagedata;*/
}

unsigned char * Texture::getImage()
{
	return Imagedata;
}
