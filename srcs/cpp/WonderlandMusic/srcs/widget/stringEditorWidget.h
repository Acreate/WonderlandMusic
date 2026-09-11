#ifndef STRINGEDITORWIDGET_H_H_HEAD__FILE__
#define STRINGEDITORWIDGET_H_H_HEAD__FILE__
#include <QDialog>

class QLineEdit;
class QPushButton;

class StringEditorWidget : public QDialog {
	Q_OBJECT;

protected:
	std::vector< QString > editNotSetString;
	bool *resultClick;
	QString *resultEditor;
	QPushButton *okBtn;
	QPushButton *cancel;
	QLineEdit *input;
	QString hint;

	size_t count;
	size_t index;
	QString *data;
	bool isTextEqu;

public:
	void initComponent( );
	StringEditorWidget( bool *result_click, QString *result_editor, QWidget *parent, const std::vector< QString > &edit_not_set_string );
	~StringEditorWidget( ) override;

protected:
	void showEvent( QShowEvent *event ) override;

private:
	void textEdited( const QString &text );
	void clickedOk( bool checked );
	void clickedCancle( bool checked );

public:
Q_SIGNALS :
	void okClick( StringEditorWidget *string_editor_widget, const QString &txt );
	void cancelClick( StringEditorWidget *string_editor_widget, const QString &txt );
};

#endif // STRINGEDITORWIDGET_H_H_HEAD__FILE__
