//This is the base class for the game states. Sub classes will override this.
//this contains the state machine, the base state class, and the base event class

#pragma once
#include <vector>
#include "Camera.h"
#include "D3DUtils.h"
#include "Level.h"
#include "LevelImporter.h"
#include "Menu.h"
#include "Player.h"
#include "Sound.h"
#include "UserInterface.h"
using std::vector;

//you have to be careful in what order you add the states in. you should add them so that
//their vector index lines up with the following enum
//state machine will start on eState 0
enum eState
{
	STATE_MAINMENU = 0,
	STATE_OPTIONSMENU,
	STATE_PLAY,
	STATE_LOSE,
	STATE_WIN,
	STATE_INTRO,
	STATE_LOADING
};

#define LEVEL_INDEX 0//which event the level load event is in the play state

class Event
{
public:
	Event() {}
	~Event(){}
	//override whichever functions are used in the child event class
	virtual void init()								{}//add parameters, this is to give needed info to event, like a menu to display
	virtual void beginEvent()						{}//do this as you enter the state
	virtual void endEvent()							{}//do this as you leave the state
	virtual void updateEvent(float _dt)				{}//do this during state update
	virtual void drawEvent3D()						{}//do this during 3d drawing
	virtual void drawEvent2D()						{}//do this during sprite drawing
	virtual void drawEventText()					{}//draw text on screen
	virtual void onLostDevice()						{}//do this on lost device
	virtual void onResetDevice()					{}//do this on reset device
	virtual void setLevel(wchar_t* _name)			{}//for EventProcessLevel only
	virtual wchar_t* getNextLevel()					{ return L""; }//for EventProcessLevel only
};

//base state class to be overridden
class State
{
public:
	State();
	~State();

	void	beginState();						//run all event.beginState
	void	endState();							//run all event.endState
	void	updateState(float _dt);				//etc
	void	drawState3D();
	void	drawState2D();
	void    drawStateText();
	void	onLostDevice();
	void	onResetDevice();

	void	addEvent(Event* newEvent);
	Event*  getEvent(UINT _index)		{ return mEvents[_index]; }
	void	setTransitioning(bool _bTrans) { bTransitioning = _bTrans; }
private:
	vector<Event*>	mEvents;
	//once this is set, it is going to a new state, cease processing events and go to end state
	bool			bTransitioning;
};
//the state machine
//keeps track of current state and runs all the events for the current state
class StateMachine
{
public:
	StateMachine();
	~StateMachine();
	void	beginState();						//run all state.beginState
	void	endState();							//run all state.endState
	void	updateState(float _dt);				//etc
	void	drawState3D();
	void	drawState2D();
	void	drawStateText();
	void	onLostDevice();
	void	onResetDevice();
	//add state or get current state
	void	addState(State* newState);
	eState	getCurrentState() { return mCurrentState; }
	void	transitionState(eState newState);//transition to new state
	void	turnOn();//initialize
	bool	getReset() { return bReset; }
	void	setReset(bool _reset) { bReset = _reset; }
	//changes loaded level
	//the file name is the level AFTER the one that's loading, the event
	//already has the one we're loading name
	//use "" if there is no level after
	void changeLevel(wchar_t* _newNextFile);
	wchar_t* getNextLevelFile(); 

private:
	vector<State*>	mStates;
	eState			mCurrentState;
	bool			bReset;
	Texture2D*		mLoadingScreen;
};

extern StateMachine* gStateMachine;

class EventDisplayMenuLoading : public Event
{
public:
	void beginEvent();
	void endEvent()							{ delete mMenu; }
	void updateEvent(float _dt)				{ mMenu->update(_dt); }
	void drawEvent2D()	{ 
		mMenu->draw();
		gStateMachine->transitionState(STATE_PLAY);
	}
	void drawEventText()					{ mMenu->drawText(); }
	void onLostDevice()						{ mMenu->onLostDevice(); }
	void onResetDevice()					{ mMenu->onResetDevice(); }
private:
	Menu* mMenu;
};


class EventDisplayMenuLoss : public Event
{
public:
	void beginEvent();
	void endEvent()							{ delete mMenu; }
	void updateEvent(float _dt)				{ mMenu->update(_dt); }
	void drawEvent2D()						{ mMenu->draw(); }
	void drawEventText()					{ mMenu->drawText(); }
	void onLostDevice()						{ mMenu->onLostDevice(); }
	void onResetDevice()					{ mMenu->onResetDevice(); }
private:
	Menu* mMenu;
};

//event to display main menu
class EventDisplayMenuMain : public Event
{
public:
	void beginEvent();
	void endEvent()							{ delete mMenu; }
	void updateEvent(float _dt)				{ mMenu->update(_dt); }
	void drawEvent2D()						{ mMenu->draw(); }
	void drawEventText()					{ mMenu->drawText(); }
	void onLostDevice()						{ mMenu->onLostDevice(); }
	void onResetDevice()					{ mMenu->onResetDevice(); }
private:
	Menu* mMenu;
};

