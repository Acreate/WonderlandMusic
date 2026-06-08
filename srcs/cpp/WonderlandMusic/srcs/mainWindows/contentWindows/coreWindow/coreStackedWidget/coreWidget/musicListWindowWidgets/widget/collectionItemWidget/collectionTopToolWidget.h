#ifndef COLLECTIONTOPTOOLWIDGET_H_H_HEAD__FILE__
#define COLLECTIONTOPTOOLWIDGET_H_H_HEAD__FILE__

#include <base/baseWidget/baseWidget.h>
#include <macro/eventMacroDefine.h>
class CollectionTopToolWidget : public BaseWidget {
	Q_OBJECT;
protected:
	QLabel* title;
public:
	CollectionTopToolWidget( QWidget *parent );
	~CollectionTopToolWidget( ) override;
protected:
	void resizeEvent(QResizeEvent *event) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
};

class Event_Default_Event_Info_Type_Name( CollectionTopToolWidget ) {
public:
	enum class EventType {
		None,
		Mouse_Press_Event,
		Mouse_Release_Event,
	};
protected:
	EventType evenType;
public:
	virtual ~CollectionTopToolWidgetEventInfo( ) = default;
	CollectionTopToolWidgetEventInfo( EventType even_type )
		: evenType( even_type ) { }
	virtual EventType getEvenType( ) const { return evenType; }
};

#endif // COLLECTIONTOPTOOLWIDGET_H_H_HEAD__FILE__
