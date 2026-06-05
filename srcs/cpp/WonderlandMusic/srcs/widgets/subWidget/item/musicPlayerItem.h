#ifndef MUSICPLAYERITEM_H_H_HEAD__FILE__
#define MUSICPLAYERITEM_H_H_HEAD__FILE__

#include "baseItem.h"

class MusicPlayerItem : public BaseItem {
	friend class MusicPlayerWidget;
public:
	MusicPlayerItem( const QString &name, const QRect &rect, const QImage &render_buff, const bool is_hide )
		: BaseItem( name, rect, render_buff, is_hide ) { }
};

#endif // MUSICPLAYERITEM_H_H_HEAD__FILE__
