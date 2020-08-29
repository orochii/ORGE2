#ifndef CACHE_H
#define CACHE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <map>
#include <iostream>
#include <sys/stat.h>

class Cache
{
    public:
        Cache();
        virtual ~Cache();
        void Init(SDL_Renderer* r);
        SDL_Texture* LoadTexture( std::string path );
        Mix_Music* LoadMusic( std::string path );
        Mix_Chunk* LoadSound( std::string path );
        inline bool fileExists (const std::string& name) {
            struct stat buffer;
            return (stat (name.c_str(), &buffer) == 0);
        }
        TTF_Font *gFont = NULL;
        void Close();
    private:
        SDL_Renderer* renderer;
        std::map<std::string, SDL_Surface*> imageResources;
        std::map<std::string, Mix_Music*> musicResources;
        std::map<std::string, Mix_Chunk*> soundResources;
};

#endif // CACHE_H
