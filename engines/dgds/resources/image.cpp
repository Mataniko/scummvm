#include "dgds/resources/image.h"
#include "dgds/compression.h"

namespace Dgds {

Image::Image(Resource *bmp) {
	// TODO Auto-generated constructor stub
	Resource *data = bmp->getSubResource("BMP:");
	loadFrames(data);

	delete data;
}

Image::~Image() {
	// TODO Auto-generated destructor stub

}

void Image::loadFrames(Resource *res) {
	Resource *inf = res->getSubResource("INF:");
	Resource *off = res->getSubResource("OFF:");

	inf->seek(0);
	_frames = inf->readUint16LE();

	for (int i = 0; i < _frames; i++) {
		_framesDefinition.push_back(FrameInfo());
		inf->seek(4 * i + 2);
		_framesDefinition[i].width = inf->readUint16LE();
		_framesDefinition[i].height = inf->readUint16LE();

		off->seek(4 * i);
		_framesDefinition[i].offset = off->readUint32LE();
	}

	/*for (int i = 0; i < _framesDefinition.size(); i++) {
	    debug("Frame Definition %i Start: %i (%02x)", i, _framesDefinition[i].offset, _framesDefinition[i].offset);
	}*/

	delete inf;
	delete off;
}

} /* namespace Dgds */
