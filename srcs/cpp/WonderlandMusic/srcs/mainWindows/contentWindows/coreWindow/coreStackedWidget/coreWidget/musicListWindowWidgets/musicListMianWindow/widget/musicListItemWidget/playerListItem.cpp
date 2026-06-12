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
	startInterspaceWidth = 15;
	maxHeight = 0;
	maxWidth = 0;
}
void PlayerListItem::appendItem( const QString &item_name ) {
	playerListItemInfos.emplace_back( new FontRender( item_name, false ) );
	updateSizeInfo( );
}
void PlayerListItem::insterItem( const QString &item_name, const size_t &index ) {
	FontRender *val = new FontRender( item_name, false );
	size_t count = playerListItemInfos.size( );
	if( count <= index )
		playerListItemInfos.emplace_back( val );

	else
		playerListItemInfos.insert( playerListItemInfos.begin( ) + index, val );
	auto stringFontSize = val->getTxtFontSize( );
	maxWidth += stringFontSize->getWidth( ) + drawDecollatorInterspace;
	int height = stringFontSize->getHeight( );
	if( height < maxHeight )
		maxHeight = height;
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
			auto stringFontSize = fontRenderData[ index ]->getTxtFontSize( );
			int width = stringFontSize->getWidth( );
			int height = stringFontSize->getHeight( );
			delete fontRenderData[ index ];
			playerListItemInfos.erase( playerListItemInfos.begin( ) + index );
			if( height == maxHeight ) {
				maxHeight = 0;
				fontRenderData = playerListItemInfos.data( );
				for( index = 0; index < count; ++index ) {
					stringFontSize = fontRenderData[ index ]->getTxtFontSize( );
					height = stringFontSize->getHeight( );
					if( height > maxHeight )
						maxHeight = height;
				}
			}
			maxWidth = maxWidth - width - drawDecollatorInterspace;
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
	// 使用预留宽度初始化宽度
	maxWidth = startInterspaceWidth;
	maxHeight = 0;
	int compHeight;
	const StringFontSize *txtFontSize;
	fontRenderData = playerListItemInfos.data( );
	for( index = 0; index < count; ++index ) {
		txtFontSize = fontRenderData[ index ]->getTxtFontSize( );
		compHeight = txtFontSize->getHeight( );
		if( compHeight > maxHeight )
			maxHeight = compHeight;
		maxWidth += txtFontSize->getHorizontalAdvance( ) + drawDecollatorInterspace;
	}
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
	maxHeight = 0;
	maxWidth = 0;
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
	 * 计算总宽度空间 = 预留宽度 + 每个项的宽度 * 选项个数
	 */
	size_t count = playerListItemInfos.size( );
	if( count == 0 )
		return 0; // 没渲染
	if( maxWidth == 0 ) {
		Message_Error_Out << QObject::tr( "绘制宽度为 0" );
		return 0;
	}
	if( maxWidth == 0 ) {
		Message_Error_Out << QObject::tr( "绘制高度为 0" );
		return 0;
	}
	QImage image( maxWidth, maxHeight, QImage::Format_RGBA8888 );
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

	FontRender **fontRenderData = playerListItemInfos.data( );
	int compHeight = drawDecollatorInterspace - drawDecollatorWidth;
	// 绘制线
	auto half = compHeight / 2;
	int oldX = startInterspaceWidth + half;
	painter.drawLine( oldX, 0, oldX, maxHeight );
	// 上一次的项目的末尾 x 位置
	oldX = startInterspaceWidth + drawDecollatorInterspace;
	const StringFontSize *txtFontSize;
	// 循环绘制
	size_t index = 0;
	for( ; index < count; ++index ) {
		fontRenderData[ index ]->drawTarget( &painter, oldX, 0 );
		txtFontSize = fontRenderData[ index ]->getTxtFontSize( );
		oldX += txtFontSize->getHorizontalAdvance( );
		compHeight = oldX + half;
		painter.drawLine( compHeight, 0, compHeight, maxHeight );
		oldX += drawDecollatorInterspace;
	}

	painter.end( );

	*render_target = image;
	return count;
}
int PlayerListItem::getDrawDecollatorWidth( ) const { return drawDecollatorWidth; }
void PlayerListItem::setDrawDecollatorWidth( const int draw_decollator_width ) { drawDecollatorWidth = draw_decollator_width; }
int PlayerListItem::getDrawDecollatorInterspace( ) const { return drawDecollatorInterspace; }
void PlayerListItem::setDrawDecollatorInterspace( const int draw_decollator_interspace ) { drawDecollatorInterspace = draw_decollator_interspace; }
bool PlayerListItem::getIndexRect( QRect &result_rect, const size_t &index ) const {
	size_t count = playerListItemInfos.size( );
	if( count <= index )
		return false; // 位置失败

	// 开始位置
	int oldX = startInterspaceWidth + drawDecollatorInterspace;
	size_t currentIndex;
	// 循环绘制
	auto fontRenderData = playerListItemInfos.data( );
	const StringFontSize *txtFontSize;
	count = index + 1;
	int horizontalAdvance;
	for( currentIndex = 0; currentIndex < count; ++currentIndex ) {
		txtFontSize = fontRenderData[ currentIndex ]->getTxtFontSize( );
		horizontalAdvance = txtFontSize->getHorizontalAdvance( );
		oldX = oldX + horizontalAdvance + drawDecollatorInterspace;
	}
	result_rect = QRect( oldX, 0, horizontalAdvance, maxHeight );
	return true;
}
size_t PlayerListItem::updateSizeInfo( ) {
	size_t count = playerListItemInfos.size( );
	if( count == 0 ) {
		maxHeight = 0;
		maxWidth = 0;
		return 0; // 更新失败
	}

	maxWidth = startInterspaceWidth;
	maxHeight = 0;
	int compHeight;
	const StringFontSize *txtFontSize;
	auto fontRenderData = playerListItemInfos.data( );
	size_t index;
	for( index = 0; index < count; ++index ) {
		txtFontSize = fontRenderData[ index ]->getTxtFontSize( );
		compHeight = txtFontSize->getHeight( );
		if( compHeight > maxHeight )
			maxHeight = compHeight;
		maxWidth += txtFontSize->getHorizontalAdvance( ) + drawDecollatorInterspace;
	}
	return 0;
}
