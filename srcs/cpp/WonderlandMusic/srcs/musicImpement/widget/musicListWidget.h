#ifndef MUSICLISTWIDGET_H_H_HEAD__FILE__
#define MUSICLISTWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include <component/musicWindow/interface/widget/iMusicListWidget.h>

#include <interface/iAppResourceCore.h>

class MusicListWidget : public QWidget, public IMusicListWidget, public IAppResourceCore {
	Q_OBJECT;

private:
	IMusicCentreWidget *musicCentreWidget = nullptr;
	UserMutex *userMutex = nullptr;
	IMusicFavoriteItem*  musicFavoriteItem = nullptr;
public:
	MusicListWidget( );
	~MusicListWidget( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;

protected:
	bool setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) override;
	bool deleteResource( ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;

public:
	bool updateMusicFavoriteItem( IMusicFavoriteItem *music_favorite_item ) override;
	bool updateCurrentMusicFavoriteItem( ) override;

	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;

	QWidget * toWidget( ) override;
	IMusicCentreWidget * getMusicCentreWidget( ) const override;
	IMusicFavoriteItem * getCurrentMusicFavoriteItem( ) const override;
	bool setCurrentMusicFavoriteItem( IMusicFavoriteItem *music_favorite_item ) override;
	bool fromYPosGetMusicItem( IMusicItem *&result_music_item, const size_t &y_pos ) const override;
	bool fromIndexGetMusicItem( IMusicItem *&result_music_item, const size_t &index ) const override;
	bool fromNameGetFirstMusicItem( IMusicItem *&result_music_item, const QString &name ) const override;
	bool fromFileBaseNameGetFirstMusicItem( IMusicItem *&result_music_item, const QString &file_base_name ) const override;
	bool fromFileAbsPathGetFirstMusicItem( IMusicItem *&result_music_item, const QString &path ) const override;
	bool fromSingerGetFirstMusicItem( IMusicItem *&result_music_item, const QString &singer ) const override;
};

#endif // MUSICLISTWIDGET_H_H_HEAD__FILE__
