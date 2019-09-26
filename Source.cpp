//Code by Giovanni Miliziano
// 1/19/2019


#include <iostream>
#include <SDL.h>
#include <ctime>
#include <cstdlib>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <cmath>
#include <string>
#include <vector>
#include <sstream>	
using namespace std;
enum groundtype { GRASS,ICE,NONMOVEICE,FASTICE,REVERSEICE,SNOW, DEATH};
enum dir { LEFT, RIGHT, DOWN, UP };
//grass 0 - 255 - 0
//ice 105 - 193 - 245
//nonmoveice 211 - 227 - 236
//fastice 58 - 7 - 77
//reverseice 236 - 129 - 225
//1950,1100 
const int screen_height = 1100;
const int screen_width = 1950;
const int camera_height = screen_height/2;
const int camera_width = screen_width/2;
int camerawidth = 350;
int cameraheight = 200;
bool onetime = true;
int rightclickdisabled = 0;
bool rightclickstop = 0;
int range;
double ydiff;
double xdiff;
double degree;
int x;
int y;
int mousex;
int mousey;
double mx;
double my;
double circleradius;
double xincrement;
double ball1centerx;
double ball1centery;
bool leveloneonce = 0;
SDL_Rect beforecameramove = { -121212,0,0,0 };
int cameralockcount = 0;
SDL_Rect cameralockfill = { 0,0,0,0 };
bool zealotrandompickagain = 1;
int zealotrandomcounter = 0;
bool healthonegone = 0;
double banespeed = 3;
double slope = 0;
double counter = 1;
int slowdown = 0;
bool rightclicked = false;
bool dead = 0;
bool wasjustreverseice = 0;
bool reverseicetograss = 0;
bool justturned = 0;
struct enemy
{
	SDL_Rect originalrect;
	bool thebool;
	SDL_Rect rect;
	SDL_Texture* text;
	dir dir;
	int randomlength;
	float randomslope;
	int randomspeed;
	double angle;
	double rotatespeed;
	bool operator==(const enemy& enemy1)
	{
		return rect.x == enemy1.rect.x && rect.y == enemy1.rect.y && rect.w == enemy1.rect.w && rect.h == enemy1.rect.h;
	}
};
struct ground
{
	SDL_Rect therect;
	groundtype thegroundtype;
	bool aboolean;
	int r;
	int g;
	int b;
	SDL_Texture* texture;
};
struct pointholder
{
	double x;
	double y;
};
struct ballz
{
	double x;
	double y;
	double speed;
	SDL_Texture* skin;
};
int player_width = 40;
int player_height = 40;
int playerangle = 0;
SDL_Window* gwindow = 0;
SDL_Surface* gsurface = 0;
SDL_Renderer* grender = 0;
TTF_Font* gfont = 0;
SDL_Texture* ball = 0;
SDL_Texture* baneling = 0;
SDL_Texture* banelingspeed = 0;
SDL_Texture* mouseskin = 0;
SDL_Texture* snow = 0;
SDL_Texture* grass = 0;
SDL_Texture* ice = 0;
SDL_Texture* nomoveice = 0;
SDL_Texture* zealot = 0;
SDL_Texture* goodrop = 0;
SDL_Texture* heart = 0;
SDL_Texture* number = 0;
SDL_Texture* gameover = 0;
SDL_Texture* reverseice = 0;
SDL_Texture* fastice = 0;
SDL_Texture* buttongreen = 0;
SDL_Texture* buttonred = 0;
SDL_Texture* gate = 0;
SDL_Texture* portal = 0;
SDL_Texture* interceptor = 0;
SDL_Texture* carrier = 0;
SDL_Texture* bluelaser = 0;
SDL_Texture* phoenix = 0;
SDL_Texture* zealottwo = 0;
SDL_Texture* explosion = 0;
SDL_Texture* artmenu = 0;
SDL_Texture* menu = 0;
SDL_Texture* menuclick = 0;
SDL_Texture* guide = 0;
SDL_Texture* guidelook = 0;
SDL_Texture* victory = 0;
SDL_Texture* avilo = 0;
SDL_Texture* architect = 0;
SDL_Texture* heartman = 0;
SDL_Texture* aviloquote = 0;
SDL_Texture* architectquote = 0;
SDL_Texture* heartmanquote = 0;
SDL_Texture* peeguy = 0;

Mix_Music* greatbigsled = 0;
Mix_Music* sledintro = 0;
Mix_Music* wishlist = 0;

Mix_Chunk* peesound = 0;
Mix_Chunk* deathsound = 0;
Mix_Chunk* portalsound = 0;
Mix_Chunk* levelsound = 0;
Mix_Chunk* carriersound = 0;
Mix_Chunk* explosionsound = 0;
Mix_Chunk* carriersoundtwo = 0;
Mix_Chunk* carriersoundthree = 0;
Mix_Chunk* cheer = 0;

SDL_Surface* theball = 0;
groundtype playerfloor = GRASS;
groundtype pastfloor = GRASS;
groundtype currentfloor = GRASS;
bool cameralock = 0;
bool longcamera = 0;
bool pastflooroff = false;
bool switchfloor = 0;
bool thecheck = false;
bool firstframe = 0;
bool currentflooroff = false;
bool thechecktwo = false;
bool firstframetwo = 0;
bool reversefirstclick = 0;
int reversegrasscounter = 0;
bool icefirstclick = 0;
bool fakesnow = 0;
bool cameralockputback = 0;
bool speedboost = 0;
int speedboostcount = 0;
bool boostjustended = 0;
int boostdelay = 0;
vector<dir> cameraputbackdir;
int icegrasscounter = 0;
bool gameoverbool = 0;
bool banelingbool = 0;
bool portaltaken = 0;
bool newlevel = 0;

//main menus
bool menuswitch = 0;
int menucounter = 0;
bool guideone = 0;
SDL_Rect guiderect = { 1820,1050,100,30 };//1950,1100 

//level 2
bool enemyoneswitch = 0;
bool enemyonemoveright = 1;
int enemyeightcounter = 0;
int enemyeightswitch = 0;
bool wasright = 0;
bool enemyswitchcircle = 0;
bool healthtwogone = 0;
bool healththreegone = 0;

//level 3


//level 4
bool buttononepressed = 0;
bool buttontwopressed = 0;
//level 5 boss
int bossx = 1300;
int bossy = 200;
bool bossspawn = 0;
vector<enemy> interceptorz;
int spawncounter = 0;
int currentinterceptor = 0;
int switchfloorcount = 0;
bool laserphase = 0;
bool spawnlaser = 1;
bool laserswitch = 0;
int lasercount = 0;
bool interceptphase = 1;
bool chasephase = 0;
bool chasephaseonce = 1;
bool phoenixphase = 0;
bool playershoot = 0;
int laserincrement = 0;
bool laserspawn = 1;
bool phoenixonce = 1;
bool candiefrombarrier = 0;
bool carriergoup = 1;
bool interceptorcosine = 0;
int lastphasecounter = 0;
int interceptorspawn = 50;
int carrierhealth = 200;
bool endphase = 0;
int explosioncounter = 0;
bool finalphase = 0;


//level 6
bool firstsong = 1;
bool cheersonce = 1;

int playerhealth = 5;
SDL_Rect speedgoorect = { 1650,950,50,50 };
int coverupy = 950;
int coveruph = 50;
SDL_Rect liverect = { 1825,960,40,40 };
SDL_Rect heartrect = { 1750,950,50,50 };
SDL_Rect speedgoocoverup = { 1650,coverupy,50,coveruph };
SDL_Rect yikes;
ballz ball1{ 100,400,3 };
ballz ball2{90,100,3};
ballz ball3{80,100,3};
ballz ball4{70,100,3};
ballz ball5{ 60,100,3 };
ballz ball6{ 50,100,3 };
ballz ball7{ 40,100,3 };
pointholder phone = { 100,400 };
pointholder phtwo = { 0,0 };
pointholder phthree = { 0,0 };
pointholder phfour = { 0,0 };
pointholder phfive = { 0,0 };
pointholder phsix = { 0,0 };
int followcounter = 0;
vector<SDL_Rect> portalvect;
vector<ground> leveloneground;
vector<enemy> leveloneenemies;
vector<SDL_Rect> levelonerects;
vector<SDL_Rect> leveltworects;
vector<SDL_Rect> levelthreerects;
vector<SDL_Rect> levelfourrects;
vector<SDL_Rect> levelfiverects;
vector<SDL_Rect> levelsixrects;
vector<ground> leveltwoground;
vector<enemy> leveltwoenemies;
vector<ground> levelthreeground;
vector<enemy> levelthreeenemies;
vector<ground> levelfourground;
vector<enemy> levelfourenemies;
vector<ground> levelfiveground;
vector<enemy> levelfiveenemies;
vector<ground> levelsixground;
vector<enemy> levelsixenemies;

int currentlevel = 0;/////////////////////////////////////////current level
SDL_Rect endone = {2100,-950,100,100};//1950,-1100,400,400
SDL_Rect endtwo = {2400,-25,100,100};//2300, -125, 300, 300
SDL_Rect endthree = {1675,-3150,100,100};//1575,-3200,300, 300
SDL_Rect endfour = {4700,325,100,100};//4600,250,300,300
SDL_Rect endfive = { 10200,300,300,500 };//8500,300,2000,500
vector<ground> * currentground = 0;
vector<enemy> * currentenemy = 0;
vector<SDL_Rect> * currentrects = 0;

 
bool init();
bool loadmedia();
SDL_Texture* loadtext(string s, SDL_Color textcolor);
SDL_Texture* loadimage(string a);
SDL_Texture* loadimageclear(string a);
SDL_Texture* loadseethroughwhite(string a);
SDL_Texture* loadseethrough(string a);
void whatamion(const SDL_Rect player,vector<ground> leveloneground);
void move();
void setxincrement(double degree, double xdiff, double ydiff, double& xincrement, double banespeed);
void moverightclick();
void movefunction();
void leveloneinitialize();
void leveltwoinitialize();
void levelthreeinitialize();
void levelfourinitialize();
void levelfiveinitialize();
void levelsixinitialize();
bool isdead(const SDL_Rect player, vector<ground> leveloneground);
void collision();
void enemymoveleftonly(enemy & enemy, int length, int speed);
void enemymovemiddleleftright(enemy & enemy, int length, int speed);
void enemymoveleftright(enemy & enemy, int length, int speed);//0 is left 1 is right
void enemymoverightleft(enemy & enemy, int length, int speed);
void enemymoveupdown(enemy & enemy, int length, int speed);
void enemymovedownup(enemy & enemy, int length, int speed);
void enemymoveslope(enemy & enemy, int length, int speed,double enemyslope);
void enemymoveslopeleftright(enemy & enemy, int length, int speed, double enemyslope);
void enemymoveslopejustright(enemy & enemy, int length, int speed, double enemyslope);
void enemymovesloperandom(enemy & enemy, int length, int speed, double enemyslope, SDL_Rect rect);
void enemyrectcounterclock(enemy & enemy, SDL_Rect therect, int speed,bool & x);//set to 0
void enemyrectclock(enemy & enemy, SDL_Rect therect, int speed, bool & x);
void enemycosine(enemy & enemy, int length, int speed, int amplitude);
void enemycosineinterceptor(enemy & enemy, int speed, int amplitude);
void enemyrotate(enemy & enemy);
void enemyrotateleveltwo(enemy & enemy);
void camerascroll(SDL_Rect & player, vector<ground> & leveloneground, vector<enemy> & enemies, vector<SDL_Rect> & boxes, dir direction, int speed, vector<enemy> & inter);
bool checkcollision(SDL_Rect a, SDL_Rect b);
bool checkcollisionmoveback(SDL_Rect & a, SDL_Rect b);//actually moves player back
bool checkcollisioncircles(SDL_Rect a, SDL_Rect b);
double distanceSquared(double x1, double y1, double x2, double y2);
void levelfive();
void close();

