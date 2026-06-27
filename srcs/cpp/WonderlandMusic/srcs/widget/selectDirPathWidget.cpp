#include "selectDirPathWidget.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QLineEdit>

#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/translate/iSelectPathWidgetTranslate.h"

#include "../tools/pathTools.h"
#include "../tools/widgetTools.h"

void SelectDirPathWidget::selectPathBtnEvent( ) {
	auto app = AppInstance::getAppInstance( );
	auto appTranslate = app->getTranslate( );
	auto selectPathWidgetTranslate = appTranslate->getSelectPathWidget( );
	QFileDialog dialog( this );
	dialog.setWindowTitle( selectPathWidgetTranslate->getSelectDirPathText( ) );

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

void SelectDirPathWidget::editorPathBtnEvent( const QString &editor_txt ) {
	auto appInstance = AppInstance::getAppInstance( );
	appInstance->setAppSettingPath( editor_txt );
}

SelectDirPathWidget::SelectDirPathWidget( QWidget *parent ) : ISelectPathWidget( parent ) {
}
