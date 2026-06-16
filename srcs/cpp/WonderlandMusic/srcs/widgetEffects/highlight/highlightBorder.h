#ifndef HIGHLIGHTBORDER_H_H_HEAD__FILE__
#define HIGHLIGHTBORDER_H_H_HEAD__FILE__
#include "../widgetEffect.h"

class HighlightBorder : public WidgetEffect {
	Q_OBJECT;
protected:
	QPen *pen;
	int penWdith;
	int drawX;
	int drawY;
	int drawWidth;
	int drawHeight;
public:
	HighlightBorder( QWidget *bind_widget );
	bool eventFilter( QObject *watched, QEvent *event ) override;
	bool renderEffect( ) override;
	~HighlightBorder( ) override;
};

#endif // HIGHLIGHTBORDER_H_H_HEAD__FILE__
