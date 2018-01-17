#include "dgds/resource.h"
#include "dgds/compression.h"

#ifndef DGDS_SCREEN_H_
#define DGDS_SCREEN_H_

namespace Dgds {

class Screen {
public:
	Screen(Resource *scr);
	virtual ~Screen();
};

} /* namespace Dgds */
#endif
