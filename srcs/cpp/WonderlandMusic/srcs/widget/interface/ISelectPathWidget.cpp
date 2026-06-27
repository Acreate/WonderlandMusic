#include "ISelectPathWidget.h"

#include <QFileInfo>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

#include "../../application/appInstance.h"
#include "../../application/appTranslate.h"
#include "../../application/translate/ISelectPathWidgetTranslate.h"

#include "../../tools/pathTools.h"

ISelectPathWidget::ISelectPathWidget( QWidget *parent ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto selectDirWidgetTranslate = appInstance->getTranslate( )->getSelectPathWidget( );
	hBoxLayout = new QHBoxLayout( this );
	hBoxLayout->setContentsMargins( 0, 0, 0, 0 );
	hBoxLayout->setSpacing( 0 );
	pathEditor = new QLineEdit( this );
	pathEditor->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum );
	pathEditor->setPlaceholderText( selectDirWidgetTranslate->getLineEditorPlaceholderText( ) );
	hBoxLayout->addWidget( pathEditor );
	selectPathButton = new QPushButton( this );
	selectPathButton->setText( selectDirWidgetTranslate->getSelectButtonText( ) );
	hBoxLayout->addWidget( selectPathButton );
	selectPathButton->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );

	connect( selectPathButton, &QPushButton::clicked, this, [this]( ) {
		this->selectPathBtnEvent( );
	} );
	connect( pathEditor, &QLineEdit::editingFinished, this, [this]( ) {
		auto editorTxt = pathEditor->text( );
		QFileInfo info( editorTxt );
		if( info.exists( ) == true )
			this->setPath( editorTxt );
		else
			this->setPath( dirSelectWorkPath );
	} );
}

void ISelectPathWidget::setPath( const QString &new_path ) {
	auto autoShortenPathName = PathTools::getAutoShortenPathName( new_path );
	if( autoShortenPathName == dirSelectWorkPath )
		return;
	dirSelectWorkPath = autoShortenPathName;
	pathEditor->setText( new_path );
	editorPathBtnEvent( dirSelectWorkPath );
}

const QString & ISelectPathWidget::getPath( ) const {
	return dirSelectWorkPath;
}
