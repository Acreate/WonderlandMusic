#ifndef MUSICCONTRESCROLLAREA_H_H_HEAD__FILE__
#define MUSICCONTRESCROLLAREA_H_H_HEAD__FILE__
#include <QScrollArea>

#include "../interface/iAppCore.h"
#include "../interface/iAppJsonData.h"

class MusicItem;
class PlayerListTopWidget;
class MusicContreWidget;

class MusicContreScrollArea : public QScrollArea, public IAppCore {
	Q_OBJECT;

protected:
	MusicContreWidget *musicContreWidget = nullptr;

public:
	MusicContreScrollArea( QWidget *parent );

	virtual bool showFavorteMusicContreList( const QString &music_favorte_widget );

	virtual void setItemWidth( const PlayerListTopWidget *player_list_top_widget );

	virtual void setItemVector( const std::vector< MusicItem * > &load_music_items );

	virtual void setItemWidth( int widget_before_width, int splite_width, int index_width, int music_name_width, int music_singer_width, int music_duration_width, int widget_after_width );

	virtual MusicContreWidget * getMusicContreWidget( ) const;

protected:
	bool deleteResource( ) override;

public:
	bool init( ) override;

	bool initBefore( ) override;

	bool initAfter( ) override;
Q_SIGNALS:
	void signal_horizontal_scroll_set_value( int value );
};

#endif // MUSICCONTRESCROLLAREA_H_H_HEAD__FILE__
