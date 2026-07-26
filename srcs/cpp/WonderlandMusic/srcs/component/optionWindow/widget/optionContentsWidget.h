#ifndef OPTIONCONTENTSWIDGET_H_H_HEAD__FILE__
#define OPTIONCONTENTSWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include "../../../interface/iAppCore.h"

class UserMutex;
class OptionPanel;
class OptionWindow;

class OptionContentsWidget : public QWidget, public IAppCore {
	Q_OBJECT;
	friend class OptionWindow;
	friend class OptionContentsScroll;

protected:
	OptionWindow *listParentWindow;
	UserMutex *userMutex = nullptr;
	std::vector< OptionPanel * > optionPanelVector;
	~OptionContentsWidget( ) override;

public:
	OptionContentsWidget( OptionWindow *parent );

	virtual void showOptionPanel( OptionPanel *option_panel );
	virtual void addOptionPanel( OptionPanel *option_panel );
	virtual void deleteOptionPanel( OptionPanel *option_panel );
	virtual bool hasOptionPanel( size_t &result_index, const OptionPanel *option_panel );
	virtual void updateOptionPanelLayout( );
	virtual int getSuggestWidth( ) const;
	virtual int getSuggestHeight( ) const;
	virtual QSize getSuggestSize( ) const;

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
};

#endif // OPTIONCONTENTSWIDGET_H_H_HEAD__FILE__
