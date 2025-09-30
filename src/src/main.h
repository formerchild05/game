#pragma once

void Redering(SDL_Texture* menuTexture, SDL_Texture* head2menu, SDL_Rect& headm2, SDL_Texture* head1menu, SDL_Rect& headm1, SDL_Texture* key1, SDL_Rect& menukey1, SDL_Texture* key2, SDL_Rect& menukey2, SDL_Texture* loaTexture, SDL_Rect& loa, SDL_Texture* loa2Texture, SDL_Texture* loa3Texture);

void RunGame(bool& quit, SDL_Texture* backgroundTexture, snake& SNAKE, SDL_Texture* appleTexture, SDL_Texture* gold, SDL_Texture* green, SDL_Event& e, snake2& SNAKE2, bool& win);

void Winner(bool& result, SDL_Event& e, bool win, SDL_Texture* p1winTexture, Mix_Chunk* wingame, SDL_Texture* p2winTexture, SDL_Texture* space, SDL_Rect& sb);

void increaseVolume();

void decreaseVolume();

void muteVolume();
