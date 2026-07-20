#ifndef OPETIONLISTWIDGET_H_H_HEAD__FILE__
#define OPETIONLISTWIDGET_H_H_HEAD__FILE__
#include <QWidget>
#include "../../../interface/iAppCore.h"

class OpetionListWidget : public QWidget, public IAppCore {
	Q_OBJECT;

public:
	OpetionListWidget( QWidget *parent );

	~OpetionListWidget( ) override;

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
};
#endif // OPETIONLISTWIDGET_H_H_HEAD__FILE__
