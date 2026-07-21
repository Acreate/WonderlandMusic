#ifndef OPTIONPANEL_H_H_HEAD__FILE__
#define OPTIONPANEL_H_H_HEAD__FILE__
#include <QImage>
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
	QImage icon;

public:
	OptionPanel( OptionWindow *option_window );
	OptionPanel( OptionWindow *option_window, const QString &name );
	OptionPanel( OptionWindow *option_window, const QImage &icon );
	OptionPanel( OptionWindow *option_window, const QString &name, const QImage &icon );
	~OptionPanel( ) override;
	virtual OptionWindow * getOptionWindow( ) const;
	virtual OptionItem * getOptionItem( ) const;
	virtual const QString & getName( ) const;
	virtual void setName( const QString &name );
	virtual const QImage & getIcon( ) const;
	virtual void setIcon( const QImage &icon );
	virtual void response( ) = 0;
	virtual QWidget * toWidget( ) = 0;
	virtual void updateInfo( );
};
#endif // OPTIONPANEL_H_H_HEAD__FILE__
