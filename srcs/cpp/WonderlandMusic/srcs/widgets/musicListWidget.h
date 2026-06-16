#ifndef MUSICLISTWIDGET_H_H_HEAD__FILE__
#define MUSICLISTWIDGET_H_H_HEAD__FILE__

#include <base/baseWidget/baseWidget.h>

class QMediaMetaData;
class MusicInfo;
class MusicListItemWidget;
class MusicListWidget : public BaseWidget {
	Q_OBJECT;
protected:
	/// @brief 鼠标下的选项
	MusicListItemWidget *activityItem;
	/// @brief 鼠标按下的选项
	std::vector< MusicListItemWidget * > selectItemVector;
	std::vector< MusicListItemWidget * > musicListItemWidgets;
public:
	MusicListWidget( QWidget *parent );
	virtual bool existMusicFilePath( const QString &file_path ) const;
	virtual size_t getMusicListItemWidgets( std::vector< const MusicListItemWidget * > &result_vector ) const;
	virtual MusicListItemWidget * getActivityItem( ) const { return activityItem; }
	virtual std::vector< const MusicListItemWidget * > getSelectItemVector( ) const;
protected:
	virtual bool appendItem( const MusicInfo &media_meta_data );
	virtual bool sort( );
};
#include <macro/eventMacroDefine.h>

class Event_Define_Event_Info_Type_Name( MusicListWidget ) {
public:
	enum class EventType {
		Load_Over,
	};
protected:
	EventType eventType;
public:
	MusicListWidgetEventInfo( EventType event_type )
		: eventType( event_type ) { }
	virtual EventType getEventType( ) const { return eventType; }
	virtual ~MusicListWidgetEventInfo( ) { }
};
#endif // MUSICLISTWIDGET_H_H_HEAD__FILE__
