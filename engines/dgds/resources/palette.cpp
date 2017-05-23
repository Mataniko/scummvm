/*
 * palette.cpp
 *
 *  Created on: 2011-08-24
 *      Author: alex
 */

#include "dgds/resources/palette.h"

#define VGA_COLOR_TRANS(x) ((x) * 255 / 63)

namespace Dgds {

Palette::Palette(Resource *res) {
	// TODO Auto-generated constructor stub
	Resource *resVGA = res->getSubResource("PAL:")->getSubResource("VGA:");

	_size = resVGA->size();
	if (_size != 0x300) {
		delete resVGA;
		return;
	}

	for (int i = 0; i < 0x300; ++i) {
		_pal[i] = VGA_COLOR_TRANS(resVGA->readByte());
	}

	delete resVGA;
}

byte *Palette::getPalette() {
	return _pal;
}

Palette::~Palette() {
	// TODO Auto-generated destructor stub
}

} /* namespace Dgds */
