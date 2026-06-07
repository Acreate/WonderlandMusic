#include "functionWidget.h"

#include "../functionDockWidget.h"
#include <QVBoxLayout>
#include <QPushButton>

#include <applications/applicationEvenTrigger.h>

#include <applications/applicationInstance.h>
FunctionWidget::FunctionWidget( FunctionDockWidget *parent ) : QWidget( parent ), functionDockWidget( parent ) {

	showMusicBtn = new QPushButton( tr( "音乐" ), this );
	connect( showMusicBtn, &QPushButton::clicked, [this]( ) {
		FunctionWidgetEvent::triggerFunctionWidgetEvent( ApplicationInstance::getApplicationInstance( )->getApplicationEvenTrigger( ), this, FunctionWidgetEventInfo( FunctionWidgetEventInfo::EventType::Show_Music ) );
	} );
	showSettingBtn = new QPushButton( tr( "设置" ), this );
	connect( showSettingBtn, &QPushButton::clicked, [this]( ) {
		FunctionWidgetEvent::triggerFunctionWidgetEvent( ApplicationInstance::getApplicationInstance( )->getApplicationEvenTrigger( ), this, FunctionWidgetEventInfo( FunctionWidgetEventInfo::EventType::Show_Setting ) );
	} );
}
void FunctionWidget::resizeEvent( QResizeEvent *event ) {
	showMusicBtn->move( 0, 0 );
	int nextY = showMusicBtn->height( );
	showSettingBtn->move( 0, nextY );
	nextY += showSettingBtn->height( );
	setMinimumHeight( nextY ); // 配置最小

	int maxWidth = showMusicBtn->width( );

	int settingWidth = showSettingBtn->width( );
	if( maxWidth < settingWidth )
		maxWidth = settingWidth;
	setFixedWidth( maxWidth );
}
