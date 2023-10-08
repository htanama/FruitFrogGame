//This is my code by Harry Tanama
//FruitFrogGame1.cpp - testing file with potential

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;


// Play an audio chunk on a specific channel.
// Syntax int Mix_PlayChannel(int channel, Mix_Chunk *chunk, int loops)
//Play our sound file, and capture the channel on which it is played
/*channel = Mix_PlayChannel(-1, Game_Music, 0);
if(channel == -1) {
    printf("Unable to play WAV file: %s\n", Mix_GetError());
}
*/
// int channel;				    //Channel on which our sound is played

int audio_rate = 22050;			//Frequency of audio playback
int audio_channels = 2;			//2 channels = stereo
int audio_buffers = 4096;		//Size of the audio buffers in memory
Uint16 audio_format = AUDIO_S16SYS; 	//Format of the audio we're playing
    
// SDL_Mixer data needed for music in the game  
// Mix_Music - Mix_Music is a data type used for music in the SDL Mixer library. The SDL Mixer library is a multi-channel audio mixer that supports 8 channels of 16 bit stereo audio and a single channel for music. Y
Mix_Music *Game_Music = NULL;	//Pointer to our sound, in memory
Mix_Chunk *Apple_Sound = NULL;
Mix_Chunk *HitByLog_Sound = NULL;
Mix_Chunk *stepSound = NULL;

int player_points = 0;

int random = 0; 

