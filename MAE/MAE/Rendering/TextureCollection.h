#pragma once

#include <string>
#include <map>

class TextureCollectionBase {
public:
	inline class Texture* findTexture(const std::string& name) {
		return findTexture(name.c_str());
	}

	virtual class Texture* findTexture(const char* name) = 0;
};

class TextureCollection: public TextureCollectionBase {
public:
	void add(std::string name, class Texture* tex) {
		m_map[name] = tex;
	}

	class Texture* findTexture(const char* name) {
		auto it = m_map.find(name);

		if (it == m_map.end())
			return nullptr;

		return it->second;
	}

private:
	std::map<std::string, class Texture*> m_map;
};
