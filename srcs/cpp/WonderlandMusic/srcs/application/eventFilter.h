#ifndef EVENTFILTER_H_H_HEAD__FILE__
#define EVENTFILTER_H_H_HEAD__FILE__
#include <QObject>

class MessageErrorOut;
class EventFilter : public QObject {
	Q_OBJECT;
public:
	EventFilter( ) { }
	bool eventFilter( QObject *watched, QEvent *event ) override;
};

#endif // EVENTFILTER_H_H_HEAD__FILE__
