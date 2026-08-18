#ifndef OPTIONPANEL_H_H_HEAD__FILE__
#define OPTIONPANEL_H_H_HEAD__FILE__
#include <QWidget>

#include <interface/iAppCore.h>
class OptionButton;
class CoreInfo;
class OptionWindow;

class OptionPanel : public IAppCore {
private:
	friend class OptionWindow;

	OptionWindow *optionWindow = nullptr;
	OptionButton *optionButton = nullptr;
	QString *name;
	QImage *icon;

protected:
	~OptionPanel( ) override;

public:
	OptionPanel( );
	OptionPanel( const QString &name );
	OptionPanel( const QImage &icon );
	OptionPanel( const QString &name, const QImage &icon );
	virtual OptionWindow * getOptionWindow( ) const;

public:
	virtual const QString & getName( ) const;
	virtual const QImage & getIcon( ) const;
	virtual void setName( const QString &name );
	virtual void setIcon( const QImage &icon );
	virtual QWidget * toWidget( ) = 0;
	virtual bool showPanelBefore( ) = 0;
	virtual bool hidePanelBefore( ) = 0;
	virtual bool releasePanelBefore( ) = 0;
};

#endif // OPTIONPANEL_H_H_HEAD__FILE__
