#ifndef TRANSPARENCYSCROLLBAR_H_H_HEAD__FILE__
#define TRANSPARENCYSCROLLBAR_H_H_HEAD__FILE__
#include <QScrollBar>

class TransparencyScrollBar : public QScrollBar {
	Q_OBJECT;

public:
	TransparencyScrollBar( QWidget *widget );
	~TransparencyScrollBar( ) override;

public:
	bool event( QEvent *event ) override;
};

#endif // TRANSPARENCYSCROLLBAR_H_H_HEAD__FILE__
