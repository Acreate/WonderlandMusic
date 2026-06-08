#ifndef MUSICLISTMAINWIDGET_H_H_HEAD__FILE__
#define MUSICLISTMAINWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include <macro/eventMacroDefine.h>

#include <base/baseWidget/baseWidget.h>

class MusicCollectionScrollArea;
class MusicListScrollArea;
class MusicListMainWidget : public BaseWidget {
	Q_OBJECT;
protected:
	MusicListScrollArea *musicListScrollArea;
	MusicCollectionScrollArea *musicCollectionScrollArea;
	bool readyDragWidgetWidth;
	bool isragWidgetWidth;
	QRect currentContentsRect;
	int currentWidgetWidth;
	int currentWidgetHeight;
	int minCollectionWidth;
public:
	MusicListMainWidget( QWidget *parent );
	~MusicListMainWidget( ) override;
	virtual int getMusicCollectionWidth( ) const;
	virtual void setMusicCollectionWidth( int new_width );
protected:
	virtual void updateSubWidgetSize( );
	void resizeEvent( QResizeEvent *event ) override;
};

class Event_Default_Event_Info_Type_Name( MusicListMainWidget ) {
public:
	enum class EventType {
		None,
		Show_Draw_Mouse_ICO,
		HIDE_Draw_Mouse_ICO,
		Start_Draw_Music_Widget_Width,
		Over_Draw_Music_Widget_Width
	};
protected:
	EventType enventType;
	int newMusicWidgetWidth;
public:
	virtual ~MusicListMainWidgetEventInfo( ) = default;
	MusicListMainWidgetEventInfo( const EventType envent_type )
		: enventType( envent_type ) { }
	MusicListMainWidgetEventInfo( const EventType envent_type, const int new_music_widget_width ) : enventType( envent_type ), newMusicWidgetWidth( new_music_widget_width ) { }
	virtual int getNewMusicWidgetWidth( ) const { return newMusicWidgetWidth; }
	virtual EventType getEventType( ) const { return enventType; }
};

#endif // MUSICLISTMAINWIDGET_H_H_HEAD__FILE__
