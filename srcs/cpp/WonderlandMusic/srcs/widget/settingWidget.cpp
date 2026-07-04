#include "settingWidget.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QPushButton>
#include <qboxlayout.h>
#include <QScrollArea>
#include <QGroupBox>
#include <QLineEdit>

#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/translate/settingWidgetTranslate.h"

#include "../tools/pathTools.h"
#include "../tools/widgetTools.h"

bool SettingWidget::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( mainSettingWdiget );
	disconnect( );
	return true;
}

void SettingWidget::clickSelectAppSettingPathBtn( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto settingWidgetTranslate = appInstance->getAppDataManage( )->getTranslate( )->getSettingWidget( );
	QFileInfo fileInfo;

	QFileDialog dialog( this );
	dialog.setWindowTitle( settingWidgetTranslate->getSelectDirPathDialogTitle( ) );
	auto editorAppSettingHomePath = selectDirPathLineEdit->text( );
	fileInfo.setFile( editorAppSettingHomePath );

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
	editorAppSettingHomePath = PathTools::getAutoShortenPathName( data[ 0 ] );
	selectDirPathLineEdit->setText( editorAppSettingHomePath );
}

void SettingWidget::changedSelectAppSettingPathEditor( ) {
	auto text = selectDirPathLineEdit->text( );
	auto editorAppSettingHomePath = PathTools::getAutoShortenPathName( text );
	selectDirPathLineEdit->setText( editorAppSettingHomePath );
}

void SettingWidget::clickOkBtn( ) {
	AppInstance::getAppInstance( )->getAppDataManage( )->setAppSettingPath( selectDirPathLineEdit->text( ), true );
}

void SettingWidget::clickCancelBtn( ) {
	if( selectDirPathLineEdit == nullptr )
		return;
	auto appSetHomePath = AppInstance::getAppInstance( )->getAppDataManage( )->getAppSettingPath( );
	selectDirPathLineEdit->setText( appSetHomePath );
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
	auto settingWidgetTranslate = appInstance->getAppDataManage( )->getTranslate( )->getSettingWidget( );
	ok->setText( settingWidgetTranslate->getOkBtnTxt( ) );
	cancel->setText( settingWidgetTranslate->getCancelBtnTxt( ) );

	connect( ok, &QPushButton::clicked, this, &SettingWidget::clickOkBtn );
	connect( cancel, &QPushButton::clicked, this, &SettingWidget::clickCancelBtn );

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
	auto appDataManage = appInstance->getAppDataManage( );
	auto settingWidgetTranslate = appDataManage->getTranslate( )->getSettingWidget( );
	selectSettingPathGroupBox->setTitle( settingWidgetTranslate->getSetectPathGroupTitle( ) );

	return selectSettingPathGroupBox;
}

QWidget * SettingWidget::initAppSettingPathWdiget( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto appDataManage = appInstance->getAppDataManage( );
	auto settingWidgetTranslate = appDataManage->getTranslate( )->getSettingWidget( );

	QWidget *selectWidget = new QWidget( );
	QHBoxLayout *seleceLayout = new QHBoxLayout( selectWidget );

	selectDirPathLineEdit = new QLineEdit( selectWidget );
	selectDirPathLineEdit->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum );
	selectDirPathLineEdit->setPlaceholderText( settingWidgetTranslate->getSelectDirLinePlaceholderTxt( ) );
	seleceLayout->addWidget( selectDirPathLineEdit );
	connect( selectDirPathLineEdit, &QLineEdit::editingFinished, this, &SettingWidget::changedSelectAppSettingPathEditor );

	QPushButton *selectDirPathBtn = new QPushButton( selectWidget );
	selectDirPathBtn->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
	selectDirPathBtn->setText( settingWidgetTranslate->getSelectDirBtnTxt( ) );
	seleceLayout->addWidget( selectDirPathBtn );
	connect( selectDirPathBtn, &QPushButton::clicked, this, &SettingWidget::clickSelectAppSettingPathBtn );

	connect( appDataManage, &AppDataManage::signal_change_setting_path, this, [this] ( const QString &home_path ) {
		selectDirPathLineEdit->setText( home_path );
	} );
	return selectWidget;
}

SettingWidget::SettingWidget( QWidget *parent ) : QWidget( parent ) {
}

SettingWidget::~SettingWidget( ) {
	deleteResource( );
}

bool SettingWidget::initWidget( ) {
	mainSettingWdiget = initMainSettingWdiget( );
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
	selectDirPathLineEdit->setText( AppInstance::getAppInstance( )->getAppDataManage( )->getAppSettingPath( ) );

	return true;
}

bool SettingWidget::initBefore( ) {
	return true;
}

bool SettingWidget::initAfter( ) {
	return true;
}

void SettingWidget::hideEvent( QHideEvent *event ) {
	QWidget::hideEvent( event );
	clickCancelBtn( );
}
