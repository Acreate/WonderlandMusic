#ifndef MUSICLISTTOPWIDGET_H_H_HEAD__FILE__
#define MUSICLISTTOPWIDGET_H_H_HEAD__FILE__

#include <base/baseWidget/baseWidget.h>
class LabelItem;
class PlayerListItem;
class FontRender;
class StringFontSize;
class MusicListTopWidget : public BaseWidget {
	Q_OBJECT;
protected:
	/// @brief 音乐名称项
	LabelItem *musicNameItem;
	/// @brief 音乐主唱项
	LabelItem *musicSingerItem;
	/// @brief 音乐播放时长项
	LabelItem *musicPlayerTimeItem;
public:
	MusicListTopWidget( QWidget *parent );
	~MusicListTopWidget( ) override;
protected:
	void resizeEvent( QResizeEvent *event ) override;
	void paintEvent( QPaintEvent *event ) override;
};
#include <macro/eventMacroDefine.h>
class Event_Define_Event_Info_Type_Name( MusicListTopWidget ) {
public:
	enum class EventType {
		Drag_Start_Item_Width,
		Drag_End_Item_Width,
	};
protected:
	EventType eventType;
public:
	virtual ~MusicListTopWidgetEventInfo( ) = default;
	MusicListTopWidgetEventInfo( EventType event_type )
		: eventType( event_type ) { }
	virtual EventType getEventType( ) const { return eventType; }
};
#endif // MUSICLISTTOPWIDGET_H_H_HEAD__FILE__
