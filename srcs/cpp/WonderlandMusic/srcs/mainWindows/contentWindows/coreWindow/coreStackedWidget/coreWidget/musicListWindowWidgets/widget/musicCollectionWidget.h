#ifndef MUSICCOLLECTIONWIDGET_H_H_HEAD__FILE__
#define MUSICCOLLECTIONWIDGET_H_H_HEAD__FILE__

#include <base/baseWidget/baseWidget.h>

class CollectionItemWidget;
class CollectionTopToolWidget;
class MusicCollectionWidget : public BaseWidget {
	Q_OBJECT;
protected:
	CollectionTopToolWidget *collectionTopToolWidget;
	std::vector< CollectionItemWidget * > collectionItemWidgets;
	CollectionItemWidget *selectCurrentCollectionItemWidget;
	int subItemOffsetX;
public:
	MusicCollectionWidget( QWidget *parent );
	~MusicCollectionWidget( ) override;
	virtual CollectionTopToolWidget * getCollectionTopToolWidget( ) const { return collectionTopToolWidget; }
	virtual CollectionItemWidget * getSelectCurrentCollectionItemWidget( ) const { return selectCurrentCollectionItemWidget; }
	virtual bool removeTargetItemWidget( CollectionItemWidget *target_item_widget );
	virtual bool removeCurrentItemWidget( ) {
		return removeTargetItemWidget( selectCurrentCollectionItemWidget );
	}
	virtual bool appendItemWidget( const QString &item_name );
protected:
	void resizeEvent( QResizeEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
};

#include <macro/eventMacroDefine.h>

class Event_Default_Event_Info_Type_Name( MusicCollectionWidget ) {
public:
	enum class EventType {
		Mouse_Left_Press_Select_Top_Item,
		Mouse_Left_Release_Select_Top_Item,
		Mouse_Right_Press_Select_Top_Item,
		Mouse_Right_Release_Select_Top_Item,

		Mouse_Left_Press_Select_Sub_Item,
		Mouse_Left_Release_Select_Sub_Item,
		Mouse_Right_Press_Select_Sub_Item,
		Mouse_Right_Release_Select_Sub_Item,

	};
protected:
	EventType eventType;
public:
	virtual ~MusicCollectionWidgetEventInfo( ) { }
	MusicCollectionWidgetEventInfo( EventType event_type )
		: eventType( event_type ) { }
	virtual EventType getEventType( ) const { return eventType; }
};

#endif // MUSICCOLLECTIONWIDGET_H_H_HEAD__FILE__
