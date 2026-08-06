#ifndef MUSICLISTWIDGET_H_H_HEAD__FILE__
#define MUSICLISTWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include <interface/iAppCore.h>

#include <interface/iAppJsonData.h>

class UserMutex;
class MusicItem;

class MusicListWidget : public QWidget, public IAppCore, public IAppJsonData {
	Q_OBJECT;
	friend class MusicCentreWidget;

protected:
	UserMutex *userMutex = nullptr;
	MusicCentreWidget *musicCentreWidget;
	std::vector< MusicItem * > musicItems;

public:
	MusicListWidget( MusicCentreWidget *music_centre_widget );
	~MusicListWidget( ) override;

protected:
	bool deleteResource( ) override;
	void paintEvent( QPaintEvent *event ) override;
	virtual void setMusicItemInfoVector( const std::vector< MusicItem * > &music_items );
	virtual void unsafetyClearMusicItemVector( );

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	virtual bool updateItem( MusicItem *music_item );
	virtual bool removeItem( MusicItem *music_item );
	virtual MusicCentreWidget * getMusicCentreWidget( ) const;
	virtual void clearMusicItemVector( );
};
#endif // MUSICLISTWIDGET_H_H_HEAD__FILE__
