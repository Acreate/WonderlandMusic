#include "favoriteItemWidget.h"

#include <QHBoxLayout>
#include <QJsonObject>
#include <QLineEdit>

#include "../application/appDataJsonKey.h"
#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/jsonKey/favorItemWidgetJsonKey.h"

#include "../tools/arrayTools.h"

FavoriteItemWidget::~FavoriteItemWidget( ) {
}

FavoriteItemWidget::FavoriteItemWidget( ) : FavoriteItemWidget( nullptr ) {
}

FavoriteItemWidget::FavoriteItemWidget( QWidget *parent ) : QWidget( parent ) {
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

bool FavoriteItemWidget::getJsonDataVector( QJsonObject &get_json_object, const std::vector< std::pair< FavoriteItemWidget *, std::vector< MusicItem * > > > &conver_vector ) {
	QJsonObject vectorData;
	size_t count = conver_vector.size( );
	auto data = conver_vector.data( );
	size_t index = 0;
	size_t jsonCount = 0;
	for( ; index < count; index += 1 ) {
		QJsonObject getJson;
		if( data[ index ]->getJsonData( getJson ) ) {
			vectorData.insert( QString::number( jsonCount ), getJson );
			jsonCount += 1;
		}
	}
	auto jsonKey = AppInstance::getAppInstance( )->getAppDataManage( )->getAppDataJsonKey( )->getFavorItemWidget( );
	QJsonObject vector;
	vector.insert( jsonKey->getFavoriteData( ), vectorData );
	vector.insert( jsonKey->getFavoriteCount( ), QString::number( jsonCount ) );
	get_json_object.insert( jsonKey->getFavoriteVector( ), vector );
	return true;
}

bool FavoriteItemWidget::setJsonDataVector( std::vector< std::pair< FavoriteItemWidget *, std::vector< MusicItem * > > > &result_vector, const QJsonObject &set_json_object ) {
	if( set_json_object.empty( ) )
		return false;
	auto jsonKey = AppInstance::getAppInstance( )->getAppDataManage( )->getAppDataJsonKey( )->getFavorItemWidget( );

	auto find = set_json_object.find( jsonKey->getFavoriteVector( ) );
	auto end = set_json_object.end( );
	if( find == end )
		return false;
	QJsonObject vector = find.value( ).toObject( );
	end = vector.end( );
	find = vector.find( jsonKey->getFavoriteCount( ) );
	if( find == end )
		return false;
	bool conver;
	auto vectorCount = find->toString( ).toULongLong( &conver );
	if( conver == false )
		return false;
	if( vectorCount == 0 )
		return true;
	find = vector.find( jsonKey->getFavoriteData( ) );
	if( find == end )
		return false;
	result_vector.resize( vectorCount );
	auto setData = result_vector.data( );
	QJsonObject vectorData = find.value( ).toObject( );
	auto begin = vectorData.begin( );
	end = vectorData.end( );
	for( ; begin != end; ++begin ) {
		auto index = begin.key( ).toULongLong( &conver );
		if( conver == false )
			continue;
		if( index >= vectorCount )
			continue;
		auto jsonObject = begin.value( ).toObject( );
		auto musicItem = new FavoriteItemWidget( );
		if( musicItem->setJsonData( jsonObject ) == false ) {
			delete musicItem;
			continue;
		}
		setData[ index ] = musicItem;
	}
	vectorCount = ArrayTools::sortNullptr( setData, vectorCount );
	result_vector.resize( vectorCount );
	return true;
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
