#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

class TextureManager
{
public:
	TextureManager();
	~TextureManager();
	unsigned Load(const aiString& file);
	unsigned ForceLoad(const aiString& file);
	void Clear();
	TextureManager* GetInstance();
private:
	 instance;
};


#endif 
