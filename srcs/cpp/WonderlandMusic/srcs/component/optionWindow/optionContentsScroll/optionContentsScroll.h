#ifndef OPTIONCONTENTSSCROLL_H_H_HEAD__FILE__
#define OPTIONCONTENTSSCROLL_H_H_HEAD__FILE__
#include <QScrollArea>

#include "../../../interface/iAppCore.h"

class UserMutex;
class OptionPanel;
class OptionWindow;

class OptionContentsScroll : public QScrollArea, public IAppCore {
	Q_OBJECT;
	friend class OptionWindow;

private:
	OptionWindow *optionWindow = nullptr;
	UserMutex *userMutex = nullptr;
	OptionPanel *currentOptionPanel = nullptr;

protected:
	OptionContentsScroll( OptionWindow *option_window );
	~OptionContentsScroll( ) override;
	bool deleteResource( ) override;

	virtual void hideOptionPanel( OptionPanel *option_panel );
	virtual void showOptionPanel( OptionPanel *option_panel );

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	virtual void hideOptionPanel( );
	virtual void showOptionPanel( );
};

#endif // OPTIONCONTENTSSCROLL_H_H_HEAD__FILE__
