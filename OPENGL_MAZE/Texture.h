#pragma once
#include<iostream>
#include<string>
class Texture
{
public:
	Texture();
	Texture(const std::string Texture_path);
	~Texture();

	unsigned char* getImage();

public:
	int width;
	int height;
	int components;
private:
	unsigned char * Imagedata;

};

