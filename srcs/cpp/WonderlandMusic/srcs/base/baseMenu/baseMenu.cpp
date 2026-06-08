#include "baseMenu.h"

#include <source_location>
BaseMenu::BaseMenu( QWidget *parent ) : QMenu( parent ), BaseClass( ) {
}
BaseMenu::BaseMenu( const QString &titile, QWidget *parent ) : QMenu( parent ), BaseClass( ) {
}
BaseMenu::BaseMenu( const QString &titile ) : QMenu( ), BaseClass( ) {
}
BaseMenu::BaseMenu( ) : QMenu( ), BaseClass( ) {
}
