#ifndef COLLECTIONITEMWIDGET_H_H_HEAD__FILE__
#define COLLECTIONITEMWIDGET_H_H_HEAD__FILE__

#include <base/baseWidget/baseWidget.h>
#include <macro/eventMacroDefine.h>
class CollectionItemWidget : public BaseWidget {
	Q_OBJECT;
protected:
	QLabel *itemTitleLable;
public:
	CollectionItemWidget( QWidget *parent );
	virtual QString getTitleName( ) const;
	virtual void setTitleName( const QString &new_title_name ) const;
protected:
	void resizeEvent( QResizeEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
};

class Event_Default_Event_Info_Type_Name( CollectionItemWidget ) {
public:
	enum class EventType {
		None,
		Mouse_Press_Event,
		Mouse_Release_Event,
	};
protected:
	EventType evenType;
public:
	virtual ~CollectionItemWidgetEventInfo( ) = default;
	CollectionItemWidgetEventInfo( EventType even_type )
		: evenType( even_type ) { }
	virtual EventType getEvenType( ) const { return evenType; }
};

#endif // COLLECTIONITEMWIDGET_H_H_HEAD__FILE__
