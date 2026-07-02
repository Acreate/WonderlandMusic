#include "optionDockWidget.h"

#include <QPushButton>
#include <qboxlayout.h>

#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/translate/optionDockWidgetTranslate.h"

#include "../window/mainWindow.h"

OptionDockWidget::OptionDockWidget( MainWindow *parent ) : QDockWidget( parent ), mainWindow( parent ) {
}

bool OptionDockWidget::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( showAboutWidgetBtn );
	Delete_Resource_App_Core_Ptr( showSettingWidgetBtn );
	Delete_Resource_App_Core_Ptr( showPlayListWidgetBtn );
	Delete_Resource_App_Core_Ptr( leftOptionWidget );
	Delete_Resource_App_Core_Ptr( titleBarWidget );
	if( mainWindow )
		mainWindow->removeDockWidget( this );
	return false;
}

bool OptionDockWidget::init( ) {
	deleteResource( );

	setAllowedAreas( Qt::LeftDockWidgetArea );

	titleBarWidget = new QWidget( this );
	setTitleBarWidget( titleBarWidget );
	setContentsMargins( 0, 0, 0, 0 );

	leftOptionWidget = new QWidget( this );

	// 创建左侧容器组件布局
	auto *optionLayout = new QVBoxLayout( leftOptionWidget );
	optionLayout->setContentsMargins( 0, 0, 0, 0 );
	optionLayout->setSpacing( 0 );
	auto appInstance = AppInstance::getAppInstance( );
	auto appDataManage = appInstance->getAppDataManage( );
	auto appTranslate = appDataManage->getTranslate( );
	auto optionDockWidget = appTranslate->getOptionDockWidget( );
	showPlayListWidgetBtn = new QPushButton( optionDockWidget->getMusicTypeName( ), leftOptionWidget );
	optionLayout->addWidget( showPlayListWidgetBtn, 0, Qt::AlignTop );
	connect( showPlayListWidgetBtn, &QPushButton::clicked, this, &signal_click_player_button );

	showSettingWidgetBtn = new QPushButton( optionDockWidget->getSettingWidget( ), leftOptionWidget );
	optionLayout->addWidget( showSettingWidgetBtn, 0, Qt::AlignTop );
	connect( showSettingWidgetBtn, &QPushButton::clicked, this, &signal_click_setting_button );

	showAboutWidgetBtn = new QPushButton( optionDockWidget->getAboutWidget( ), leftOptionWidget );
	optionLayout->addWidget( showAboutWidgetBtn, 0, Qt::AlignTop );
	connect( showAboutWidgetBtn, &QPushButton::clicked, this, &signal_click_about_button );

	// 底部弹顶
	QSpacerItem *spacerItem = new QSpacerItem( 1, 1, QSizePolicy::Ignored, QSizePolicy::Expanding );
	optionLayout->addSpacerItem( spacerItem );
	// 强制宽度
	leftOptionWidget->adjustSize( );
	leftOptionWidget->setFixedWidth( leftOptionWidget->width( ) );

	setWidget( leftOptionWidget );
	mainWindow->addDockWidget( Qt::DockWidgetArea::LeftDockWidgetArea, this );
	return true;
}
