#ifndef OPTIONWINDOW_H_H_HEAD__FILE__
#define OPTIONWINDOW_H_H_HEAD__FILE__
#include <QMainWindow>
#include "../../interface/iAppCore.h"
#include "../../interface/iAppJsonData.h"
class UserMutex;
class OptionPanel;
class OptionItem;

class OptionWindow : public QMainWindow, public IAppCore, public IAppJsonData {
	Q_OBJECT;

protected:
	UserMutex *mutex = nullptr;
	std::vector< OptionPanel * > optionPanelVector;

protected Q_SLOTS:
	void removeOptionPanel( OptionPanel *option_item );

public:
	OptionWindow( QWidget *paretn );
	~OptionWindow( ) override;
	virtual void updateOptionPanelInfo( OptionPanel *option_panel );
	virtual void deleteOptionPanel( OptionPanel *option_item );
	virtual bool addOptionPanel( OptionPanel *option_panel );
	virtual bool getOptionPanelIndex( size_t &result_index, const OptionPanel *option_panel );
	virtual bool moveOptionPanelIndex( const OptionPanel *option_panel, const size_t &target_index );
	virtual void updateWindow( );

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
};
#endif // OPTIONWINDOW_H_H_HEAD__FILE__
