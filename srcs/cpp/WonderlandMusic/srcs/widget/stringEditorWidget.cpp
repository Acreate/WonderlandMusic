#include "stringEditorWidget.h"

#include <qboxlayout.h>
#include <QLineEdit>
#include <QPushButton>
#include "../application/translate/stringEditorWidgetTranslate.h"

void StringEditorWidget::initComponent( ) {
	setModal( true );          // 设置模态
	setWindowModality( Qt::ApplicationModal ); // 模态类型
	auto mainLayout = new QVBoxLayout( this );
	auto widgetPenel = new QWidget( this );
	mainLayout->addWidget( widgetPenel );
	auto vboxLayout = new QVBoxLayout( widgetPenel );

	input = new QLineEdit( this );
	vboxLayout->addWidget( input );
	auto buttonLayout = new QHBoxLayout( widgetPenel );
	vboxLayout->addLayout( buttonLayout );
	okBtn = new QPushButton( this );
	buttonLayout->addWidget( okBtn );
	cancel = new QPushButton( this );
	buttonLayout->addWidget( cancel );

	connect( input, &QLineEdit::textEdited, this, &StringEditorWidget::textEdited );
	connect( okBtn, &QPushButton::clicked, this, &StringEditorWidget::clickedOk );
	connect( cancel, &QPushButton::clicked, this, &StringEditorWidget::clickedCancle );
}
StringEditorWidget::StringEditorWidget( bool *result_click, QString *result_editor, QWidget *parent, const std::vector< QString > &edit_not_set_string ) : QDialog( parent ), editNotSetString( edit_not_set_string ), resultClick( result_click ), resultEditor( result_editor ) {
	initComponent( );
	*result_click = false;
	result_editor->clear( );
	count = editNotSetString.size( );
	data = editNotSetString.data( );
}
StringEditorWidget::~StringEditorWidget( ) {
}
void StringEditorWidget::showEvent( QShowEvent *event ) {
	QDialog::showEvent( event );
	if( AppTranslateTools::getStringEditorWidget( [this] ( StringEditorWidgetTranslate &translate ) {
		cancel->setText( translate.getCancelString( ) );
		okBtn->setText( translate.getOkString( ) );
		hint = translate.getHint( );
	} ) == false ) {
		hide( );
		deleteLater( );
	}
}
void StringEditorWidget::textEdited( const QString &text ) {
	*resultEditor = text;
	if( count == 0 )
		return;
	for( index = 0; index < count; index += 1 )
		if( isTextEqu = ( data[ index ] == text ), isTextEqu )
			break;
	okBtn->setEnabled( !isTextEqu );
}
void StringEditorWidget::clickedOk( bool checked ) {
	*resultClick = true;
}
void StringEditorWidget::clickedCancle( bool checked ) {
	*resultClick = false;
}
