#include "settingWidget.h"

#include <QPushButton>
#include <qboxlayout.h>
#include <QScrollArea>
#include <QGroupBox>
#include <QLineEdit>

#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/translate/settingWidgetTranslate.h"

void SettingWidget::deleteResource( ) {
	#define d_r( ptr ) if(ptr ) (delete ptr, ptr = nullptr)
}

QWidget * SettingWidget::initMainSettingWdiget( ) {
	auto settingScrollWdiget = initSettingScrollWdiget( );
	if( settingScrollWdiget == nullptr )
		return nullptr;

	auto settingButtonWidget = initSettingButtonWdiget( );
	if( settingButtonWidget == nullptr )
		return nullptr;

	QWidget *mainSetting = new QWidget( this );
	mainSetting->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
	QVBoxLayout *mainSettingVBoxLayout = new QVBoxLayout( mainSetting );
	mainSettingVBoxLayout->setContentsMargins( 0, 0, 0, 0 );
	mainSettingVBoxLayout->setSpacing( 20 );;

	settingScrollWdiget->setParent( mainSetting );
	mainSettingVBoxLayout->addWidget( settingScrollWdiget );

	settingButtonWidget->setParent( mainSetting );
	mainSettingVBoxLayout->addWidget( settingButtonWidget );

	return mainSetting;
}

QWidget * SettingWidget::initSettingScrollWdiget( ) {
	auto selectGroupBox = initSelectSettingPathGroupBoxWdiget( );
	if( selectGroupBox == nullptr )
		return nullptr;
	QScrollArea *settingScrollArea = new QScrollArea( );
	settingScrollArea->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
	settingScrollArea->setWidgetResizable( true );
	settingScrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	settingScrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );

	QWidget *settingConter = new QWidget( settingScrollArea );
	settingScrollArea->setWidget( settingConter );

	QVBoxLayout *conterLayout = new QVBoxLayout( settingConter );
	selectGroupBox->setParent( settingConter );
	conterLayout->addWidget( selectGroupBox );
	conterLayout->addSpacerItem( new QSpacerItem( 0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding ) );
	settingConter->adjustSize( );
	return settingScrollArea;
}

QWidget * SettingWidget::initSettingButtonWdiget( ) {
	QWidget *buttonWidget = new QWidget( );
	QHBoxLayout *buttonWidgetLayout = new QHBoxLayout( buttonWidget );
	buttonWidgetLayout->setContentsMargins( 0, 0, 0, 0 );
	buttonWidgetLayout->setSpacing( 0 );

	QPushButton *ok = new QPushButton( buttonWidget );
	QPushButton *cancel = new QPushButton( buttonWidget );
	buttonWidgetLayout->addSpacerItem( new QSpacerItem( 10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum ) );
	buttonWidgetLayout->addWidget( ok );
	buttonWidgetLayout->addWidget( cancel );

	auto appInstance = AppInstance::getAppInstance( );
	auto settingWidgetTranslate = appInstance->getTranslate( )->getSettingWidget( );
	ok->setText( settingWidgetTranslate->getOkBtnTxt( ) );
	cancel->setText( settingWidgetTranslate->getCancelBtnTxt( ) );

	buttonWidget->adjustSize( );
	return buttonWidget;
}

QWidget * SettingWidget::initSelectSettingPathGroupBoxWdiget( ) {
	auto appSettingPathWdiget = initAppSettingPathWdiget( );
	if( appSettingPathWdiget == nullptr )
		return nullptr;

	QGroupBox *selectSettingPathGroupBox = new QGroupBox( );

	QVBoxLayout *selectGroupBox = new QVBoxLayout( selectSettingPathGroupBox );
	appSettingPathWdiget->setParent( selectSettingPathGroupBox );
	selectGroupBox->addWidget( appSettingPathWdiget );

	auto appInstance = AppInstance::getAppInstance( );
	auto settingWidgetTranslate = appInstance->getTranslate( )->getSettingWidget( );
	selectSettingPathGroupBox->setTitle( settingWidgetTranslate->getSetectPathGroupTitle( ) );

	selectSettingPathGroupBox->adjustSize( );

	return selectSettingPathGroupBox;
}

QWidget * SettingWidget::initAppSettingPathWdiget( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto settingWidgetTranslate = appInstance->getTranslate( )->getSettingWidget( );

	QWidget *selectWidget = new QWidget( );
	QHBoxLayout *seleceLayout = new QHBoxLayout( selectWidget );

	QLineEdit *selectDirPathLineEdit = new QLineEdit( selectWidget );
	selectDirPathLineEdit->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum );
	selectDirPathLineEdit->setPlaceholderText( settingWidgetTranslate->getSelectDirLinePlaceholderTxt( ) );
	seleceLayout->addWidget( selectDirPathLineEdit );

	QPushButton *selectDirPathBtn = new QPushButton( selectWidget );
	selectDirPathBtn->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
	selectDirPathBtn->setText( settingWidgetTranslate->getSelectDirBtnTxt( ) );
	seleceLayout->addWidget( selectDirPathBtn );

	selectWidget->adjustSize( );
	return selectWidget;
}

SettingWidget::SettingWidget( QWidget *parent ) : QWidget( parent ) {
}

bool SettingWidget::loadJsonPathInfo( ) {
	return true;
}

bool SettingWidget::writeJsonPathInfo( ) {
	return true;
}

bool SettingWidget::initWidget( ) {
	auto mainSettingWdiget = initMainSettingWdiget( );
	if( mainSettingWdiget == nullptr )
		return false;
	QVBoxLayout *vBoxLayout = new QVBoxLayout( this );
	vBoxLayout->addWidget( mainSettingWdiget );
	vBoxLayout->setContentsMargins( 10, 10, 20, 20 );
	vBoxLayout->setSpacing( 10 );
	return true;
}

bool SettingWidget::init( ) {
	deleteResource( );
	if( initWidget( ) == false )
		return false;

	if( loadJsonPathInfo( ) == false )
		return false;
	return true;
}

void SettingWidget::hideEvent( QHideEvent *event ) {
	writeJsonPathInfo( );
	QWidget::hideEvent( event );
}
