#ifndef OPTIONLISTWIDGET_H_H_HEAD__FILE__
#define OPTIONLISTWIDGET_H_H_HEAD__FILE__

#include <QWidget>
#include "../../../interface/iAppCore.h"
class OptionListDockWidget;
class QDockWidget;
class OptionWindow;
class UserMutex;
class OptionButton;
class OptionItem;
class QScrollArea;

class OptionListWidget : public QWidget, public IAppCore {
	Q_OBJECT;

protected:
	OptionWindow *listParentWindow;
	UserMutex *mutex = nullptr;
	std::vector< OptionButton * > optionButtonVector;
	int suggestWidth;
	int suggestHeight;

	virtual void resetUpdateOptionButton( const std::vector< OptionButton * > &option_buttons );

public:
	OptionListWidget( OptionWindow *parent );
	~OptionListWidget( ) override;
	virtual void addOptionButton( OptionButton *option_item );
	virtual void removeOptionButton( OptionButton *option_item );
	virtual void removeAllOptionButton( );
	virtual bool hasOptionButton( size_t &result_index, const OptionButton *option_item );
	virtual void updateOptionButtonLayout( );
	virtual int getSuggestWidth( ) const;
	virtual int getSuggestHeight( ) const;
	virtual QSize getSuggestSize( ) const;
	virtual void toSuggestSize( );
	virtual void setSuggestSize( );

protected:
	void paintEvent( QPaintEvent *event ) override;

	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
Q_SIGNALS:
	void signal_click_item( OptionButton *option_button );
};
#endif // OPTIONLISTWIDGET_H_H_HEAD__FILE__
