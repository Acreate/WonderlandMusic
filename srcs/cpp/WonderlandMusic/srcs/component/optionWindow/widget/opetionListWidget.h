#ifndef OPETIONLISTWIDGET_H_H_HEAD__FILE__
#define OPETIONLISTWIDGET_H_H_HEAD__FILE__
#include <QWidget>
#include "../../../interface/iAppCore.h"
class UserMutex;
class OptionButton;
class OptionItem;

class OpetionListWidget : public QWidget, public IAppCore {
	Q_OBJECT;

protected:
	UserMutex *mutex = nullptr;
	std::vector< OptionButton * > labelVector;

public:
	OpetionListWidget( QWidget *parent );
	~OpetionListWidget( ) override;
	virtual void addItem( OptionItem *option_item );
	virtual void deleteItem( OptionItem *option_item );
	virtual bool hasItem( size_t &result_index, const OptionItem *option_item );

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
Q_SIGNALS:
	void signal_click_item( OptionItem *option_item );
};
#endif // OPETIONLISTWIDGET_H_H_HEAD__FILE__
