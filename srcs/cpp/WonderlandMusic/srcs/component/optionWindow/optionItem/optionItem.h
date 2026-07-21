#ifndef OPTIONITEM_H_H_HEAD__FILE__
#define OPTIONITEM_H_H_HEAD__FILE__
#include <QObject>
class QImage;
class QString;
class OptionPanel;
class IAppCore;
class IAppJsonData;
class OptionWindow;

class OptionItem : public QObject {
	Q_OBJECT;
	friend class OptionPanel;

public:
	enum class Show_Type {
		Txt,
		Icon,
		All
	};

protected:
	OptionPanel *optionPanel;
	Show_Type showType = Show_Type::All;
	~OptionItem( ) override;
	OptionItem( Show_Type show_type );

public:
	virtual const QString & getName( ) const;
	virtual void setName( const QString &name );
	virtual const QImage & getIcon( ) const;
	virtual void setIcon( const QImage &icon );
	virtual Show_Type getShowType( ) const;
	virtual void setShowType( const Show_Type show_type );
	virtual OptionPanel * getOptionPanel( ) const;
Q_SIGNALS:
	void signal_delete_OptionPanel( OptionPanel *option_panel );
};
#endif // OPTIONITEM_H_H_HEAD__FILE__
