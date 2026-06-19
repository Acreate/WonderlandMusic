#ifndef PLAYERWIDGETMENU_H_H_HEAD__FILE__
#define PLAYERWIDGETMENU_H_H_HEAD__FILE__

#include <QMenu>
class MusicInfoItemWidget;
class PlayerListWidget;

class PlayerWidgetMenu : public QMenu {
	Q_OBJECT;
	
protected:
	PlayerListWidget *playerListWidget;
	QVector< MusicInfoItemWidget * > musicInfoItemWidgetVector;

public:
	PlayerWidgetMenu( PlayerListWidget *player_list_widget );
	virtual bool init();
};

#endif // PLAYERWIDGETMENU_H_H_HEAD__FILE__
