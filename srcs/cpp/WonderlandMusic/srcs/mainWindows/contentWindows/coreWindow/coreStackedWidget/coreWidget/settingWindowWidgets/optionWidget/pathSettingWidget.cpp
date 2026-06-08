#include "pathSettingWidget.h"

#include <QDir>
#include <QLabel>

#include "../optionStackWidget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "../../../../../../../applications/applicationEvenTrigger.h"
#include "../../../../../../../applications/applicationInstance.h"

#include "../../../../../../../msgInfo/messageErrorOut.h"
PathSettingWidget::PathSettingWidget( OptionStackWidget *parent ) : BaseWidget( parent ), optionStackWidget( parent ) {
	loadFileInfoPathEditInputLine = new QLineEdit( this );
	loadFileInfoPathSelectBtn = new QPushButton( tr( "路径选择..." ), this );
	loadFileInfoPathText = new QLabel( tr( "音乐列表保存路径" ) + ":", this );

	auto mainLayout = new QVBoxLayout( this );
	auto subWidget = new QWidget( this );
	mainLayout->addWidget( subWidget, 0, Qt::AlignmentFlag::AlignTop );
	auto subLayout = new QHBoxLayout( subWidget );
	subLayout->setSpacing( 0 );
	subLayout->setContentsMargins( 0, 0, 0, 0 );
	subLayout->addWidget( loadFileInfoPathText, 2 );
	subLayout->addWidget( loadFileInfoPathEditInputLine, 26 );
	subLayout->addWidget( loadFileInfoPathSelectBtn, 2 );

	connect( loadFileInfoPathEditInputLine, &QLineEdit::editingFinished, [this]( ) {
		auto checkPath = loadFileInfoPathEditInputLine->text( );
		if( musiInfoPath == checkPath )
			return;
		QFileInfo fileInfoTool( checkPath );
		auto absoluteFilePath = fileInfoTool.absoluteFilePath( );
		if( musiInfoPath == absoluteFilePath )
			return;
		if( fileInfoTool.exists( ) == false ) {
			QDir dir( absoluteFilePath );
			if( dir.mkdir( absoluteFilePath ) == false ) {
				MessageErrorOut( ) << tr( "文件夹路径构建失败，请检查权限是否足够" ) << " : " << absoluteFilePath;
				return;
			}
		} else if( fileInfoTool.isFile( ) ) {
			MessageErrorOut( ) << tr( "该路径是一个文件，请选择一个有效的文件夹路径" ) << " : " << absoluteFilePath;
			return;
		}
		musiInfoPath = absoluteFilePath;

		auto applicationInstance = ApplicationInstance::getApplicationInstance( );
		auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
		PathSettingWidgetEvent::triggerPathSettingWidgetEvent(
			applicationEvenTrigger, this, PathSettingWidgetEventInfo( PathSettingWidgetEventInfo::EventType::Update_Music_info_File_Path_Info ) );
	} );

	auto applicationInstance = ApplicationInstance::getApplicationInstance( );
	auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
	// 接受软件加载的目录路径
	connect( applicationEvenTrigger, &ApplicationEvenTrigger::triggerApplicationInstanceEvent, [this] ( auto, const ApplicationInstanceEventInfo &info ) {
		auto eventType = info.getEventType( );
		switch( eventType ) {
			case ApplicationInstanceEventInfo::EventType::Load_Music_Info_Path_Text : {
				auto loadMusicInofPath = info.getLoadMusicInofPath( );
				musiInfoPath = loadMusicInofPath;
				loadFileInfoPathEditInputLine->setText( loadMusicInofPath );
			}
			break;
		}
	} );

}
QString PathSettingWidget::getLoadFileInfoPath( ) const {
	return musiInfoPath;
}
void PathSettingWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );

}
