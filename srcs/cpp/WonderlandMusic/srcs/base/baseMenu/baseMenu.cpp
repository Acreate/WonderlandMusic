#include "baseMenu.h"

#include <source_location>
BaseMenu::BaseMenu( QWidget *parent ) : BaseMenu( "", parent ) {
}
BaseMenu::BaseMenu( const QString &titile, QWidget *parent ) : QMenu( parent ), BaseClass( ) {
}
BaseMenu::BaseMenu( const QString &titile ) : BaseMenu( titile, nullptr ) {
}
BaseMenu::BaseMenu( ) : BaseMenu( "", nullptr ) {
}
