#ifndef OPTIONPANEL_H_H_HEAD__FILE__
#define OPTIONPANEL_H_H_HEAD__FILE__
#include <QIcon>
#include "../../../interface/iAppCore.h"
#include "../../../interface/iAppJsonData.h"
class OptionItem;
class OptionWindow;

class OptionPanel : public IAppCore, public IAppJsonData {
	friend class OptionWindow;

protected:
	OptionWindow *optionWindow;
	OptionItem *optionItem = nullptr;
	QString name;
	QIcon icon;

public:
	OptionPanel( OptionWindow *option_window );
	OptionPanel( OptionWindow *option_window, const QString &name );
	OptionPanel( OptionWindow *option_window, const QIcon &icon );
	OptionPanel( OptionWindow *option_window, const QString &name, const QIcon &icon );
	~OptionPanel( ) override;
	virtual OptionWindow * getOptionWindow( ) const;
	virtual OptionItem * getOptionItem( ) const;
	virtual const QString & getName( ) const;
	virtual void setName( const QString &name );
	virtual const QIcon & getIcon( ) const;
	virtual void setIcon( const QIcon &icon );
	virtual void response( ) = 0;
	virtual QWidget * toWidget( ) = 0;
	virtual void updateInfo( );
};
#endif // OPTIONPANEL_H_H_HEAD__FILE__
