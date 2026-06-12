#ifndef PLAYERLISTITEM_H_H_HEAD__FILE__
#define PLAYERLISTITEM_H_H_HEAD__FILE__
#include <vector>

class FontRender;
class QImage;
class QString;
class PlayerListItem {
protected:
	/// @brief 渲染项的序列
	std::vector< FontRender * > playerListItemInfos;
	/// @brief 绘制的分隔符宽度
	int drawDecollatorWidth;
	/// @brief 绘制的分隔符占用空间
	int drawDecollatorInterspace;
public:
	virtual ~PlayerListItem( );
	PlayerListItem( );
	virtual void appendItem( const QString &item_name );
	virtual void insterItem( const QString &item_name, const size_t &index );
	virtual bool removeItem( const QString &item_name );
	virtual bool removeAllItem( const QString &item_name );
	virtual bool clearItem( );
	virtual bool hasItem( const QString &item_name );
	virtual size_t renderBuff( QImage *render_target );
	virtual const std::vector< FontRender * > & getPlayerListItemInfoVector( ) const { return playerListItemInfos; }
};

#endif // PLAYERLISTITEM_H_H_HEAD__FILE__
