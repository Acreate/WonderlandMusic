#include "eventFilter.h"
bool EventFilter::eventFilter( QObject *watched, QEvent *event ) {
	return QObject::eventFilter( watched, event );
}
