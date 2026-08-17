#ifndef MUSICWIDGETCHILD_H_H_HEAD__FILE__
#define MUSICWIDGETCHILD_H_H_HEAD__FILE__
#include <interface/iAppJsonData.h>

class MusicWidgetChild : public IAppJsonData {
private:
	friend class MusicCentreWidget;

protected:
	virtual bool setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) = 0;
};

#endif // MUSICWIDGETCHILD_H_H_HEAD__FILE__
