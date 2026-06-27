#ifndef ISELECTDIRWIDGET_H_H_HEAD__FILE__
#define ISELECTDIRWIDGET_H_H_HEAD__FILE__

#include <QWidget>

class QPushButton;
class QLineEdit;
class QHBoxLayout;

class ISelectDirWidget : public QWidget {
	Q_OBJECT;

protected:
	QHBoxLayout *hBoxLayout;
	QLineEdit *pathEditor;
	QPushButton *selectPathButton;
	QString dirSelectWorkPath;

protected:
	virtual void selectPathBtnEvent( ) = 0;

	virtual void editorPathBtnEvent( const QString &editor_txt ) = 0;

public:
	ISelectDirWidget( QWidget *parent );

	virtual void setPath( const QString &new_path );

	virtual const QString & getPath( ) const;
};
#endif // ISELECTDIRWIDGET_H_H_HEAD__FILE__
