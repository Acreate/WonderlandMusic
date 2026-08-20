#ifndef MUSICWIDGETCHILD_H_H_HEAD__FILE__
#define MUSICWIDGETCHILD_H_H_HEAD__FILE__
#include <interface/iAppJsonData.h>
#include "../musicCentreWidgetChild/iMusicCentreWidgetChild.h"

class MusicWidgetChild : public IAppJsonData, public IMusicCentreWidgetChild {
	friend class MusicCentreWidget;
};

#endif // MUSICWIDGETCHILD_H_H_HEAD__FILE__