int main(int argc, char* args[])
{
	if (!init())
	{
		cout << "could not initialize!";
	}
	else
	{
		if (!loadmedia())
		{
			cout << "could not load media!";
		}
		else
		{
		
			leveloneinitialize();
			leveltwoinitialize();
			levelthreeinitialize();
			levelfourinitialize();
			levelfiveinitialize();
			levelsixinitialize();

			bool leave = false;
			SDL_Event e;
			while (leave == false)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						leave = true;
					}
					if (e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{
						case SDLK_ESCAPE: if (guideone == 0) {
							guideone = 1;
						}
						else guideone = 0; break;
						case SDLK_x: playershoot = 1; break;
						case SDLK_r: cameralock = true; longcamera = false; break;
						case SDLK_t: cameralock = false; longcamera = false; break;
						case SDLK_y: cameralock = false; longcamera = true; break;
						case SDLK_q:
							if (gameoverbool == 1)
							{
								cout << "Gameover: ";
								buttononepressed = 0;
								buttontwopressed = 0;
								healthonegone = 0;
								healthtwogone = 0;
								healththreegone = 0;
								speedboost = 0;
								speedboostcount = 0;
								playerhealth = 5;
								coverupy = 950;
								coveruph = 50;
								boostjustended = 0;
								gameoverbool = 0;
								currentlevel = 1;
								currentground = &leveloneground;
								currentenemy = &leveloneenemies;
								currentrects = &levelonerects;
								ball1.x = (*currentground)[0].therect.x + 50;
								ball1.y = (*currentground)[0].therect.y + 50;
							} gameoverbool = 0; break;
						case SDLK_f: if (boostjustended == 0 && speedboost == 0)
						{
							banespeed += 3; setxincrement(degree, xdiff, ydiff, xincrement, banespeed); speedboost = 1; ball1.skin = banelingspeed; break;
						}break;
						}
					}
					SDL_Color colorwhite = { 0,0,0 };
					number = loadtext(to_string(playerhealth), colorwhite);
					if (speedboostcount > 150 && speedboost == 1)
					{
						speedboostcount = 0;
						speedboost = 0;
						ball1.skin = baneling;
						if (banelingbool == 0)
						{
							banespeed -= 3;
							setxincrement(degree, xdiff, ydiff, xincrement, banespeed);
						}
						boostjustended = 1;
					}
					if (speedboost == 1)
					{
						speedboostcount++;
					}
					if (rightclickstop == 1)
					{
						rightclickdisabled++;
					}
					if (rightclickdisabled == 30)
					{
						rightclickstop = 0;
						rightclickdisabled = 0;
					}
					if (gameoverbool == 1 || rightclickstop == 1)
					{

					}
					//mouse scroll mechanics
					else if (playerfloor == NONMOVEICE)
					{
						rightclicked = true;
						//to stop glitched just keep going if your on non movable ice even if you stopped moving one pixel before you got there
					}
					else
					{
						if (e.type == SDL_MOUSEBUTTONDOWN)
						{
							if (e.button.button == SDL_BUTTON_LEFT)
							{//1840,1050,100,30
								if (mousex > 1840 && mousex < 1950 && mousey > 1050 && mousey < 1080)
								{
									guideone = 1;
								}
								if (currentlevel == 0 && (mousex > 500 && mousex < 1100 && mousey > 700 && mousey < 1000))
								{
									menuswitch = 1;
								}
							}
							if (currentlevel == 0 || guideone == 1)
							{

							}
							else
							{
								SDL_GetMouseState(&mousex, &mousey);
								if (e.button.button == SDL_BUTTON_RIGHT)
								{
									if ((mousex == ball1.x && mousey == ball1.y) || ((mousex > ball1.x - 5 && mousex < ball1.x + 40) && (mousey < ball1.y + 40 && mousey>ball1.y - 5)))
									{

									}
									else
									{

										if (1 == 0)
										{

										}
										else
										{
											ball1centerx = (ball1.x + (ball1.x + 20)) / 2;
											ball1centery = (ball1.y + (ball1.y + 20)) / 2;
											rightclicked = true;

											mx = mousex;
											my = mousey;
											circleradius = distanceSquared(mx, my, ball1centerx, ball1centery);
											degree = acos((mx - ball1centerx) / circleradius);
											if (playerfloor == REVERSEICE)
											{
												reversefirstclick = 1;
											}
											else
											{
												reversefirstclick = 0;
											}
											reverseicetograss = 0;
											ydiff = my - ball1centery;
											xdiff = mx - ball1centerx;
											setxincrement(degree, xdiff, ydiff, xincrement, banespeed);

											if ((ydiff < 10 && ydiff > -10) && (xdiff < 10 && xdiff > -10))
											{
												rightclicked = false;
											}
											if (xdiff == 0)
											{
												rightclicked = false;
											}
											else
											{
												slope = ydiff / xdiff;
											}
											if (slope == 0)
											{
												cout << "slope is 0";
											}
										}
									}
								}
							}
						}
					}
				}
				if (currentlevel == 0)
				{
					if (Mix_PlayingMusic() == 0)
					{
						Mix_PlayMusic(sledintro, 0);
					}

					SDL_GetMouseState(&mousex, &mousey);
					SDL_SetRenderDrawColor(grender, 255, 255, 255, 255);
					SDL_RenderClear(grender);
					if (menuswitch == 1)
					{
						Mix_HaltMusic();
						SDL_RenderCopy(grender, artmenu, 0, 0);
						menucounter++;
						if (menucounter > 100)
						{
							currentlevel = 1;
						}
					}
					else
					{
						if (mousex > 500 && mousex < 1100 && mousey > 700 && mousey < 1000)
						{
							SDL_RenderCopy(grender, menuclick, 0, 0);
						}
						else
						{
							SDL_RenderCopy(grender, menu, 0, 0);
						}
					}

					SDL_Rect Mouse = { mousex,mousey,25,25 };
					SDL_RenderCopy(grender, mouseskin, 0, &Mouse);
					SDL_RenderPresent(grender);
				}
				else
				{
					if (gameoverbool == 1)
					{

					}
					else
					{
						SDL_GetMouseState(&mousex, &mousey);
						if (guideone == 1)
						{
						}
						else
						{
						SDL_GetMouseState(&mousex, &mousey);
						if (cameralock == 1)
						{
							if (ball1.x < 600)
							{
								camerascroll(yikes, *currentground, *currentenemy, *currentrects, LEFT, -banespeed, interceptorz);
							}
							if (ball1.x > 1200)
							{
								camerascroll(yikes, *currentground, *currentenemy, *currentrects, RIGHT, -banespeed, interceptorz);
							}
							if (ball1.y > 600)
							{
								camerascroll(yikes, *currentground, *currentenemy, *currentrects, DOWN, -banespeed, interceptorz);
							}
							if (ball1.y < 400)
							{
								camerascroll(yikes, *currentground, *currentenemy, *currentrects, UP, -banespeed, interceptorz);
							}
						}
						else if (longcamera == 1)
						{
							if (mousex > screen_width - 150)
							{
								if (mousex > screen_width - 35)
								{
									camerascroll(yikes, *currentground, *currentenemy, *currentrects, RIGHT, -15, interceptorz);
								}
								else
								{
									camerascroll(yikes, *currentground, *currentenemy, *currentrects, RIGHT, -7, interceptorz);
								}
							}
							if (mousex < 150)
							{
								if (mousex < 35)
								{
									camerascroll(yikes, *currentground, *currentenemy, *currentrects, LEFT, -15, interceptorz);
								}
								else
								{
									camerascroll(yikes, *currentground, *currentenemy, *currentrects, LEFT, -7, interceptorz);
								}
							}
							if (mousey < 100)
							{
								if (mousey < 35)
								{
									camerascroll(yikes, *currentground, *currentenemy, *currentrects, UP, -15, interceptorz);
								}
								else
								{
									camerascroll(yikes, *currentground, *currentenemy, *currentrects, UP, -7, interceptorz);
								}
							}
							if (mousey > screen_height - 100)
							{
								if (mousey > screen_height - 35)
								{
									camerascroll(yikes, *currentground, *currentenemy, *currentrects, DOWN, -15, interceptorz);
								}
								else
								{
									camerascroll(yikes, *currentground, *currentenemy, *currentrects, DOWN, -7, interceptorz);
								}
							}
						}
						else//1950,1100 
						{
							if (mousex > 1300)
							{
								if (mousex > screen_width - 35)
								{
									camerascroll(yikes, *currentground, *currentenemy, *currentrects, RIGHT, -10, interceptorz);
								}
								else
								{
									camerascroll(yikes, *currentground, *currentenemy, *currentrects, RIGHT, -5, interceptorz);
								}
							}
							if (mousex < 700)
							{
								if (mousex < 35)
								{
									camerascroll(yikes, *currentground, *currentenemy, *currentrects, LEFT, -10, interceptorz);
								}
								else
								{
									camerascroll(yikes, *currentground, *currentenemy, *currentrects, LEFT, -5, interceptorz);
								}
							}
							if (mousey < 350)
							{
								if (mousey < 35)
								{
									camerascroll(yikes, *currentground, *currentenemy, *currentrects, UP, -10, interceptorz);
								}
								else
								{
									camerascroll(yikes, *currentground, *currentenemy, *currentrects, UP, -5, interceptorz);
								}
							}
							if (mousey > 800)
							{
								if (mousey > screen_height - 35)
								{
									camerascroll(yikes, *currentground, *currentenemy, *currentrects, DOWN, -10, interceptorz);
								}
								else
								{
									camerascroll(yikes, *currentground, *currentenemy, *currentrects, DOWN, -5, interceptorz);
								}
							}
						}
						}
					}
					//player move, enemies move and heart spawn, then ground enemy player ui render, then death stuff
					whatamion(yikes, *currentground);
					movefunction();
					if (cameralockcount == 0)
					{
						cameralockfill = yikes;
					}
					SDL_SetRenderDrawColor(grender, 255, 255, 255, 255);
					SDL_RenderClear(grender);
					SDL_RenderCopy(grender, snow, 0, 0);

					if (currentlevel == 1)
					{
						enemymoveslope(leveloneenemies[0], 200, 4, 1);
						enemymoveleftonly(leveloneenemies[14], 1350, 10);
						enemyrectclock(leveloneenemies[1], levelonerects[0], 8, leveloneenemies[1].thebool);
						enemyrectclock(leveloneenemies[2], levelonerects[0], 8, leveloneenemies[2].thebool);
						enemyrectclock(leveloneenemies[3], levelonerects[0], 8, leveloneenemies[3].thebool);
						enemyrectclock(leveloneenemies[4], levelonerects[0], 8, leveloneenemies[4].thebool);
						enemyrectclock(leveloneenemies[5], levelonerects[0], 8, leveloneenemies[5].thebool);
						enemyrectclock(leveloneenemies[6], levelonerects[0], 8, leveloneenemies[6].thebool);
						enemyrectclock(leveloneenemies[7], levelonerects[1], 8, leveloneenemies[7].thebool);
						enemyrectclock(leveloneenemies[8], levelonerects[1], 8, leveloneenemies[8].thebool);
						enemyrectclock(leveloneenemies[9], levelonerects[1], 8, leveloneenemies[9].thebool);
						enemyrectclock(leveloneenemies[10], levelonerects[1], 8, leveloneenemies[10].thebool);
						enemyrectclock(leveloneenemies[11], levelonerects[1], 8, leveloneenemies[11].thebool);
						enemyrectclock(leveloneenemies[12], levelonerects[1], 8, leveloneenemies[12].thebool);
						enemyrectclock(leveloneenemies[15], levelonerects[2], 10, leveloneenemies[15].thebool);
						if (zealotrandompickagain == 1)
						{
							for (int i = 16; i < leveloneenemies.size(); i++)
							{
								leveloneenemies[i].thebool = 0;
								int randomseed = rand() % 5;
								if (randomseed == 1)
								{
									leveloneenemies[i].randomspeed = rand() % 3 + 1;
									leveloneenemies[i].dir = (dir)(rand() % 2);
									leveloneenemies[i].thebool = 1;
									leveloneenemies[i].randomlength = rand() % 200 + 150;
									leveloneenemies[i].randomslope = 1;
									int negative = rand() % 2;
									if (negative == 0)
									{
										leveloneenemies[i].randomslope = leveloneenemies[i].randomslope * -1;
									}
								}
							}
							zealotrandompickagain = 0;
						}
						for (int i = 16; i < leveloneenemies.size(); i++)
						{
							if (leveloneenemies[i].thebool == 1)
							{
								enemymovesloperandom(leveloneenemies[i], leveloneenemies[i].randomlength, leveloneenemies[i].randomspeed, leveloneenemies[i].randomslope, levelonerects[3]);
							}
						}
						if (zealotrandomcounter == 100)
						{
							zealotrandompickagain = 1;
							zealotrandomcounter = 0;
						}
						zealotrandomcounter++;
						if (healthonegone == 0)
						{
							SDL_RenderCopy(grender, heart, 0, &levelonerects[4]);
						}
						SDL_Rect ball2rect = { ball2.x,ball2.y,player_width,player_height };
						SDL_Rect ball3rect = { ball3.x,ball3.y,player_width,player_height };
						SDL_Rect ball4rect = { ball4.x,ball4.y,player_width,player_height };
						SDL_Rect ball5rect = { ball5.x,ball5.y,player_width,player_height };
						SDL_Rect ball6rect = { ball6.x,ball6.y,player_width,player_height };
						SDL_Rect ball7rect = { ball7.x,ball7.y,player_width,player_height };
						//SDL_Rect yikes2 = { 250,50,30,30 };
						//SDL_Rect femrect = { 400,200,150,150 };
						//SDL_Rect square = { 202,252,100,100 };
						//SDL_Rect square2 = { 100,100,10,10 };
						//SDL_Rect screen = { 0,0,screen_width,screen_height };	
					}
					if (currentlevel == 2)
					{
						if (enemyoneswitch == 0)
						{
							enemymoveslopejustright(leveltwoenemies[0], 325, 4, -2);
						}
						else
						{
							if (enemyonemoveright == 0)
							{
								leveltwoenemies[0].rect.x -= 8;
							}
							else
							{
								leveltwoenemies[0].rect.x += 8;
							}
							if (leveltwoenemies[0].rect.x > leveltwoenemies[0].originalrect.x + 785)
							{
								enemyonemoveright = 0;
							}
							if (leveltwoenemies[0].rect.x < leveltwoenemies[0].originalrect.x + 330)
							{
								enemyonemoveright = 1;
								enemyoneswitch = 0;
							}
						}
						enemymoveslopeleftright(leveltwoenemies[1], 150, 2, -1);
						enemymovedownup(leveltwoenemies[2], 650, 6);
						enemymovedownup(leveltwoenemies[3], 550, 6);
						enemyrotate(leveltwoenemies[4]);
						enemyrotate(leveltwoenemies[5]);
						enemyrotate(leveltwoenemies[6]);
						enemyrotateleveltwo(leveltwoenemies[14]);
						enemyrotateleveltwo(leveltwoenemies[15]);
						enemymoverightleft(leveltwoenemies[9], 750, 5);
						enemymoverightleft(leveltwoenemies[7], 1250, 5);
						enemymovemiddleleftright(leveltwoenemies[10], 650, 7);
						enemymoverightleft(leveltwoenemies[11], 350, 6);
						enemymoveleftright(leveltwoenemies[12], 420, 7);
						enemymovemiddleleftright(leveltwoenemies[13], 200, 7);
						if (enemyeightswitch == 0)
						{
							enemymoverightleft(leveltwoenemies[8], 500, 5);
							if (enemyeightcounter == 2)
							{
								enemyeightswitch = 1;
								enemyeightcounter = 0;
								leveltwoenemies[8].dir = LEFT;
							}
						}
						else
						{
							if (leveltwoenemies[8].dir == RIGHT)
							{
								wasright = 1;
							}
							else
							{
								wasright = 0;
							}
							enemymoveleftright(leveltwoenemies[8], 700, 5);
							if (leveltwoenemies[8].dir == LEFT && wasright == 1)
							{
								leveltwoenemies[8].dir = RIGHT;
							}
						}

					}
					if (currentlevel == 3)
					{
						enemyrotate(levelthreeenemies[0]);
						enemyrotate(levelthreeenemies[1]);
						enemyrotate(levelthreeenemies[2]);
						enemyrotate(levelthreeenemies[3]);
						enemyrotate(levelthreeenemies[4]);
						enemyrotate(levelthreeenemies[5]);
						enemymoveleftright(levelthreeenemies[17], 850, 16);
						enemymoverightleft(levelthreeenemies[19], 850, 18);
						enemymovemiddleleftright(levelthreeenemies[21], 425, 17);
						enemymoveleftright(levelthreeenemies[18], 850, 9);
						enemymoverightleft(levelthreeenemies[20], 850, 7);
						enemymovemiddleleftright(levelthreeenemies[22], 425, 10);
						enemymoverightleft(levelthreeenemies[23], 400, 7);
						enemymoverightleft(levelthreeenemies[24], 400, 6);
					}
					if (currentlevel == 4)
					{
						enemymoverightleft(levelfourenemies[0], 2300, 15);
						enemymovedownup(levelfourenemies[1], 450, 7);
						enemymoverightleft(levelfourenemies[2], 450, 3);
						enemymoveslope(levelfourenemies[3], 800, 5, -.3);
						enemyrectclock(levelfourenemies[4], levelfourrects[0], 7, levelfourenemies[4].thebool);
						enemymoverightleft(levelfourenemies[5], 700, 7);
						enemycosine(levelfourenemies[6], 800, 3, 150);
						enemycosine(levelfourenemies[7], 800, 3, 150);
						enemymovedownup(levelfourenemies[8], 170, 1);
						enemymoveslopejustright(levelfourenemies[9], 175, 1, 1);
						enemymoveslope(levelfourenemies[10], 300, 2, -.4);
						enemymoveslopejustright(levelfourenemies[11], 300, 2, .5);
						enemymoverightleft(levelfourenemies[12], 720, 6);
						enemymoverightleft(levelfourenemies[13], 300, 1);
						enemyrectclock(levelfourenemies[14], levelfourrects[1], 3, levelfourenemies[14].thebool);
						enemyrotate(levelfourenemies[15]);
						enemycosine(levelfourenemies[16], 0, 1, 100);
						enemycosine(levelfourenemies[17], 0, 1, 100);
						//starts at 7
					}
					if (currentlevel == 5)
					{
						enemymovedownup(levelfiveenemies[0], 200, 2);
						enemymoveupdown(levelfiveenemies[1], 300, 3);
						enemymoveupdown(levelfiveenemies[2], 200, 2);
					}
					//levels and ground

					for (int i = 0; i < (*currentground).size(); i++)
					{
						if ((*currentground)[i].thegroundtype == GRASS)
						{
								SDL_RenderCopy(grender, grass, 0, &(*currentground)[i].therect);			
						}
						else if ((*currentground)[i].thegroundtype == ICE)
						{
							SDL_RenderCopy(grender, ice, 0, &(*currentground)[i].therect);
						}
						else if ((*currentground)[i].thegroundtype == REVERSEICE)
						{
							SDL_RenderCopy(grender, reverseice, 0, &(*currentground)[i].therect);
						}
						else if ((*currentground)[i].thegroundtype == NONMOVEICE)
						{
							SDL_RenderCopy(grender, nomoveice, 0, &(*currentground)[i].therect);
						}
						else if ((*currentground)[i].thegroundtype == FASTICE)
						{
							SDL_RenderCopy(grender, fastice, 0, &(*currentground)[i].therect);
						}
						else if ((*currentground)[i].thegroundtype == DEATH)
						{
							if (((*currentground)[i].aboolean == 1))
							{

							}
							else
							{
								SDL_RenderCopy(grender, bluelaser, 0, &(*currentground)[i].therect);
							}
						}
						else
						{
							SDL_SetRenderDrawColor(grender, (*currentground)[i].r, (*currentground)[i].g, (*currentground)[i].b, 255);
							SDL_RenderFillRect(grender, &(*currentground)[i].therect);
						}
					}
					for (int i = 0; i < (*currentenemy).size(); i++)
					{
						SDL_RenderCopy(grender, (*currentenemy)[i].text, 0, &(*currentenemy)[i].rect);
					}
					//hearts and buttons and gates
					if (currentlevel == 1)
					{
						if (checkcollision(yikes, levelonerects[5]))
						{
							Mix_PlayChannel(0, levelsound, 0);
							newlevel = 1;
							ball1.x = 100;
							ball1.y = 400;
							dead = 1;
							portaltaken = 1;
							currentlevel = 2;
							speedboost = 0;
							speedboostcount = 0;
							coverupy = 950;
							coveruph = 50;
							boostjustended = 0;
							currentground = &leveltwoground;
							currentenemy = &leveltwoenemies;
							currentrects = &leveltworects;
						}
						SDL_SetRenderDrawColor(grender, 0, 0, 255, 255);
						SDL_RenderFillRect(grender, &levelonerects[5]);
					}
					else if (currentlevel == 2)
					{
						if (checkcollision(yikes, leveltworects[1]))
						{
							newlevel = 1;
							Mix_PlayChannel(0, levelsound, 0);
							ball1.x = 100;
							ball1.y = 400;
							dead = 1;
							portaltaken = 1;
							currentlevel = 3;
							speedboost = 0;
							speedboostcount = 0;
							coverupy = 950;
							coveruph = 50;
							boostjustended = 0;
							currentground = &levelthreeground;
							currentenemy = &levelthreeenemies;
							currentrects = &levelthreerects;
						}
						SDL_SetRenderDrawColor(grender, 0, 0, 255, 255);
						SDL_RenderFillRect(grender, &leveltworects[1]);
					}
					else if (currentlevel == 3)
					{
						if (checkcollision(yikes, levelthreerects[2]))
						{
							Mix_PlayChannel(0, levelsound, 0);
							newlevel = 1;
							ball1.x = 100;
							ball1.y = 400;
							dead = 1;
							portaltaken = 1;
							currentlevel = 4;
							speedboost = 0;
							speedboostcount = 0;
							coverupy = 950;
							coveruph = 50;
							boostjustended = 0;
							currentground = &levelfourground;
							currentenemy = &levelfourenemies;
							currentrects = &levelfourrects;
						}
						SDL_SetRenderDrawColor(grender, 0, 0, 255, 255);
						SDL_RenderFillRect(grender, &levelthreerects[2]);
						if (checkcollision(yikes, levelthreerects[1]))
						{
							portaltaken = 1;
							dead = 1;
						}
						SDL_RenderCopy(grender, portal, 0, &levelthreerects[1]);
					}
					else if (currentlevel == 4)
					{
						if (checkcollision(yikes, levelfourrects[7]))
						{
							Mix_PlayChannel(0, levelsound, 0);
							newlevel = 1;
							ball1.x = 100;
							ball1.y = 400;
							dead = 1;
							portaltaken = 1;
							currentlevel = 5;
							speedboost = 0;
							speedboostcount = 0;
							coverupy = 950;
							coveruph = 50;
							boostjustended = 0;
							currentground = &levelfiveground;
							currentenemy = &levelfiveenemies;
							currentrects = &levelfiverects;
						}
						SDL_SetRenderDrawColor(grender, 0, 0, 255, 255);
						SDL_RenderFillRect(grender, &levelfourrects[7]);
						if (checkcollision(yikes, levelfourrects[6]) || checkcollision(yikes, levelfourrects[5]))
						{
							portaltaken = 1;
							dead = 1;
						}
						SDL_RenderCopy(grender, portal, 0, &levelfourrects[5]);
						SDL_RenderCopy(grender, portal, 0, &levelfourrects[6]);
						if (checkcollision(yikes, levelfourrects[2]) && buttononepressed == 0)
						{
							buttononepressed = 1;
						}
						if (checkcollision(yikes, levelfourrects[3]) && buttontwopressed == 0)
						{
							buttontwopressed = 1;
						}
						if (buttononepressed == 1)
						{
							SDL_RenderCopy(grender, buttonred, 0, &levelfourrects[2]);
						}
						else
						{
							SDL_RenderCopy(grender, buttongreen, 0, &levelfourrects[2]);
						}
						if (buttontwopressed == 1)
						{
							SDL_RenderCopy(grender, buttonred, 0, &levelfourrects[3]);
						}
						else
						{
							SDL_RenderCopy(grender, buttongreen, 0, &levelfourrects[3]);
						}
						if (buttononepressed == 1 && buttontwopressed == 1)
						{

						}
						else
						{
							if (checkcollision(yikes, levelfourrects[4]))
							{
								ball1.x -= 10;
							}
							SDL_RenderCopy(grender, gate, 0, &levelfourrects[4]);
						}
					}
					else if (currentlevel == 5)
					{
						levelfive();
						SDL_RenderFillRect(grender, &levelfiverects[5]);
						if (checkcollision(yikes, levelfiverects[5]))
						{
							Mix_PlayChannel(0, levelsound, 0);
							newlevel = 1;
							ball1.x = 100;
							ball1.y = 400;
							dead = 1;
							portaltaken = 1;
							currentlevel = 6;
							speedboost = 0;
							speedboostcount = 0;
							coverupy = 950;
							coveruph = 50;
							boostjustended = 0;
							currentground = &levelsixground;
							currentenemy = &levelsixenemies;
							currentrects = &levelsixrects;
						}

					}
					else if (currentlevel == 6)
					{
						if (cheersonce == 1)
						{
							Mix_PlayChannel(0, cheer, 0);

							cheersonce = 0;
						}
						if (Mix_PlayingMusic() == 0)
						{
							if (firstsong == 1)
							{
								Mix_PlayMusic(greatbigsled, 2);
								firstsong = 0;
							}
							else if (firstsong == 0)
							{
								Mix_PlayMusic(wishlist, 2);
								firstsong = 1;
							}
						}
						SDL_RenderCopy(grender, victory, 0, &levelsixrects[0]);
						SDL_RenderCopy(grender, avilo, 0, &levelsixrects[1]);
						SDL_RenderCopy(grender, architect, 0, &levelsixrects[2]);
						SDL_RenderCopy(grender, heartman, 0, &levelsixrects[3]);
						if (checkcollision(yikes, levelsixrects[7]))
						{
							Mix_PlayChannel(-1, peesound, 0);
						}
						SDL_RenderCopy(grender, peeguy, 0, &levelsixrects[7]);

						if (checkcollision(yikes, levelsixrects[1]))
						{
							SDL_RenderCopy(grender, aviloquote, 0, &levelsixrects[4]);
						}
						if (checkcollision(yikes, levelsixrects[3]))
						{
							SDL_RenderCopy(grender, heartmanquote, 0, &levelsixrects[5]);
						}
						if (checkcollision(yikes, levelsixrects[2]))
						{
							SDL_RenderCopy(grender, architectquote, 0, &levelsixrects[6]);
						}
						
					}
					if (healththreegone == 0 && currentlevel == 3)
					{
						SDL_RenderCopy(grender, heart, 0, &levelthreerects[0]);
					}
					if (healthtwogone == 0 && currentlevel == 2)
					{
						SDL_RenderCopy(grender, heart, 0, &leveltworects[0]);
					}
					if (healthonegone == 0 && currentlevel == 1)
					{
						SDL_RenderCopy(grender, heart, 0, &levelonerects[4]);
					}

					//player stuff
					yikes.x = ball1.x; yikes.y = ball1.y; yikes.w = player_width; yikes.h = player_height;
					if (cameralock == 1)
					{
						if (cameralockcount > 0)
						{
							yikes.x = ball1.x; yikes.y = ball1.y;
							SDL_RenderCopyEx(grender, ball1.skin, 0, &yikes, playerangle, 0, SDL_FLIP_NONE);
							cameralockcount = 0;
						}
					}
					else
					{
						yikes.x = ball1.x; yikes.y = ball1.y;
						SDL_RenderCopyEx(grender, ball1.skin, 0, &yikes, playerangle, 0, SDL_FLIP_NONE);
					}
					//UI STUFF
					speedgoocoverup = { 1650,coverupy,50,coveruph };
					SDL_RenderCopy(grender, number, 0, &liverect);
					SDL_RenderCopy(grender, heart, 0, &heartrect);
					SDL_RenderCopy(grender, goodrop, 0, &speedgoorect);
					if (speedboost == 1)
					{
						SDL_SetRenderDrawColor(grender, 255, 0, 0, 255);
						SDL_RenderFillRect(grender, &speedgoocoverup);
					}
					if (boostjustended == 1)
					{
						if (coveruph == 0)
						{
							boostjustended = 0;
							coverupy = 950;
							coveruph = 50;
							banelingbool = 0;
						}
						else
						{
							if (boostdelay == 20)
							{
								coverupy++;
								coveruph--;
								boostdelay = 0;
							}
						}
						SDL_SetRenderDrawColor(grender, 255, 0, 0, 255);
						SDL_RenderFillRect(grender, &speedgoocoverup);
						boostdelay++;
					}
					SDL_RenderCopy(grender, guidelook, 0, &guiderect);
					
					
					if (guideone == 1)
					{
						SDL_RenderCopy(grender, guide, 0, 0);
					}
					if (gameoverbool == 1)
					{
						SDL_RenderCopy(grender, gameover, 0, 0);
					}
					SDL_Rect Mouse = { mousex,mousey,25,25 };
					SDL_RenderCopy(grender, mouseskin, 0, &Mouse);

					SDL_SetRenderDrawColor(grender, 0, 0, 0, 255);
					SDL_RenderPresent(grender);////////render present
					if (healththreegone == 0 && currentlevel == 3)
					{
						if (checkcollision(yikes, levelthreerects[0]))
						{
							playerhealth++;
							healththreegone = 1;
						}
					}
					if (healthtwogone == 0 && currentlevel == 2)
					{
						if (checkcollision(yikes, leveltworects[0]))
						{
							playerhealth++;
							healthtwogone = 1;
						}
					}
					if (healthonegone == 0 && currentlevel == 1)
					{
						if (checkcollision(yikes, levelonerects[4]))
						{
							playerhealth++;
							healthonegone = 1;
						}
					}
					//death stuff
					if (currentlevel == 5)
					{
						//carrier
						if (checkcollision(yikes, levelfiverects[0]))
						{
							dead = 1;
						}
						//interceptorz
						for (int i = 0; i < 50; i++)
						{
							if (checkcollision(yikes, interceptorz[i].rect))
							{
								dead = 1;
							}
						}
						//borders
						if (candiefrombarrier == 1)
						{
							for (int i = 26; i < 30; i++)
							{
								if (checkcollision(yikes, levelfiveground[i].therect))
								{
									dead = 1;
								}
							}
						}
						else
						{
						}
						//lasers
						if (levelfiverects.size() > 7 && laserphase == 1)
						{
							if (checkcollision(yikes, levelfiverects[6]) || checkcollision(yikes, levelfiverects[7]))
							{
								dead = 1;
							}
						}
						if (levelfiverects.size() > 6)
						{
							if (checkcollision(yikes, levelfiverects[6]))
							{
								dead = 1;
							}
						}
					}
					for (int i = 0; i < (*currentenemy).size(); i++)
					{
						if (checkcollision(yikes, (*currentenemy)[i].rect))
						{
							dead = 1;
						}
					}
					if (isdead(yikes, *currentground) || dead == 1)
					{
						rightclickstop = 1;
						if (currentfloor == NONMOVEICE)
						{
							rightclicked = 0;
						}
						dead = 0;
						if (gameoverbool == 0)
						{
							if (portaltaken == 1)
							{
								if (newlevel == 1)
								{
									newlevel = 0;
								}
								else
								{
									Mix_PlayChannel(0, portalsound, 0);
								}
							}
							else
							{
								Mix_PlayChannel(0, deathsound, 0);
								if (currentlevel == 6)
								{

								}
								else
								{
									playerhealth--;
									cout << endl << "you died... I am literally, truthfully, metaphorically, and sincerely sorry for your loss." << endl;
								}
							}
						}
						if (playerhealth == 0)
						{
							gameoverbool = 1;
							playerhealth = 3;
						}
						if (speedboost == 1 && banelingbool == 0)
						{
							banelingbool = 1;
						}

						portaltaken = 0;
						ball1.skin = baneling;
						rightclicked = false;
						pastflooroff = 0;//dont get stuck when you die on snow
						if (currentlevel == 5)
						{
							levelfiveground[0].therect.x = levelfiveground[1].therect.x - 250;
						}
						ball1.x = (*currentground)[0].therect.x + 50;
						ball1.y = (*currentground)[0].therect.y + 50;
						ball2.x = leveloneground[0].therect.x - 10 + leveloneground[0].therect.w / 2;
						ball2.y = leveloneground[0].therect.y + leveloneground[0].therect.y / 2;
						ball3.x = leveloneground[0].therect.x - 20 + leveloneground[0].therect.w / 2;
						ball3.y = leveloneground[0].therect.y + leveloneground[0].therect.y / 2;
						ball4.x = leveloneground[0].therect.x - 30 + leveloneground[0].therect.w / 2;
						ball4.y = leveloneground[0].therect.y + leveloneground[0].therect.y / 2;
						ball5.x = leveloneground[0].therect.x - 40 + leveloneground[0].therect.w / 2;
						ball5.y = leveloneground[0].therect.y + leveloneground[0].therect.y / 2;
						ball6.x = leveloneground[0].therect.x - 50 + leveloneground[0].therect.w / 2;
						ball6.y = leveloneground[0].therect.y + leveloneground[0].therect.y / 2;
						ball7.x = leveloneground[0].therect.x - 60 + leveloneground[0].therect.w / 2;
						ball7.y = leveloneground[0].therect.y + leveloneground[0].therect.y / 2;


						if (currentlevel == 5)
						{
							levelfiveground[0].therect.x = levelfiveground[1].therect.x - 250;
							if (laserphase == 1)
							{
								levelfiverects.pop_back();
								levelfiverects.pop_back();
							}
							if (levelfiverects.size() > 6)
							{
								levelfiverects.pop_back();
							}
							for (int i = 26; i < 30; i++)
							{
								levelfiveground[i].aboolean = 1;
							}

							buttononepressed = 0;
							buttontwopressed = 0;
							//level 5 boss
							bossx = (*currentground)[0].therect.x + 1300;
							bossy = (*currentground)[0].therect.y - 100;
							bossspawn = 0;

							spawncounter = 0;
							currentinterceptor = 0;
							switchfloorcount = 0;
							levelfiveground[1].thegroundtype = ICE;
							laserphase = 0;
							spawnlaser = 1;
							laserswitch = 0;
							lasercount = 0;
							interceptphase = 1;
							chasephase = 0;
							chasephaseonce = 1;
							phoenixphase = 0;
							playershoot = 0;
							laserincrement = 0;
							laserspawn = 1;
							phoenixonce = 1;
							candiefrombarrier = 0;
							carriergoup = 1;
							interceptorcosine = 0;
							lastphasecounter = 0;
							interceptorspawn = 50;
							carrierhealth = 400;
							endphase = 0;
							explosioncounter = 0;
							finalphase = 0;
							for (int i = 0; i < 50; i++)
							{
								interceptorz[i].rect = { 0,0,25,25 }; interceptorz[i].originalrect = { 0,0,0,0 }; interceptorz[i].angle = 0; interceptorz[i].thebool = 0; interceptorz[i].text = interceptor;
							}
							levelfiverects[0] = { bossx,bossy,400,400 };
							levelfiverects[1] = { (*currentground)[0].therect.x + 400,(*currentground)[0].therect.y - 300,50,10000 };
							////5325,300,300,300 grass
							levelfiverects[2] = { (*currentground)[20].therect.x + 200,(*currentground)[20].therect.y + 100,150,150 };//(*currentground)[0].therect.x + 400
							levelfiverects[3] = { 0,0,0,0 };
							levelfiverects[4] = { 0,0,0,0 };



						}

						phone = { static_cast<double>((*currentground)[0].therect.x + (*currentground)[0].therect.w / 2),static_cast<double>((*currentground)[0].therect.y + (*currentground)[0].therect.y / 2) };
						phtwo = { static_cast<double>(leveloneground[0].therect.x - 10 + leveloneground[0].therect.w / 2),static_cast<double>(leveloneground[0].therect.y + leveloneground[0].therect.y / 2) };
						phthree = { static_cast<double>(leveloneground[0].therect.x - 20 + leveloneground[0].therect.w / 2),static_cast<double>(leveloneground[0].therect.y + leveloneground[0].therect.y / 2) };
						phfour = { static_cast<double>(leveloneground[0].therect.x - 30 + leveloneground[0].therect.w / 2),static_cast<double>(leveloneground[0].therect.y + leveloneground[0].therect.y / 2) };
						phfive = { static_cast<double>(leveloneground[0].therect.x - 40 + leveloneground[0].therect.w / 2),static_cast<double>(leveloneground[0].therect.y + leveloneground[0].therect.y / 2) };
						phsix = { static_cast<double>(leveloneground[0].therect.x - 50 + leveloneground[0].therect.w / 2),static_cast<double>(leveloneground[0].therect.y + leveloneground[0].therect.y / 2) };
						rightclicked = false;
						xincrement = 0;
						slope = 0;
						ydiff = 0;
						xdiff = 0;
						playerfloor = GRASS;
						banespeed = 3;
					}
					cameralockputback = 0;
					cameralockcount++;
					//SDL_Delay(1000);
				}
			}
		}
	}

	close();
	return 0;
}

