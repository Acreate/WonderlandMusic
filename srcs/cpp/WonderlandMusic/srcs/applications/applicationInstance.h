#ifndef APPLICATIONINSTANCE_H_H_HEAD__FILE__
#define APPLICATIONINSTANCE_H_H_HEAD__FILE__
#include <QObject>

class Application;
class ApplicationInstance : public QObject {
	Q_OBJECT;
private:
	friend class Application;
private:
	static ApplicationInstance *instance;
public:
	static ApplicationInstance * getInstance( );
private:
	Application *application;
	ApplicationInstance( Application *const application );
public:
	virtual Application * getApplication( ) const { return application; }
};

#endif // APPLICATIONINSTANCE_H_H_HEAD__FILE__
