#ifndef IMUSICCENTREWIDGETCHILD_H_H_HEAD__FILE__
#define IMUSICCENTREWIDGETCHILD_H_H_HEAD__FILE__
#include <classTypeInfo/classTypeInfoVar.h>
class IMusicCentreWidget;

class IMusicCentreWidgetChild : public virtual ClassTypeInfoVar {
protected:
	~IMusicCentreWidgetChild( ) override;

public:
	IMusicCentreWidgetChild( );
	virtual bool setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) = 0;
	virtual IMusicCentreWidget * getMusicCentreWidget( ) const = 0;
};

#endif // IMUSICCENTREWIDGETCHILD_H_H_HEAD__FILE__