//event to display options menu
class EventDisplayMenuOptions : public Event
{
public:
	void beginEvent();
	void endEvent()							{ delete mMenu; }
	void updateEvent(float _dt)				{ mMenu->update(_dt); }
	void drawEvent2D()						{ mMenu->draw(); }
	void drawEventText()					{ mMenu->drawText(); }
	void onLostDevice()						{ mMenu->onLostDevice(); }
	void onResetDevice()					{ mMenu->onResetDevice(); }
private:
	Menu* mMenu;
};

class EventDisplayMenuStory : public Event
{
public:
	void beginEvent();
	void endEvent()							{ delete mMenu; }
	void updateEvent(float _dt)				{ mMenu->update(_dt); }
	void drawEvent2D()						{ mMenu->draw(); }
	void drawEventText()					{ mMenu->drawText(); }
	void onLostDevice()						{ mMenu->onLostDevice(); }
	void onResetDevice()					{ mMenu->onResetDevice(); }
private:
	Menu* mMenu;
};

class EventDisplayMenuWin : public Event
{
public:
	void beginEvent();
	void endEvent()							{ delete mMenu; }
	void updateEvent(float _dt)				{ mMenu->update(_dt); }
	void drawEvent2D()						{ mMenu->draw(); }
	void drawEventText()					{ mMenu->drawText(); }
	void onLostDevice()						{ mMenu->onLostDevice(); }
	void onResetDevice()					{ mMenu->onResetDevice(); }
private:
	Menu* mMenu;
};


class EventDisplayUserInterface : public Event
{
public:
	void beginEvent();
	void endEvent()							{ delete mInterface; }
	void updateEvent(float _dt);			
	void drawEvent2D()						{ mInterface->draw(); }
	void drawEventText()					{ mInterface->drawText(); }
	void onLostDevice()						{ mInterface->onLostDevice(); }
	void onResetDevice()					{ mInterface->onResetDevice(); }
private:
	UserInterface* mInterface;
};

//an event to start music
class EventMusicStart : public Event
{
public:
	EventMusicStart(char* _music);
	void beginEvent();
	void updateEvent(float _dt)				{ gSound->mSystem->update(); }
	void endEvent();
private:
	char* mFile;
	Sound* mMusic;
};

//event to process the game camera
class EventProcessCamera : public Event
{
public:
	void beginEvent()
	{
		if (gCameraMain == NULL)
			gCameraMain = new Camera(D3DXVECTOR3(0.0f, 1000.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		else
			gCameraMain->init(D3DXVECTOR3(0.0f, 1000.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	void updateEvent(float _dt){ gCameraMain->update(); }
	//the full screen change will crash if we delete the camera, so just keep it and reinitialize it next time
	void endEvent(){}
};
 
//event to process follower/protected AI unit
class EventProcessFollower : public Event
{
public:
	void beginEvent(){
		gFollower = new Follower(L"Content/Models/DartFinal.x", L"Content/Textures/Tiny_skin.dds",
			L"Content/Textures/Tiny_skin_n.dds", g_levelImp->getBart().getPos()/*D3DXVECTOR3(1000.0f, 50.0f, 0.0f)*/, 100, 32.0f/*, D3DXVECTOR3(0.25, 0.25f, 0.25f)*/);
	}
	void endEvent()				{ delete gFollower;  }
	void updateEvent(float _dt)	{ gFollower->update(_dt); }
	void drawEvent3D()			{ gFollower->draw(); }
};

//event to display a given game level
class EventProcessLevel : public Event
{
public:
	EventProcessLevel();
	EventProcessLevel(wchar_t* _fileName, wchar_t* _nextFile, UINT _levelNum): 
		mLevelName(_fileName), mNextLevelName(_nextFile), mLevelNumber(_levelNum){}
	void beginEvent();
	void updateEvent(float  _dt)				{ gCurrentLevel->update(_dt); }
	void drawEvent3D()						{ gCurrentLevel->draw(); }
	void onLostDevice()						{ gCurrentLevel->onLostDevice(); }
	void onResetDevice()					{ gCurrentLevel->onResetDevice(); }
	void setLevel(wchar_t* _name)			{ 
		mLevelName = mNextLevelName; 
		mNextLevelName = _name;
		++mLevelNumber;
	}
	wchar_t* getNextLevel(){ return mNextLevelName; }
private:
	wchar_t* mLevelName;
	wchar_t* mNextLevelName;
	UINT mLevelNumber;
};

class EventProcessPlayer : public Event
{
	void beginEvent(){
		gPlayer = new Player(L"Content/Models/DartFinal.x", L"Content/Textures/Tiny_skin.dds",
			L"Content/Textures/Tiny_skin_n.dds", g_levelImp->getDart().getPos()/*D3DXVECTOR3(0.0f, 50.0f, 0.0f)*/,
			100, 40.0f, D3DXVECTOR3(1.25, 1.25f, 1.25f));
	}
	void updateEvent(float _dt)	{ gPlayer->update(_dt); }
	void drawEvent3D()			{ gPlayer->draw(); }
	void endEvent()
	{
		delete gPlayer;
	}
};