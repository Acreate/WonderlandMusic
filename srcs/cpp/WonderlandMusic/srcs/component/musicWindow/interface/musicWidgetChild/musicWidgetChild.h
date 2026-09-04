#ifndef MUSICWIDGETCHILD_H_H_HEAD__FILE__
#define MUSICWIDGETCHILD_H_H_HEAD__FILE__
#include <interface/iAppJsonData.h>
#include "../musicCentreWidgetChild/iMusicCentreWidgetChild.h"

class MusicWidgetChild : public IAppJsonData, public IMusicCentreWidgetChild {
protected:
	~MusicWidgetChild( ) override;
};

#endif // MUSICWIDGETCHILD_H_H_HEAD__FILE__
