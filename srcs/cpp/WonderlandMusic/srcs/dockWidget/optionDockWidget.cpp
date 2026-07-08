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

OptionDockWidget::~OptionDockWidget( ) {
	deleteResource( );
}

bool OptionDockWidget::deleteResource( ) {
	disconnect( );
	Delete_Resource_App_Core_Ptr( showAboutWidgetBtn );
	Delete_Resource_App_Core_Ptr( showSettingWidgetBtn );
	Delete_Resource_App_Core_Ptr( showPlayListWidgetBtn );
	Delete_Resource_App_Core_Ptr( leftOptionWidget );
	Delete_Resource_App_Core_Ptr( titleBarWidget );
	if( mainWindow )
		mainWindow->removeDockWidget( this );
	return false;
}

bool OptionDockWidget::getJsonData( QJsonObject &get_json_object ) const {
	return false;
}

bool OptionDockWidget::setJsonData( const QJsonObject &set_json_object ) {
	return false;
}

bool OptionDockWidget::init( ) {
	setAllowedAreas( Qt::LeftDockWidgetArea );
	setContentsMargins( 0, 0, 0, 0 );
	setTitleBarWidget( titleBarWidget );

	// 组件布局
	optionLayout->setContentsMargins( 0, 0, 0, 0 );
	optionLayout->setSpacing( 0 );
	optionLayout->addWidget( showPlayListWidgetBtn, 0, Qt::AlignTop );
	optionLayout->addWidget( showSettingWidgetBtn, 0, Qt::AlignTop );
	optionLayout->addWidget( showAboutWidgetBtn, 0, Qt::AlignTop );
	optionLayout->addSpacerItem( spacerItem );

	setWidget( leftOptionWidget );
	mainWindow->addDockWidget( Qt::DockWidgetArea::LeftDockWidgetArea, this );
	return true;
}

bool OptionDockWidget::initBefore( ) {
	deleteResource( );
	titleBarWidget = new QWidget( this );
	leftOptionWidget = new QWidget( this );
	optionLayout = new QVBoxLayout( leftOptionWidget );
	spacerItem = new QSpacerItem( 1, 1, QSizePolicy::Ignored, QSizePolicy::Expanding );

	showPlayListWidgetBtn = new QPushButton( leftOptionWidget );

	showSettingWidgetBtn = new QPushButton( leftOptionWidget );

	showAboutWidgetBtn = new QPushButton( leftOptionWidget );

	return true;
}

bool OptionDockWidget::initAfter( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto appDataManage = appInstance->getAppDataManage( );
	auto appTranslate = appDataManage->getTranslate( );
	auto optionDockWidget = appTranslate->getOptionDockWidget( );
	showPlayListWidgetBtn->setText( optionDockWidget->getMusicTypeName( ) );
	showSettingWidgetBtn->setText( optionDockWidget->getSettingWidget( ) );
	showAboutWidgetBtn->setText( optionDockWidget->getAboutWidget( ) );
	
	// 强制宽度
	leftOptionWidget->adjustSize( );
	leftOptionWidget->setFixedWidth( leftOptionWidget->width( ) );

	connect( showPlayListWidgetBtn, &QPushButton::clicked, this, &OptionDockWidget::signal_click_player_button );
	connect( showSettingWidgetBtn, &QPushButton::clicked, this, &OptionDockWidget::signal_click_setting_button );
	connect( showAboutWidgetBtn, &QPushButton::clicked, this, &OptionDockWidget::signal_click_about_button );

	int maxWidth = showPlayListWidgetBtn->width( );
	int compWidth = showSettingWidgetBtn->width( );
	if( maxWidth < compWidth )
		maxWidth = compWidth;
	compWidth = showAboutWidgetBtn->width( );
	if( maxWidth < compWidth )
		maxWidth = compWidth;
	setFixedWidth( maxWidth );
	return true;
}
