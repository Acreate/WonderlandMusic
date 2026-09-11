#ifndef MUSICWIDGETSIZEINFO_H_H_HEAD__FILE__
#define MUSICWIDGETSIZEINFO_H_H_HEAD__FILE__
#include <component/musicWindow/interface/info/iMusicWidgetSizeInfo.h>

class MusicWidgetSizeInfo : public IMusicWidgetSizeInfo {
	IMusicCentreWidget *musicCentreWidget = nullptr;

private:
	int favoriteWidth;
	int titleHeight;

public:
	MusicWidgetSizeInfo( );
	~MusicWidgetSizeInfo( ) override;

protected:
	bool setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) override;

public:
	bool initInfo( ) override;
	int getFavoriteWidth( ) const override;
	int getTitleHeight( ) const override;
	bool updateMusicWidgetLayout( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	IMusicCentreWidget * getMusicCentreWidget( ) const override;

protected:
	int setFavoriteWidth( const int &favoriet_width ) override;
	int setTitleHeight( const int &title_height ) override;
};

#endif // MUSICWIDGETSIZEINFO_H_H_HEAD__FILE__
