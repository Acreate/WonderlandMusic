#ifndef IMUSICCENTREWIDGETCHILD_H_H_HEAD__FILE__
#define IMUSICCENTREWIDGETCHILD_H_H_HEAD__FILE__
#include <interface/iAppCore.h>
class MusicCentreWidget;

class IMusicCentreWidgetChild : public IAppCore {
private:
	friend class MusicCentreWidget;

protected:
	virtual bool setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) = 0;

public:
	virtual MusicCentreWidget * getMusicCentreWidget( ) const = 0;
};

#endif // IMUSICCENTREWIDGETCHILD_H_H_HEAD__FILE__
