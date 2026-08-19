#ifndef MUSICWIDGETSIZEINFO_H_H_HEAD__FILE__
#define MUSICWIDGETSIZEINFO_H_H_HEAD__FILE__
#include "../component/musicWindow/interface/info/iMusicWidgetSizeInfo.h"

class MusicWidgetSizeInfo : public IMusicWidgetSizeInfo {
public:
	MusicWidgetSizeInfo( );
	~MusicWidgetSizeInfo( ) override;

protected:
	bool setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) override;

public:
	int getFavoriteWidth( ) const override;
	int getTitleHeight( ) const override;
	bool updateMusicWidgetLayout( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;

protected:
	int setFavoriteWidth( const int &favoriet_width ) override;
	int setTitleHeight( const int &favoriet_width ) override;
};

#endif // MUSICWIDGETSIZEINFO_H_H_HEAD__FILE__
