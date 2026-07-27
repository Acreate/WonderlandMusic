#ifndef OPTIONPANEL_H_H_HEAD__FILE__
#define OPTIONPANEL_H_H_HEAD__FILE__
#include <QWidget>

#include "../../../interface/iAppCore.h"
#include "../../../interface/iAppJsonData.h"
class OptionContentsScroll;
class OptionButton;
class CoreInfo;
class OptionWindow;

class OptionPanel : public IAppCore, public IAppJsonData {
private:
	friend class OptionWindow;

	OptionWindow *optionWindow = nullptr;
	OptionButton *optionButton = nullptr;
	OptionContentsScroll *optionContentsScroll = nullptr;
	QString *name;
	QImage *icon;

protected:
	~OptionPanel( ) override;
	virtual void setVerticalScrollBarPolicy( Qt::ScrollBarPolicy policy );
	virtual void setHorizontalScrollBarPolicy( Qt::ScrollBarPolicy policy );

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
};
#endif // OPTIONPANEL_H_H_HEAD__FILE__
