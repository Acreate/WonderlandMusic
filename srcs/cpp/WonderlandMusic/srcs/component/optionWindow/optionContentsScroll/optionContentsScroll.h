#ifndef OPTIONCONTENTSSCROLL_H_H_HEAD__FILE__
#define OPTIONCONTENTSSCROLL_H_H_HEAD__FILE__
#include <QScrollArea>

#include "../../../interface/iAppCore.h"

class OptionContentsWidget;
class OptionWindow;

class OptionContentsScroll : public QScrollArea, public IAppCore {
	Q_OBJECT;
	friend class OptionWindow;

private:
	OptionWindow *optionWindow = nullptr;
	OptionContentsWidget *optionContentsWidget = nullptr;

protected:
	OptionContentsScroll( OptionWindow *option_window );
	~OptionContentsScroll( ) override;
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
};

#endif // OPTIONCONTENTSSCROLL_H_H_HEAD__FILE__
