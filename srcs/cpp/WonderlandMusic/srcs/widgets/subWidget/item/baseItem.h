#ifndef BASEITEM_H_H_HEAD__FILE__
#define BASEITEM_H_H_HEAD__FILE__

#include <QImage>
#include <QString>

class BaseItem {
protected:
	QString name;
	QRect rect;
	QImage renderBuff;
	bool isHide;
public:
	virtual ~BaseItem( ) = default;
	BaseItem( const QString &name, const QRect &rect, const QImage &render_buff, const bool is_hide ) : name( name ), rect( rect ), renderBuff( render_buff ), isHide( is_hide ) { }
	virtual const QString & getName( ) const { return name; }
	virtual const QRect & getRect( ) const { return rect; }
	virtual const QImage & getRenderBuff( ) const { return renderBuff; }
	virtual bool isIsHide( ) const { return isHide; }
};

#endif // BASEITEM_H_H_HEAD__FILE__