bool init() //initialize video, screen, render and color, lineartexture, IMG
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			success = false;
		}
		
		gwindow = SDL_CreateWindow("Ice Baneling Escape", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, 0);//|| SDL_WINDOW_FULLSCREEN
		if (gwindow == 0)
		{
			success = false;
		}
		grender = SDL_CreateRenderer(gwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (grender == 0)
		{
			success = false;
		}
		else
		{
			SDL_SetRenderDrawColor(grender, 255, 255, 255, 255);

			int imgflags = IMG_INIT_PNG;
			if (!(IMG_Init(imgflags) & imgflags))
			{
				success = false;
			}
			Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		}
		if (TTF_Init() == -1)
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
			success = false;
		}
		SDL_ShowCursor(SDL_DISABLE);
		srand(time(0));
	}


	return success;
}
bool loadmedia()
{
	bool success = true;
	ball = loadimageclear("dot.BMP");
	if (ball == 0)
	{
		success = false;
	}
	ball1.skin = ball;
	SDL_Color colorwhite = { 0,0,0 };
	SDL_Color blue = { 0,0,255 };
	gfont = TTF_OpenFont("NewAmsterdam.ttf", 28);
	number = loadtext(to_string(playerhealth),colorwhite);
	victory = loadtext("Victory!", blue);
	aviloquote = loadtext("GET AWAY FROM ME YOU FUCKING MAPHACKER! BLIZZARD BALANCE THIS GAME!", colorwhite);
	architectquote = loadtext("With effort, intelligence and consideration, nothing is impossible... right?", colorwhite);
	heartmanquote = loadtext("I seek this girls attention... the one with the behemoth attraction, an enthralling smile, and of course... that curly hair I immensely want to curl right next to.", colorwhite);//She had a collosus attraction, an enthralling smile, and of course... that curly hair that I wanted to curl right next to immensely.



	baneling = loadimage("baneling.PNG");
	banelingspeed = loadimage("banelingspeed.PNG");
	snow = loadimage("snow.JPG");
	mouseskin = loadimage("scmouse.PNG");
	grass = loadimage("grass.JPG");
	ice = loadimage("ice.JPG");
	nomoveice = loadimage("nonmoveice.PNG");
	zealot = loadimage("zealot.JPG");
	goodrop = loadimage("goodrop.PNG");
	heart = loadimage("heart.PNG");
	gameover = loadimage("gameover.JPG");
	reverseice = loadimage("reverseice.JPG");
	fastice = loadimage("fastice.JPG");
	buttongreen = loadimage("button.PNG");
	buttonred = loadimage("buttonred.PNG");
	gate = loadimage("gate.PNG");
	portal = loadimage("portal.PNG");
	interceptor = loadimage("interceptor.JPG");
	carrier = loadimage("carrier.PNG");
	bluelaser = loadimage("bluelaser.PNG");
	phoenix = loadimage("phoenix.PNG");
	zealottwo = loadimage("zealotz.PNG");
	explosion = loadimage("explosion.JPG");
	artmenu = loadimage("menu.PNG");
	menu = loadimage("menu1.PNG");
	menuclick = loadimage("menu1click.PNG");
	guide = loadimage("guide.PNG");
	guidelook = loadimage("themenu.PNG");
	avilo = loadseethroughwhite("aviloface.PNG");
	heartman = loadseethrough("heart1.PNG");
	architect = loadimage("architect.PNG");
	peeguy = loadseethroughwhite("peeguy.PNG");
	

	peesound = Mix_LoadWAV("peesound.wav");
	deathsound = Mix_LoadWAV("deathsound.wav");
	portalsound = Mix_LoadWAV("portalsound.wav");
	levelsound = Mix_LoadWAV("beatlevel.wav");
	carriersound = Mix_LoadWAV("carrierhasarrived.wav");
	explosionsound = Mix_LoadWAV("Explosion.wav");
	carriersoundtwo = Mix_LoadWAV("protoss2.wav");
	carriersoundthree = Mix_LoadWAV("protoss3.wav");
	cheer = Mix_LoadWAV("cheers.wav");

	greatbigsled = Mix_LoadMUS("greatbigsled.wav");
	sledintro = Mix_LoadMUS("greatbigsledclip.wav");
	wishlist = Mix_LoadMUS("wishlist.wav");

	return success;
}
SDL_Texture* loadseethroughwhite(string a)
{
	SDL_Texture* returntexture = 0;
	SDL_Surface* tempsurface = IMG_Load(a.c_str());
	SDL_SetColorKey(tempsurface, SDL_TRUE, SDL_MapRGB(tempsurface->format, 255, 255, 255)); //white
	returntexture = SDL_CreateTextureFromSurface(grender, tempsurface);
	SDL_FreeSurface(tempsurface);
	return returntexture;
}
SDL_Texture* loadseethrough(string a)
{
	SDL_Texture* returntexture = 0;
	SDL_Surface* tempsurface = IMG_Load(a.c_str());
	SDL_SetColorKey(tempsurface, SDL_TRUE, SDL_MapRGB(tempsurface->format, 0, 0, 0)); //black
	returntexture = SDL_CreateTextureFromSurface(grender, tempsurface);
	SDL_FreeSurface(tempsurface);
	return returntexture;
}
void leveloneinitialize()
{
	ground grassone;
	grassone.therect = { 0,300,250,200 };
	grassone.thegroundtype = GRASS;
	grassone.r = 0; grassone.g = 255; grassone.b = 0;
	ground grasstwo;
	grasstwo.therect = { 1750,300,200,200 };
	grasstwo.thegroundtype = GRASS;
	grasstwo.r = 0; grasstwo.g = 255; grasstwo.b = 0;
	ground grassthree;
	grassthree.therect = { 1950,-500,400,600 };
	grassthree.thegroundtype = GRASS;
	grassthree.r = 0; grassthree.g = 255; grassthree.b = 0;
	ground grassfour;
	grassfour.therect = { 2150,100,200,200 };
	grassfour.thegroundtype = GRASS;
	grassfour.r = 0; grassfour.g = 255; grassfour.b = 0;
	ground grassfive;
	grassfive.therect = { -200,-1100,200,1200 };
	grassfive.thegroundtype = GRASS;
	grassfive.r = 0; grassfive.g = 255; grassfive.b = 0;
	ground grasssix;
	grasssix.therect = { 1950,-1100,400,400 };
	grasssix.thegroundtype = GRASS;
	grasssix.r = 0; grasssix.g = 255; grasssix.b = 0;
	ground grassseven;
	grassseven.therect = { -600,-700,400,200 };
	grassseven.thegroundtype = GRASS;
	grassseven.r = 0; grassseven.g = 255; grassseven.b = 0;
	ground grasseight;
	grasseight.therect = { -600,-100,200,200 };
	grasseight.thegroundtype = GRASS;
	grasseight.r = 0; grasseight.g = 255; grasseight.b = 0;
	ground fastone;
	fastone.thegroundtype = FASTICE;
	fastone.therect = {};
	fastone.r = 58; fastone.g = 7; fastone.b = 77;
	ground iceone;
	iceone.therect = { 250,300,1500,200 };
	iceone.thegroundtype = ICE;
	iceone.r = 105; iceone.g = 193; iceone.b = 245;
	ground icetwo;
	icetwo.therect = { 1950,300,400,200 };
	icetwo.thegroundtype = ICE;
	icetwo.r = 105; icetwo.g = 193; icetwo.b = 245;
	ground icethree;
	icethree.therect = { 0,-500,1950,600 };
	icethree.thegroundtype = ICE;
	icethree.r = 105; icethree.g = 193; icethree.b = 245;
	ground icefour;
	icefour.therect = { 0,-1100,1950,400 };
	icefour.thegroundtype = ICE;
	icefour.r = 105; icefour.g = 193; icefour.b = 245;
	ground icefive;
	icefive.therect = { -600,-500,200,400 };
	icefive.thegroundtype = NONMOVEICE;
	icefive.r = 211; icefive.g = 227; icefive.b = 236;
	ground nonmoveone;
	nonmoveone.therect = {};
	nonmoveone.thegroundtype = NONMOVEICE;
	nonmoveone.r = 211; nonmoveone.g = 227; nonmoveone.b = 236;
	ground reverseiceone;
	reverseiceone.therect = {};
	reverseiceone.thegroundtype = REVERSEICE;
	reverseiceone.r = 236; reverseiceone.g = 129; reverseiceone.b = 225;

	if (leveloneonce == 0)//get enemies and ground in 2 vectors
	{
		leveloneground.push_back(grassone);
		leveloneground.push_back(grasstwo);
		leveloneground.push_back(grassthree);
		leveloneground.push_back(grassfour);
		leveloneground.push_back(grassfive);
		leveloneground.push_back(grasssix);
		leveloneground.push_back(grassseven);
		leveloneground.push_back(grasseight);
		leveloneground.push_back(iceone);
		leveloneground.push_back(icetwo);
		leveloneground.push_back(icethree);
		leveloneground.push_back(icefour);
		leveloneground.push_back(icefive);
		leveloneground.push_back(fastone);
		//leveloneground.push_back(snowone);
		//leveloneground.push_back(snowtwo);
		leveloneground.push_back(nonmoveone);
		leveloneground.push_back(reverseiceone);
		leveloneonce = 1;
	}
	ball1.skin = baneling;
    yikes = { static_cast<int>(ball1.x),static_cast<int>(ball1.y),player_width,player_height };
	enemy enemyone;
	enemyone.rect = { 2250,450,50,50 }; enemyone.originalrect = { 2250,450,50,50 }; enemyone.dir = RIGHT; enemyone.thebool = 0; enemyone.text = zealot;

	enemy enemytwo;
	enemytwo.rect = { 300,450,50,50 }; enemytwo.originalrect = { 300,450,50,50 }; enemytwo.dir = LEFT; enemytwo.thebool = 0; enemytwo.text = zealot;
	SDL_Rect enemytworect = { 275,450,1400,50 };
	enemy enemythree;
	enemythree.rect = { 700,500,50,50 }; enemythree.originalrect = { 700,500,50,50 }; enemythree.dir = LEFT; enemythree.thebool = 0; enemythree.text = zealot;
	enemy enemyfour;
	enemyfour.rect = { 1300,500,50,50 }; enemyfour.originalrect = { 1300,500,50,50 }; enemyfour.dir = LEFT; enemyfour.thebool = 0; enemyfour.text = zealot;
	enemy enemyfive;
	enemyfive.rect = { 1800,500,50,50 }; enemyfive.originalrect = { 1800,500,50,50 }; enemyfive.dir = LEFT; enemyfive.thebool = 0; enemyfive.text = zealot;
	enemy enemysix;
	enemysix.rect = { 2300,500,50,50 }; enemysix.originalrect = { 2300,500,50,50 }; enemysix.dir = LEFT; enemysix.thebool = 0; enemysix.text = zealot;
	enemy enemyseven;
	enemyseven.rect = { 2800,500,50,50 }; enemyseven.originalrect = { 2800,500,50,50 }; enemyseven.dir = LEFT; enemyseven.thebool = 0; enemyseven.text = zealot;

	enemy enemynine;
	enemynine.rect = { 300,350,50,50 }; enemynine.originalrect = { 300,350,50,50 }; enemynine.dir = LEFT; enemynine.thebool = 0; enemynine.text = zealot;
	SDL_Rect enemythreerect = { 275,275,1400,50 };
	enemy enemyten;
	enemyten.rect = { 700,275,50,50 }; enemyten.originalrect = { 700,275,50,50 }; enemyten.dir = LEFT; enemyten.thebool = 0; enemyten.text = zealot;
	enemy enemyeleven;
	enemyeleven.rect = { 1300,325,50,50 }; enemyeleven.originalrect = { 1300,325,50,50 }; enemyeleven.dir = LEFT; enemyeleven.thebool = 0; enemyeleven.text = zealot;
	enemy enemytwelve;
	enemytwelve.rect = { 1800,325,50,50 }; enemytwelve.originalrect = { 1800,325,50,50 }; enemytwelve.dir = LEFT; enemytwelve.thebool = 0; enemytwelve.text = zealot;
	enemy enemythirteen;
	enemythirteen.rect = { 2300,325,50,50 }; enemythirteen.originalrect = { 2300,325,50,50 }; enemythirteen.dir = LEFT; enemythirteen.thebool = 0; enemythirteen.text = zealot;
	enemy enemyfourteen;
	enemyfourteen.rect = { 2800,325,50,50 }; enemyfourteen.originalrect = { 2800,325,50,50 }; enemyfourteen.dir = LEFT; enemyfourteen.thebool = 0; enemyfourteen.text = zealot;
	enemy enemyfifteen;
	enemyfifteen.rect = { 3300,325,50,50 }; enemyfifteen.originalrect = { 3300,325,50,50 }; enemyfifteen.dir = LEFT; enemyfifteen.thebool = 0; enemyfifteen.text = zealot;

	enemy enemysixteen;
	enemysixteen.rect = { 1500,-500,50,600 }; enemysixteen.originalrect = { 1500,-500,50,600 }; enemysixteen.dir = LEFT; enemysixteen.thebool = 0; enemysixteen.text = zealot;

	enemy enemyseventeen;
	SDL_Rect enemyfourrect = { -560,-470,100,310 };
	SDL_Rect randomrect = { 0,-1100,1950,400 };
	enemyseventeen.rect = { -560,-470,25,25 }; enemyseventeen.originalrect = { -500,-470,25,25 }; enemyseventeen.dir = LEFT; enemyseventeen.thebool = 0; enemyseventeen.text = zealot;

	//rect 0,-1100,1950,400
	//random 20 enemies
	enemy randomone;
	randomone.rect = { (rand() % 1875 + 25), (rand() % 275 - 1075),50,50 }; randomone.originalrect = randomone.rect; randomone.dir = (dir)(rand() % 4); randomone.text = zealot; randomone.thebool = 0;
	enemy randomtwo;
	randomtwo.rect = { (rand() % 1875 + 25), (rand() % 275 - 1075),50,50 }; randomtwo.originalrect = randomtwo.rect; randomtwo.dir = (dir)(rand() % 4); randomtwo.text = zealot; randomtwo.thebool = 0;
	enemy randomthree;
	randomthree.rect = { (rand() % 1875 + 25), (rand() % 275 - 1075),50,50 }; randomthree.originalrect = randomthree.rect; randomthree.dir = (dir)(rand() % 4); randomthree.text = zealot; randomthree.thebool = 0;
	enemy randomfour;
	randomfour.rect = { (rand() % 1875 + 25), (rand() % 275 - 1075),50,50 }; randomfour.originalrect = randomfour.rect; randomfour.dir = (dir)(rand() % 4); randomfour.text = zealot; randomfour.thebool = 0;
	enemy randomfive;
	randomfive.rect = { (rand() % 1875 + 25), (rand() % 275 - 1075),50,50 }; randomfive.originalrect = randomfive.rect; randomfive.dir = (dir)(rand() % 4); randomfive.text = zealot; randomfive.thebool = 0;
	enemy randomsix;
	randomsix.rect = { (rand() % 1875 + 25), (rand() % 275 - 1075),50,50 }; randomsix.originalrect = randomsix.rect; randomsix.dir = (dir)(rand() % 4); randomsix.text = zealot; randomsix.thebool = 0;
	enemy randomseven;
	randomseven.rect = { (rand() % 1875 + 25), (rand() % 275 - 1075),50,50 }; randomseven.originalrect = randomseven.rect; randomseven.dir = (dir)(rand() % 4); randomseven.text = zealot; randomseven.thebool = 0;
	enemy randomeight;
	randomeight.rect = { (rand() % 1875 + 25), (rand() % 275 - 1075),50,50 }; randomeight.originalrect = randomeight.rect; randomeight.dir = (dir)(rand() % 4); randomeight.text = zealot; randomeight.thebool = 0;
	enemy randomnine;
	randomnine.rect = { (rand() % 1875 + 25), (rand() % 275 - 1075),50,50 }; randomnine.originalrect = randomnine.rect; randomnine.dir = (dir)(rand() % 4); randomnine.text = zealot; randomnine.thebool = 0;
	enemy randomten;
	randomten.rect = { (rand() % 1875 + 25), (rand() % 275 - 1075),50,50 }; randomten.originalrect = randomten.rect; randomten.dir = (dir)(rand() % 4); randomten.text = zealot; randomten.thebool = 0;
	enemy randomeleven;
	randomeleven.rect = { (rand() % 1875 + 25), (rand() % 275 - 1075),50,50 }; randomeleven.originalrect = randomeleven.rect; randomeleven.dir = (dir)(rand() % 4); randomeleven.text = zealot; randomeleven.thebool = 0;
	enemy randomtwelve;
	randomtwelve.rect = { (rand() % 1875 + 25), (rand() % 275 - 1075),50,50 }; randomtwelve.originalrect = randomtwelve.rect; randomtwelve.dir = (dir)(rand() % 4); randomtwelve.text = zealot; randomtwelve.thebool = 0;
	enemy randomthirteen;
	randomthirteen.rect = { (rand() % 1875 + 25), (rand() % 275 - 1075),50,50 }; randomthirteen.originalrect = randomthirteen.rect; randomthirteen.dir = (dir)(rand() % 4); randomthirteen.text = zealot; randomthirteen.thebool = 0;
	enemy randomfourteen;
	randomfourteen.rect = { (rand() % 1875 + 25), (rand() % 275 - 1075),50,50 }; randomfourteen.originalrect = randomfourteen.rect; randomfourteen.dir = (dir)(rand() % 4); randomfourteen.text = zealot; randomfourteen.thebool = 0;
	enemy randomfifteen;
	randomfifteen.rect = { (rand() % 1875 + 25), (rand() % 275 - 1075),50,50 }; randomfifteen.originalrect = randomfifteen.rect; randomfifteen.dir = (dir)(rand() % 4); randomfifteen.text = zealot; randomfifteen.thebool = 0;
	enemy randomsixteen;
	randomsixteen.rect = { (rand() % 1875 + 25), (rand() % 275 - 1075),50,50 }; randomsixteen.originalrect = randomsixteen.rect; randomsixteen.dir = (dir)(rand() % 4); randomsixteen.text = zealot; randomsixteen.thebool = 0;
	enemy randomseventeen;
	randomseventeen.rect = { (rand() % 1875 + 25), (rand() % 275 - 1075),50,50 }; randomseventeen.originalrect = randomseventeen.rect; randomseventeen.dir = (dir)(rand() % 4); randomseventeen.text = zealot; randomseventeen.thebool = 0;
	enemy randomeighteen;
	randomeighteen.rect = { (rand() % 1875 + 25), (rand() % 275 - 1075),50,50 }; randomeighteen.originalrect = randomeighteen.rect; randomeighteen.dir = (dir)(rand() % 4); randomeighteen.text = zealot; randomeighteen.thebool = 0;
	enemy randomnineteen;
	randomnineteen.rect = { (rand() % 1875 + 25), (rand() % 275 - 1075),50,50 }; randomnineteen.originalrect = randomnineteen.rect; randomnineteen.dir = (dir)(rand() % 4); randomnineteen.text = zealot; randomnineteen.thebool = 0;
	enemy randomtwenty;
	randomtwenty.rect = { (rand() % 1875 + 25), (rand() % 275 - 1075),50,50 }; randomtwenty.originalrect = randomtwenty.rect; randomtwenty.dir = (dir)(rand() % 4); randomtwenty.text = zealot; randomtwenty.thebool = 0;

	//-600,-100,200,200
	SDL_Rect secretheart = { -525,-15,50,50 };

	levelonerects.push_back(enemytworect);
	levelonerects.push_back(enemythreerect);
	levelonerects.push_back(enemyfourrect);
	levelonerects.push_back(randomrect);
	levelonerects.push_back(secretheart);
	levelonerects.push_back(endone);


	leveloneenemies.push_back(enemyone);
	leveloneenemies.push_back(enemytwo);
	leveloneenemies.push_back(enemythree);
	leveloneenemies.push_back(enemyfour);
	leveloneenemies.push_back(enemyfive);
	leveloneenemies.push_back(enemysix);
	leveloneenemies.push_back(enemyseven);
	leveloneenemies.push_back(enemynine);
	leveloneenemies.push_back(enemyten);
	leveloneenemies.push_back(enemyeleven);
	leveloneenemies.push_back(enemytwelve);
	leveloneenemies.push_back(enemythirteen);
	leveloneenemies.push_back(enemyfourteen);
	leveloneenemies.push_back(enemyfifteen);
	leveloneenemies.push_back(enemysixteen);
	leveloneenemies.push_back(enemyseventeen);

	leveloneenemies.push_back(randomone);
	leveloneenemies.push_back(randomtwo);
	leveloneenemies.push_back(randomthree);
	leveloneenemies.push_back(randomfour);
	leveloneenemies.push_back(randomfive);
	leveloneenemies.push_back(randomsix);
	leveloneenemies.push_back(randomseven);
	leveloneenemies.push_back(randomeight);
	leveloneenemies.push_back(randomnine);
	leveloneenemies.push_back(randomten);
	leveloneenemies.push_back(randomeleven);
	leveloneenemies.push_back(randomtwelve);
	leveloneenemies.push_back(randomthirteen);
	leveloneenemies.push_back(randomfourteen);
	leveloneenemies.push_back(randomfifteen);
	leveloneenemies.push_back(randomsixteen);
	leveloneenemies.push_back(randomseventeen);
	leveloneenemies.push_back(randomeighteen);
	leveloneenemies.push_back(randomnineteen);
	leveloneenemies.push_back(randomtwenty);

	currentground = &leveloneground;
	currentenemy = &leveloneenemies;
	currentrects = &levelonerects;
}
void leveltwoinitialize()
{
	ground grasstwoone;
	grasstwoone.therect = { 0,300,250,200 };
	grasstwoone.thegroundtype = GRASS;
	grasstwoone.r = 0; grasstwoone.g = 255; grasstwoone.b = 0;
	ground grasstwo;
	grasstwo.therect = { 450,-600,400,100 };
	grasstwo.thegroundtype = GRASS;
	ground grassthree;
	grassthree.therect = { 25,1150,200,200};
	grassthree.thegroundtype = GRASS;
	ground grassfour;
	grassfour.therect = { 1550,850,125,125 };
	grassfour.thegroundtype = GRASS;
	ground grassfive;
	grassfive.therect = { 1550,1575,125,125 };
	grassfive.thegroundtype = GRASS;

	//15 criss cross
	ground grasssix;
	grasssix.therect = { 1675,1575,30,125 };
	grasssix.thegroundtype = GRASS;
	ground grassseven;
	grassseven.therect = { 1687,1550,50,25 };
	grassseven.thegroundtype = GRASS;
	ground grasseight;
	grasseight.therect = { 1720,1525,50,25 };
	grasseight.thegroundtype = GRASS;
	ground grassnine;
	grassnine.therect = { 1745,1500,50,25 };
	grassnine.thegroundtype = GRASS;
	ground grassten;
	grassten.therect = { 1775,1525,50,25 };
	grassten.thegroundtype = GRASS;
	ground grasseleven;
	grasseleven.therect = { 1800,1550,50,25 };
	grasseleven.thegroundtype = GRASS;
	ground grasstwelve;
	grasstwelve.therect = { 1825,1575,30,125 };
	grasstwelve.thegroundtype = GRASS;
	ground grassthirteen;
	grassthirteen.therect = { 1837,1700,50,25 };
	grassthirteen.thegroundtype = GRASS;
	ground grassfourteen;
	grassfourteen.therect = { 1863,1725,50,25 };
	grassfourteen.thegroundtype = GRASS;
	ground grassfifteen;
	grassfifteen.therect = { 1888,1750,50,25 };
	grassfifteen.thegroundtype = GRASS;
	ground grasssixteen;
	grasssixteen.therect = { 1918,1725,50,25 };
	grasssixteen.thegroundtype = GRASS;
	ground grassseventeen;
	grassseventeen.therect = { 1943,1700,50,25 };
	grassseventeen.thegroundtype = GRASS;
	ground grasseighteen;
	grasseighteen.therect = { 1968,1575,30,125 };
	grasseighteen.thegroundtype = GRASS;
	//end 15
	ground grassnineteen;
	grassnineteen.therect = { 1998,1575,525,125 };
	grassnineteen.thegroundtype = GRASS;
	ground grasstwenty;
	grasstwenty.therect = { 2400,475,125,225 };
	grasstwenty.thegroundtype = GRASS;
	ground grasstwentyone;
	grasstwentyone.therect = { 2300,-125,300,300 };
	grasstwentyone.thegroundtype = GRASS;
	ground grasstwentytwo;
	grasstwentytwo.therect = { 700,1200,100,100 };
	grasstwentytwo.thegroundtype = GRASS;

	ground iceone;
	iceone.therect = { 125,100,250,200 };
	iceone.thegroundtype = ICE;
	iceone.r = 105; iceone.g = 193; iceone.b = 245;
	ground icetwo;
	icetwo.therect = { 250,-100,250,200 };
	icetwo.thegroundtype = ICE;
	icetwo.r = 105; icetwo.g = 193; icetwo.b = 245;
	ground icethree;
	icethree.therect = { 325,-300,250,200 };
	icethree.thegroundtype = ICE;
	ground icefour;
	icefour.therect = { 450,-500,700,200 };
	icefour.thegroundtype = ICE;
	ground icefive;
	icefive.therect = { 1025,-300,125,1000 };
	icefive.thegroundtype = ICE;
	ground icesix;
	icesix.therect = { 25,1050,200,100 };
	icesix.thegroundtype = ICE;
	ground iceseven;
	iceseven.therect = { 100,950,200,100 };
	iceseven.thegroundtype = ICE;
	ground iceeight;
	iceeight.therect = { 250,700,600,400 };
	iceeight.thegroundtype = ICE;
	ground icenine;
	icenine.therect = { 2400,700,125,875 };//1575- 700
	icenine.thegroundtype = NONMOVEICE;


	ground nonmoveone;
	nonmoveone.therect = { 1025,700,125,400 };
	nonmoveone.thegroundtype = NONMOVEICE;	
	ground nonmovetwo;
	nonmovetwo.therect = { 850,850,700,125 };
	nonmovetwo.thegroundtype = NONMOVEICE;
	ground nonmovethree;
	nonmovethree.therect = { 1550,975,125,600 };
	nonmovethree.thegroundtype = NONMOVEICE;
	ground nonmovefour;
	nonmovefour.therect = { 2400,175,125,300 };
	nonmovefour.thegroundtype = NONMOVEICE;
	
	
	ground reverseone;
	reverseone.therect = { 1025,1100,125,700 };
	reverseone.thegroundtype = REVERSEICE;
	ground reversetwo;
	reversetwo.therect = { 25,1550,1000,250 };
	reversetwo.thegroundtype = REVERSEICE;
	ground reversethree;
	reversethree.therect = { 25,1350,200,200 };
	reversethree.thegroundtype = REVERSEICE;
	ground reversefour;
	reversefour.therect = { 500,1100,100,200 };
	reversefour.thegroundtype = REVERSEICE;
	ground reversefive;
	reversefive.therect = { 600,1200,100,100 };
	reversefive.thegroundtype = REVERSEICE;

	//0,300,250,200
	enemy enemyone;
	enemyone.rect = {215,225,50,50}; enemyone.originalrect = { 215,225,50,50 }; enemyone.dir = RIGHT; enemyone.thebool = 0; enemyone.text = zealot;
	enemy enemytwo;
	enemytwo.rect = {1055,900,50,50}; enemytwo.originalrect = { 1055,900,50,50 }; enemytwo.dir = RIGHT; enemytwo.thebool = 0; enemytwo.text = zealot;
	enemy enemythree;
	enemythree.rect = { 625,1225,50,50 }; enemythree.originalrect = { 625,1225,50,50 }; enemythree.dir = DOWN; enemythree.thebool = 0; enemythree.text = zealot;
	enemy enemyfour;
	enemyfour.rect = { 325,1400,50,50 }; enemyfour.originalrect = { 325,1400,50,50 }; enemyfour.dir = DOWN; enemyfour.thebool = 0; enemyfour.text = zealot;
	enemy enemyfive;// 250,700,600,400
	enemyfive.rect = { 550,900,50,50 }; enemyfive.originalrect = { 525,850,100,100 }; enemyfive.dir = DOWN; enemyfive.thebool = 0; enemyfive.text = zealot;
	enemyfive.angle = 0; enemyfive.rotatespeed = .06;
	enemy enemysix;// 250,700,600,400
	enemysix.rect = { 650,900,50,50 }; enemysix.originalrect = { 525,850,300,300 }; enemysix.dir = DOWN; enemysix.thebool = 0; enemysix.text = zealot;
	enemysix.angle = 0; enemysix.rotatespeed = .06;
	enemy enemyseven;// 250,700,600,400
	enemyseven.rect = { 750,900,50,50 }; enemyseven.originalrect = { 525,850,500,500 }; enemyseven.dir = DOWN; enemyseven.thebool = 0; enemyseven.text = zealot;
	enemyseven.angle = 0; enemyseven.rotatespeed = .06;
	//4left right 1550,850,125,125
	enemy enemyeight;
	enemyeight.rect = { 1350,1010,100,100 }; enemyeight.originalrect = { 1350,1010,100,100 }; enemyeight.dir = RIGHT; enemyeight.thebool = 0; enemyeight.text = zealot;
	enemy enemynine;
	enemynine.rect = { 2100,1150,100,100 }; enemynine.originalrect = { 2100,1150,100,100 }; enemynine.dir = RIGHT; enemynine.thebool = 0; enemynine.text = zealot;
	enemy enemyeleven;
	enemyeleven.rect = { 2000,1350,100,100 }; enemyeleven.originalrect = { 2000,1350,100,100 }; enemyeleven.dir = RIGHT; enemyeleven.thebool = 0; enemyeleven.text = zealot;
	enemy enemytwelve;
	enemytwelve.rect = { 1950,750,100,100 }; enemytwelve.originalrect = { 1950,750,100,100 }; enemytwelve.dir = RIGHT; enemytwelve.thebool = 0; enemytwelve.text = zealot;
	//3 left right 2400,175,125,400
	enemy enemythirteen;
	enemythirteen.rect = { 2275,200,50,50 }; enemythirteen.originalrect = { 2275,200,50,50 }; enemythirteen.dir = RIGHT; enemythirteen.thebool = 0; enemythirteen.text = zealot;
	enemy enemyfourteen;
	enemyfourteen.rect = { 2650,300,50,50 }; enemyfourteen.originalrect = { 2650,270,50,50 }; enemyfourteen.dir = LEFT; enemyfourteen.thebool = 0; enemyfourteen.text = zealot;
	enemy enemyfifteen;
	enemyfifteen.rect = { 2425,400,50,50 }; enemyfifteen.originalrect = { 2425,340,50,50 }; enemyfifteen.dir = RIGHT; enemyfifteen.thebool = 0; enemyfifteen.text = zealot;
	enemy enemysixteen;//1825,1575,30,125
	enemysixteen.rect = { 1825,1600,35,35 }; enemysixteen.originalrect = { 1750,1600,150,100 }; enemysixteen.dir = RIGHT; enemysixteen.thebool = 0; enemysixteen.text = zealot;
	enemysixteen.angle = 0; enemysixteen.rotatespeed = .06;
	enemy enemyseventeen;//1825,1575,30,125
	enemyseventeen.rect = { 1825,1600,35,35 }; enemyseventeen.originalrect = { 1900, 1650, 150, 100 }; enemyseventeen.dir = RIGHT; enemyseventeen.thebool = 0; enemyseventeen.text = zealot;
	enemyseventeen.angle = 0; enemyseventeen.rotatespeed = .06;

	SDL_Rect secrethearts = { 725,1225,50,50 };
	leveltworects.push_back(secrethearts);
	leveltworects.push_back(endtwo);

	leveltwoenemies.push_back(enemyone); 
	leveltwoenemies.push_back(enemytwo);
	leveltwoenemies.push_back(enemythree);
	leveltwoenemies.push_back(enemyfour);
	leveltwoenemies.push_back(enemyfive);
	leveltwoenemies.push_back(enemysix);
	leveltwoenemies.push_back(enemyseven);
	leveltwoenemies.push_back(enemyeight);
	leveltwoenemies.push_back(enemynine);
	leveltwoenemies.push_back(enemytwelve);//9
	leveltwoenemies.push_back(enemyeleven);
	leveltwoenemies.push_back(enemythirteen);
	leveltwoenemies.push_back(enemyfourteen);//12
	leveltwoenemies.push_back(enemyfifteen);
	leveltwoenemies.push_back(enemysixteen);
	leveltwoenemies.push_back(enemyseventeen);



	leveltwoground.push_back(grasstwoone);
	leveltwoground.push_back(iceone);
	leveltwoground.push_back(icetwo);
	leveltwoground.push_back(icethree);
	leveltwoground.push_back(icefour);
	leveltwoground.push_back(icefive);
	leveltwoground.push_back(icesix);
	leveltwoground.push_back(iceseven);
	leveltwoground.push_back(iceeight);
	leveltwoground.push_back(icenine);
	leveltwoground.push_back(grasstwo);
	leveltwoground.push_back(grassthree);
	leveltwoground.push_back(grassfour);
	leveltwoground.push_back(grassfive);
	leveltwoground.push_back(grasssix);
	leveltwoground.push_back(grassseven);
	leveltwoground.push_back(grasseight);
	leveltwoground.push_back(grassnine);
	leveltwoground.push_back(grassten);
	leveltwoground.push_back(grasseleven);
	leveltwoground.push_back(grasstwelve);
	leveltwoground.push_back(grassthirteen);
	leveltwoground.push_back(grassfourteen);
	leveltwoground.push_back(grassfifteen);
	leveltwoground.push_back(grasssixteen);
	leveltwoground.push_back(grassseventeen);
	leveltwoground.push_back(grasseighteen);
	leveltwoground.push_back(grassnineteen);
	leveltwoground.push_back(grasstwentyone);
	leveltwoground.push_back(grasstwentytwo);
	leveltwoground.push_back(nonmoveone);
	leveltwoground.push_back(nonmovetwo);
	leveltwoground.push_back(nonmovethree);
	leveltwoground.push_back(nonmovefour);
	leveltwoground.push_back(grasstwenty);
	leveltwoground.push_back(reverseone);
	leveltwoground.push_back(reversetwo);
	leveltwoground.push_back(reversethree);
	leveltwoground.push_back(reversefour);
	leveltwoground.push_back(reversefive);

	//currentground = &leveltwoground;
	//currentenemy = &leveltwoenemies;
	//currentrects = &leveltworects;
}
void levelthreeinitialize()
{
	ground grasstwoone;
	grasstwoone.therect = { 0,300,250,200 };
	grasstwoone.thegroundtype = GRASS;
	ground grasstwo;
	grasstwo.therect = {2400,600,300,300};
	grasstwo.thegroundtype = GRASS;
	ground grassthree;
	grassthree.therect = { 3100,-550,300,300 };
	grassthree.thegroundtype = GRASS;
	ground grassfour;
	grassfour.therect = { 1700,-2900,60, 300 };
	grassfour.thegroundtype = GRASS;
	ground grassfive;
	grassfive.therect = { 1575,-3200,300, 300 };
	grassfive.thegroundtype = GRASS;
	ground grasssix;
	grasssix.therect = { 4980,-100,200,200 };
	grasssix.thegroundtype = GRASS;

	ground iceone;
	iceone.therect = { 250,300,1200,300 };
	iceone.thegroundtype = ICE;
	ground icetwo;
	icetwo.therect = { 1200,600,1200,300 };
	icetwo.thegroundtype = ICE;
	ground icethree;
	icethree.therect = { 1200,-550,1900,200 };
	icethree.thegroundtype = ICE;
	ground icefour;
	icefour.therect = { 1200,-950,1000,200 };
	icefour.thegroundtype = ICE;
	ground icefive;
	icefive.therect = { 1200,-1350,1000,200 };
	icefive.thegroundtype = ICE;
	ground icesix;
	icesix.therect = { 1200,-1950,1000,400 };
	icesix.thegroundtype = ICE;
	ground iceseven;
	iceseven.therect = { 1700,-2250,60,300 };
	iceseven.thegroundtype = ICE;
	ground iceeight;
	iceeight.therect = { 1760,-2250,200,60 };
	iceeight.thegroundtype = ICE;
	ground icenine;
	icenine.therect = { 1900,-2400,60,150 };
	icenine.thegroundtype = ICE;
	ground iceten;
	iceten.therect = { 1700,-2400,200,60 };
	iceten.thegroundtype = ICE;
	ground iceeleven;
	iceeleven.therect = { 1700,-2600,60,200 };
	iceeleven.thegroundtype = ICE;

	ground fasticeone;
	fasticeone.therect = { 3400,-450,500,100 };
	fasticeone.thegroundtype = FASTICE;
	ground fasticetwo;
	fasticetwo.therect = { 3900,-420,100,100 };
	fasticetwo.thegroundtype = FASTICE;
	ground fasticethree;
	fasticethree.therect = { 4000,-390,100,100 };
	fasticethree.thegroundtype = FASTICE;
	ground fasticefour;
	fasticefour.therect = { 4030,-290,100,400 };
	fasticefour.thegroundtype = FASTICE;
	ground fasticefive;
	fasticefive.therect = { 4060,110,100,100 };
	fasticefive.thegroundtype = FASTICE;
	ground fasticesix;
	fasticesix.therect = { 4090,210,100,100 };
	fasticesix.thegroundtype = FASTICE;
	ground fasticeseven;
	fasticeseven.therect = { 4190,250,400,100 };
	fasticeseven.thegroundtype = FASTICE;
	ground fasticeeight;
	fasticeeight.therect = { 4520,150,100,100 };
	fasticeeight.thegroundtype = FASTICE;
	ground fasticenine;
	fasticenine.therect = { 4550,50,100,100 };
	fasticenine.thegroundtype = FASTICE;
	ground fasticeten;
	fasticeten.therect = { 4580,-50,400,100 };
	fasticeten.thegroundtype = FASTICE;


	ground nonmoveone;
	nonmoveone.therect = {1200,-750,1000,200};
	nonmoveone.thegroundtype = NONMOVEICE;
	ground nonmovetwo;
	nonmovetwo.therect = { 1200,-1150,1000,200 };
	nonmovetwo.thegroundtype = NONMOVEICE;
	ground nonmovethree;
	nonmovethree.therect = { 1200,-1550,1000,200 };
	nonmovethree.thegroundtype = NONMOVEICE;

	ground reverseone;
	reverseone.therect = {2450,50,200,550};
	reverseone.thegroundtype = REVERSEICE;
	ground reversetwo;
	reversetwo.therect = { 1000,50,1450,200 };
	reversetwo.thegroundtype = REVERSEICE;
	ground reversethree;
	reversethree.therect = { 1000,-250,200,350 };
	reversethree.thegroundtype = REVERSEICE;
	ground reversefour;
	reversefour.therect = { 1200,-250,1800,200 };
	reversefour.thegroundtype = REVERSEICE;
	ground reversefive;
	reversefive.therect = { 2800,-50,200,600 };
	reversefive.thegroundtype = REVERSEICE;
	ground reversesix;
	reversesix.therect = { 3000,350,400,200 };
	reversesix.thegroundtype = REVERSEICE;
	ground reverseseven;
	reverseseven.therect = { 3100,-250,300,600 };
	reverseseven.thegroundtype = REVERSEICE;


	levelthreeground.push_back(grasstwoone);
	levelthreeground.push_back(grasstwo);
	levelthreeground.push_back(grassthree);
	levelthreeground.push_back(grassfour);
	levelthreeground.push_back(grassfive);
	levelthreeground.push_back(grasssix);
	levelthreeground.push_back(iceone);
	levelthreeground.push_back(icetwo);
	levelthreeground.push_back(icethree);
	levelthreeground.push_back(icefour);
	levelthreeground.push_back(icefive);
	levelthreeground.push_back(icesix);
	levelthreeground.push_back(iceseven);
	levelthreeground.push_back(iceeight);
	levelthreeground.push_back(icenine);
	levelthreeground.push_back(iceten);
	levelthreeground.push_back(iceeleven);
	levelthreeground.push_back(reverseone);
	levelthreeground.push_back(reversetwo);
	levelthreeground.push_back(reversethree);
	levelthreeground.push_back(reversefour);
	levelthreeground.push_back(reversefive);
	levelthreeground.push_back(reversesix);
	levelthreeground.push_back(reverseseven);
	levelthreeground.push_back(nonmoveone);
	levelthreeground.push_back(nonmovetwo);
	levelthreeground.push_back(nonmovethree);
	levelthreeground.push_back(fasticeone);
	levelthreeground.push_back(fasticetwo);
	levelthreeground.push_back(fasticethree);
	levelthreeground.push_back(fasticefour);
	levelthreeground.push_back(fasticefive);
	levelthreeground.push_back(fasticesix);
	levelthreeground.push_back(fasticeseven);
	levelthreeground.push_back(fasticeeight);
	levelthreeground.push_back(fasticenine);
	levelthreeground.push_back(fasticeten);

	enemy enemyone;//ice 1 250,300,1200,300
	enemyone.rect = { 400,400,50,50 }; enemyone.originalrect = { 400,425,225,50 }; enemyone.dir = DOWN; enemyone.thebool = 0; enemyone.text = zealot;
	enemyone.angle = 0; enemyone.rotatespeed = .07;
	enemy enemytwo;//ice 1 250,300,1200,300
	enemytwo.rect = { 700,400,50,50 }; enemytwo.originalrect = { 800,425,225,50 }; enemytwo.dir = DOWN; enemytwo.thebool = 0; enemytwo.text = zealot;
	enemytwo.angle = 40; enemytwo.rotatespeed = .08;
	enemy enemythree;//ice 1 250,300,1200,300
	enemythree.rect = { 1000,400,50,50 }; enemythree.originalrect = { 1200,425,225,50 }; enemythree.dir = DOWN; enemythree.thebool = 0; enemythree.text = zealot;
	enemythree.angle = 145; enemythree.rotatespeed = .09;
	enemy enemyfour;//ice 2 1200,600,1200,300 
	enemyfour.rect = { 1350,700,50,50 }; enemyfour.originalrect = { 1350,725,225,50 }; enemyfour.dir = DOWN; enemyfour.thebool = 0; enemyfour.text = zealot;
	enemyfour.angle = 95; enemyfour.rotatespeed = .09;
	enemy enemyfive;//ice 2 1200,600,1200,300 
	enemyfive.rect = { 1650,700,50,50 }; enemyfive.originalrect = { 1650,725,225,50 }; enemyfive.dir = DOWN; enemyfive.thebool = 0; enemyfive.text = zealot;
	enemyfive.angle = 200; enemyfive.rotatespeed = .08;
	enemy enemysix;//ice 2 1200,600,1200,300 
	enemysix.rect = { 1650,700,50,50 }; enemysix.originalrect = { 1950,725,225,50 }; enemysix.dir = DOWN; enemysix.thebool = 0; enemysix.text = zealot;
	enemysix.angle = 40; enemysix.rotatespeed = .06;
	enemy enemyseven;//reverse 1000,50,1450,200
	enemyseven.rect = { 1650,200,50,50 }; enemyseven.originalrect = { 1650,200,50,50 }; enemyseven.dir = DOWN; enemyseven.thebool = 0; enemyseven.text = zealot;
	enemy enemyeight;//reverse 1000,-250,200,350
	enemyeight.rect = { 1150,-25,50,50 }; enemyeight.originalrect = { 1650,200,50,50 }; enemyeight.text = zealot;
	enemy enemynine;//reverse 1200,-250,1800,200 
	enemynine.rect = { 1600,-100,50,50 }; enemynine.originalrect = { 1600,-100,50,50 }; enemynine.text = zealot;
	enemy enemyten;//reverse 1200,-250,1800,200 
	enemyten.rect = { 2000,-250,50,50 }; enemyten.originalrect = { 2000,-250,50,50 }; enemyten.text = zealot;
	enemy enemyeleven;//reverse 1200,-250,1800,200 
	enemyeleven.rect = { 2300,-175,50,50 }; enemyeleven.originalrect = { 2300,-175,50,50 }; enemyeleven.text = zealot;
	enemy enemytwelve;//reverse 2800,-50,200,600
	enemytwelve.rect = { 2950,125,50,50 }; enemytwelve.originalrect = { 2950,125,50,50 }; enemytwelve.text = zealot;
	enemy enemythirteen;//reverse 3100,-250,300,600
	enemythirteen.rect = { 3150,225,50,50 }; enemythirteen.originalrect = { 3150,225,50,50 }; enemythirteen.text = zealot;
	enemy enemyfourteen;//reverse 3100,-250,300,600
	enemyfourteen.rect = { 3300,50,50,50 }; enemyfourteen.originalrect = { 3300,50,50,50 }; enemyfourteen.text = zealot;
	enemy enemyfifteen;//reverse 3100,-250,300,600
	enemyfifteen.rect = { 3225,-150,50,50 }; enemyfifteen.originalrect = { 3225,-150,50,50 }; enemyfifteen.text = zealot;
	enemy enemysixteen;//fast 4030,-290,100,400
	enemysixteen.rect = { 4030,-90,25,25 }; enemysixteen.originalrect = { 4030,-90,25,25 }; enemysixteen.text = zealot;
	enemy enemyseventeen;//fast 4190,250,400,100
	enemyseventeen.rect = { 4390,325,25,25 }; enemyseventeen.originalrect = { 4390,325,25,25 }; enemyseventeen.text = zealot;
	enemy enemyeightteen;//nonmove 1200,-850,1000,300
	enemyeightteen.rect = { 2100,-675,50,50 }; enemyeightteen.originalrect = { 2100,-675,50,50 }; enemyeightteen.dir = LEFT; enemyeightteen.thebool = 0; enemyeightteen.text = zealot;
	enemy enemynineteen;//ice 1200,-1050,1000,200
	enemynineteen.rect = { 2100,-875,50,50 }; enemynineteen.originalrect = { 2100,-875,50,50 }; enemynineteen.dir = LEFT; enemynineteen.thebool = 0; enemynineteen.text = zealot;
	enemy enemytwenty;//ice 1200,-1350,1000,300
	enemytwenty.rect = { 1250,-1075,50,50 }; enemytwenty.originalrect = { 1250,-1075,50,50 }; enemytwenty.dir = LEFT; enemytwenty.thebool = 0; enemytwenty.text = zealot;
	enemy enemytwentyone;//ice 1200,-1350,1000,300
	enemytwentyone.rect = { 1250,-1275,50,50 }; enemytwentyone.originalrect = { 1250,-1275,50,50 }; enemytwentyone.dir = LEFT; enemytwentyone.thebool = 0; enemytwentyone.text = zealot;
	enemy enemytwentytwo;//ice 1200,-1350,1000,300
	enemytwentytwo.rect = { 1675,-1475,50,50 }; enemytwentytwo.originalrect = { 1675,-1475,50,50 }; enemytwentytwo.dir = LEFT; enemytwentytwo.thebool = 0; enemytwentytwo.text = zealot;
	enemy enemytwentythree;//ice 1200,-1350,1000,300
	enemytwentythree.rect = { 1675,-1650,50,50 }; enemytwentythree.originalrect = { 1675,-1650,50,50 }; enemytwentythree.dir = LEFT; enemytwentythree.thebool = 0; enemytwentythree.text = zealot;
	enemy enemytwentyfour;//ice 1900,-2700,60,150
	enemytwentyfour.rect = { 1600,-2325,50,50 }; enemytwentyfour.originalrect = { 1600,-2325,50,50 }; enemytwentyfour.dir = LEFT; enemytwentyfour.thebool = 0; enemytwentyfour.text = zealot;
	enemy enemytwentyfive;//grass 1700,-3200,60, 300
	enemytwentyfive.rect = { 1500,-2850,50,50 }; enemytwentyfive.originalrect = { 1500,-2850,50,50 }; enemytwentyfive.dir = LEFT; enemytwentyfive.thebool = 0; enemytwentyfive.text = zealot;

	levelthreeenemies.push_back(enemyone);
	levelthreeenemies.push_back(enemytwo);
	levelthreeenemies.push_back(enemythree);
	levelthreeenemies.push_back(enemyfour);
	levelthreeenemies.push_back(enemyfive);
	levelthreeenemies.push_back(enemysix);
	levelthreeenemies.push_back(enemyseven);
	levelthreeenemies.push_back(enemyeight);
	levelthreeenemies.push_back(enemynine);
	levelthreeenemies.push_back(enemyten);
	levelthreeenemies.push_back(enemyeleven);
	levelthreeenemies.push_back(enemytwelve);
	levelthreeenemies.push_back(enemythirteen);
	levelthreeenemies.push_back(enemyfourteen);
	levelthreeenemies.push_back(enemyfifteen);
	levelthreeenemies.push_back(enemysixteen);
	levelthreeenemies.push_back(enemyseventeen);
	levelthreeenemies.push_back(enemyeightteen);//17
	levelthreeenemies.push_back(enemynineteen);
	levelthreeenemies.push_back(enemytwenty);
	levelthreeenemies.push_back(enemytwentyone);
	levelthreeenemies.push_back(enemytwentytwo);
	levelthreeenemies.push_back(enemytwentythree);
	levelthreeenemies.push_back(enemytwentyfour);
	levelthreeenemies.push_back(enemytwentyfive);

	SDL_Rect secrethearts = { 5055,-25,50,50 };//4980,-100,200,200
	SDL_Rect portalfromthree = { 5150,-25,50,50 };// 4980,-100,200,200

	levelthreerects.push_back(secrethearts);
	levelthreerects.push_back(portalfromthree);
	levelthreerects.push_back(endthree);

	//currentground = &levelthreeground;
	//currentenemy = &levelthreeenemies;
	//currentrects = &levelthreerects;
}
void levelfourinitialize()
{
	ground grasstwoone;
	grasstwoone.therect = { 0,300,250,200 };
	grasstwoone.thegroundtype = GRASS;
	ground grassone;
	grassone.therect = {500,-75,200,50};
	grassone.thegroundtype = GRASS;
	ground grasstwo;
	grasstwo.therect = { 1100,-275,200,200 };
	grasstwo.thegroundtype = GRASS;
	ground grassthree;
	grassthree.therect = { 2000,-75,200,50 };
	grassthree.thegroundtype = GRASS;
	ground grassfour;
	grassfour.therect = { 900,825,200,50 };
	grassfour.thegroundtype = GRASS;
	ground grassfive;
	grassfive.therect = { 1800,875,200,200 };
	grassfive.thegroundtype = GRASS;
	ground grasssix;
	grasssix.therect = { 1863,1075,75,600 };
	grasssix.thegroundtype = GRASS;
	ground grassseven;
	grassseven.therect = { 1938,1600,900,75 };
	grassseven.thegroundtype = GRASS;
	ground grasseight;
	grasseight.therect = { 2275,1675,75,75 };
	grasseight.thegroundtype = GRASS;
	ground grassnine;
	grassnine.therect = { 3838,1338,200,600};
	grassnine.thegroundtype = GRASS;
	ground grassten;//250,350,2500,100
	grassten.therect = { 2750,250,350,300 };
	grassten.thegroundtype = GRASS;
	ground grasseleven;//3100,250,1500,300
	grasseleven.therect = { 4600,250,300,300 };
	grasseleven.thegroundtype = GRASS;


	ground grassoneone;//1100,-275,200,200
	grassoneone.therect = {1300,-213,400,75};
	grassoneone.thegroundtype = GRASS;
	ground grassonetwo;
	grassonetwo.therect = {1625,-463,75,250};
	grassonetwo.thegroundtype = GRASS;
	ground grassonethree;
	grassonethree.therect = {1700,-463,400,75};
	grassonethree.thegroundtype = GRASS;
	ground grassonefour;
	grassonefour.therect = {2100,-688,75,300};
	grassonefour.thegroundtype = GRASS;
	ground grassonefive;
	grassonefive.therect = {1300,-688,800,75};
	grassonefive.thegroundtype = GRASS;
	ground grassonesix;
	grassonesix.therect = {1300,-613,75,150};
	grassonesix.thegroundtype = GRASS;
	ground grassoneseven;
	grassoneseven.therect = {1250,-538,50,75};
	grassoneseven.thegroundtype = GRASS;
	ground grassoneeight;
	grassoneeight.therect = {1175,-963,75,500};
	grassoneeight.thegroundtype = GRASS;
	ground grassonenine;
	grassonenine.therect = {1250,-963,400,75};
	grassonenine.thegroundtype = GRASS;
	ground grassoneten;
	grassoneten.therect = { 2000,-1076,200,300 };
	grassoneten.thegroundtype = GRASS;
	ground grassoneeleven;
	grassoneeleven.therect = { 1700,-613,75,75 };
	grassoneeleven.thegroundtype = GRASS;

	ground iceone;
	iceone.therect = { 250,350,2500,100 };
	iceone.thegroundtype = ICE;
	ground icetwo;
	icetwo.therect = { 2838,1338,1000,600 };
	icetwo.thegroundtype = ICE;
	ground icethree;
	icethree.therect = { 1650,-1076,350,300 };
	icethree.thegroundtype = ICE;
	ground icefour;//2750,250,350,300
	icefour.therect = { 3100,250,1500,300 };
	icefour.thegroundtype = ICE;

	ground nonmoveone;
	nonmoveone.therect = {250,-75,2500,425};
	nonmoveone.thegroundtype = NONMOVEICE;
	ground nonmovetwo;
	nonmovetwo.therect = { 250,450,2500,425 };
	nonmovetwo.thegroundtype = NONMOVEICE;


	levelfourground.push_back(grasstwoone);
	levelfourground.push_back(iceone);
	levelfourground.push_back(icetwo);
	levelfourground.push_back(icethree);
	levelfourground.push_back(icefour);
	levelfourground.push_back(nonmoveone);
	levelfourground.push_back(nonmovetwo);
	levelfourground.push_back(grassone);
	levelfourground.push_back(grasstwo);
	levelfourground.push_back(grassthree);
	levelfourground.push_back(grassfour);
	levelfourground.push_back(grassfive);
	levelfourground.push_back(grasssix);
	levelfourground.push_back(grassseven);
	levelfourground.push_back(grasseight);
	levelfourground.push_back(grassnine);
	levelfourground.push_back(grassten);
	levelfourground.push_back(grasseleven);
	levelfourground.push_back(grassoneone);
	levelfourground.push_back(grassonetwo);
	levelfourground.push_back(grassonethree);
	levelfourground.push_back(grassonefour);
	levelfourground.push_back(grassonefive);
	levelfourground.push_back(grassonesix);
	levelfourground.push_back(grassoneseven);
	levelfourground.push_back(grassoneeight);
	levelfourground.push_back(grassonenine);
	levelfourground.push_back(grassoneten);
	levelfourground.push_back(grassoneeleven);


	enemy enemyone;//250,350,2500,100
	enemyone.rect = { 300,375,50,50 }; enemyone.originalrect = { 300,375,50,50 }; enemyone.dir = RIGHT; enemyone.thebool = 0; enemyone.text = zealot;
	enemy enemytwo;
	enemytwo.rect = { 2600,150,50,50 }; enemytwo.originalrect = { 2600,150,50,50 }; enemytwo.dir = DOWN; enemytwo.thebool = 0; enemytwo.text = zealot;
	enemy enemythree;//1800,875,200,200
	enemythree.rect = { 1650,750,50,50 }; enemythree.originalrect = { 1650,750,50,50 }; enemythree.dir = RIGHT; enemythree.thebool = 0; enemythree.text = zealot;
	enemy enemyfour;//1100,-275,200,200
	enemyfour.rect = { 1250,0,50,50 }; enemyfour.originalrect = { 1250,0,50,50 }; enemyfour.dir = RIGHT; enemyfour.thebool = 0; enemyfour.text = zealot;
	enemy enemyfive;//1863,1075,75,600
	enemyfive.rect = { 1800,1100,50,50 }; enemyfive.originalrect = { 1800,1100,50,50 }; enemyfive.dir = RIGHT; enemyfive.thebool = 0; enemyfive.text = zealot;
	SDL_Rect enemyrects = {1800,1100,63,400};
	enemy enemysix;//1938,1600,900,75
	enemysix.rect = { 1950,1610,50,50 }; enemysix.originalrect = { 1950,1610,50,50 }; enemysix.dir = RIGHT; enemysix.thebool = 0; enemysix.text = zealot;
	enemy enemyseven;//2838,1338,1000,600
	enemyseven.rect = { 3700,1200,50,350 }; enemyseven.originalrect = { 3700,1200,50,350 }; enemyseven.dir = LEFT; enemyseven.thebool = 0; enemyseven.text = zealot;
	enemyseven.angle = 0;
	enemy enemyeight;//2838,1338,1000,600
	enemyeight.rect = { 3700,1700,50,350 }; enemyeight.originalrect = { 3700,1700,50,350 }; enemyeight.dir = LEFT; enemyeight.thebool = 0; enemyeight.text = zealot;
	enemyeight.angle = 0;
	enemy enemynine;//1300,-213,400,75
	enemynine.rect = { 1475,-300,50,50 }; enemynine.originalrect = { 1475,-300,50,50 }; enemynine.dir = DOWN; enemynine.thebool = 0; enemynine.text = zealot;
	enemy enemyten;//1300,-213,400,75
	enemyten.rect = { 1550,-300,50,50 }; enemyten.originalrect = { 1550,-300,50,50 }; enemyten.dir = RIGHT; enemyten.thebool = 0; enemyten.text = zealot;
	enemy enemyeleven;//1700,-463,400,75
	enemyeleven.rect = { 1875,-440,50,50 }; enemyeleven.originalrect = { 1875,-440,50,50 }; enemyeleven.dir = RIGHT; enemyeleven.thebool = 0; enemyeleven.text = zealot;
	enemy enemytwelve;//1700,-463,400,75
	enemytwelve.rect = { 1925,-540,50,50 }; enemytwelve.originalrect = { 1925,-540,50,50 }; enemytwelve.dir = RIGHT; enemytwelve.thebool = 0; enemytwelve.text = zealot;
	enemy enemythirteen;//1300,-688,800,75
	enemythirteen.rect = { 1310,-676,50,50 }; enemythirteen.originalrect = { 1310,-676,50,50 }; enemythirteen.dir = RIGHT; enemythirteen.thebool = 0; enemythirteen.text = zealot;
	enemy enemyfourteen;//1250,-538,50,75
	enemyfourteen.rect = { 1100,-526,50,50 }; enemyfourteen.originalrect = { 1100,-526,50,50 }; enemyfourteen.dir = RIGHT; enemyfourteen.thebool = 0; enemyfourteen.text = zealot;
	enemy enemyfifteen;//1175,-963,75,500
	enemyfifteen.rect = { 1100,-940,50,50 }; enemyfifteen.originalrect = { 1100,-940,50,50 }; enemyfifteen.dir = RIGHT; enemyfifteen.thebool = 0; enemyfifteen.text = zealot;
	SDL_Rect enemyrectstwo = { 1100,-940,75,400 };
	enemy enemysixteen;//1650,-1076,350,300 
	enemysixteen.rect = {1650,-1076,50,50 }; enemysixteen.originalrect = { 1800,-950,225,50 }; enemysixteen.dir = LEFT; enemysixteen.thebool = 0; enemysixteen.text = zealot;
	enemysixteen.angle = 0; enemysixteen.rotatespeed = .04;
	enemy enemyseventeen;//3100,250,1500,300
	enemyseventeen.rect = { 3200,200,1300,100 }; enemyseventeen.originalrect = { 3200,200,1300,100 }; enemyseventeen.dir = LEFT; enemyseventeen.thebool = 0; enemyseventeen.text = zealot;
	enemyseventeen.angle = 0;
	enemy enemyeighteen;//3100,250,1500,300
	enemyeighteen.rect = { 3200,450,1300,100 }; enemyeighteen.originalrect = { 3200,450,1300,100 }; enemyeighteen.dir = LEFT; enemyeighteen.thebool = 0; enemyeighteen.text = zealot;
	enemyeighteen.angle = 0;

	levelfourenemies.push_back(enemyone);
	levelfourenemies.push_back(enemytwo);
	levelfourenemies.push_back(enemythree);
	levelfourenemies.push_back(enemyfour);
	levelfourenemies.push_back(enemyfive);
	levelfourenemies.push_back(enemysix);
	levelfourenemies.push_back(enemyseven);
	levelfourenemies.push_back(enemyeight);
	levelfourenemies.push_back(enemynine);
	levelfourenemies.push_back(enemyten);
	levelfourenemies.push_back(enemyeleven);
	levelfourenemies.push_back(enemytwelve);
	levelfourenemies.push_back(enemythirteen);
	levelfourenemies.push_back(enemyfourteen);
	levelfourenemies.push_back(enemyfifteen);
	levelfourenemies.push_back(enemysixteen);
	levelfourenemies.push_back(enemyseventeen);
	levelfourenemies.push_back(enemyeighteen);

	SDL_Rect buttonone = {2075,-951,50,50};// 2000,-1076,200,300
	SDL_Rect buttontwo = {3913,1613,50,50};// 3838,1338,200,600
	SDL_Rect gateone = {2700,250,50,300};//250,350,2500,100
	SDL_Rect portalone = {2150,-951,50,50};
	SDL_Rect portaltwo = {3975,1613,50,50};

	levelfourrects.push_back(enemyrects);
	levelfourrects.push_back(enemyrectstwo);
	levelfourrects.push_back(buttonone);
	levelfourrects.push_back(buttontwo);
	levelfourrects.push_back(gateone);
	levelfourrects.push_back(portalone);
	levelfourrects.push_back(portaltwo);
	levelfourrects.push_back(endfour);

	//currentground = &levelfourground;
	//currentenemy = &levelfourenemies;
	//currentrects = &levelfourrects;
}
void levelfiveinitialize()
{
	ground grasstwoone;
	grasstwoone.therect = { 0,300,250,200 };
	grasstwoone.thegroundtype = GRASS;
	ground grasstwo;//3325,425,150,75
	grasstwo.therect = { 3475,350,600,200 };
	grasstwo.thegroundtype = GRASS;
	ground grassthree;//4825,410,500,75
	grassthree.therect = { 5325,300,300,300 };
	grassthree.thegroundtype = GRASS;
	ground grassfour;//7425,-250,75,1400
	grassfour.therect = { 8000,300,500,500 };
	grassfour.thegroundtype = GRASS;



	ground iceone;
	iceone.therect = { 250,-100,1000,1000 };
	iceone.thegroundtype = ICE;
	ground icetwo;
	icetwo.therect = { 1250,350,800,75 };
	icetwo.thegroundtype = ICE;
	ground icethree;
	icethree.therect = { 1950,275,150,75 };
	icethree.thegroundtype = ICE;
	ground icefour;
	icefour.therect = { 2050,200,150,75 };
	icefour.thegroundtype = ICE;
	ground icefive;
	icefive.therect = { 2150,275,100,75 };
	icefive.thegroundtype = ICE;
	ground icesix;
	icesix.therect = { 2200,350,75,300 };
	icesix.thegroundtype = ICE;
	ground iceseven;
	iceseven.therect = { 2240,650,150,75 };
	iceseven.thegroundtype = ICE;
	ground iceeight;
	iceeight.therect = { 2340,725,150,75 };
	iceeight.thegroundtype = ICE;
	ground icenine;
	icenine.therect = { 2440,650,100,75 };
	icenine.thegroundtype = ICE;
	ground iceten;
	iceten.therect = { 2500,350,75,300 };
	iceten.thegroundtype = ICE;
	ground iceeleven;
	iceeleven.therect = { 2540,275,150,75 };
	iceeleven.thegroundtype = ICE;
	ground icetwelve;
	icetwelve.therect = { 2640,200,150,75 };
	icetwelve.thegroundtype = ICE;
	ground icethirteen;
	icethirteen.therect = { 2740,275,100,75 };
	icethirteen.thegroundtype = ICE;
	ground icefourteen;
	icefourteen.therect = { 2800,350,75,200 };
	icefourteen.thegroundtype = ICE;
	ground icefifteen;
	icefifteen.therect = { 2875,475,150,75 };
	icefifteen.thegroundtype = ICE;
	ground icesixteen;
	icesixteen.therect = { 3025,425,150,75 };
	icesixteen.thegroundtype = ICE;
	ground iceseventeen;
	iceseventeen.therect = { 3175,475,150,75 };
	iceseventeen.thegroundtype = ICE;
	ground iceeightteen;
	iceeightteen.therect = { 3325,425,150,75 };
	iceeightteen.thegroundtype = ICE;
	ground icenineteen;//8000,300,500,500
	icenineteen.therect = { 8500,300,2000,500 };
	icenineteen.thegroundtype = ICE;

	ground fastone;//3475,350,600,200
	fastone.therect = {4075,410,500,75};
	fastone.thegroundtype = FASTICE;
	ground fasttwo;
	fasttwo.therect = { 4450,485,125,300 };
	fasttwo.thegroundtype = FASTICE;
	ground fastthree;
	fastthree.therect = { 4450,785,500,125 };
	fastthree.thegroundtype = FASTICE;
	ground fastfour;
	fastfour.therect = { 4825,485,125,300 };
	fastfour.thegroundtype = FASTICE;
	ground fastfive;
	fastfive.therect = { 4825,410,500,75 };
	fastfive.thegroundtype = FASTICE;

	//1950,1100 
	ground deathone;//5325,300,300,300
	deathone.therect = {5625,-250,75,1400};
	deathone.thegroundtype = DEATH; deathone.aboolean = 1;
	ground deathtwo;
	deathtwo.therect = {7425,-250,75,1400};
	deathtwo.thegroundtype = DEATH; deathtwo.aboolean = 1;
	ground deaththree;
	deaththree.therect = {5625,-250,1800,75};
	deaththree.thegroundtype = DEATH; deaththree.aboolean = 1;
	ground deathfour;
	deathfour.therect = {5625,1150,1800,75};
	deathfour.thegroundtype = DEATH; deathfour.aboolean = 1;

	levelfiveground.push_back(grasstwoone);
	levelfiveground.push_back(iceone);
	levelfiveground.push_back(icetwo);
	levelfiveground.push_back(icethree);
	levelfiveground.push_back(icefour);
	levelfiveground.push_back(icefive);
	levelfiveground.push_back(icesix);
	levelfiveground.push_back(iceseven);
	levelfiveground.push_back(iceeight);
	levelfiveground.push_back(icenine);
	levelfiveground.push_back(iceten);
	levelfiveground.push_back(iceeleven);
	levelfiveground.push_back(icetwelve);
	levelfiveground.push_back(icethirteen);
	levelfiveground.push_back(icefourteen);
	levelfiveground.push_back(icefifteen);
	levelfiveground.push_back(icesixteen);
	levelfiveground.push_back(iceseventeen);
	levelfiveground.push_back(iceeightteen);//18
	levelfiveground.push_back(grasstwo);
	levelfiveground.push_back(grassthree);
	levelfiveground.push_back(fastone);
	levelfiveground.push_back(fasttwo);
	levelfiveground.push_back(fastthree);
	levelfiveground.push_back(fastfour);
	levelfiveground.push_back(fastfive);
	levelfiveground.push_back(deathone);//26
	levelfiveground.push_back(deathtwo);
	levelfiveground.push_back(deaththree);
	levelfiveground.push_back(deathfour);
	levelfiveground.push_back(grassfour);
	levelfiveground.push_back(icenineteen);



	enemy enemyone;//3475,350,600,200
	enemyone.rect = { 3575,300,75,75 }; enemyone.originalrect = { 3575,300,75,75 }; enemyone.dir = DOWN; enemyone.thebool = 0; enemyone.text = zealottwo;
	enemy enemytwo;//3475,350,600,200
	enemytwo.rect = { 3775,550,75,75 }; enemytwo.originalrect = { 3775,550,75,75 }; enemytwo.dir = DOWN; enemytwo.thebool = 0; enemytwo.text = zealottwo;
	enemy enemythree;//3475,350,600,200
	enemythree.rect = { 3975,400,75,75 }; enemythree.originalrect = { 3975,400,75,75 }; enemythree.dir = DOWN; enemythree.thebool = 0; enemythree.text = zealottwo;

	levelfiveenemies.push_back(enemyone);
	levelfiveenemies.push_back(enemytwo);
	levelfiveenemies.push_back(enemythree);

	for (int i = 0; i < 50; i++)
	{
		enemy intone;
		intone.rect = { 0,0,25,25 }; intone.originalrect = { 0,0,0,0 }; intone.angle = 0; intone.thebool = 0; intone.text = interceptor;
		interceptorz.push_back(intone);
	}

	SDL_Rect boss = { bossx,bossy,400,400 };
	SDL_Rect spawnxposition = { 400,0,50,10000 };
	//5325,300,300,300 grass
	SDL_Rect thephoenix = { 5525,400,150,150 };
	SDL_Rect laserbeam = { 0,0,0,0 };
	SDL_Rect carrierhealthbar = { 0,0,0,0 };

	levelfiverects.push_back(boss);
	levelfiverects.push_back(spawnxposition);
	levelfiverects.push_back(thephoenix);
	levelfiverects.push_back(laserbeam);
	levelfiverects.push_back(carrierhealthbar);
	levelfiverects.push_back(endfive);


	//currentground = &levelfiveground;
	//currentenemy = &levelfiveenemies;
	//currentrects = &levelfiverects;
}
void levelsixinitialize()
{
	ground grasstwoone;
	grasstwoone.therect = { 0,300,250,200 };
	grasstwoone.thegroundtype = GRASS;
	ground grassone;
	grassone.therect = {250,0,800,800};
	grassone.thegroundtype = GRASS;

	ground iceone;
	iceone.therect = {550,300,200,200};
	iceone.thegroundtype = ICE;

	ground icetwo;
	icetwo.therect = { 1050,0,300,800 };
	icetwo.thegroundtype = REVERSEICE;

	levelsixground.push_back(grasstwoone);
	levelsixground.push_back(grassone);
	levelsixground.push_back(iceone);
	levelsixground.push_back(icetwo);

	SDL_Rect victory = {400,-300,700,200};
	SDL_Rect avilorect = { 300,25,100,100 };
	SDL_Rect architectrect = {800,600,200,200};
	SDL_Rect heartmanrect = {900,25,100,100};
	SDL_Rect aviloquoterect = {300,-50,700,25};
	SDL_Rect architectquoterect = {700,-50,1000,25};
	SDL_Rect heartmanquoterect = {800,850,800,25};
	SDL_Rect peeman = { 1200,600,200,300 };
	
	levelsixrects.push_back(victory);
	levelsixrects.push_back(avilorect);
	levelsixrects.push_back(architectrect);
	levelsixrects.push_back(heartmanrect);
	levelsixrects.push_back(aviloquoterect);
	levelsixrects.push_back(architectquoterect);
	levelsixrects.push_back(heartmanquoterect);
	levelsixrects.push_back(peeman);


	//currentground = &levelsixground;
	//currentenemy = &levelsixenemies;
	//currentrects = &levelsixrects;
}
SDL_Texture* loadtext(string s, SDL_Color textcolor)
{
	SDL_Surface* tempsurface = TTF_RenderText_Blended_Wrapped(gfont, s.c_str(), textcolor, screen_width);
	SDL_Texture* returntexture;
	returntexture = SDL_CreateTextureFromSurface(grender, tempsurface);
	//cout << tempsurface->w << " " << tempsurface->h;
	//get width and height
	SDL_FreeSurface(tempsurface);
	return returntexture;
}
SDL_Texture* loadimage(string a)
{
	SDL_Surface* tempsurf;
	tempsurf = IMG_Load(a.c_str());
	if (tempsurf == 0)
	{
		cout << "could not load image";
	}
	SDL_Texture* temptext;
	temptext = SDL_CreateTextureFromSurface(grender, tempsurf);

	SDL_FreeSurface(tempsurf);
	return temptext;
}
SDL_Texture* loadimageclear(string a) //white
{
	SDL_Surface* tempsurf;
	tempsurf = IMG_Load(a.c_str());
	if (tempsurf == 0)
	{
		cout << "could not load image";
	}
	SDL_SetColorKey(tempsurf, SDL_TRUE, SDL_MapRGB(tempsurf->format, 255, 255, 255));
	SDL_Texture* temptext;
	temptext = SDL_CreateTextureFromSurface(grender, tempsurf);

	SDL_FreeSurface(tempsurf);
	return temptext;
}
void collision()
{
	if (ball1.x <= 0)
	{
		ball1.x = 0;
	}
	if ((ball1.x + 20) >= screen_width)
	{
		ball1.x = screen_width - 20;
	}
	if (ball1.y <= 0)
	{
		ball1.y = 0;
	}
	if ((ball1.y + 20) >= screen_height)
	{
		ball1.y = screen_height - 20;
	}
}
bool checkcollisioncircles(SDL_Rect a, SDL_Rect b) //sqrt((x2-x1)^2+(y2-y1)^2)
{
	//centers, radii
	int acenterx = (a.x + (a.w / 2));
	int acentery = (a.y + (a.h / 2));
	int aradius = (a.w / 2);
	int bcenterx = (b.x + (b.w / 2));
	int bcentery = (b.y + (b.h / 2));
	int bradius = (b.w / 2);
	if (distanceSquared(acenterx, acentery, bcenterx, bcentery) < (bradius + aradius))
	{
		cout << "true" << endl;
		return true;
	}
	//if distance formula is less than aradius + bradius then they hit
	return false;
}
bool checkcollisionmoveback(SDL_Rect & a, SDL_Rect b)
{
	string side;
	bool ycheck = false;
	bool xcheck = false;


	if (a.y + a.h > b.y && a.y < b.y + b.h) //when it hits bottom of box
	{
		ycheck = true;
	}
	if (a.x + a.w > b.x && a.x < b.x + b.w) //when it hits bottom of box
	{
		xcheck = true;
	}


	for (int i = 0; i <= ball1.speed; i++) //if square is super small might have problem
	{

		if (a.y + i == (b.y + b.h))
		{
			side = "up";
		}
		else if ((a.y + a.h - i) == b.y)
		{
			side = "bottom";
		}
		else if ((a.x + i == (b.x + b.w)))
		{
			side = "left";
		}
		else if ((a.x + a.w - i) == b.x)
		{
			side = "right";
		}
	}

	if (xcheck == true && ycheck == true)
	{

		if (side == "left")
		{
			ball1.x = b.x + b.w;

		}
		if (side == "right")
		{
			ball1.x = b.x - 20;
		}
		if (side == "up")
		{
			ball1.y = b.y + b.h;
		}
		if (side == "bottom")
		{
			ball1.y = b.y - 20;
		}
		return true;
	}

	return false;

}
bool checkcollision(SDL_Rect a, SDL_Rect b)
{

	string side;
	bool ycheck = false;
	bool xcheck = false;


	if (a.y + a.h > b.y && a.y < b.y + b.h) //when it hits bottom of box
	{
		ycheck = true;
	}
	if (a.x + a.w > b.x && a.x < b.x + b.w) //when it hits bottom of box
	{
		xcheck = true;
	}


	for (int i = 0; i <= ball1.speed; i++) //if square is super small might have problem
	{

		if (a.y + i == (b.y + b.h))
		{
			side = "up";
		}
		else if ((a.y + a.h - i) == b.y)
		{
			side = "bottom";
		}
		else if ((a.x + i == (b.x + b.w)))
		{
			side = "left";
		}
		else if ((a.x + a.w - i) == b.x)
		{
			side = "right";
		}
	}

	if (xcheck == true && ycheck == true)
	{

		if (side == "left")
		{
			//ball1.x = b.x + b.w;

		}
		if (side == "right")
		{
			//ball1.x = b.x - 20;
		}
		if (side == "up")
		{
			//ball1.y = b.y + b.h;
		}
		if (side == "bottom")
		{
			//ball1.y = b.y - 20;
		}
		return true;
	}

	return false;
}
void moverightclick() // y - mousey = (ydiff/xdiff)*(x-mousex) y = slopex - slope*mousex + mousey
{
	int mousex;
	int mousey;
	double slope;
	bool atmouse = false;
	SDL_GetMouseState(&mousex, &mousey);
	ydiff = ball1.y - mousey;
	xdiff = mousex - ball1.x;
	slope = ydiff / xdiff;
	while (atmouse == false)
	{
		if (slowdown == 1)
		{
			//ball1.x++;
			ball1.y = (slope*ball1.x) - (slope*mousex) + mousey;
			//counter++;
		}
		slowdown++;
			if (slowdown == 10)
			{
				slowdown = 1;
			}
		if (ball1.x == mousex && ball1.y == mousey)
		{
			atmouse = true;
		}
	}

}
void move()
{
	bool left = 0;
	bool right = 0;
	bool up = 0;
	bool down = 0;
	const Uint8* currentkeystate = SDL_GetKeyboardState(0);
	if (currentkeystate[SDL_SCANCODE_A])
	{
		ball1.x -= ball1.speed;
		left = 1;

	}
	if (currentkeystate[SDL_SCANCODE_D])
	{
		ball1.x += ball1.speed;
		right = 1;
	}
	if (currentkeystate[SDL_SCANCODE_W])
	{
		ball1.y -= ball1.speed;
		up = 1;

	}
	if (currentkeystate[SDL_SCANCODE_S])
	{
		ball1.y += ball1.speed;
		down = 1;

	}
	//constant movement
	
	
	int tempx = x;
	int tempy = y;
	SDL_GetMouseState(&x, &y);
	if (tempy != y || tempx != x)
	{
		onetime = true;
	}
	if (onetime == true)
	{
		
		xdiff = x - ball1.x;
		ydiff = y - ball1.y;
		range = ball1.y;
		onetime = false;
	}
	if (slowdown == 1)
	{
		ball1.x += xdiff;
		ball1.y += ydiff;
	}
	slowdown++;
	if (slowdown >= 5)
	{
		slowdown = 0;
	}
	/*if (ball1.y < y)
	{
		ball1.y = ((ydiff / xdiff)*ball1.x);
	}
	if (ball1.y > y)
	{
		ball1.y = ((ydiff / xdiff)*ball1.x);
	}
	if (ball1.x < x)
	{
		ball1.x++;
	}
	if (ball1.x > x)
	{
		ball1.x--;
	}*/
	


	//end of movement
	SDL_Rect yikes = { ball1.x,ball1.y,20,20 }; //ball1 rect
	SDL_Rect square = { 202,252,100,100 };
	SDL_Rect square2 = { 100,100,10,10 };
	SDL_Rect femrect = { 400,200,150,150 };
	SDL_Rect yikes2 = { 250,50,30,30 };
	collision();
	checkcollision(yikes, square);
	/*checkcollision(yikes, square2);
	if (checkcollisioncircles(yikes, yikes2))
	{
		if (up == 1)
		{
			ball1.y += ball1.speed;
		}
		if (down == 1)
		{
			ball1.y -= ball1.speed;
		}
		if (left == 1)
		{
			ball1.x += ball1.speed;
		}
		if (right == 1)
		{
			ball1.x -= ball1.speed;
		}
	}
	if (checkcollision(yikes, femrect))
	{
		Mix_PlayChannel(-1, feministsound, 0);
	}*/
}
double distanceSquared(double x1, double y1, double x2, double y2)
{
	double deltaX = x2 - x1;
	double deltaY = y2 - y1;
	return sqrt(deltaX*deltaX + deltaY*deltaY);
}
void close()
{
	SDL_DestroyWindow(gwindow);
	gwindow = 0;
	SDL_DestroyRenderer(grender);
	grender = 0;

	Mix_Quit();
	SDL_Quit();
	IMG_Quit();
}
void movefunction()
{	
	if (rightclicked == true)
	{
		if (xdiff < 100 && xdiff > -100 && (ydiff > 10 || ydiff < -10))
		{
			//increment y
			if (ydiff < 0)
			{
				if (playerfloor == REVERSEICE && reversefirstclick == 1)
				{
					ball1.y += xincrement;
					ball1centery += xincrement;
				}
				else
				{
					if (reversefirstclick == 1 || reverseicetograss == 1)
					{
						ball1.y += xincrement;
						ball1centery += xincrement;
					}
					else
					{
						ball1.y -= xincrement;
						ball1centery -= xincrement;
					}
				}
			}
			else
			{
				if (playerfloor == REVERSEICE && reversefirstclick == 1)
				{
					ball1.y -= xincrement;
					ball1centery -= xincrement;
				}
				else
				{
					if (reversefirstclick == 1 || reverseicetograss == 1)
					{
						ball1.y -= xincrement;
						ball1centery -= xincrement;
					}
					else
					{
						ball1.y += xincrement;
						ball1centery += xincrement;
					}
				}
			}
			//change x
			ball1.x = -(((my - ball1centery) / slope) - mx) - 10;
			ball1centerx = -(((my - ball1centery) / slope) - mx);
			counter++;
			//check when to stop
			if (ydiff < 0)
			{
				if (ball1centery <= my)
				{
					if (playerfloor == ICE || playerfloor == FASTICE || playerfloor == NONMOVEICE || playerfloor == REVERSEICE || reversegrasscounter >= 1)
					{

					}
					else
					{
						rightclicked = false;
					}
				}
			}
			else
			{
				if (ball1centery >= my)
				{
					if (playerfloor == ICE || playerfloor == FASTICE || playerfloor == NONMOVEICE || playerfloor == REVERSEICE || reversegrasscounter >= 1)
					{

					}
					else
					{
						rightclicked = false;
					}
				}
			}
		}
		else
		{
			//increment x
			if (xdiff < 0)
			{
				if (playerfloor == REVERSEICE && reversefirstclick == 1)
				{
					ball1.x += xincrement;
					ball1centerx += xincrement;
				}
				else
				{
					if (reversefirstclick == 1 || reverseicetograss == 1)
					{
						ball1.x += xincrement;
						ball1centerx += xincrement;
					}
					else
					{
						ball1.x -= xincrement;
						ball1centerx -= xincrement;
					}
				}
			}
			else
			{
				if (playerfloor == REVERSEICE && reversefirstclick == 1)
				{
					ball1.x -= xincrement;
					ball1centerx -= xincrement;
				}
				else
				{
					if (reversefirstclick == 1 || reverseicetograss == 1)
					{
						ball1.x -= xincrement;
						ball1centerx -= xincrement;
					}
					else
					{
						ball1.x += xincrement;
						ball1centerx += xincrement;		
					}
				}
			}
			//change y
			ball1.y = -(slope * (mx - ball1centerx) - my) - 10;//-10 is to offset the center we dont want ball1.y to go to center point
			ball1centery = -(slope * (mx - ball1centerx) - my);
			//counter++;
			//tell when to stop
			if (xdiff < 0)
			{
				if (ball1centerx <= mx)
				{
					if (playerfloor == ICE || playerfloor == FASTICE || playerfloor == NONMOVEICE || playerfloor == REVERSEICE || reversegrasscounter >= 1)
					{

					}
					else
					{
						rightclicked = false;
					}
				}
			}
			else
			{
				if (ball1centerx >= mx)
				{
					if (playerfloor == ICE || playerfloor == FASTICE || playerfloor == NONMOVEICE || playerfloor == REVERSEICE || reversegrasscounter >= 1)
					{

					}
					else
					{
						rightclicked = false;
					}
				}
			}
		}
	
		if (reversegrasscounter >= 1)
		{
			if (wasjustreverseice == 1 && justturned == 0)
			{
				justturned = 1;
				reverseicetograss = 1;
			}
			reversegrasscounter++;
		}
		if (wasjustreverseice == 1)
		{
			if (reversegrasscounter == 20)
			{
				justturned = 0;
				rightclicked = 0;
				reversegrasscounter = 0;
				reversefirstclick = 0;
				wasjustreverseice = 0;
				reverseicetograss = 0;
			}
		}
		else
		{
			if (reversegrasscounter == 15)
			{
				justturned = 0;
				rightclicked = 0;
				reversegrasscounter = 0;
				reversefirstclick = 0;
				wasjustreverseice = 0;
				reverseicetograss = 0;
			}
		}
		
		if (followcounter == 1)
		{
			ball7.x = phsix.x;
			ball7.y = phsix.y;
			ball6.x = phfive.x;
			ball6.y = phfive.y;
			ball5.x = phfour.x;
			ball5.y = phfour.y;
			ball4.x = phthree.x;
			ball4.y = phthree.y;
			ball3.x = phtwo.x;
			ball3.y = phtwo.y;
			ball2.x = phone.x;
			ball2.y = phone.y;

			phone.x = ball1.x;
			phone.y = ball1.y;
			phtwo.x = ball2.x;
			phtwo.y = ball2.y;
			phthree.x = ball3.x;
			phthree.y = ball3.y; 
			phfour.x = ball4.x;
			phfour.y = ball4.y;
			phfive.x = ball5.x;
			phfive.y = ball5.y;
			phsix.x = ball6.x;
			phsix.y = ball6.y;
			followcounter = 0;
		
		}
		followcounter++;
	}
}
void whatamion(const SDL_Rect player, vector<ground> leveloneground)
{
	//cout << "pastflooroff" << pastflooroff <<" "<< endl;
	if (leveloneground.empty())
	{
		return;
	}
	for (int i = 0; i < leveloneground.size(); i++)
	{
		if (checkcollision(player, leveloneground[i].therect))
		{
			if (leveloneground[i].thegroundtype == currentfloor && currentflooroff == 1)
			{
				thechecktwo = 1;
			}
			if (playerfloor != leveloneground[i].thegroundtype)
			{
				if (leveloneground[i].thegroundtype == pastfloor && pastflooroff == 1)
				{
					thecheck = 1;
				}
				else
				{
					switchfloor = 1;
					pastfloor = playerfloor;
					pastflooroff = 1;
					firstframe = 1;
					playerfloor = leveloneground[i].thegroundtype;
					currentfloor = playerfloor;
					firstframetwo = 1;
					currentflooroff = 1;
					break;
				}
			}
		}
	}
	if (firstframe == 0)
	{
		if (thecheck == 0)
		{
			pastflooroff = 0;
			thecheck = 0;
		}
		else
		{
			thecheck = 0;
		}
	}
	else
	{
		firstframe = 0;
	}
	if (firstframetwo == 0)
	{
		if (thechecktwo == 0)
		{
			currentflooroff = 0;
			pastflooroff = 0;
			thechecktwo = 0;
		}
		else
		{
			thechecktwo = 0;
		}
	}
	else
	{
		firstframetwo = 0;
	}
	if (switchfloor == 1)
	{
		if (playerfloor == REVERSEICE)
		{
			wasjustreverseice = 1;
			if (speedboost == 1 && banelingbool == 0)
			{
				banespeed = 6 + 3;
				setxincrement(degree, xdiff, ydiff, xincrement, banespeed);
			}
			else
			{
				banespeed = 6;
				setxincrement(degree, xdiff, ydiff, xincrement, banespeed);
			}
			//slope = slope * -1;
			reversefirstclick = 0;
			reversegrasscounter = 0;
		}
		if (playerfloor == SNOW)
		{
			rightclicked = false;
		}
		if (playerfloor == DEATH)
		{
			/*if (candiefrombarrier == 1)if hitting when candiefrombarrier is on then die
			{
				dead = 1;
				cout << "dead";
			}
			cout << "notdead";*/
		}
		if (playerfloor == NONMOVEICE)
		{
			wasjustreverseice = 0;
			if (speedboost == 1 && banelingbool == 0)
			{
				banespeed = 6 + 3;
				setxincrement(degree, xdiff, ydiff, xincrement, banespeed);
			}
			else
			{
				banespeed = 6;
				setxincrement(degree, xdiff, ydiff, xincrement, banespeed);
			}
			reversegrasscounter = 0;
		}
		if (playerfloor == FASTICE)
		{
			wasjustreverseice = 0;
			if (speedboost == 1 && banelingbool == 0)
			{
				banespeed = 10 + 3;
				setxincrement(degree, xdiff, ydiff, xincrement, banespeed);
			}
			else
			{
				banespeed = 10;
				setxincrement(degree, xdiff, ydiff, xincrement, banespeed);
			}
			reversegrasscounter = 0;
		}
		if (playerfloor == GRASS)
		{
			if (wasjustreverseice == 1)
			{
			}
			if (speedboost == 1 && banelingbool == 0)
			{
				banespeed = 3 + 3;
				setxincrement(degree, xdiff, ydiff, xincrement, banespeed);
			}
			else
			{
				banespeed = 3;
				setxincrement(degree, xdiff, ydiff, xincrement, banespeed);
			}
			//reversefirstclick = 0;
			reversegrasscounter++;
				//rightclicked = false;
		
			//rightclicked = false;
		}
		if (playerfloor == ICE)
		{
			wasjustreverseice = 0;
			if (speedboost == 1 && banelingbool == 0)
			{
				banespeed = 6 + 3;
				setxincrement(degree, xdiff, ydiff, xincrement, banespeed);
			}
			else
			{
				banespeed = 6;
				setxincrement(degree, xdiff, ydiff, xincrement, banespeed);
			}
			reversegrasscounter = 0;
		}
		switchfloor = 0;
		
	}
}
bool isdead(SDL_Rect player, vector<ground> leveloneground)
{
	//if your not hitting any of the things your dead
	if (phoenixphase == 1)
	{
		return 0;
	}
	else
	{
		for (int i = 0; i < leveloneground.size(); i++)
		{
			if (checkcollision(player, leveloneground[i].therect))
			{
				return 0;
			}
		}
		return 1;
	}
	
}
void setxincrement(double degree, double xdiff, double ydiff, double& xincrement, double banespeed)
{
	if (abs(cos(degree)) < cos(0) && abs(cos(degree)) >= cos(.2618))
	{
		if (xdiff<100 && xdiff > -100 && (ydiff > 10 || ydiff < -10))
		{
			xincrement = banespeed * .16666;
		}

		else
		{
			xincrement = banespeed;
		}
	}
	if (abs(cos(degree)) < cos(.2618) && abs(cos(degree)) >= cos(.2618 * 2))
	{
		if (xdiff<100 && xdiff > -100 && (ydiff > 10 || ydiff < -10))
		{
			xincrement = banespeed * .25;
		}
		else
		{
			xincrement = banespeed * .9666;
		}
	}
	if (abs(cos(degree)) < cos(.2618 * 2) && abs(cos(degree)) >= cos(.2618 * 3))
	{
		if (xdiff<100 && xdiff > -100 && (ydiff > 10 || ydiff < -10))
		{
			xincrement = banespeed * .46666;
		}
		else
		{
			xincrement = banespeed * .83333;
		}
	}
	if (abs(cos(degree)) < cos(.2618 * 3) && abs(cos(degree)) >= cos(.2618 * 4))
	{
		if (xdiff<100 && xdiff > -100 && (ydiff > 10 || ydiff < -10))
		{
			xincrement = banespeed * .766666;
		}
		else
		{
			xincrement = banespeed * .66666;
		}
	}
	if (abs(cos(degree)) < cos(.2618 * 4) && abs(cos(degree)) >= cos(.2618 * 5))
	{
		if (xdiff<100 && xdiff > -100 && (ydiff > 10 || ydiff < -10))
		{
			xincrement = banespeed * .86666;
		}
		else
		{
			xincrement = banespeed * .41666;
		}
	}
	if (abs(cos(degree)) < cos(.2618 * 5) && abs(cos(degree)) >= cos(.2618 * 6))
	{
		if (xdiff<100 && xdiff > -100 && (ydiff > 10 || ydiff < -10))
		{
			xincrement = banespeed;
		}
		else
		{
			xincrement = banespeed * .16666;
		}
	}
}
void enemymoveleftright(enemy & enemy,int length,int speed)//0 is left 1 is right
{
	if (enemy.dir == LEFT)
	{
		enemy.rect.x -= speed;
		if (enemy.rect.x < enemy.originalrect.x - length)
		{
			enemy.dir = RIGHT;
		}
	}
	else if (enemy.dir == RIGHT)
	{
		enemy.rect.x += speed;
		if (enemy.rect.x > enemy.originalrect.x)
		{
			if (enemy == leveltwoenemies[8])
			{
				enemyeightswitch = 0;
			}
			enemy.dir = LEFT;
		}
	}

}
void enemymoveleftonly(enemy & enemy, int length, int speed)//0 is left 1 is right
{
	if (enemy.dir == LEFT)
	{
		enemy.rect.x -= speed;
		if (enemy.rect.x < enemy.originalrect.x - length)
		{
			enemy.rect.x = enemy.originalrect.x;
		}
	}
	
}
void enemymovemiddleleftright(enemy & enemy, int length, int speed)
{
	if (enemy.dir == LEFT)
	{
		enemy.rect.x -= speed;
		if (enemy.rect.x < enemy.originalrect.x - length)
		{
			enemy.dir = RIGHT;
		}
	}
	else if (enemy.dir == RIGHT)
	{
		enemy.rect.x += speed;
		if (enemy.rect.x > enemy.originalrect.x + length)
		{
			enemy.dir = LEFT;
		}
	}
}
void enemymoverightleft(enemy & enemy, int length, int speed)//0 is left 1 is right
{
	if (enemy.dir == LEFT)
	{
		enemy.rect.x -= speed;
		if (enemy.rect.x < enemy.originalrect.x)
		{
			enemy.dir = RIGHT;
			if (enemy == leveltwoenemies[8])
			{
				enemyeightcounter++;
			}
		}
	}
	else if (enemy.dir == RIGHT)
	{
		enemy.rect.x += speed;
		if (enemy.rect.x > enemy.originalrect.x + length)
		{
			enemy.dir = LEFT;
		}
	}

}
void enemymoveupdown(enemy & enemy, int length, int speed)
{
	if (enemy.dir == DOWN)
	{
		enemy.rect.y += speed;
		if (enemy.rect.y > enemy.originalrect.y)
		{
			enemy.dir = UP;
		}
	}
	else if (enemy.dir == UP)
	{
		enemy.rect.y -= speed;
		if (enemy.rect.y < enemy.originalrect.y - length)
		{
			enemy.dir = DOWN;
		}
	}
}
void enemymovedownup(enemy & enemy, int length, int speed)
{
	if (enemy.dir == DOWN)
	{
		enemy.rect.y += speed;
		if (enemy.rect.y > enemy.originalrect.y + length)
		{
			enemy.dir = UP;
		}
	}
	else if (enemy.dir == UP)
	{
		enemy.rect.y -= speed;
		if (enemy.rect.y < enemy.originalrect.y)
		{
			enemy.dir = DOWN;
		}
	}
}
void enemymoveslope(enemy & enemy, int length, int speed, double enemyslope)
{
	if (enemy.dir == LEFT)
	{
		enemy.rect.x -= speed;
		enemy.rect.y = (enemyslope*enemy.rect.x) - (enemyslope*enemy.originalrect.x) + enemy.originalrect.y;
		if (enemy.rect.x < enemy.originalrect.x - length)
		{
			enemy.dir = RIGHT;
		}
	}
	if (enemy.dir == RIGHT)
	{
		enemy.rect.x += speed;
		enemy.rect.y = (enemyslope*enemy.rect.x) - (enemyslope*enemy.originalrect.x) + enemy.originalrect.y;
		if (enemy.rect.x > enemy.originalrect.x)
		{
			enemy.dir = LEFT;
		}
	}

}
void enemymoveslopeleftright(enemy & enemy, int length, int speed, double enemyslope)
{
	if (enemy.dir == LEFT)
	{
		enemy.rect.x -= speed;
		enemy.rect.y = (enemyslope*enemy.rect.x) - (enemyslope*enemy.originalrect.x) + enemy.originalrect.y;
		if (enemy.rect.x < enemy.originalrect.x - length)
		{
			enemy.dir = RIGHT;
		}
	}
	if (enemy.dir == RIGHT)
	{
		enemy.rect.x += speed;
		enemy.rect.y = (enemyslope*enemy.rect.x) - (enemyslope*enemy.originalrect.x) + enemy.originalrect.y;
		if (enemy.rect.x > enemy.originalrect.x + length)
		{
			enemy.dir = LEFT;
		}
	}

}
void enemymoveslopejustright(enemy & enemy, int length, int speed, double enemyslope)
{
	if (enemy.dir == LEFT)
	{
		enemy.rect.x -= speed;
		enemy.rect.y = (enemyslope*enemy.rect.x) - (enemyslope*enemy.originalrect.x) + enemy.originalrect.y;
		if (enemy.rect.x < enemy.originalrect.x)
		{
			enemy.dir = RIGHT;
		}
	}
	if (enemy.dir == RIGHT)
	{
		enemy.rect.x += speed;
		enemy.rect.y = (enemyslope*enemy.rect.x) - (enemyslope*enemy.originalrect.x) + enemy.originalrect.y;
		if (enemy.rect.x > enemy.originalrect.x + length)
		{
			enemyoneswitch = 1;
			enemy.dir = LEFT;
		}
	}
}
void enemymovesloperandom(enemy & enemy, int length, int speed, double enemyslope, SDL_Rect rect)
{//rect 0,-1100,1950,400
	if (enemy.dir == LEFT)
	{
		if (enemy.randomslope > 0)
		{
			enemy.rect.y -= speed;
		}
		else
		{
			enemy.rect.y += speed;
		}
		enemy.rect.x -= 1;
		//enemy.rect.y = (enemyslope*enemy.rect.x) - (enemyslope*enemy.originalrect.x) + enemy.originalrect.y;
		if (enemy.rect.x <= rect.x || enemy.rect.x + enemy.rect.w >= rect.x + rect.w || enemy.rect.y <= rect.y || enemy.rect.y + enemy.rect.h >= rect.y + rect.h)
		{
			if (enemy.rect.x <= rect.x)
			{
				if (enemy.randomslope > 0)
				{
					enemy.rect.y += enemyslope;
				}
				else
				{
					enemy.rect.y -= enemyslope;
				}
				enemy.rect.x += 1;
			}
			else if (enemy.rect.x + enemy.rect.w >= rect.x + rect.w)
			{
				if (enemy.randomslope > 0)
				{
					enemy.rect.y += speed;
				}
				else
				{
					enemy.rect.y -= speed;
				}
				enemy.rect.x += 1;
			}
			else if (enemy.rect.y <= rect.y)
			{
				if (enemy.randomslope > 0)
				{
					enemy.rect.y += speed;
				}
				else
				{
					enemy.rect.y -= speed;
				}
				enemy.rect.x += 1;
			}
			else if (enemy.rect.y + enemy.rect.h >= rect.y + rect.h)
			{
				if (enemy.randomslope > 0)
				{
					enemy.rect.y += speed;
				}
				else
				{
					enemy.rect.y -= speed;
				}
				enemy.rect.x += 1;
			}
			enemy.dir = RIGHT;
			enemy.randomslope = enemy.randomslope * -1;
			//enemy.thebool = 0;
		}
		else if (enemy.rect.x < enemy.originalrect.x - length)
		{
			enemy.thebool = 0;
			enemy.dir = RIGHT;
		}
	}
	if (enemy.dir == RIGHT)
	{
		if (enemy.randomslope > 0)
		{
			enemy.rect.y -= speed;
		}
		else
		{
			enemy.rect.y += speed;
		}
		enemy.rect.x += 1;
		//enemy.rect.y = (enemyslope*enemy.rect.x) - (enemyslope*enemy.originalrect.x) + enemy.originalrect.y;
		if (enemy.rect.x <= rect.x || enemy.rect.x + enemy.rect.w >= rect.x + rect.w || enemy.rect.y <= rect.y || enemy.rect.y + enemy.rect.h >= rect.y + rect.h)
		{
			if (enemy.rect.x <= rect.x)
			{
				if (enemy.randomslope > 0)
				{
					enemy.rect.y += speed;
				}
				else
				{
					enemy.rect.y -= speed;
				}
				enemy.rect.x -= 1;
			}
			else if (enemy.rect.x + enemy.rect.w >= rect.x + rect.w)
			{
				if (enemy.randomslope > 0)
				{
					enemy.rect.y += speed;
				}
				else
				{
					enemy.rect.y -= speed;
				}
				enemy.rect.x -= 1;
			}
			else if (enemy.rect.y <= rect.y)
			{
				if (enemy.randomslope > 0)
				{
					enemy.rect.y += speed;
				}
				else
				{
					enemy.rect.y -= speed;
				}
				enemy.rect.x -= 1;
			}
			else if (enemy.rect.y + enemy.rect.h >= rect.y + rect.h)
			{
				if (enemy.randomslope > 0)
				{
					enemy.rect.y += speed;
				}
				else
				{
					enemy.rect.y -= speed;
				}
				enemy.rect.x -= 1;
			}
			enemy.dir = LEFT;
			enemy.randomslope = enemy.randomslope * -1;
			//enemy.thebool = 0;
		}
		else if (enemy.rect.x > enemy.originalrect.x + length)
		{
			enemy.thebool = 0;
			enemy.dir = LEFT;
		}
	}

}
void enemycosine(enemy & enemy, int length, int speed, int amplitude)
{
	if (enemy.dir == RIGHT)
	{
		enemy.rect.x += speed;
		enemy.rect.y = amplitude * cos(enemy.angle/2) + enemy.originalrect.y;
		enemy.angle += .1;
		if (enemy.rect.x > enemy.originalrect.x)
		{
			enemy.dir = LEFT;
		}
	}
	else if (enemy.dir == LEFT)
	{
		enemy.rect.x -= speed;
		enemy.rect.y = amplitude * cos(enemy.angle/2) + enemy.originalrect.y;
		enemy.angle += .1;
		if (enemy.rect.x < enemy.originalrect.x - length)
		{
			enemy.dir = RIGHT;
		}
	}

}
void enemycosineinterceptor(enemy & enemy, int speed, int amplitude)
{
		enemy.rect.x -= speed;
		enemy.rect.y = amplitude * cos(enemy.angle / 2) + enemy.originalrect.y;
		enemy.angle += .1;
}
void enemyrectcounterclock(enemy & enemy, SDL_Rect therect, int speed,bool & x)//set x to 0, 0 means x movement
{
	if (x == 0)
	{
		if (enemy.dir == LEFT)
		{
			if (enemy.rect.x < therect.x)
			{
				x = 1;
				enemy.dir = DOWN;
			}
			enemy.rect.x -= speed;
		}
		else if (enemy.dir == RIGHT)
		{
			if (enemy.rect.x > therect.x + therect.w)
			{
				x = 1;
				enemy.dir = UP;
			}
			enemy.rect.x += speed;
		}
	}
	else if (x == 1)
	{
		if (enemy.dir == UP)
		{
			if (enemy.rect.y < therect.y)
			{
				x = 0;
				enemy.dir = LEFT;
			}
			enemy.rect.y -= speed;
		}
		else if (enemy.dir == DOWN)
		{
			if (enemy.rect.y > therect.y + therect.h)
			{
				x = 0;
				enemy.dir = RIGHT;
			}
			enemy.rect.y += speed;
		}
	}
}
void enemyrectclock(enemy & enemy, SDL_Rect therect, int speed, bool & x)
{
	if (x == 0)
	{
		if (enemy.dir == LEFT)
		{
			if (enemy.rect.x < therect.x)
			{
				x = 1;
				enemy.dir = UP;
			}
			enemy.rect.x -= speed;
		}
		else if (enemy.dir == RIGHT)
		{
			if (enemy.rect.x > therect.x + therect.w)
			{
				x = 1;
				enemy.dir = DOWN;
			}
			enemy.rect.x += speed;
		}
	}
	else if (x == 1)
	{
		if (enemy.dir == UP)
		{
			if (enemy.rect.y < therect.y)
			{
				x = 0;
				enemy.dir = RIGHT;
			}
			enemy.rect.y -= speed;
		}
		else if (enemy.dir == DOWN)
		{
			if (enemy.rect.y > therect.y + therect.h)
			{
				x = 0;
				enemy.dir = LEFT;
			}
			enemy.rect.y += speed;
		}
	}
}
void enemyrotate(enemy & enemy)
{
	double radian = -(enemy.angle * 3.14) / 180;
	enemy.rect.x = (enemy.originalrect.w / 2) * cos(enemy.angle) + (enemy.originalrect.x);
	enemy.rect.y = (enemy.originalrect.w / 2) * sin(enemy.angle) + (enemy.originalrect.y);
	if (enemy.rotatespeed != NULL)
	{
		enemy.angle += enemy.rotatespeed;
	}
	else
	{
		cout << "sup";
		enemy.angle += .06;
	}
}
void enemyrotateleveltwo(enemy & enemy)
{
	double radian = -(enemy.angle * 3.14) / 180;
	enemy.rect.x = (enemy.originalrect.w / 2) * cos(enemy.angle) + (enemy.originalrect.x);
	enemy.rect.y = (enemy.originalrect.w / 2) * sin(enemy.angle) + (enemy.originalrect.y);
	if (enemy == leveltwoenemies[15])
	{
		enemy.angle -= .04;
	}
	else
	{
		enemy.angle += .03;
	}
}
void camerascroll(SDL_Rect & player, vector<ground> & leveloneground, vector<enemy> & enemies,vector<SDL_Rect> & boxes, dir direction,int speed,vector<enemy> & inter)
{
	if (direction == LEFT || direction == UP)
	{
		speed = speed * -1;
	}
	for (int i = 0; i < leveloneground.size(); i++)
	{
		if (direction == UP || direction == DOWN)
		{
			leveloneground[i].therect.y += speed;
		}
		else
		{
			leveloneground[i].therect.x += speed;
		}
	}
	for (int i = 0; i < boxes.size(); i++)
	{
		if (direction == UP || direction == DOWN)
		{
			boxes[i].y += speed;
		}
		else
		{
			boxes[i].x += speed;
		}
	}
	for (int i = 0; i < enemies.size(); i++)
	{
		if (direction == UP || direction == DOWN)
		{
			enemies[i].rect.y += speed;
			enemies[i].originalrect.y += speed;
		}
		else
		{
			enemies[i].rect.x += speed;
			enemies[i].originalrect.x += speed;
		}
	}
	for (int i = 0; i < inter.size(); i++)
	{
		if (direction == UP || direction == DOWN)
		{
			inter[i].rect.y += speed;
			inter[i].originalrect.y += speed;
		}
		else
		{
			inter[i].rect.x += speed;
			inter[i].originalrect.x += speed;
		}
	}
	if (direction == UP || direction == DOWN)
	{
		ball1.y += speed;
		my += speed;
		ball1centery += speed;
	}
	else
	{
		mx += speed;
		ball1.x += speed;
		ball1centerx += speed;
	}
	
	ball7.x = phsix.x;
	ball7.y = phsix.y;
	ball6.x = phfive.x;
	ball6.y = phfive.y;
	ball5.x = phfour.x;
	ball5.y = phfour.y;
	ball4.x = phthree.x;
	ball4.y = phthree.y;
	ball3.x = phtwo.x;
	ball3.y = phtwo.y;
	ball2.x = phone.x;
	ball2.y = phone.y;

	phone.x = ball1.x;
	phone.y = ball1.y;
	phtwo.x = ball2.x;
	phtwo.y = ball2.y;
	phthree.x = ball3.x;
	phthree.y = ball3.y;
	phfour.x = ball4.x;
	phfour.y = ball4.y;
	phfive.x = ball5.x;
	phfive.y = ball5.y;
	phsix.x = ball6.x;
	phsix.y = ball6.y;
}
void levelfive()
{
	if (checkcollision(yikes,levelfiverects[1]) && bossspawn == 0)
	{
		bossspawn = 1;
		levelfiveground[0].therect.x = levelfiveground[1].therect.x - 3000;
		Mix_PlayChannel(0, carriersound, 0);
	}
	if (checkcollision(yikes, levelfiverects[2]) && phoenixphase == 0)
	{
		phoenixphase = 1;
	}
	if (bossspawn == 1)
	{
		
		if (finalphase == 1)
		{

		}
		else
		{
			SDL_RenderCopy(grender, carrier, 0, &levelfiverects[0]);
		}

		SDL_RenderCopy(grender, phoenix, 0, &levelfiverects[2]);
		

		//interceptors
		//spawn
		if (spawncounter >= interceptorspawn && interceptphase == 1)
		{
			interceptorz[currentinterceptor].thebool = 1;
			interceptorz[currentinterceptor].rotatespeed = .04;
			interceptorz[currentinterceptor].randomspeed = rand() % 3;//tells whether y is negative or positive
			int random = rand() % 250 + 100;
			interceptorz[currentinterceptor].originalrect = { levelfiverects[0].x,levelfiverects[0].y + 200,random,50 };
			interceptorz[currentinterceptor].rect = { levelfiverects[0].x + random/2,levelfiverects[0].y + 200,35,35 };
			interceptorz[currentinterceptor].randomlength = rand() % 150 + 50;//amplitude
			currentinterceptor++;
			if (currentinterceptor >= 50)
			{
				currentinterceptor = 0;
			}
			spawncounter = 0;
		}
		//print and move move random x position and y positive or negative
		for (int i = 0; i < interceptorz.size(); i++)
		{
			if (interceptorz[i].thebool == 1)
			{
				SDL_RenderCopy(grender, interceptorz[i].text, 0, &interceptorz[i].rect);
				if (interceptorcosine == 1)
				{
					enemycosineinterceptor(interceptorz[i], 5, interceptorz[i].randomlength);
				}
				else
				{
					int randomt = rand() % 3 + 1;
					interceptorz[i].originalrect.x -= randomt;
					interceptorz[i].rect.x -= randomt;
					int randomz = rand() % 2 + 1;
					if (interceptorz[i].randomspeed == 0)
					{
						interceptorz[i].originalrect.y -= randomz;
						interceptorz[i].rect.y -= randomz;
					}
					else if (interceptorz[i].randomspeed == 1)
					{
						interceptorz[i].originalrect.y += randomz;
						interceptorz[i].rect.y += randomz;
					}
					else if (interceptorz[i].randomspeed == 2)
					{
						if (interceptorz[i].randomspeed == 2)
						{
							interceptorz[i].originalrect.y += randomz;
							interceptorz[i].rect.y += randomz;
							interceptorz[i].randomspeed = 3;
						}
						else
						{
							interceptorz[i].originalrect.y -= randomz;
							interceptorz[i].rect.y -= randomz;
							interceptorz[i].randomspeed = 2;
						}
					}
					enemyrotate(interceptorz[i]);
				}
			}
			else
			{

			}
			//clean up
			if (interceptorz[i].rect.x < levelfiveground[1].therect.x - 100)
			{
				interceptorz[i].thebool = 0;
			}
			if (phoenixphase == 1)
			{
				if (interceptorz[i].rect.x < levelfiveground[26].therect.x - 100)
				{
					interceptorz[i].thebool = 0;
				}
			}
		}
		//end of interceptorz
		//laserphase
		if (laserphase == 1)
		{
			if (spawnlaser == 1)
			{
				lasercount++;
				if (laserswitch == 0)
				{
					int randomx = rand() % 800;
					int secondx = randomx + 200;
					SDL_Rect rectone = { levelfiveground[1].therect.x,levelfiveground[1].therect.y,randomx,75 };
					SDL_Rect recttwo = { levelfiveground[1].therect.x + randomx + 200,levelfiveground[1].therect.y,(levelfiveground[1].therect.x + levelfiveground[1].therect.w) - (levelfiveground[1].therect.x + randomx + 200) ,75 };
					levelfiverects.push_back(rectone);
					levelfiverects.push_back(recttwo);
					spawnlaser = 0;

					laserswitch = 1;
				}
				else
				{
					int randomx = rand() % 800;
					int secondx = randomx + 200;
					SDL_Rect rectone = { levelfiveground[1].therect.x,levelfiveground[1].therect.y,75,randomx };
					SDL_Rect recttwo = { levelfiveground[1].therect.x,levelfiveground[1].therect.y + randomx + 200, 75,(levelfiveground[1].therect.y + levelfiveground[1].therect.h) - (levelfiveground[1].therect.y + randomx + 200) };
					levelfiverects.push_back(rectone);
					levelfiverects.push_back(recttwo);
					spawnlaser = 0;

					laserswitch = 0;
				}
			}
			if (laserswitch == 1)
			{
				levelfiverects[6].y += 7;
				levelfiverects[7].y += 7;
			}
			else
			{
				levelfiverects[6].x += 6;
				levelfiverects[7].x += 6;
			}
			if (laserswitch == 1)
			{
				SDL_RenderCopy(grender, bluelaser, 0, &levelfiverects[6]);
				SDL_RenderCopy(grender, bluelaser, 0, &levelfiverects[7]);
				if (levelfiverects[6].y >= levelfiveground[1].therect.y + levelfiveground[1].therect.h)
				{
					spawnlaser = 1;
					levelfiverects.pop_back();
					levelfiverects.pop_back();
					if (lasercount == 6)
					{
						laserphase = 0;
						chasephase = 1;
					}
				}
			}
			else
			{
				SDL_RenderCopy(grender, bluelaser, 0, &levelfiverects[6]);
				SDL_RenderCopy(grender, bluelaser, 0, &levelfiverects[7]);
				if (levelfiverects[6].x >= levelfiveground[1].therect.x + levelfiveground[1].therect.w)
				{
					spawnlaser = 1;
					levelfiverects.pop_back();
					levelfiverects.pop_back();
					if (lasercount == 8)//should be 8
					{
						laserphase = 0;
						chasephase = 1;
					}
				}
			}
			
		}
		//end of laserphase
		//chasephase
		if (chasephase == 1)
		{
			if (phoenixphase == 1)
			{
				chasephase = 0;
			}
			if (chasephaseonce == 1)
			{
				SDL_Rect fire = { levelfiveground[1].therect.x,levelfiveground[1].therect.y-1500,100,4000 };
				levelfiverects.push_back(fire);
				
				chasephaseonce = 0;
			}
		
			levelfiverects[6].x += 4;
			levelfiverects[0].x += 5;
			SDL_RenderCopy(grender, bluelaser, 0, &levelfiverects[6]);
		}
		//end of chase phase
		//phoenix phase
		if (phoenixphase == 1)
		{
			interceptorspawn = 60;
			interceptphase = 1;
			levelfiverects[2].x = yikes.x - 50;
			levelfiverects[2].y = yikes.y - 40;
			banespeed = 8;
			setxincrement(degree, xdiff, ydiff, xincrement, banespeed);
			if (lastphasecounter > 1000)
			{
				interceptorcosine = 0;
				if (lastphasecounter % 500 == 0)
				{
					interceptorspawn -= 5;
				}
			}
			if (phoenixonce == 1)
			{
				interceptorcosine = 1;
				//7425,-250,75,1400
				levelfiverects[0] = { levelfiveground[27].therect.x - 500,levelfiveground[27].therect.y + 600,400,400 };
				phoenixonce = 0;
			}
			if (levelfiverects[6].x < levelfiveground[26].therect.x)
			{
				levelfiverects[6].x += 8;
				SDL_RenderCopy(grender, bluelaser, 0, &levelfiverects[6]);
			}
			else
			{
				if (checkcollision(levelfiverects[3], levelfiverects[0]))
				{
					carrierhealth--;
				}
				if (carrierhealth <= 0)
				{
					endphase = 1;
					Mix_PlayChannel(0, explosionsound, 0);
					interceptphase = 0;
					//phoenixphase = 0;
				}
				if (endphase == 1)
				{
					for (int i = 0; i < 50; i++)
					{
						interceptorz[i].rect = { 0,0,0,0 }; interceptorz[i].originalrect = { 0,0,0,0 };
					}
				
					levelfiverects[4] = { levelfiverects[0].x,levelfiverects[0].y,400,400 };
					SDL_RenderCopy(grender, explosion, 0, &levelfiverects[4]);
					Mix_PlayChannel(0, explosionsound, 0);
					explosioncounter++;
					if (explosioncounter > 200)
					{
						rightclickstop = 1;
						rightclicked = 0;
						ball1.x = levelfiveground[30].therect.x + 200; ball1.y = levelfiveground[30].therect.y + 200;
						bossspawn = 0;
						phoenixphase = 0;
						levelfiverects[2] = { 0,0,0,0 };
						levelfiverects[0] = { 0,0,0,0 };
						levelfiverects[4] = { 0,0,0,0 };
						
					}
				}
				else
				{
					SDL_SetRenderDrawColor(grender, 255, 0, 0, 0);
					levelfiverects[4] = { 300, 30, carrierhealth, 25 };
					SDL_RenderFillRect(grender, &levelfiverects[4]);
				
					
				}
				candiefrombarrier = 1;
				if (levelfiveground[26].aboolean == 0)
				{

				}
				else
				{
					for (int i = 26; i < 30; i++)
					{
						levelfiveground[i].aboolean = 0;
					}
				}
			}

			//carrier movement
			if (endphase == 1)
			{

			}
			else
			{
				if (carriergoup == 1)
				{
					levelfiverects[0].y -= 4;
					if (levelfiverects[0].y < levelfiveground[28].therect.y + 100)
					{
						carriergoup = 0;
					}
				}
				else
				{
					levelfiverects[0].y += 4;
					if (levelfiverects[0].y > (levelfiveground[29].therect.y - 500))
					{
						carriergoup = 1;
					}
				}
			}
			if (playershoot == 1)
			{
				if (laserspawn == 1)
				{
					laserspawn = 0;
				}
				levelfiverects[3] = { yikes.x,yikes.y,2000,25 };
				//levelfiverects[3].x += 5;
				if (laserincrement < 200)
				{
					SDL_RenderCopy(grender, bluelaser, 0, &levelfiverects[3]);
				}
				else
				{
					levelfiverects[3] = { -10000,-10000,10,10 };
				}
				laserincrement += 5;
				if (laserincrement > 700)
				{
					playershoot = 0;
					laserspawn = 1;
					laserincrement = 0;		
				}
			}

			lastphasecounter++;
		}
		//end of phoenix phase
		if (switchfloorcount == 400)
		{
			Mix_PlayChannel(0, carriersoundtwo, 0);
		}
		if (switchfloorcount == 500)
		{
			levelfiveground[1].thegroundtype = REVERSEICE;
		}
		if (switchfloorcount == 900)
		{
			Mix_PlayChannel(0, carriersoundthree, 0);
		}
		if (switchfloorcount == 1000)
		{
			levelfiveground[1].thegroundtype = ICE;
		}
		if (switchfloorcount == 1300)
		{
			levelfiveground[1].thegroundtype = FASTICE;
		}
		if (switchfloorcount == 1600)
		{
			interceptphase = 0;
		}
		if (switchfloorcount == 1700)
		{
			Mix_PlayChannel(0, carriersoundtwo, 0);
		}
		if (switchfloorcount == 1800)//is 3000
		{
			levelfiveground[1].thegroundtype = ICE;
			laserphase = 1;
			interceptphase = 0;
		}

		spawncounter++;
		switchfloorcount++;
	}




}