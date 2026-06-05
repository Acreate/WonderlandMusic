#ifndef MUSICVECTORINFOITEM_H_H_HEAD__FILE__
#define MUSICVECTORINFOITEM_H_H_HEAD__FILE__

#include "baseItem.h"

class MusicVectorInfoItem : public BaseItem {
	friend class MusicVectorInfoWidget;
public:
	MusicVectorInfoItem( const QString &name, const QRect &rect, const QImage &render_buff, const bool is_hide )
		: BaseItem( name, rect, render_buff, is_hide ) { }
};
#endif // MUSICVECTORINFOITEM_H_H_HEAD__FILE__
