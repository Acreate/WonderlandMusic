#include "ISelectDirWidget.h"

#include <QFileInfo>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

#include "../../application/appInstance.h"
#include "../../application/appTranslate.h"
#include "../../application/translate/iSelectDirWidgetTranslate.h"

#include "../../tools/pathTools.h"

ISelectDirWidget::ISelectDirWidget( QWidget *parent ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto selectDirWidgetTranslate = appInstance->getTranslate( )->getSelectDirWidget( );
	hBoxLayout = new QHBoxLayout( this );
	hBoxLayout->setContentsMargins( 0, 0, 0, 0 );
	hBoxLayout->setSpacing( 0 );
	pathEditor = new QLineEdit( this );
	pathEditor->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum );
	pathEditor->setPlaceholderText( selectDirWidgetTranslate->getPathLineEditorPlaceholderText( ) );
	hBoxLayout->addWidget( pathEditor );
	selectPathButton = new QPushButton( this );
	selectPathButton->setText( selectDirWidgetTranslate->getPathSelectButtonText( ) );
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

void ISelectDirWidget::setPath( const QString &new_path ) {
	dirSelectWorkPath = PathTools::getAutoShortenPathName( new_path );;
	pathEditor->setText( new_path );
	emit this->editorPathBtnEvent( dirSelectWorkPath );
}

const QString & ISelectDirWidget::getPath( ) const {
	return dirSelectWorkPath;
}
