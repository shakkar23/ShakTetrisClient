#pragma once

#include <map>
#include <string>
#include <string_view>
#include <utility>

#include <SDL.h>
#include <SDL_image.h>

#include "RenderWindow.hpp"

class RenderWindow;

class Renderable {
public:
	Renderable() :texture(nullptr) {}
	Renderable(Texture* tex) :texture(tex) {}
	virtual void load(RenderWindow& window, std::string path, int32_t x, int32_t y, uint8_t sections) = 0;
	virtual void render(RenderWindow& renderer) = 0;
	Texture* texture;
};


class Texture {
public:
	Texture() = default;
	Texture(RenderWindow& window, std::string_view path) :path(path) {
		auto surface = IMG_Load(path.data());
		if (surface == nullptr) [[unlikely]] {
			throw "a surface didnt load";
		}

		width  = surface->w;
		height = surface->h;

		this->texture = SDL_CreateTextureFromSurface(window.getRenderer(), surface);
		SDL_FreeSurface(surface);

	}
	Texture(const Texture& other) :
		texture(other.texture),
		path(other.path),
		width(other.width),
		height(other.height)
	{
		if (texture)
			SDL_DestroyTexture(texture);
		this->texture = other.texture;
	}
	~Texture() {
		if (texture)
			SDL_DestroyTexture(texture);
	}


	SDL_Texture* texture;
	std::string path;
	uint16_t width;
	uint16_t height;
};

class Sprite : public Renderable {
public:
	Sprite() :Renderable(),  srcRect({ 0,0,0,0 }), destRect({ 0,0,0,0 }) {};
	Sprite(RenderWindow& window, std::string_view path, Texture* tex) {

		// set class members
		this->texture = tex;
		this->srcRect = { 0, 0, tex->width, tex->height };
		this->destRect = { 0, 0, 0, 0 };
	}

	void load(RenderWindow& window, std::string path, int32_t x = 0, int32_t y = 0, uint8_t sections = 0) override;
	void render(RenderWindow& renderer) override;

	SDL_Rect srcRect = { 0,0,0,0 };
	SDL_Rect destRect = { 0,0,0,0 };
};

// a sprite sheet is a collection of other smaller "sprites" that are represented by NxN N being "sections"
// you are freely allowed to manipulate where 
class SpriteSheet : public Renderable {
public:
	SpriteSheet() :Renderable(), srcRect({ 0,0,0,0 }), destRect({ 0,0,0,0 }), tileSize(0) {};
	SpriteSheet(int32_t x, int32_t y, uint8_t tileSize, Texture* tex, std::string path) : Renderable(tex), tileSize(tileSize) {

		// set class members
		this->srcRect = { tileSize * x, tileSize * y, tileSize, tileSize };
		this->destRect = { 0, 0, tileSize, tileSize };
	}

	~SpriteSheet() {
	}

	// the x and y are 0,0 on the top left of the texture
	void load(RenderWindow& window, std::string path, int32_t x, int32_t y, uint8_t tileSize) override;
	void render(RenderWindow& window) override;
	void updateSection(uint8_t x, uint8_t y);
	SDL_Rect srcRect = { 0,0,0,0 };
	SDL_Rect destRect = { 0,0,0,0 };
	uint8_t tileSize = 0;
};

// surface textures are always going to render its entire self no matter what
class SurfaceTexture : public Renderable {
	// the rule of 5, 
	// if you define the destructor, move constructor, move assignment operator, copy constructor, or copy assignment operator, 
	// then you should define all of them, even if only to delete them
public:
	SurfaceTexture() :
		Renderable(),
		surface(nullptr),
		texture(nullptr),
		path(),
		destRect({}),
		width(0), height(0) {};
	SurfaceTexture(RenderWindow& window, std::string_view path) {
		
		surface = IMG_Load(path.data());

		width = surface->w;
		height = surface->h;
		destRect = {};

		this->texture = SDL_CreateTextureFromSurface(window.getRenderer(), surface);
		if (texture == NULL || surface == NULL) {
			std::string error = "setSurfaceColorMod failed because: ";

			error += SDL_GetError();

			throw error;
		}

		this->path = path;
	}

