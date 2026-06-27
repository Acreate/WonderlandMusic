#ifndef SELECTFILEPATHWIDGET_H_H_HEAD__FILE__
#define SELECTFILEPATHWIDGET_H_H_HEAD__FILE__
#include "interface/ISelectDirWidget.h"

class SelectFilePathWidget : public ISelectDirWidget {
	Q_OBJECT;

protected:
	void selectPathBtnEvent( ) override;

	void editorPathBtnEvent( const QString &editor_txt ) override;

public:
	SelectFilePathWidget( QWidget *parent );
};
#endif // SELECTFILEPATHWIDGET_H_H_HEAD__FILE__
