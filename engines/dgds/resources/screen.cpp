/*
 * screen.cpp
 *
 *  Created on: 2011-08-24
 *      Author: alex
 */

#include "screen.h"
#include "common/file.h"

namespace Dgds {

Screen::Screen(Resource *scr) {
	// TODO Auto-generated constructor stub
	Resource *data = scr->getSubResource("SCR:")->getSubResource("VQT:");

	data->seek(0);

	Common::MemoryReadStream *ms = decompLZW(data, 320 * 200);
	Common::DumpFile outFile;
	outFile.open("scr.vqt");

	char *fileContents = new char[1024];
	int len;
	for (int i = ms->size(); i > 0; i -= len) {
		len = ms->read(fileContents, 1024 < i ? 1024 : i);
		outFile.write(fileContents, len);
	}
	delete fileContents;

	outFile.close();


}

Screen::~Screen() {
	// TODO Auto-generated destructor stub
}

} /* namespace Dgds */