int main(int argc, char* argv[]){

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL; 
    SDL_Texture *background_texture = NULL;
       
    SDL_Texture *frog_texture = NULL;
    
    SDL_Texture *apple_texture = NULL;
    SDL_Texture *apple_texture2 = NULL;
    SDL_Texture *apple_texture3 = NULL;
    SDL_Texture *apple_texture4 = NULL;
    SDL_Texture *apple_texture5 = NULL;
    SDL_Texture *apple_texture6 = NULL;
    SDL_Texture *apple_texture7 = NULL;
    SDL_Texture *apple_texture8 = NULL;
    SDL_Texture *apple_texture9 = NULL;
    SDL_Texture *apple_texture10 = NULL;
    SDL_Texture *apple_texture11 = NULL;
    SDL_Texture *apple_texture12 = NULL;


    SDL_Texture *log_texture = nullptr;
    SDL_Texture *log_texture2 = nullptr;
    SDL_Texture *log_texture3 = nullptr;
    SDL_Texture *log_texture4 = nullptr;
    SDL_Texture *log_texture5 = nullptr;
    SDL_Texture *log_texture6 = nullptr;
    
    SDL_Surface *Text_Surface = nullptr;
    SDL_Texture *Text_Texture = nullptr;
    
  	if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
		std::cout <<"SDL cannot be initialized\n" << SDL_GetError();
		return -1;
	}

	else {
		std::cout <<"SDL video system initialized and ready\n";
	}

    //Initialize SDL_mixer with our chosen audio settings. Without this function the SDL_Mixer will not work. 
    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
	    printf("Unable to initialize audio: %s\n", Mix_GetError());
	    exit(1); // exit(1): used to indicate exit failure. Both exit(0) and exit(1) are jump statements of C++ and are used to terminate the program. And both report the status of termination of the program to the operating system.
    }

    //Load our WAV file from disk
	Game_Music = Mix_LoadMUS("mushroom_dance.wav");
	if(Game_Music == NULL) {
	    printf("Unable to load WAV file: %s\n", Mix_GetError());
	}

    Mix_PlayMusic(Game_Music, -1);

    Apple_Sound = Mix_LoadWAV("apple_bite.ogg");
    if(Apple_Sound == NULL) {    
	    printf("Unable to load WAV file: %s\n", Mix_GetError());
	}

    HitByLog_Sound = Mix_LoadWAV("hit20.mp3");
    if(HitByLog_Sound == NULL) {    
	    printf("Unable to load WAV file: %s\n", Mix_GetError());
	}

    stepSound = Mix_LoadWAV("stepdirt_1.wav");
    if(stepSound == NULL){
        printf("Unable to load WAV file: %s\n", Mix_GetError());
    }

	window = SDL_CreateWindow ("Fruit Frog", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
    // SDL_CreateRenderer - Create a 2D rendering context for a window.
    renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);

    // int __cdecl IMG_Init(int flags) Initialize SDL_image. This function loads dynamic libraries that SDL_image needs, and prepares them for use. This must be the first function you call in SDL_image.
    IMG_Init (IMG_INIT_PNG);
    
    // SDL_Surface - A structure that contains a collection of pixels used in software blitting.
    SDL_Surface *background_image = IMG_Load("background.png");
	// SDL_CreateTextureFromSurface - Create a texture from an existing surface. Versus SDL_CreateTexture - Create a texture for a rendering context.
    background_texture = SDL_CreateTextureFromSurface (renderer, background_image);    

    SDL_Surface *frog_image = IMG_Load("frog.png");
    frog_texture = SDL_CreateTextureFromSurface(renderer, frog_image);
    /* SDL_Rect defines a rectangular area, it is a structure that contains the definition of a rectangle, with the origin at the upper left. */
    SDL_Rect rect_frog = {0, 650, 50, 50};
    
    SDL_Surface *apple_image = IMG_Load("apple.png");
    apple_texture = SDL_CreateTextureFromSurface(renderer, apple_image); 
    apple_texture2 = SDL_CreateTextureFromSurface(renderer, apple_image); 
    apple_texture3 = SDL_CreateTextureFromSurface(renderer, apple_image); 
    apple_texture4 = SDL_CreateTextureFromSurface(renderer, apple_image); 
    apple_texture5 = SDL_CreateTextureFromSurface(renderer, apple_image); 
    apple_texture6 = SDL_CreateTextureFromSurface(renderer, apple_image); 
    apple_texture7 = SDL_CreateTextureFromSurface(renderer, apple_image); 
    apple_texture8 = SDL_CreateTextureFromSurface(renderer, apple_image);
    apple_texture9 = SDL_CreateTextureFromSurface(renderer, apple_image); 
    apple_texture10 = SDL_CreateTextureFromSurface(renderer, apple_image); 
    apple_texture11 = SDL_CreateTextureFromSurface(renderer, apple_image); 
    apple_texture12 = SDL_CreateTextureFromSurface(renderer, apple_image);  
    
    int apple_width = apple_image->w; 
    int apple_height = apple_image->h;
    
    srand(time(0));
    random = (rand()%1000) + 1;
    SDL_Rect rect_apple = {random, 200, apple_width/2, apple_height/2};   
    
    random = (rand()%1000) + 1;
    SDL_Rect rect_apple2 = {random, 200, apple_width/2, apple_height/2};  
    
    random = (rand()%1000) + 1;
    SDL_Rect rect_apple3 = {random, 200, apple_width/2, apple_height/2};    
    
    random = (rand()%1000) + 1;
    SDL_Rect rect_apple4 = {random, 200, apple_width/2, apple_height/2};
    
    //Level 2 falling apples
    random = (rand()%1000) + 1;
    SDL_Rect rect_apple5 = {random, 150, apple_width/2, apple_height/2};

    random = (rand()%1000) + 1;
    SDL_Rect rect_apple6 = {random, 150, apple_width/2, apple_height/2};

    random = (rand()%1000) + 1;
    SDL_Rect rect_apple7 = {random, 150, apple_width/2, apple_height/2};

    random = (rand()%1000) + 1;
    SDL_Rect rect_apple8 = {random, 150, apple_width/2, apple_height/2};

    // Level 3 falling apples
    SDL_Rect rect_apple9 = {25, 150, apple_width/2, apple_height/2};
    SDL_Rect rect_apple10 = {100, 150, apple_width/2, apple_height/2};
    SDL_Rect rect_apple11 = {300, 150, apple_width/2, apple_height/2};
    SDL_Rect rect_apple12 = {500, 150, apple_width/2, apple_height/2};

    // gravity for falling apple. 
    float gravity = rect_apple.y; 
    float gravity2 = rect_apple2.y; 
    float gravity3 = rect_apple3.y; 
    float gravity4 = rect_apple4.y; 
    float gravity5 = rect_apple5.y;
    float gravity6 = rect_apple6.y;
    float gravity7 = rect_apple7.y;
    float gravity8 = rect_apple8.y;
    float gravity9 = rect_apple9.y;
    float gravity10 = rect_apple10.y;
    float gravity11 = rect_apple11.y;
    float gravity12 = rect_apple12.y;


    SDL_Surface *log_image = IMG_Load("woodlog.png");
    log_texture = SDL_CreateTextureFromSurface(renderer, log_image); 
    log_texture2 = SDL_CreateTextureFromSurface(renderer, log_image); 
    log_texture3 = SDL_CreateTextureFromSurface(renderer, log_image); 
    log_texture4 = SDL_CreateTextureFromSurface(renderer, log_image); 
    log_texture5 = SDL_CreateTextureFromSurface(renderer, log_image); 
    log_texture6 = SDL_CreateTextureFromSurface(renderer, log_image); 

    int log_width = log_image->w; 
    int log_height = log_image->h;

    srand(time(0));
    random = (rand()%1000) + 1;    
    SDL_Rect rect_log = {random, 0, log_width/1.3, log_height/1.3};  

    random = (rand()%1000) + 1;    
    SDL_Rect rect_log2 = {random, 100, log_width/1.3, log_height/1.3};
    
    random = (rand()%1000) + 1;  
    SDL_Rect rect_log3 = {random, 200, log_width/1.3, log_height/1.3};
    
    random = (rand()%1000) + 1;      
    SDL_Rect rect_log4 = {random, 0, log_width/1.3, log_height/1.3};
    
    random = (rand()%1000) + 1;      
    SDL_Rect rect_log5 = {random, 100, log_width/1.3, log_height/1.3};    
    
    random = (rand()%1000) + 1;      
    SDL_Rect rect_log6 = {random, 200, log_width/1.3, log_height/1.3};

    float gravity_log = 0.0f;
    float gravity_log2 = 0.0f;
    float gravity_log3 = 0.0f;
    float gravity_log4 = 0.0f;
    float gravity_log5 = 0.0f;
    float gravity_log6 = 0.0f;

    TTF_Init();  // TTF_Init - Initialize SDL_ttf.
    
    TTF_Font *font = TTF_OpenFont("MartianMono.ttf", 50);
    SDL_Color color = {255, 255, 255};

    // TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
    //SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, "FRUIT FROG GAME", color); 

    // now you can convert it into a texture
    //SDL_Texture *Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    //SDL_Rect Message_rect; //create a rect
    //Message_rect.x = 0;  //controls the rect's x coordinate 
    //Message_rect.y = 0; // controls the rect's y coordinte
    //Message_rect.w = 100; // controls the width of the rect
    //Message_rect.h = 100; // controls the height of the rect

    // (0,0) is on the top left of the window/screen,
    // think a rect as the text's box,
    // that way it would be very simple to understand

    // Now since it's a texture, you have to put RenderCopy
    // in your game loop area, the area where the whole code executes

    // you put the renderer's name first, the Message,
    // the crop size (you can ignore this if you don't want
    // to dabble with cropping), and the rect which is the size
    // and coordinate of your texture
    //SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    

    // These variables create condition to only touch the if statement ONCE because the game loops keep executing the if statement more than ONCE. 
    // Is the object collide? Only execute the if statement ONCE. 
    // This variable is use to turn off the if statement in the game loop to stop adding player scores multiple time becaues game loop keep executing the if statement in LINE 301(If statement conditions).
    int AppleCollision_TouchOnce = 1;
    int AppleCollision2_TouchOnce = 1;
    int AppleCollision3_TouchOnce = 1;
    int AppleCollision4_TouchOnce = 1;
    int AppleCollision5_TouchOnce = 1;
    int AppleCollision6_TouchOnce = 1;
    int AppleCollision7_TouchOnce = 1;
    int AppleCollision8_TouchOnce = 1;
    int AppleCollision9_TouchOnce = 1;
    int AppleCollision10_TouchOnce = 1;
    int AppleCollision11_TouchOnce = 1;
    int AppleCollision12_TouchOnce = 1;

    // counter for log hitting the frog to stop drawing the falling log after it hits the frog.
    bool LogHitFrog = false; 
    bool Log2HitFrog = false; 
    bool Log3HitFrog = false; 
    bool Log4HitFrog = false; 
    bool Log5HitFrog = false; 
    bool Log6HitFrog = false; 

    // Copy a portion of the texture to the current rendering target.
    // SDL_RenderCopy(renderer, frog_texture, NULL, &rect_frog);
    SDL_Event event;
    bool running = true;
    
    //GAME LOOP
    while (running) { 
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            running = false;
                            break;
                        case SDLK_LEFT:
                            rect_frog.x -= 10;
                            Mix_PlayChannel(-1, stepSound, 0);
                            break;
                        case SDLK_RIGHT:
                            rect_frog.x += 10;
                            Mix_PlayChannel(-1, stepSound, 0);
                            break;
                    }
                    break;
            }
           
            // Check Charcter boundaries
            if (rect_frog.x < 0)
                rect_frog.x = 0;
            if (rect_frog.y < 0)
                rect_frog.y = 0;
            if (rect_frog.x + rect_frog.w > 1024)
                rect_frog.x = 1024 - rect_frog.w;
            if (rect_frog.y + rect_frog.h > 768)
                rect_frog.y = 768 - rect_frog.h;
        }
                     
        // SDL_RenderClear Clear the current rendering target with the drawing color.
        // Syntax: int SDL_RenderClear(SDL_Renderer * renderer);
        SDL_RenderClear(renderer);
        
        // Determine whether two rectangles intersect.
        SDL_bool AppleCollision = SDL_HasIntersection (&rect_apple, &rect_frog); 
        SDL_bool AppleCollision2 = SDL_HasIntersection (&rect_apple2, &rect_frog); 
        SDL_bool AppleCollision3 = SDL_HasIntersection (&rect_apple3, &rect_frog); 
        SDL_bool AppleCollision4 = SDL_HasIntersection (&rect_apple4, &rect_frog); 
        SDL_bool AppleCollision5 = SDL_HasIntersection (&rect_apple5, &rect_frog); 
        SDL_bool AppleCollision6 = SDL_HasIntersection (&rect_apple6, &rect_frog);   
        SDL_bool AppleCollision7 = SDL_HasIntersection (&rect_apple7, &rect_frog); 
        SDL_bool AppleCollision8 = SDL_HasIntersection (&rect_apple8, &rect_frog); 
        SDL_bool AppleCollision9 = SDL_HasIntersection (&rect_apple9, &rect_frog); 
        SDL_bool AppleCollision10 = SDL_HasIntersection (&rect_apple10, &rect_frog);   
        SDL_bool AppleCollision11 = SDL_HasIntersection (&rect_apple11, &rect_frog); 
        SDL_bool AppleCollision12 = SDL_HasIntersection (&rect_apple12, &rect_frog); 

        // Determine whether two rectangles intersect.
        SDL_bool LogCollision = SDL_HasIntersection (&rect_log, &rect_frog); 
        SDL_bool LogCollision2= SDL_HasIntersection (&rect_log2, &rect_frog); 
        SDL_bool LogCollision3 = SDL_HasIntersection (&rect_log3, &rect_frog); 
        SDL_bool LogCollision4 = SDL_HasIntersection (&rect_log4, &rect_frog); 
        SDL_bool LogCollision5 = SDL_HasIntersection (&rect_log5, &rect_frog); 
        SDL_bool LogCollision6 = SDL_HasIntersection (&rect_log6, &rect_frog); 


        // apple image movement downward - falling
        rect_apple.y = gravity; 
        gravity += 0.08f;       
        
        rect_apple2.y = gravity2;
        gravity2 += 0.08f;                  

        rect_apple3.y = gravity3;
        gravity3 += 0.08f;  

        rect_apple4.y = gravity4; 
        gravity4 += 0.08f;  

        // 2nd batch of falling apples.
        if ( (rect_log.y > 600 ) )
        {
            rect_apple5.y = gravity5;
            gravity5 += 0.08f; 
        }
        
        if ( (rect_log.y > 600 ) )
        {
            rect_apple6.y = gravity6;
            gravity6 += 0.08f; 
        }

       if ( (rect_log.y > 600 ) )
        {
            rect_apple7.y = gravity7;
            gravity7 += 0.08f; 
        }

       if ( (rect_log.y > 600 ) )
        {
            rect_apple8.y = gravity8;
            gravity8 += 0.08f; 
        }

        // Level 3 Falling apples.
        if ( (rect_log4.y > 600 ) )
        {
            rect_apple9.y = gravity9;
            gravity9 += 0.08f; 
        }
        
        if ( (rect_log4.y > 600 ) )
        {
            rect_apple10.y = gravity10;
            gravity10 += 0.08f; 
        }

       if ( (rect_log4.y > 600 ) )
        {
            rect_apple11.y = gravity11;
            gravity11 += 0.08f; 
        }

       if ( (rect_log4.y > 600 ) )
        {
            rect_apple12.y = gravity12;
            gravity12 += 0.08f; 
        }

        // if Log DO NOT hit Frog, DO this if condition. Log keeps falling. 
        // if Log hits Frog is false, then log keeps falling
        if (LogHitFrog == false)
        {   
            // log image movement
            rect_log.y = gravity_log;
            gravity_log += 0.09f;
        }
        // if Log2 hits Frog is false, then log2 keeps falling
        if (Log2HitFrog == false)
        { 
            // log image movement
            rect_log2.y = gravity_log2;
            gravity_log2 += 0.09f;    
        }

        if (Log3HitFrog == false)
        {
            // log image movement
            rect_log3.y = gravity_log3;            
            gravity_log3 += 0.09f;   
        }  

        // 2nd batch of falling logs conditions before it is render to the screen.
        if (Log4HitFrog == false && (rect_log.y > 600))
        {   
            // log image movement
            rect_log4.y = gravity_log4;
            gravity_log4 += 0.09f;
        }

        if (Log5HitFrog == false && (rect_log.y > 600))
        { 
            // log image movement
            rect_log5.y = gravity_log5;
            gravity_log5 += 0.09f;    
        }

        if (Log6HitFrog == false && (rect_log.y > 600))
        {
            // log image movement
            rect_log6.y = gravity_log6;            
            gravity_log6 += 0.09f;   
        }  

        //  check apple boundaries
        if (rect_apple.y + rect_apple.h > 768)
            rect_apple.y = 768 - rect_apple.h;
        if (rect_apple2.y + rect_apple2.h > 768)
            rect_apple2.y = 768 - rect_apple2.h;
        if (rect_apple3.y + rect_apple3.h > 768)
            rect_apple3.y = 768 - rect_apple3.h;
        if (rect_apple4.y + rect_apple4.h > 768)        
            rect_apple4.y = 768 - rect_apple4.h;
        if (rect_apple5.y + rect_apple5.h > 768)
            rect_apple5.y = 768 - rect_apple5.h;
        if (rect_apple6.y + rect_apple6.h > 768)        
            rect_apple6.y = 768 - rect_apple6.h;
        if (rect_apple7.y + rect_apple7.h > 768)
            rect_apple7.y = 768 - rect_apple7.h;  
        if (rect_apple8.y + rect_apple8.h > 768)
            rect_apple8.y = 768 - rect_apple8.h;  
        if (rect_apple9.y + rect_apple9.h > 768)
            rect_apple9.y = 768 - rect_apple9.h;
        if (rect_apple10.y + rect_apple10.h > 768)        
            rect_apple10.y = 768 - rect_apple10.h;
        if (rect_apple11.y + rect_apple11.h > 768)
            rect_apple11.y = 768 - rect_apple11.h;  
        if (rect_apple12.y + rect_apple12.h > 768)
            rect_apple12.y = 768 - rect_apple12.h; 

        //  check log boundaries
        if (rect_log.y + rect_log.h > 768)
            rect_log.y = 768 - rect_log.h;
        if (rect_log2.y + rect_log2.h > 768)
            rect_log2.y = 768 - rect_log2.h;
        if (rect_log3.y + rect_log3.h > 768)
            rect_log3.y = 768 - rect_log3.h;
        if (rect_log4.y + rect_log4.h > 768)
            rect_log4.y = 768 - rect_log4.h;
        if (rect_log5.y + rect_log5.h > 768)
            rect_log5.y = 768 - rect_log5.h;
        if (rect_log6.y + rect_log6.h > 768)
            rect_log6.y = 768 - rect_log6.h;

        // SDL_HasIntersection - Determine whether two rectangles intersect.
        // Syntax SDL_bool SDL_HasIntersection(const SDL_Rect * A, const SDL_Rect * B);
        if (AppleCollision && AppleCollision_TouchOnce == 1)
        {
            player_points++;
            AppleCollision_TouchOnce++;  
            apple_image = IMG_Load("eattenApple.png");
            apple_texture = SDL_CreateTextureFromSurface(renderer, apple_image); 
            Mix_PlayChannel(-1, Apple_Sound, 0);
            SDL_RenderCopy(renderer, apple_texture, NULL, &rect_apple); // SDL_RenderCopy - Copy a portion of the texture to the current rendering target.                                            
        }

        if (AppleCollision2 && AppleCollision2_TouchOnce == 1)
        {
            player_points++;
            AppleCollision2_TouchOnce++;
            apple_image = IMG_Load("eattenApple.png");
            apple_texture2 = SDL_CreateTextureFromSurface(renderer, apple_image); 
            Mix_PlayChannel(-1, Apple_Sound, 0);
            SDL_RenderCopy(renderer, apple_texture2, NULL, &rect_apple2); // SDL_RenderCopy - Copy a portion of the texture to the current rendering target.               
        }    
        
        if (AppleCollision3 && AppleCollision3_TouchOnce == 1)
        {
            player_points++;
            apple_image = IMG_Load("eattenApple.png");
            apple_texture3 = SDL_CreateTextureFromSurface(renderer, apple_image); 
            Mix_PlayChannel(-1, Apple_Sound, 0);
            SDL_RenderCopy(renderer, apple_texture3, NULL, &rect_apple3); // SDL_RenderCopy - Copy a portion of the texture to the current rendering target. 
            AppleCollision3_TouchOnce++;            
        }

        if (AppleCollision4 && AppleCollision4_TouchOnce == 1)
        {
            player_points ++;
            apple_image = IMG_Load("eattenApple.png");
            apple_texture4 = SDL_CreateTextureFromSurface(renderer, apple_image); 
            Mix_PlayChannel(-1, Apple_Sound, 0);
            SDL_RenderCopy(renderer, apple_texture4, NULL, &rect_apple4); // SDL_RenderCopy - Copy a portion of the texture to the current rendering target.  
            AppleCollision4_TouchOnce++;              
        }

        if (AppleCollision5 && AppleCollision5_TouchOnce == 1)
        {
            player_points ++;
            apple_image = IMG_Load("eattenApple.png");
            apple_texture5 = SDL_CreateTextureFromSurface(renderer, apple_image); 
            Mix_PlayChannel(-1, Apple_Sound, 0);
            SDL_RenderCopy(renderer, apple_texture5, NULL, &rect_apple5); // SDL_RenderCopy - Copy a portion of the texture to the current rendering target.  
            AppleCollision5_TouchOnce++;              
        }

        if (AppleCollision6 && AppleCollision6_TouchOnce == 1)
        {
            player_points ++;
            apple_image = IMG_Load("eattenApple.png");
            apple_texture6 = SDL_CreateTextureFromSurface(renderer, apple_image); 
            Mix_PlayChannel(-1, Apple_Sound, 0);
            SDL_RenderCopy(renderer, apple_texture6, NULL, &rect_apple6); // SDL_RenderCopy - Copy a portion of the texture to the current rendering target.  
            AppleCollision6_TouchOnce++;              
        }

        if (AppleCollision7 && AppleCollision7_TouchOnce == 1)
        {
            player_points ++;
            apple_image = IMG_Load("eattenApple.png");
            apple_texture7 = SDL_CreateTextureFromSurface(renderer, apple_image); 
            Mix_PlayChannel(-1, Apple_Sound, 0);
            SDL_RenderCopy(renderer, apple_texture7, NULL, &rect_apple7); // SDL_RenderCopy - Copy a portion of the texture to the current rendering target.  
            AppleCollision7_TouchOnce++;              
        }
 
        if (AppleCollision8 && AppleCollision8_TouchOnce == 1)
        {
            player_points ++;
            apple_image = IMG_Load("eattenApple.png");
            apple_texture8 = SDL_CreateTextureFromSurface(renderer, apple_image); 
            Mix_PlayChannel(-1, Apple_Sound, 0);
            SDL_RenderCopy(renderer, apple_texture8, NULL, &rect_apple8); // SDL_RenderCopy - Copy a portion of the texture to the current rendering target.  
            AppleCollision8_TouchOnce++;              
        }

        if (AppleCollision9 && AppleCollision9_TouchOnce == 1)
        {
            player_points ++;
            apple_image = IMG_Load("eattenApple.png");
            apple_texture9 = SDL_CreateTextureFromSurface(renderer, apple_image); 
            Mix_PlayChannel(-1, Apple_Sound, 0);
            SDL_RenderCopy(renderer, apple_texture9, NULL, &rect_apple9); // SDL_RenderCopy - Copy a portion of the texture to the current rendering target.  
            AppleCollision9_TouchOnce++;              
        }

        if (AppleCollision10 && AppleCollision10_TouchOnce == 1)
        {
            player_points ++;
            apple_image = IMG_Load("eattenApple.png");
            apple_texture10 = SDL_CreateTextureFromSurface(renderer, apple_image); 
            Mix_PlayChannel(-1, Apple_Sound, 0);
            SDL_RenderCopy(renderer, apple_texture10, NULL, &rect_apple10); // SDL_RenderCopy - Copy a portion of the texture to the current rendering target.  
            AppleCollision10_TouchOnce++;              
        }

        if (AppleCollision11 && AppleCollision11_TouchOnce == 1)
        {
            player_points ++;
            apple_image = IMG_Load("eattenApple.png");
            apple_texture11 = SDL_CreateTextureFromSurface(renderer, apple_image); 
            Mix_PlayChannel(-1, Apple_Sound, 0);
            SDL_RenderCopy(renderer, apple_texture11, NULL, &rect_apple11); // SDL_RenderCopy - Copy a portion of the texture to the current rendering target.  
            AppleCollision11_TouchOnce++;              
        }

        if (AppleCollision12 && AppleCollision12_TouchOnce == 1)
        {
            player_points ++;
            apple_image = IMG_Load("eattenApple.png");
            apple_texture12 = SDL_CreateTextureFromSurface(renderer, apple_image); 
            Mix_PlayChannel(-1, Apple_Sound, 0);
            SDL_RenderCopy(renderer, apple_texture12, NULL, &rect_apple12); // SDL_RenderCopy - Copy a portion of the texture to the current rendering target.  
            AppleCollision12_TouchOnce++;              
        }

        //if LogHitFrog is not true, then do the if statement. 
        if (LogCollision && !LogHitFrog) //Log has not hit the frog yet so this if statement needs to be execute it. 
        {
            LogHitFrog = true; // set LogHitFrog to true.
            Mix_PlayChannel(-1, HitByLog_Sound, 0);
            
            log_image = IMG_Load("deadFrog.png");
            log_texture = SDL_CreateTextureFromSurface(renderer, log_image);
            rect_log.h = rect_frog.h;
            rect_log.w = rect_frog.w;
            rect_log.y = rect_frog.y; 
            //SDL_RenderCopy(renderer, log_texture, NULL, &rect_log);

            //frog_image = IMG_Load("blank.png");
            //frog_texture = SDL_CreateTextureFromSurface(renderer, frog_image);            
            rect_frog = {0, 0, 0, 0}; // put frog character on 0,0 corrodinate, top left hand corner of the screen.

            background_image = IMG_Load("gameover.png");
	        background_texture = SDL_CreateTextureFromSurface (renderer, background_image);   
        }

        if (LogCollision2 && !Log2HitFrog) //Log2 has not hit the frog yet so this if statement needs to be execute it. 
        {
            Log2HitFrog = true ; // set Log2HitFrog to true
            Mix_PlayChannel(-1, HitByLog_Sound, 0);
            
            log_image = IMG_Load("deadFrog.png");
            log_texture2 = SDL_CreateTextureFromSurface(renderer, log_image);
            rect_log2.h = 60;
            rect_log2.w = 60;
            rect_log2.y = rect_frog.y; 
            
            //frog_image = IMG_Load("blank.png");
            //frog_texture = SDL_CreateTextureFromSurface(renderer, frog_image);            
            rect_frog = {0, 0, 0, 0}; // put frog character on 0,0 corrodinate, top left hand corner of the screen.

            background_image = IMG_Load("gameover.png");
	        background_texture = SDL_CreateTextureFromSurface (renderer, background_image);
        }
    
        if (LogCollision3 && !Log3HitFrog) //Log3 has not hit the frog yet so this if statement needs to be execute it. 
        {
            Log3HitFrog = true ; // set Log3HitFrog to true
            Mix_PlayChannel(-1, HitByLog_Sound, 0);
            
            log_image = IMG_Load("deadFrog.png");
            log_texture3 = SDL_CreateTextureFromSurface(renderer, log_image);
            rect_log3.h = 60;
            rect_log3.w = 60;
            rect_log3.y = rect_frog.y; 

            //frog_image = IMG_Load("blank.png");
            //rog_texture = SDL_CreateTextureFromSurface(renderer, frog_image);            
            rect_frog = {0, 0, 0, 0}; // put frog character on 0,0 corrodinate, top left hand corner of the screen.

            background_image = IMG_Load("TempGameOver.png");
	        background_texture = SDL_CreateTextureFromSurface (renderer, background_image);
        }

        if (LogCollision4 && !Log4HitFrog) //Log4 has not hit the frog yet so this if statement needs to be execute i
        {
            Log4HitFrog = true ; // set Log3HitFrog to true  
            Mix_PlayChannel(-1, HitByLog_Sound, 0);
            
            log_image = IMG_Load("deadFrog.png");
            log_texture4 = SDL_CreateTextureFromSurface(renderer, log_image);
            rect_log4.h = 60;
            rect_log4.w = 60;
            rect_log4.y = rect_frog.y; 

            //frog_image = IMG_Load("blank.png");
            //frog_texture = SDL_CreateTextureFromSurface(renderer, frog_image);            
            rect_frog = {0, 0, 0, 0}; // put frog character on 0,0 corrodinate, top left hand corner of the screen.

            background_image = IMG_Load("gameover.png");
	        background_texture = SDL_CreateTextureFromSurface (renderer, background_image);
        }

        if (LogCollision5 && !Log5HitFrog)
        {
            Log5HitFrog = true; 
            Mix_PlayChannel(-1, HitByLog_Sound, 0);
            
            log_image = IMG_Load("deadFrog.png");
            log_texture5 = SDL_CreateTextureFromSurface(renderer, log_image);
            rect_log5.h = 60;
            rect_log5.w = 60;
            rect_log5.y = rect_frog.y; 

            //frog_image = IMG_Load("blank.png");
            //frog_texture = SDL_CreateTextureFromSurface(renderer, frog_image);            
            rect_frog = {0, 0, 0, 0}; // put frog character on 0,0 corrodinate, top left hand corner of the screen.

            background_image = IMG_Load("gameover.png");
	        background_texture = SDL_CreateTextureFromSurface (renderer, background_image);
        }

        if (LogCollision6 && !Log6HitFrog)
        {
            Log6HitFrog = true; 
            Mix_PlayChannel(-1, HitByLog_Sound, 0);
            
            log_image = IMG_Load("deadFrog.png");
            log_texture6 = SDL_CreateTextureFromSurface(renderer, log_image);
            rect_log6.h = 60;
            rect_log6.w = 60;
            rect_log6.y = rect_frog.y; 

            //frog_image = IMG_Load("blank.png");
            //frog_texture = SDL_CreateTextureFromSurface(renderer, frog_image);            
            rect_frog = {0, 0, 0, 0}; // put frog character on 0,0 corrodinate, top left hand corner of the screen.

            background_image = IMG_Load("gameover.png");
	        background_texture = SDL_CreateTextureFromSurface (renderer, background_image);
        }

        //convert int to string and put the data to string.     
        std::string text = "Total Score = " + std::to_string(player_points);                
        Text_Surface = TTF_RenderText_Solid(font, text.c_str(), color);
        Text_Texture = SDL_CreateTextureFromSurface(renderer, Text_Surface);
        int textW = 0;
        int textH = 0; 
        // SDL_QueryTexture to retrieve the basic settings of a texture, including the format, access, width, and height.
        SDL_QueryTexture(Text_Texture, NULL, NULL, &textW, &textH);
        SDL_Rect show_Text = {0 ,0, textW, textH};

        SDL_RenderCopy(renderer, background_texture, NULL, NULL); // Copy the texture to the current rendering target. srcrect=NULL for the entire texture. dstrect=NULL for the entire rendering target.
        SDL_RenderCopy(renderer, frog_texture, NULL, &rect_frog);

        SDL_RenderCopy(renderer, apple_texture, NULL, &rect_apple);
        SDL_RenderCopy(renderer, apple_texture2, NULL, &rect_apple2);
        SDL_RenderCopy(renderer, apple_texture3, NULL, &rect_apple3);
        SDL_RenderCopy(renderer, apple_texture4, NULL, &rect_apple4);

        // Level 2 Falling Apple
        if ( (rect_log.y > 600 ) )
        {
            SDL_RenderCopy(renderer, apple_texture5, NULL, &rect_apple5);
        }

        if ( (rect_log.y > 600 ) )
        {
            SDL_RenderCopy(renderer, apple_texture6, NULL, &rect_apple6);
        }

        if ( (rect_log.y > 600 ) )
        {
            SDL_RenderCopy(renderer, apple_texture7, NULL, &rect_apple7);
        }

        if ( (rect_log.y > 600 ) )
        {
            SDL_RenderCopy(renderer, apple_texture8, NULL, &rect_apple8);
        }

        // Level 3 Falling Apple
        if ( (rect_log4.y > 600 ))
        {
            SDL_RenderCopy(renderer, apple_texture9, NULL, &rect_apple9);
        }

        if ( (rect_log4.y > 600 ) )
        {
            SDL_RenderCopy(renderer, apple_texture10, NULL, &rect_apple10);
        }

        if ( (rect_log4.y > 600 ) )
        {
            SDL_RenderCopy(renderer, apple_texture11, NULL, &rect_apple11);
        }

        if ((rect_log4.y > 600 ))
        {
            SDL_RenderCopy(renderer, apple_texture12, NULL, &rect_apple12);
        }

        // if Log hits frog, render dead frog and stop log from falling.
        if(LogHitFrog)
        {
            log_image = IMG_Load("deadFrog.png");
            log_texture = SDL_CreateTextureFromSurface(renderer, log_image);
            gravity_log = 650;
            rect_log.y = 650; // original position of the rect_frog = {0, 650, 50, 50};
            SDL_RenderCopy(renderer, log_texture, NULL, &rect_log); 
        }
        else // log keeps falling
        {
            SDL_RenderCopy(renderer, log_texture, NULL, &rect_log);
        }

        if(Log2HitFrog)
        {
            log_image = IMG_Load("deadFrog.png");
            log_texture2 = SDL_CreateTextureFromSurface(renderer, log_image);
            gravity_log2 = 650;
            rect_log.y = 650; // original position of the rect_frog = {0, 650, 50, 50};
            SDL_RenderCopy(renderer, log_texture2, NULL, &rect_log2);             
        }
        else
        {
            SDL_RenderCopy(renderer, log_texture2, NULL, &rect_log2);
        }
        // if Log3 hits frog, render dead frog and stop log from falling.
        if(Log3HitFrog) 
        {
            log_image = IMG_Load("deadFrog.png");
            log_texture3 = SDL_CreateTextureFromSurface(renderer, log_image);
            gravity_log3 = 650;
            rect_log3.y = 650; // original position of the rect_frog = {0, 650, 50, 50};
            SDL_RenderCopy(renderer, log_texture3, NULL, &rect_log3); // SDL_RenderCopy to copy a portion of the texture to the current rendering target.                      
        }
        else // log3 keeps falling
        {
            SDL_RenderCopy(renderer, log_texture3, NULL, &rect_log3);   
        }

        if(Log4HitFrog)
        {
            log_image = IMG_Load("deadFrog.png");
            log_texture4 = SDL_CreateTextureFromSurface(renderer, log_image);
            gravity_log4 = 650;
            rect_log4.y = 650; // original position of the rect_frog = {0, 650, 50, 50};
            SDL_RenderCopy(renderer, log_texture4, NULL, &rect_log4); // SDL_RenderCopy to copy a portion of the texture to the current rendering target.                                  
        }
        else 
        {            
           // render log4 when apple, apple2, or apple3.y value > 500 - maybe near the bottom of the screen. 
           if ( (rect_log.y > 600) )
           {
                SDL_RenderCopy(renderer, log_texture4, NULL, &rect_log4);
           }
        }
      
        if(Log5HitFrog)
        {
            log_image = IMG_Load("deadFrog.png");
            log_texture5 = SDL_CreateTextureFromSurface(renderer, log_image);
            gravity_log5 = 650;
            rect_log5.y = 650; // original position of the rect_frog = {0, 650, 50, 50};
            SDL_RenderCopy(renderer, log_texture5, NULL, &rect_log5); // SDL_RenderCopy to copy a portion of the texture to the current rendering target.                      
        }
        else 
        {
           // render log4 when apple, apple2, or apple3.y value > 500 - maybe near the bottom of the screen. 
           if ( (rect_log.y > 600) )
           {
                SDL_RenderCopy(renderer, log_texture5, NULL, &rect_log5);          
           }
        }

        if(Log6HitFrog)
        {
            log_image = IMG_Load("deadFrog.png");
            log_texture6 = SDL_CreateTextureFromSurface(renderer, log_image);
            gravity_log5 = 650;
            rect_log6.y = 650; // original position of the rect_frog = {0, 650, 50, 50};
            SDL_RenderCopy(renderer, log_texture6, NULL, &rect_log6); // SDL_RenderCopy to copy a portion of the texture to the current rendering target.           
        } 
        else 
        {            
            if ( (rect_log.y > 600) )
            {
                SDL_RenderCopy(renderer, log_texture6, NULL, &rect_log6);          
            } 
        }  

        SDL_RenderCopy(renderer, Text_Texture, NULL, &show_Text); 

        // Update the screen with any rendering performed since the previous call. 
        // Rendering all the textures and surfaces. 
        SDL_RenderPresent(renderer);        

    } // exit game loop. 

    // clear and free the memory from textures, surfaces and renderers pointers. 
	SDL_DestroyTexture(background_texture);
    SDL_DestroyTexture(frog_texture);
    
    SDL_DestroyTexture(apple_texture);
    SDL_DestroyTexture(apple_texture2);
    SDL_DestroyTexture(apple_texture3);
    SDL_DestroyTexture(apple_texture4);
    SDL_DestroyTexture(apple_texture5);
    SDL_DestroyTexture(apple_texture6);
    SDL_DestroyTexture(apple_texture7);
    SDL_DestroyTexture(apple_texture8);
    SDL_DestroyTexture(apple_texture9);
    SDL_DestroyTexture(apple_texture10);
    SDL_DestroyTexture(apple_texture11);
    SDL_DestroyTexture(apple_texture12);

    SDL_DestroyTexture(log_texture);
    SDL_DestroyTexture(log_texture2);
    SDL_DestroyTexture(log_texture3);
    SDL_DestroyTexture(log_texture4);
    SDL_DestroyTexture(log_texture5);
    SDL_DestroyTexture(log_texture6);

    SDL_DestroyTexture(Text_Texture);

    SDL_FreeSurface (log_image);
    SDL_FreeSurface (apple_image);
    SDL_FreeSurface (frog_image);
    SDL_FreeSurface(background_image);
        
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow (window);

    TTF_CloseFont(font); // TTF_CloseFont - Dispose of a previously-created font.

	//Release the memory allocated to our sound
	// Mix_FreeChunk(Game_Music);

    Mix_FreeMusic(Game_Music);      // Mix_Music *Game_Music = NULL;	
    Mix_FreeChunk (Apple_Sound);    //   Mix_Chunk *Apple_Sound = NULL;
    Mix_FreeChunk (HitByLog_Sound);
    Mix_FreeChunk (stepSound);
  	
    //Need to make sure that SDL_mixer and SDL have a chance to clean up
	Mix_CloseAudio();
	
    window = NULL;
	renderer = nullptr; 
    background_texture = NULL;
    frog_texture = NULL;
    apple_texture = NULL;
    apple_texture2 = NULL;
    apple_texture3 = NULL;
    apple_texture4 = NULL;
    log_texture = nullptr;
    Text_Surface = nullptr;
    Text_Texture = nullptr;

    TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return 0;
}