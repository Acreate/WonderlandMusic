#ifndef SELECTFILEPATHWIDGET_H_H_HEAD__FILE__
#define SELECTFILEPATHWIDGET_H_H_HEAD__FILE__

#include "interface/ISelectPathWidget.h"

class SelectFilePathWidget : public ISelectPathWidget {
	Q_OBJECT;

protected:
	void selectPathBtnEvent( ) override;

	void editorPathBtnEvent( const QString &editor_txt ) override;

public:
	SelectFilePathWidget( QWidget *parent );
};
#endif // SELECTFILEPATHWIDGET_H_H_HEAD__FILE__
