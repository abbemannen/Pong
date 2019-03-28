#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_net.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 500;


SDLNet_Init();

IPaddress ip;

//char adress[]="www.google.com";
SDLNet_ResolveHost(&ip, "130.229.156.68", 1234); // server ip adress

	//send right flipper pos
int* sendxpos = bstrect.x;
int* sendypos = bstrect.y;

//get left flipper pos

int* getxpos = cstrect.x;
int* getypos = cstrect.y;

// ball pos to receive

int* ballx = dstrect.x;
int* bally = dstrect.y;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void closeSDL();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

SDL_Surface* gXOut = NULL;

SDL_Surface* gPaddle = NULL;

SDL_Surface* gDamp = NULL;

SDL_Renderer* gRenderer = NULL;

int* horizontal_direction = 1;
int* vertical_direction = 0;
int yangle = 3;

int main(int argc, const char * argv[]) {
	// insert code here...
	printf("Hello, World!\n");
	//Main loop flag
	bool quit = false;
	// ball
	SDL_Rect dstrect;
	dstrect.x = 640 / 2;
	dstrect.y = 480 / 2;
	dstrect.w = 46;
	dstrect.h = 45;
	// right flipper
	SDL_Rect bstrect;
	bstrect.x = 740;
	bstrect.y = 480 / 2;
	bstrect.w = 46;
	bstrect.h = 45;
	// left flipper
	SDL_Rect cstrect;
	cstrect.x = 40;
	cstrect.y = 480 / 2;
	cstrect.w = 46;
	cstrect.h = 45;


	//Event handler
	SDL_Event e;

	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Apply the image
			SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, &dstrect);
			//Update the surface
			SDL_UpdateWindowSurface(gWindow);

			//Apply the image
			SDL_BlitSurface(gPaddle, NULL, gScreenSurface, &bstrect);

			//Apply the image
			SDL_BlitSurface(gPaddle, NULL, gScreenSurface, &cstrect);

			//Update the surface
			SDL_UpdateWindowSurface(gWindow);
		}
	}

	//While application is running
	while (!quit) {
		//Handle events on queue
		while (SDL_PollEvent(&e) >= 0)
		{

			//int direction = 1;
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				printf("QUIT!\n");
				quit = true;
			}

			TCPsocket client = SDLNet_TCP_Open(&ip);
			//TCPsocket server = SDLNet_TCP_Open(&remote_ip);

			//IPaddress *remote_ip;

			//Communication

			SDLNet_TCP_Recv(client, getxpos, sizeof(getxpos));
			SDLNet_TCP_Recv(client, getypos, sizeof(getypos));

			SDLNet_TCP_Recv(client, ballx, sizeof(ballx);
			SDLNet_TCP_Recv(client, bally, sizeof(bally);

			SDLNet_TCP_Send(client, sendxpos, sizeof(sendxpos);
			SDLNet_TCP_Send(client, sendypos, sizeof(sendypos);
			


			//remote_ip = SDLNet_TCP_GetPeerAddress(server);

			


			SDLNet_TCP_Close(client);

			//Moves Flipper

			if (e.type == SDL_KEYDOWN)
			{
				//Select surfaces based on key press
				switch (e.key.keysym.sym)
				{

				case SDLK_UP:
					bstrect.y -= 4;
					break;
				case SDLK_DOWN:
					bstrect.y += 4;
					break;
				}
			}

			// randomizes angle

			// Checks if ball needs to change direction

			if (dstrect.x == 740)
			{
				horizontal_direction = 2;
				if (vertical_direction == 1 || vertical_direction == 0)
				{
					vertical_direction = 1;
				}
				else
					vertical_direction = 2;
			}

			if (dstrect.x == 20)
			{
				horizontal_direction = 1;
				if (vertical_direction == 2 || vertical_direction == 0)
				{
					vertical_direction = 2;
				}
				else
					vertical_direction = 1;
			}

			if (dstrect.y <= 10)
			{
				//horizontal_direction = 1;
				vertical_direction = 2;
				yangle = rand() % 4 + 1;

			}
			if (dstrect.y >= 400)
			{
				//horizontal_direction = 1;
				vertical_direction = 1;
				yangle = rand() % 4 + 1;
			}


			// BLOCK BALL RIGHT SIDE

			if (dstrect.x >= bstrect.x - 10 && dstrect.y >= bstrect.y - 30 && dstrect.y <= bstrect.y + 160)
			{

				horizontal_direction = 2;
				if (vertical_direction == 1 || vertical_direction == 0)
				{
					vertical_direction = 1;
				}
				else
					vertical_direction = 2;

			}



			// Give ball a movement speed and direction.

			if (horizontal_direction == 2)
			{
				dstrect.x -= 3;

				SDL_Delay(3);
			}

			if (horizontal_direction == 1)
			{
				dstrect.x += 3;

				SDL_Delay(3);
			}

			if (vertical_direction == 2)
			{

				dstrect.y += yangle;
				SDL_Delay(3);
			}

			if (vertical_direction == 1)
			{

				dstrect.y -= yangle;
				SDL_Delay(3);
			}








			//Clear screen

			SDL_FillRect(gScreenSurface, NULL, 0x000000);
			SDL_Rect fillRect = { 100, 100, 20, 60 };
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(gRenderer, &fillRect);
			SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, &dstrect);
			SDL_BlitSurface(gPaddle, NULL, gScreenSurface, &bstrect);
			SDL_BlitSurface(gDamp, NULL, gScreenSurface, &cstrect);
			SDL_UpdateWindowSurface(gWindow);

		}


	}
	//Apply the image
	SDL_BlitSurface(gXOut, NULL, gScreenSurface, &dstrect);

	//Update the surface
	SDL_UpdateWindowSurface(gWindow);

	




	//Free resources and close SDL
	closeSDL();

	return 0;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	gHelloWorld = SDL_LoadBMP("ball.bmp");
	if (gHelloWorld == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "ball.bmp", SDL_GetError());
		success = false;
	}
	gXOut = SDL_LoadBMP("ball2.bmp");
	gPaddle = SDL_LoadBMP("paddle.bmp");
	gDamp = SDL_LoadBMP("paddle.bmp");

	return success;
}

void closeSDL()
{
	//Deallocate surface
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDLNet_Quit();
	SDL_Quit();
}
