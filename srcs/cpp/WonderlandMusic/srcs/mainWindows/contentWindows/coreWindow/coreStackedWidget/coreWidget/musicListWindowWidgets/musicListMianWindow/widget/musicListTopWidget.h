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
	/// @brief 标题列表
	std::vector< LabelItem * > titleVector;
	/// @brief 最小高度
	int minHeight;
	/// @brief 检测的大宽度
	int maxWidth;
	/// @brief 检测的最小宽度
	int minWidth;
	/// @brief 检测拖拽的大宽度
	int dragMaxWidth;
	/// @brief 检测拖拽的最小宽度
	int dragMinWidth;
	/// @brief 是否准备好拖拽
	bool readyDrag;
	/// @brief 允许拖拽
	bool permissonDrag;
	/// @brief 当前拖拽项
	LabelItem *currentDragItem;
	/// @brief 当前拖拽项的前一项
	LabelItem *currentDragPrevItem;
	/// @brief 拖拽偏移 x
	int dragOffsetX;
public:
	MusicListTopWidget( QWidget *parent );
	~MusicListTopWidget( ) override;
	virtual const LabelItem * getTopItem( const size_t &item_index ) const;
	virtual int getMaxWidth( ) const { return maxWidth; }
	virtual int getMinWidth( ) const { return minWidth; }
	virtual bool isReadyDrag( ) const { return readyDrag; }
	virtual bool isPermissonDrag( ) const { return permissonDrag; }
	virtual const LabelItem * getCurrentDragItem( ) const { return currentDragItem; }
	virtual std::vector< const LabelItem * > getTitleVector( ) const;
	virtual void normalTitleSize( );
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
		Update_Item_Width,
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
