/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL: https://scummvm-dgds.googlecode.com/svn/trunk/dgds.cpp $
 * $Id: dgds.cpp 28 2010-06-19 11:16:58Z alexbevi $
 *
 */

#include "common/config-manager.h"
#include "common/debug-channels.h"
#include "common/system.h"
#include "common/savefile.h"
#include "graphics/palette.h"
#include "gui/EventRecorder.h"

#include "engines/util.h"

#include "dgds/dgds.h"
#include "dgds/game_willy.h"

#include "dgds/resources/moviegroup.h"
#include "dgds/resources/movie.h"
#include "dgds/resources/image.h"
#include "dgds/resources/font.h"
#include "dgds/resources/screen.h"
#include "dgds/resources/palette.h"

namespace Dgds {

DgdsEngine::DgdsEngine(OSystem *syst, Common::Language lang): Engine(syst), _language(lang), _resMgr(NULL) {
	DebugMan.addDebugChannel(kDebugResources, "Resources", "Debug Information for Resources");

	DebugMan.enableDebugChannel("Resources");
	_rnd = new Common::RandomSource("dgds");
}

DgdsEngine::~DgdsEngine() {
	if (_resMgr)
		delete _resMgr;

	if (_game)
		delete _game;

	DebugMan.clearAllDebugChannels();
	delete _rnd;
}

Common::Error DgdsEngine::run() {
	// Initialize backend
	initGraphics(320, 200, true);

	Common::String gameName = Resman.findGDS();
	if (!gameName.size())
		return Common::kNoGameDataFoundError;

	if (gameName == "WILLY") {
		debug("Starting Willy Beamish");
		_game = new WillyBeamish(this);
	} else {
		error("DGDS Title %s currently not supported", gameName.c_str());
	}




	// debug
	//Resource *nurse = Resman.load("CN_NURSE.BMP");
	//Image *img = new Image(nurse);

	Resource *scrRes = Resman.load("DYNAMIX.SCR");
//	Screen *scr = new Screen(scrRes);
	Resource *palRes = Resman.load("DYNAMIX.PAL");
	Palette *pal = new Palette(palRes);
	Resource *fntRes = Resman.load("8X8.FNT");
	Font *font = new Font(fntRes);

	_system->getPaletteManager()->setPalette(pal->getPalette(), 0, 256);
	while (true) {

		for (int i = 0; i < 256; i++) {
			_system->delayMillis(400);
			_system->fillScreen(i);
			Graphics::Surface *screenSurface = _system->lockScreen();
			font->drawString(screenSurface, 10, 10, "whatever you want to say", 0);
			_system->unlockScreen();
			_system->updateScreen();
		}

	}

	/*
	Resource *ttm = Resman.load("TITLE.TTM");
	Movie *m = new Movie(ttm);
	m->play();

	delete ttm;
	delete m;

	Resource *fntRes = Resman.load("WVCR.FNT");
	Font *font = new Font(fntRes);

	Resource *palRes = Resman.load("DYNAMIX.PAL");
	Palette *pal = new Palette(palRes);

	byte *bPal = pal->getPalette();
	byte wPal[0x300];

	for (int i = 0; i < 0x300; i++) {
	    wPal[i] = 0xff;
	}


	_system->getPaletteManager()->setPalette(bPal, 0, 256);
	while (true) {

	    for (int i = 0; i < 256; i++) {
	        _system->delayMillis(200);
	        _system->fillScreen(i);
	        Graphics::Surface *screenSurface = _system->lockScreen();
	        font->drawString(screenSurface, 10, 10, "whatever you want to say", 0);
	        _system->unlockScreen();
	        _system->updateScreen();
	    }

	}
	*/

	// end debug




	/*
	bool end = false;
	Common::EventManager *em = _system->getEventManager();
	while (!end) {
	    Common::Event ev;
	    if (em->pollEvent(ev)) {
	        if (ev.type == Common::EVENT_KEYDOWN) {
	            if (ev.kbd.keycode == Common::KEYCODE_ESCAPE)
	                end = true;
	        }
	    }
	    _system->delayMillis(10);
	}
	*/

	return Common::kNoError;
}

} // End of namespace Dgds
