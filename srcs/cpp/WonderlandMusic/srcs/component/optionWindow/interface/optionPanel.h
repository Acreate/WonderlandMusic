#ifndef OPTIONPANEL_H_H_HEAD__FILE__
#define OPTIONPANEL_H_H_HEAD__FILE__
#include <QWidget>

#include "../../../interface/iAppCore.h"
#include "../../../interface/iAppJsonData.h"
class OptionButton;
class CoreInfo;
class OptionWindow;

class OptionPanel : public IAppCore, public IAppJsonData {
private:
	friend class OptionWindow;

	OptionWindow *optionWindow = nullptr;
	OptionButton *optionButton = nullptr;

protected:
	~OptionPanel( ) override;

	virtual void setName( const QString &name );
	virtual void setIcon( const QImage &icon );

public:
	OptionPanel( OptionWindow *option_window );
	OptionPanel( OptionWindow *option_window, const QString &name );
	OptionPanel( OptionWindow *option_window, const QImage &icon );
	OptionPanel( OptionWindow *option_window, const QString &name, const QImage &icon );
	virtual OptionWindow * getOptionWindow( ) const;

	virtual const QString & getName( ) const;
	virtual const QImage & getIcon( ) const;
	virtual QWidget * toWidget( ) = 0;
};
#endif // OPTIONPANEL_H_H_HEAD__FILE__
