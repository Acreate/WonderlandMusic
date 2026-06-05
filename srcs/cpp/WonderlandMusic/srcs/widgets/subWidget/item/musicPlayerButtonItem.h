#ifndef MUSICPLAYERBUTTONITEM_H_H_HEAD__FILE__
#define MUSICPLAYERBUTTONITEM_H_H_HEAD__FILE__
#include "baseItem.h"

class MusicPlayerButtonItem : public BaseItem {
	friend class MusicPlayerButtonWidget;
public:
	MusicPlayerButtonItem( const QString &name, const QRect &rect, const QImage &render_buff, const bool is_hide )
		: BaseItem( name, rect, render_buff, is_hide ) { }
};

#endif // MUSICPLAYERBUTTONITEM_H_H_HEAD__FILE__
