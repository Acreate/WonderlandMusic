#ifndef OPTIONWINDOW_H_H_HEAD__FILE__
#define OPTIONWINDOW_H_H_HEAD__FILE__
#include <QMainWindow>
#include "../../interface/iAppCore.h"
#include "../../interface/iAppJsonData.h"
#include "../../interface/iAppResourceCore.h"
class OptionButton;
class OptionListDockWidget;
class OptionListWidget;
class UserMutex;
class OptionPanel;
class OptionItem;

class OptionWindow : public QMainWindow, public IAppCore, public IAppJsonData, public IAppResourceCore {
	Q_OBJECT;
	friend class OptionPanel;
	friend class OptionButton;

protected:
	UserMutex *mutex = nullptr;
	OptionListDockWidget *optionListDockWidget = nullptr;
	std::vector< OptionPanel * > optionPanelVector;
	OptionPanel *currentOptionPanelWidget = nullptr;

protected :
	virtual void removeOptionPanel( OptionPanel *option_panel );
	virtual size_t removeAllOptionPanel( std::vector< OptionPanel * > &result_remove_panel );
	virtual size_t removeAllOptionPanel( ) {
		std::vector< OptionPanel * > resultRemovePanel;
		return removeAllOptionPanel( resultRemovePanel );
	}

	virtual bool hideOptionPanel( );
	virtual bool hideOptionPanel( OptionPanel *option_panel );

public:
	OptionWindow( );
	~OptionWindow( ) override;
	virtual void updateOptionPanelInfo( OptionPanel *option_panel );
	virtual bool addOptionPanel( OptionPanel *option_panel );
	virtual bool getOptionPanelIndex( size_t &result_index, const OptionPanel *option_panel );
	virtual bool getOptionButtonIndex( size_t &result_index, const OptionButton *option_button );
	virtual bool moveOptionPanelIndex( const OptionPanel *option_panel, const size_t &target_index );
	virtual void updateWindow( );
	virtual bool showOptionButton( OptionButton *option_button );
	virtual bool setOptionPanelName( OptionPanel *option_panel, const QString &name );
	virtual bool setOptionPanelIcon( OptionPanel *option_panel, const QImage &icon );

	virtual bool showOptionPanel( );
	virtual bool showOptionPanel( OptionPanel *option_panel );

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
Q_SIGNALS:
	void signal_show_OptionPanel( OptionPanel *option_panel );
};
#endif // OPTIONWINDOW_H_H_HEAD__FILE__
