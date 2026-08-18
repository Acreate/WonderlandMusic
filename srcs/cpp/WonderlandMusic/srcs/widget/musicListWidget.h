#ifndef MUSICLISTWIDGET_H_H_HEAD__FILE__
#define MUSICLISTWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include "../component/musicWindow/interface/widget/iMusicListWidget.h"

#include "../interface/iAppResourceCore.h"

class MusicListWidget : public QWidget, public IMusicListWidget, public IAppResourceCore {
	Q_OBJECT;

public:
	MusicListWidget( );
	~MusicListWidget( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;

protected:
	bool setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) override;
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;

	QWidget * toWidget( ) override;
	bool drawWidgeTarget( QWidget *widget ) override;
	MusicCentreWidget * getMusicCentreWidget( ) const override;
	IMusicFavoriteItem * getCurrentMusicFavoriteItem( ) const override;
	bool setCurrentMusicFavoriteItem( IMusicFavoriteItem *music_favorite_item ) override;
	bool fromYPosGetMusicItem( IMusicItem *&result_music_item, const size_t &y_pos ) override;
	bool fromIndexGetMusicItem( IMusicItem *&result_music_item, const size_t &index ) override;
	bool fromNameGetFirstMusicItem( IMusicItem *&result_music_item, const QString &name ) override;
	bool fromFileBaseNameGetFirstMusicItem( IMusicItem *&result_music_item, const QString &file_base_name ) override;
	bool fromFileAbsPathGetFirstMusicItem( IMusicItem *&result_music_item, const QString &path ) override;
	bool fromSingerGetFirstMusicItem( IMusicItem *&result_music_item, const QString &singer ) override;
};

#endif // MUSICLISTWIDGET_H_H_HEAD__FILE__
