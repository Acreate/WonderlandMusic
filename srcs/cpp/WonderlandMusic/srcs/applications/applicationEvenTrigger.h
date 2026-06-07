#ifndef APPLICATIONEVENTRIGGER_H_H_HEAD__FILE__
#define APPLICATIONEVENTRIGGER_H_H_HEAD__FILE__
#include <QObject>

class Application;
class ApplicationInstance;
class ApplicationEvenTrigger : public QObject {
	Q_OBJECT;
protected:
	ApplicationInstance *applicationInstance;
	Application *application;
public:
	ApplicationEvenTrigger( QObject *const parent, ApplicationInstance *const application_instance, Application *const application );
};

#endif // APPLICATIONEVENTRIGGER_H_H_HEAD__FILE__
