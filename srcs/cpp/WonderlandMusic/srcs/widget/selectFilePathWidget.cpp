#include "selectFilePathWidget.h"

#include <QFileDialog>
#include <QLineEdit>

#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/translate/iSelectPathWidgetTranslate.h"

#include "../tools/pathTools.h"
#include "../tools/widgetTools.h"

void SelectFilePathWidget::selectPathBtnEvent( ) {
	auto app = AppInstance::getAppInstance( );
	auto appTranslate = app->getTranslate( );
	auto selectPathWidgetTranslate = appTranslate->getSelectPathWidget( );
	QFileDialog dialog( this );
	dialog.setWindowTitle( selectPathWidgetTranslate->getSelectFilePathText( ) );

	dirSelectWorkPath = pathEditor->text( );
	QFileInfo fileInfo( dirSelectWorkPath );
	if( fileInfo.exists( ) == false )
		fileInfo.setFile( app->getAppSettingPath( ) );
	auto openDirPath = fileInfo.absoluteFilePath( );
	dialog.setDirectory( openDirPath );
	dialog.setFileMode( QFileDialog::Directory );

	QRect geometry = this->geometry( );
	auto curentWindowSize = geometry.size( );
	dialog.resize( curentWindowSize );
	auto center = geometry.center( );
	center = mapToGlobal( center );
	WidgetTools::moveWidgetToCenterPos( center, &dialog );
	if( dialog.exec( ) != QDialog::Accepted )
		return;
	QStringList files = dialog.selectedFiles( );
	auto data = files.data( );
	dirSelectWorkPath = data[ 0 ];
	dirSelectWorkPath = PathTools::getAutoShortenPathName( dirSelectWorkPath );
	this->setPath( dirSelectWorkPath );
}

void SelectFilePathWidget::editorPathBtnEvent( const QString &editor_txt ) {
}

SelectFilePathWidget::SelectFilePathWidget( QWidget *parent ) : ISelectPathWidget( parent ) {
}
