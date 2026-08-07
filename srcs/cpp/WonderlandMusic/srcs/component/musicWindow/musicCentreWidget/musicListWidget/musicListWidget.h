#ifndef MUSICLISTWIDGET_H_H_HEAD__FILE__
#define MUSICLISTWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include <interface/iAppCore.h>

#include <interface/iAppJsonData.h>

class MusicTitleWidget;
class MusicCentreWidget;
class MusicWindow;
class UserMutex;
class MusicItem;

class MusicListWidget : public QWidget, public IAppCore, public IAppJsonData {
	Q_OBJECT;
	friend class MusicCentreWidget;
	friend class MusicWindow;

protected:
	UserMutex *userMutex = nullptr;
	MusicCentreWidget *musicCentreWidget;
	std::vector< MusicItem * > musicItemVector;
	int intervalWidth;
	int separatorWidth;
	int musicCodeWidth;
	int musicNameWidth;
	int musicSingerNameWidth;
	int musicDurationTimeWidth;

public:
	MusicListWidget( MusicCentreWidget *music_centre_widget );
	~MusicListWidget( ) override;

protected:
	bool deleteResource( ) override;
	void paintEvent( QPaintEvent *event ) override;
	virtual void setMusicItemInfoVector( const std::vector< MusicItem * > &music_items );

	virtual bool unSafetyClearInfo( );
	virtual bool unSafetyClearShow( );
	virtual bool unSafetyUpdateInfo( );
	virtual bool unSafetyUpdateShow( );

	virtual void unSafetyClear( );
	virtual bool hasItem( size_t &result_index, const MusicItem *music_item ) const;
	virtual bool addItem( MusicItem *music_item );
	virtual void updateItemWidthInfo( MusicTitleWidget *music_title_widget, int interval_width, int separator_width, int music_code_width, int music_name_width, int music_singer_name_width, int music_duration_time_width );

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	virtual bool updateItem( MusicItem *music_item );
	virtual bool removeItem( MusicItem *music_item );
	virtual MusicCentreWidget * getMusicCentreWidget( ) const;
	virtual bool updateInfo( );
	virtual bool updateShow( );
	virtual void clear( );
};
#endif // MUSICLISTWIDGET_H_H_HEAD__FILE__
