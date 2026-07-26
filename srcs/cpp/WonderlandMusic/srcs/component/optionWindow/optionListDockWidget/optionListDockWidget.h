#ifndef OPTIONLISTDOCKWIDGET_H_H_HEAD__FILE__
#define OPTIONLISTDOCKWIDGET_H_H_HEAD__FILE__

#include <QDockWidget>

#include "../../../interface/iAppCore.h"

class OptionListWidget;
class OptionItem;
class QScrollArea;
class OptionContentsWidget;
class OptionWindow;

class OptionListDockWidget : public QDockWidget, public IAppCore {
	Q_OBJECT;
	friend class OptionWindow;

protected:
	OptionWindow *optionWindow;
	QWidget *dockTitleWidget = nullptr;
	QScrollArea *scrollArea = nullptr;
	OptionListWidget *optionListWidget = nullptr;

	OptionListDockWidget( OptionWindow *option_window );

public:
	virtual OptionWindow * getOptionWindow( ) const;
	virtual QScrollArea * getScrollArea( ) const;
	virtual OptionListWidget * getOptionListWidget( ) const;

	virtual void updateOptionButtonLayout( );

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
};

#endif // OPTIONLISTDOCKWIDGET_H_H_HEAD__FILE__
