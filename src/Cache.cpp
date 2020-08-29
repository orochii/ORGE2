#include "Cache.h"

Cache::Cache() {}
Cache::~Cache() {}

void Cache::Init(SDL_Renderer* r) {
    renderer = r;
    gFont = TTF_OpenFont( "Media/OrochiiFon.ttf", 28 );
}

SDL_Texture* Cache::LoadTexture(std::string path) {
    std::string fullPath = "Media/Graphics/" + path;
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* image = nullptr;
    std::map<std::string, SDL_Surface*>::iterator it;
    it = imageResources.find(fullPath);
    if (it != imageResources.end()) {
        image = it->second;
    } else {
        image = IMG_Load( fullPath.c_str() );
        imageResources[ fullPath ] = image;
    }
    if (image != nullptr) {
        newTexture = SDL_CreateTextureFromSurface(renderer, image);
    }
    return newTexture;
}

Mix_Music* Cache::LoadMusic( std::string path ) {
    std::string fullPath = "Media/Audio/BGM/" + path;
    Mix_Music* mus = NULL;
    std::map<std::string, Mix_Music*>::iterator it;
    it = musicResources.find(fullPath);
    if (it != musicResources.end()) {
        mus = it->second;
    } else {
        mus = Mix_LoadMUS( fullPath.c_str() );
        musicResources[ fullPath ] = mus;
    }
    return mus;
}

Mix_Chunk* Cache::LoadSound( std::string path ) {
    std::string fullPath = "Media/Audio/SE/" + path;
    Mix_Chunk* sfx = NULL;
    std::map<std::string, Mix_Chunk*>::iterator it;
    it = soundResources.find(fullPath);
    if (it != soundResources.end()) {
        sfx = it->second;
    } else {
        sfx = Mix_LoadWAV( fullPath.c_str() );
        soundResources[ fullPath ] = sfx;
    }
    return sfx;
}

void Cache::Close() {
    // Clear all image cache.
    for (std::pair<std::string, SDL_Surface*> element : imageResources) {
		SDL_Surface *surf = element.second;
		SDL_FreeSurface(surf);
	}
	// Clear all music cache.
    for (std::pair<std::string, Mix_Music*> element : musicResources) {
		Mix_Music *mus = element.second;
		Mix_FreeMusic(mus);
	}
	// Clear all sound cache.
    for (std::pair<std::string, Mix_Chunk*> element : soundResources) {
		Mix_Chunk *sfx = element.second;
		Mix_FreeChunk(sfx);
	}
	// Clear the font
	TTF_CloseFont(gFont);
}
