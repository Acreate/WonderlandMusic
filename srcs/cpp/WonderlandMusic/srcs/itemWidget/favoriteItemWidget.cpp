#include "favoriteItemWidget.h"
#include <QHBoxLayout>
#include <QJsonObject>
#include <QLineEdit>
#include "../application/appDataJsonKey.h"
#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/appMusicManage.h"
#include "../application/jsonKey/favorItemWidgetJsonKey.h"

FavoriteItemWidget::~FavoriteItemWidget( ) {
}

FavoriteItemWidget::FavoriteItemWidget( FavoriteItem *favor_item ) : QWidget( nullptr ), favoriteItem( favor_item ) {
	lineEdit = new QLineEdit( this );
	connect( lineEdit, &QLineEdit::editingFinished, this, [this]( ) {
		lineEdit->setEnabled( false );
		emit signal_change_name_finished( );
	} );
	connect( lineEdit, &QLineEdit::textChanged, this, [this]( ) {
		updateWidth( );
	} );
	auto styleSheet = R"(
QLineEdit {
    background-color: transparent;    
	border: none;
    outline: none; 
    color: black;
}

/* 禁用状态：文字变灰，背景依旧透明 */
QLineEdit:disabled {
    background-color: transparent;
    color: black;
}

/* 只读状态可选配置 */
QLineEdit:read-only {
    background-color: transparent;
    color: black;
})";
	lineEdit->setStyleSheet( styleSheet );
	lineEdit->update( );
	lineEdit->setEnabled( false );
	lineEdit->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum );
	auto mainLayout = new QHBoxLayout( this );
	mainLayout->addWidget( lineEdit );
}

QString FavoriteItemWidget::getFavoriteName( ) const {
	return lineEdit->text( );
}

void FavoriteItemWidget::setFavoriteName( const QString &name ) {
	lineEdit->setText( name );
}

void FavoriteItemWidget::updateWidth( ) {
	QFontMetrics fm( lineEdit->font( ) );
	// 计算文字像素宽度 + 左右内边距余量
	int textW = fm.horizontalAdvance( lineEdit->text( ) );
	int padding = 12; // 左右留白，可自行调整
	int totalW = textW + padding;

	int minw = qMax( totalW, 30 );
	// 设置最小宽度，防止缩成0
	lineEdit->setMinimumWidth( minw );
	adjustSize( );
}

FavoriteItem * FavoriteItemWidget::getFavorItem( ) const {
	return favoriteItem;
}

bool FavoriteItemWidget::getJsonData( QJsonObject &get_json_object ) const {
	auto jsonKey = AppInstance::getAppInstance( )->getAppDataManage( )->getAppDataJsonKey( )->getFavorItemWidget( );

	QJsonObject obj;
	obj.insert( jsonKey->getName( ), lineEdit->text( ) );
	get_json_object.insert( jsonKey->getFavorItemWidget( ), obj );
	return false;
}

bool FavoriteItemWidget::setJsonData( const QJsonObject &set_json_object ) {
	if( set_json_object.empty( ) )
		return false;
	auto jsonKey = AppInstance::getAppInstance( )->getAppDataManage( )->getAppDataJsonKey( )->getFavorItemWidget( );

	auto find = set_json_object.find( jsonKey->getFavorItemWidget( ) );
	if( find == set_json_object.end( ) )
		return false;
	auto jsonObejct = find.value( ).toObject( );
	find = jsonObejct.find( jsonKey->getName( ) );
	if( find == jsonObejct.end( ) )
		return false;
	lineEdit->setText( find.value( ).toString( lineEdit->text( ) ) );
	return true;
}

void FavoriteItemWidget::mouseDoubleClickEvent( QMouseEvent *event ) {
	QWidget::mouseDoubleClickEvent( event );
	if( isEnabled( ) == false )
		return;
	lineEdit->setEnabled( true );
	lineEdit->setFocus( );
}

void FavoriteItemWidget::focusOutEvent( QFocusEvent *event ) {
	QWidget::focusOutEvent( event );
	lineEdit->setEnabled( false );
}
