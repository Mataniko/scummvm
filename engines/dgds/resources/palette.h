#ifndef DGDS_PALETTE_H_
#define DGDS_PALETTE_H_

#include "dgds/resource.h"

namespace Dgds {

class Palette {
public:
	Palette(Resource *res);
	byte *getPalette();
	virtual ~Palette();

private:
	byte _pal[256 * 3];
	uint32 _size;
};

} /* namespace Dgds */
#endif
