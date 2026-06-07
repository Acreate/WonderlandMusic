#ifndef MUSICLISTMAINWIDGET_H_H_HEAD__FILE__
#define MUSICLISTMAINWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include <macro/eventMacroDefine.h>
class MusicCollectionScrollArea;
class MusicListScrollArea;
class MusicListMainWidget : public QWidget {
	Q_OBJECT;
protected:
	MusicListScrollArea *musicListScrollArea;
	MusicCollectionScrollArea *musicCollectionScrollArea;
	bool dragWidgetWidth;
	bool readyDragWidgetWidth;
public:
	MusicListMainWidget( QWidget *parent );
protected:
	virtual void updateSubWidgetSize( );
	void resizeEvent( QResizeEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
};

class Event_Default_Event_Info_Type_Name( MusicListMainWidget ) {
public:
	enum class EventType {
		None,
		Resize_Music_Widget_Width
	};
protected:
	EventType enventType;
	int newMusicWidgetWidth;
public:
	virtual ~MusicListMainWidgetEventInfo( ) = default;
	MusicListMainWidgetEventInfo( const EventType envent_type )
		: enventType( envent_type ) { }
	MusicListMainWidgetEventInfo( int new_music_width_widtth ) : newMusicWidgetWidth( new_music_width_widtth ), enventType( EventType::Resize_Music_Widget_Width ) { }
	virtual int getNewMusicWidgetWidth( ) const { return newMusicWidgetWidth; }
	virtual EventType getEventType( ) const { return enventType; }
};

#endif // MUSICLISTMAINWIDGET_H_H_HEAD__FILE__
