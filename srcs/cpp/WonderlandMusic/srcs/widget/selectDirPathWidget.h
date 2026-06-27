#ifndef SELECTDIRPATHWIDGET_H_H_HEAD__FILE__
#define SELECTDIRPATHWIDGET_H_H_HEAD__FILE__

#include "interface/ISelectDirWidget.h"

class SelectDirPathWidget : public ISelectDirWidget {
	Q_OBJECT;

protected:
	void selectPathBtnEvent( ) override;

	void editorPathBtnEvent( const QString &editor_txt ) override;

public:
	SelectDirPathWidget( QWidget *parent );
};

#endif // SELECTDIRPATHWIDGET_H_H_HEAD__FILE__
