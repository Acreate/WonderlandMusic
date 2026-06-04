#ifndef APPLICATIONINSTANCE_H_H_HEAD__FILE__
#define APPLICATIONINSTANCE_H_H_HEAD__FILE__
#include <QObject>

class Render;
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
	Render *render;
	ApplicationInstance( Application *const application );
public:
	~ApplicationInstance( ) override;
public:
	virtual Application * getApplication( ) const { return application; }
	virtual Render * getRender( ) const { return render; }
};

#endif // APPLICATIONINSTANCE_H_H_HEAD__FILE__
