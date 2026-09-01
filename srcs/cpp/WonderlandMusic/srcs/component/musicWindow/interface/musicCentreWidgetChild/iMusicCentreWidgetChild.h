#ifndef IMUSICCENTREWIDGETCHILD_H_H_HEAD__FILE__
#define IMUSICCENTREWIDGETCHILD_H_H_HEAD__FILE__
#include <interface/iAppCore.h>
class IMusicCentreWidget;

class IMusicCentreWidgetChild : public IAppCore {
private:
	friend class IMusicCentreWidget;

protected:
	virtual bool setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) = 0;

public:
	IMusicCentreWidgetChild( );
	~IMusicCentreWidgetChild( ) override;
	virtual IMusicCentreWidget * getMusicCentreWidget( ) const = 0;
};

#endif // IMUSICCENTREWIDGETCHILD_H_H_HEAD__FILE__
