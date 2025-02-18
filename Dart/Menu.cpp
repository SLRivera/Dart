#include <iterator>
#include <stdio.h>
#include <string>
#include "Menu.h"
#include "Sound.h"
using std::string;
using std::to_string;
using std::copy;
using stdext::checked_array_iterator;

Sound* Menu::menuMouseClick = NULL;

//menu uses texture2d variables for background image
Menu::Menu(LPCWSTR name, float positionX, float positionY, int sizeOrigX, int sizeOrigY,
	float sizeScreenX, float sizeScreenY, D3DCOLOR color) :
	Texture2D(name, positionX, positionY, sizeOrigX, sizeOrigY, sizeScreenX, sizeScreenY, color)
{
	//FR(gSound->getSystem()->createSound("Content/Audio/sndMenuKeyPress", FMOD_DEFAULT, 0, &menuKeyPress); (for later use)
	if (NULL == menuMouseClick)
		FR(gSound->getSystem()->createSound("Content/Audio/sndMenuMouseClick.wav", FMOD_DEFAULT, 0, &menuMouseClick));
}

Menu::~Menu()
{
	onLostDevice();
	for (Button* B : mButtons)
		delete B;
	for (Texture2D* T : mTextures)
		delete T;
	vector<Button*>().swap(mButtons);
	vector<Texture2D*>().swap(mTextures);
}
//check if buttons are pressed
void Menu::update(float _dt)
{
	static float delay = 0.0f;
	delay += _dt;
	if (delay > 0.2f)
	{
		//if button is clicked
		if (gDInput->mouseButtonDown(0))
		{
			delay = 0.0f;
			//.. for each button
			for (Button* B : mButtons)
			{
				//see if it triggers
				//once one triggers, don't bother checking others
				if (B->tryClick(true))
				{
					gSound->getSystem()->playSound(FMOD_CHANNEL_FREE, menuMouseClick, false, NULL);
					break;
				}
			}
		}
		//if right mouse button is clicked
		else if (gDInput->mouseButtonDown(1))
		{
			delay = 0.0f;
			//.. for each button
			for (Button* B : mButtons)
			{
				//see if it triggers
				//once one triggers, don't bother checking others
				if (B->tryClick(false))
				{
					gSound->getSystem()->playSound(FMOD_CHANNEL_FREE, menuMouseClick, false, NULL);
					break;
				}
			}
		}
	}
}
//draw background and buttons
void Menu::draw()
{
	Texture2D::draw();//background
	//button
	for (Button* B : mButtons)
		B->draw();
	//other images
	for (Texture2D* T : mTextures)
		T->draw();

}

void Menu::drawText()
{
	for (Text* T : mTexts)
		T->draw();
}

void Menu::onLostDevice()
{
	//unload texture background
	Texture2D::onLostDevice();
	//unload textures for buttons
	for (Button* B : mButtons)
		B->onLostDevice();
	for (Texture2D* T : mTextures)
		T->onLostDevice();
	for (Text* T : mTexts)
		T->onLostDevice();
}

void Menu::onResetDevice()
{
	//reload background
	Texture2D::onResetDevice();
	//reload textures for buttons
	for (Button* B : mButtons)
		B->onResetDevice();
	for (Texture2D* T : mTextures)
		T->onResetDevice();
	for (Text* T : mTexts)
		T->onResetDevice();
}
//add new button to menu
void Menu::addButton(Button* _newButton)
{
	mButtons.push_back(_newButton);
}
//add new texture
void Menu::addTexture(Texture2D* _newTexture)
{
	mTextures.push_back(_newTexture);
}

void Menu::moveTexture(UINT _index, float _x, float _y)
{
	mTextures[_index]->setPosition(_x, _y);
}
//add new text
void Menu::addText(Text* _newText)
{
	mTexts.push_back(_newText);
}

