/*
 * image.h
 *
 *  Created on: 2011-08-24
 *      Author: alex
 */

#ifndef DGDS_IMAGE_H_
#define DGDS_IMAGE_H_

#include "common/array.h"
#include "dgds/resource.h"

namespace Dgds {

struct FrameInfo {
	uint16 height;
	uint16 width;
	uint32 offset;
};

class Image {
public:
	Image(Resource *bmp);
	virtual ~Image();

private:
	uint16 _frames;
	Common::Array<FrameInfo> _framesDefinition;
	void loadFrames(Resource *res);

};

} /* namespace Dgds */
#endif
