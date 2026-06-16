#ifndef HIGHLIGHTBACKGROUND_H_H_HEAD__FILE__
#define HIGHLIGHTBACKGROUND_H_H_HEAD__FILE__


#include "../widgetEffect.h"

class HighlightBackground : public WidgetEffect {
	Q_OBJECT;
public:
	HighlightBackground( QWidget *bind_widget );
	bool eventFilter( QObject *watched, QEvent *event ) override;
	bool renderEffect( ) override;
};
#endif // HIGHLIGHTBACKGROUND_H_H_HEAD__FILE__
