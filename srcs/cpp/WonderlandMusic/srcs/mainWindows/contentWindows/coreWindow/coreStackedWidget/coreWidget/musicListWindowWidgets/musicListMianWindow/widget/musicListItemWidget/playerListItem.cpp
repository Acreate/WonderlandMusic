#include "playerListItem.h"

#include <QImage>
#include <QObject>
#include <QPainter>
#include <qstring.h>

#include <render/render.h>

#include "../../../../../../../../../msgInfo/messageErrorOut.h"

PlayerListItem::~PlayerListItem( ) {
	clearItem( );
}
PlayerListItem::PlayerListItem( ) {
	drawDecollatorWidth = 2;
	drawDecollatorInterspace = 10;
}
void PlayerListItem::appendItem( const QString &item_name ) {
	playerListItemInfos.emplace_back( new FontRender( item_name, false ) );

}
void PlayerListItem::insterItem( const QString &item_name, const size_t &index ) {
	size_t count = playerListItemInfos.size( );
	if( count <= index )
		appendItem( item_name );
	else
		playerListItemInfos.insert( playerListItemInfos.begin( ) + index, new FontRender( item_name, false ) );
}
bool PlayerListItem::removeItem( const QString &item_name ) {
	size_t count = playerListItemInfos.size( );
	if( count == 0 )
		return false; // 删除失败
	size_t index;
	FontRender **fontRenderData;
	fontRenderData = playerListItemInfos.data( );
	for( index = 0; index < count; ++index )
		if( fontRenderData[ index ]->getTxt( ) == item_name ) {
			delete fontRenderData[ index ];
			playerListItemInfos.erase( playerListItemInfos.begin( ) + index );
			return true;
		}
	return false;
}
bool PlayerListItem::removeAllItem( const QString &item_name ) {
	size_t count = playerListItemInfos.size( );
	if( count == 0 )
		return false; // 删除失败
	size_t index;
	size_t removeCount = 0;
	FontRender **fontRenderData;
	fontRenderData = playerListItemInfos.data( );
	for( index = 0; index < count; ++index )
		if( fontRenderData[ index ]->getTxt( ) == item_name ) {
			delete fontRenderData[ index ];
			fontRenderData[ index ] = nullptr;
			count -= 1;
			removeCount += 1;
		}
	if( removeCount == 0 )
		return false;
	std::vector< FontRender * > buff;
	buff.resize( count );
	auto buffData = buff.data( );
	removeCount = 0;
	for( index = 0; index < count; ++index )
		if( fontRenderData[ index ] != nullptr )
			buffData[ removeCount++ ] = fontRenderData[ index ];
	playerListItemInfos = buff;
	return true;
}
bool PlayerListItem::clearItem( ) {
	size_t count = playerListItemInfos.size( );
	if( count == 0 )
		return false;
	size_t index;
	FontRender **fontRenderData;
	fontRenderData = playerListItemInfos.data( );
	for( index = 0; index < count; ++index )
		delete fontRenderData[ index ];
	playerListItemInfos.clear( );
	return true;
}
bool PlayerListItem::hasItem( const QString &item_name ) {
	size_t count = playerListItemInfos.size( );
	if( count == 0 )
		return false;
	size_t index;
	FontRender **fontRenderData;
	fontRenderData = playerListItemInfos.data( );
	for( index = 0; index < count; ++index )
		if( fontRenderData[ index ]->getTxt( ) == item_name )
			return true;
	return false;
}
size_t PlayerListItem::renderBuff( QImage *render_target ) {

	/*
	 * 每个项的宽度 = 项目的宽度 + 分隔符
	 * 计算总宽度空间 = 头分隔符 + 每个项的宽度 * 选项个数
	 */
	size_t count = playerListItemInfos.size( );
	if( count == 0 )
		return 0; // 没渲染
	FontRender **fontRenderData;
	size_t index;
	// 使用头分隔符初始化宽度
	int width = drawDecollatorInterspace;
	int height = 0;
	int compHeight;
	const StringFontSize *txtFontSize;
	fontRenderData = playerListItemInfos.data( );
	for( index = 0; index < count; ++index ) {
		txtFontSize = fontRenderData[ index ]->getTxtFontSize( );
		compHeight = txtFontSize->getHeight( );
		if( compHeight > height )
			height = compHeight;
		width += txtFontSize->getHorizontalAdvance( ) + drawDecollatorInterspace;
	}
	if( width == 0 ) {
		Message_Error_Out << QObject::tr( "绘制宽度为 0" );
		return 0;
	}
	if( height == 0 ) {
		Message_Error_Out << QObject::tr( "绘制高度为 0" );
		return 0;
	}
	QImage image( width, height, QImage::Format_RGBA8888 );
	if( image.isNull( ) ) {
		Message_Error_Out << QObject::tr( "图像创建失败" );
		return 0;
	}
	image.fill( 0 );
	QPainter painter;
	painter.begin( &image );
	// 线段笔刷
	auto pen = painter.pen( );
	pen.setWidth( drawDecollatorWidth );
	painter.setPen( pen );

	compHeight = drawDecollatorInterspace - drawDecollatorWidth;
	// 绘制线
	auto half = compHeight / 2;
	painter.drawLine( half, 0, half, height );
	// 上一次的项目的末尾 x 位置
	int oldX = drawDecollatorInterspace;
	// 循环绘制
	for( index = 0; index < count; ++index ) {
		fontRenderData[ index ]->drawTarget( &painter, oldX, 0 );
		oldX += txtFontSize->getHorizontalAdvance( );
		compHeight = oldX + half;
		painter.drawLine( compHeight, 0, compHeight, height );
		oldX = oldX + drawDecollatorInterspace;
	}

	painter.end( );

	*render_target = image;
	return count;
}
