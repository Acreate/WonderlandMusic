#ifndef APPFUNCTIONITEM_H_H_HEAD__FILE__
#define APPFUNCTIONITEM_H_H_HEAD__FILE__
#include "baseItem.h"

class AppFunctionItem : public BaseItem {
	friend class AppFunctionWidget;
public:
	AppFunctionItem( const QString &name, const QRect &rect, const QImage &render_buff, const bool is_hide )
		: BaseItem( name, rect, render_buff, is_hide ) { }
};

#endif // APPFUNCTIONITEM_H_H_HEAD__FILE__
