#ifndef MUSICFAVORITEWIDGET_H_H_HEAD__FILE__
#define MUSICFAVORITEWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include "../component/musicWindow/interface/widget/iMusicFavoriteWidget.h"

#include "../interface/iAppResourceCore.h"

class MusicFavoriteWidget : public QWidget, public IMusicFavoriteWidget, public IAppResourceCore {
	Q_OBJECT;

public:
	MusicFavoriteWidget( );
	~MusicFavoriteWidget( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;

protected:
	bool setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) override;

public:
	QWidget * toWidget( ) override;
	bool drawWidgeTarget( QWidget *widget ) override;
	MusicCentreWidget * getMusicCentreWidget( ) const override;

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	bool fromYPosGetMusicFavoriteItem( IMusicFavoriteItem *&result_music_favorite_item, const size_t &pos_y ) const override;
	bool fromIndexGetMusicFavoriteItem( IMusicFavoriteItem *&result_music_favorite_item, const size_t &index ) const override;
	bool fromNameGetMusicFavoriteItem( IMusicFavoriteItem *&result_music_favorite_item, const QString &index ) const override;
};

#endif // MUSICFAVORITEWIDGET_H_H_HEAD__FILE__
