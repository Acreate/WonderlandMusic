#include "widgetTools.h"

#include <QFileDialog>
#include <QMenu>
#include <QWidget>
#include <QStringList>
#include <qscreen.h>

#include "../application/appInstance.h"
#include "../application/appInstance/applicationManage.h"

#include "../widget/stringEditorWidget.h"

void WidgetTools::moveWidgetToCenterPos( const QPoint &target_pos, QWidget *move_source_widget ) {
	move_source_widget->adjustSize( );
	int width = move_source_widget->width( );
	int height = move_source_widget->height( );
	auto x = target_pos.x( ) - width / 2;
	auto y = target_pos.y( ) - height / 2;
	move_source_widget->move( x, y );
}

void WidgetTools::moveWidgetToCenterPos( const QWidget *target_widget_pos, QWidget *move_source_widget ) {
	auto targetPos = target_widget_pos->geometry( ).center( );
	WidgetTools::moveWidgetToCenterPos( targetPos, move_source_widget );
}

bool WidgetTools::getMenuSuggestionShowMenuPos( QPoint &suggestion_show_pos, const QPoint &org_pos, QMenu *calculation_menu ) {
	calculation_menu->adjustSize( );
	auto menuWidth = calculation_menu->width( );
	auto menuHeight = calculation_menu->height( );
	auto screens = AppInstance::getAppInstance( )->getApplicationManage( )->screens( );
	qsizetype count = screens.size( );
	auto data = screens.data( );
	qsizetype index = 0;
	for( ; index < count; index += 1 ) {
		auto geometry = data[ index ]->geometry( );
		if( geometry.contains( org_pos ) ) {
			auto screenSize = data[ index ]->size( );
			auto screenWidth = screenSize.width( );
			auto screenHeight = screenSize.height( );

			int x = org_pos.x( );
			x = screenWidth < menuWidth + x ? x - menuWidth : x;
			int y = org_pos.y( );
			y = screenHeight < menuHeight + y ? y - menuHeight : y;
			suggestion_show_pos = QPoint( x, y );
			return true;
		}
	}
	return false;
}

bool WidgetTools::showMultipleSelectFileDialog( std::vector< QString > &result_select_file, const QString &select_default_dir_path, QWidget *parent, const QString &title_text, const QString &filter ) {
	QFileDialog *multipleSelectDialog = new QFileDialog;
	if( multipleSelectDialog == nullptr )
		return false;
	//multipleSelectDialog->setParent( parent );
	multipleSelectDialog->setFileMode( QFileDialog::ExistingFiles );
	// 该窗口路径并没有更新
	//multipleSelectDialog->setOption( QFileDialog::DontUseNativeDialog );
	multipleSelectDialog->setOption( QFileDialog::DontResolveSymlinks, true );
	multipleSelectDialog->setOption( QFileDialog::DontConfirmOverwrite, true );
	multipleSelectDialog->setOption( QFileDialog::DontUseCustomDirectoryIcons, true );
	multipleSelectDialog->setOption( QFileDialog::ReadOnly, true );
	// 3. 视图强制列表模式（详情模式加载更多列，更卡）
	multipleSelectDialog->setViewMode( QFileDialog::List );
	multipleSelectDialog->setWindowTitle( title_text );
	multipleSelectDialog->setNameFilter( filter );
	QFileInfo info( select_default_dir_path );
	auto absoluteFilePath = info.absoluteFilePath( );
	multipleSelectDialog->setDirectory( absoluteFilePath );
	moveWidgetToCenterPos( parent, multipleSelectDialog );
	multipleSelectDialog->exec( );
	auto selectList = multipleSelectDialog->selectedFiles( );
	delete multipleSelectDialog;
	qint64 qsizetype = selectList.size( );
	if( qsizetype == 0 )
		return false;
	result_select_file.resize( qsizetype );
	auto desData = result_select_file.data( );
	auto sourData = selectList.data( );
	qint64 index = 0;
	for( ; index < qsizetype; index += 1 )
		desData[ index ] = sourData[ index ];
	return true;
}

bool WidgetTools::showMultipleSelectDirDialog( std::vector< QString > &result_select_file, const QString &select_default_dir_path, QWidget *parent, const QString &title_text ) {
	QFileDialog *multipleSelectDialog = new QFileDialog;
	if( multipleSelectDialog == nullptr )
		return false;
	//multipleSelectDialog->setParent( parent );
	multipleSelectDialog->setWindowTitle( title_text );
	multipleSelectDialog->setFileMode( QFileDialog::Directory );
	//multipleSelectDialog->setOption( QFileDialog::DontUseNativeDialog );
	multipleSelectDialog->setOption( QFileDialog::DontResolveSymlinks, true );
	multipleSelectDialog->setOption( QFileDialog::DontConfirmOverwrite, true );
	multipleSelectDialog->setOption( QFileDialog::DontUseCustomDirectoryIcons, true );
	multipleSelectDialog->setOption( QFileDialog::ShowDirsOnly, true );
	moveWidgetToCenterPos( parent, multipleSelectDialog );
	QFileInfo info( select_default_dir_path );
	auto absoluteFilePath = info.absoluteFilePath( );
	multipleSelectDialog->setDirectory( absoluteFilePath );
	multipleSelectDialog->exec( );
	auto selectList = multipleSelectDialog->selectedFiles( );
	delete multipleSelectDialog;
	qint64 qsizetype = selectList.size( );
	if( qsizetype == 0 )
		return false;
	result_select_file.resize( qsizetype );
	auto desData = result_select_file.data( );
	auto sourData = selectList.data( );
	qint64 index = 0;
	for( ; index < qsizetype; index += 1 )
		desData[ index ] = sourData[ index ];
	return true;
}
bool WidgetTools::showStringEditorWidget( bool &result_click, QString &result_edit_string, QWidget *parent, const std::vector< QString > &not_set_string ) {
	auto stringEditorWidget = new StringEditorWidget( &result_click, &result_edit_string, parent, not_set_string );
	moveWidgetToCenterPos( parent, stringEditorWidget );
	stringEditorWidget->exec( );
	stringEditorWidget->hide( );
	delete stringEditorWidget;
	return true;
}
