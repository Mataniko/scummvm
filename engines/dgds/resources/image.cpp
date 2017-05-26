#include "dgds/resources/image.h"

namespace Dgds {

Image::Image(Resource *bmp) {
	// TODO Auto-generated constructor stub
	Resource *data = bmp->getSubResource("BMP:");
	_framesDefinition = new Common::Array<FrameInfo>();
	loadFrames(data);

	delete data;
}

Image::~Image() {
	// TODO Auto-generated destructor stub
	delete _framesDefinition;

}

void Image::loadFrames(Resource *res) {
	Resource *inf = res->getSubResource("INF:");
	Resource *off = res->getSubResource("OFF:");

	inf->seek(0);
	_frames = inf->readUint16LE();

	for (int i = 0; i < _frames; i++) {
		FrameInfo fr;
		inf->seek(4 * i + 2);
		fr.width = inf->readUint16LE();
		fr.height = inf->readUint16LE();

		off->seek(4 * i);
		fr.offsetX = off->readUint16LE();
		fr.offsetY = off->readUint16LE();

		_framesDefinition->push_back(fr);
	}

	delete inf;
	delete off;
}

} /* namespace Dgds */