	SurfaceTexture(SurfaceTexture&& other) :
		path(std::move(other.path)),
		destRect(other.destRect),
		width(other.width),
		height(other.height) {

		if (surface)
			SDL_FreeSurface(this->surface);

		surface = other.surface;
		other.surface = nullptr;

		if (this->texture)
			SDL_DestroyTexture(this->texture);

		texture = other.texture;
		other.texture = nullptr;

	}

	SurfaceTexture(const SurfaceTexture& other) = delete;/* :
		surface(other.surface),
		texture(other.texture),
		path(other.path),
		destRect(other.destRect),
		width(other.width),
		height(other.height) {};*/

	SurfaceTexture &operator= (const SurfaceTexture&) = delete;

	SurfaceTexture &operator=(SurfaceTexture&& other) {
		this->path = std::move(other.path);
		this->destRect = other.destRect;
		this->width = other.width;
		this->height = other.height;

		if (this->surface)
			SDL_FreeSurface(this->surface);

		this->surface = std::exchange(other.surface,nullptr);

		if (this->texture)
			SDL_DestroyTexture(this->texture);

		this->texture = std::exchange(other.texture, nullptr);
		return *this;
	}

	~SurfaceTexture() {
		if (surface)
			SDL_FreeSurface(this->surface);

		if (this->texture)
			SDL_DestroyTexture(this->texture);
	}
	void load(RenderWindow& window, std::string path, int32_t x = 0, int32_t y = 0, uint8_t tileSize = 1) override;
	void render(RenderWindow& renderer) override;

	// call this after youve made modifications using the other utility functions to "save" the changes into the texture
	inline void createTexture(RenderWindow &window) {
		if (texture)
			SDL_DestroyTexture(texture);

		texture = SDL_CreateTextureFromSurface(window.getRenderer(), surface);
	}

	inline void setSurfaceAlphaMod(RenderWindow& window, Uint8 a) {

		[[unlikely]] if (SDL_SetSurfaceAlphaMod(surface, a) != 0) {

			std::string error = "setSurfaceAlphaMod failed because: ";

			error += SDL_GetError();

			throw error;
		}
		createTexture(window);
	}

	inline void setSurfaceBlendMode(RenderWindow& window, SDL_BlendMode blend) {

		[[unlikely]] if (SDL_SetSurfaceBlendMode(surface, blend)) {

			std::string error = "SDL_SetSurfaceBlendMode failed because: ";

			error += SDL_GetError();

			throw error;
		}
		createTexture(window);
	}

	inline void setSurfaceColorMod(RenderWindow& window, Uint8 r, Uint8 g, Uint8 b) {

		[[unlikely]] if (SDL_SetSurfaceColorMod(surface, r, g, b)  != 0) {
			std::string error = "setSurfaceColorMod failed because: ";

			error += SDL_GetError();

			throw error;

		}
		createTexture(window);
	}

	SDL_Surface* surface;
	SDL_Texture* texture;
	std::string path;
	SDL_Rect destRect;
	uint8_t width;
	uint8_t height;
};

class TextureDictionary {
public:
	static Sprite		  reloadSP(RenderWindow& window, std::string_view path);
	static Sprite		  getSprite(RenderWindow& window, std::string_view path);
	static SurfaceTexture getSurfaceTexture(RenderWindow& window, std::string_view path);
	static SurfaceTexture reloadST(RenderWindow& window, std::string_view path);
	static SpriteSheet	  getSpriteSheet(RenderWindow& window, std::string_view path, uint32_t x, uint32_t y, uint8_t sections);
	static SpriteSheet    reloadSS(RenderWindow& window, std::string_view path, uint32_t x, uint32_t y, uint8_t sections);

private:
	static Texture* loadTexture(RenderWindow& window, std::string_view p_filePath);
	static inline std::map<std::string, Texture*> textures;
};
