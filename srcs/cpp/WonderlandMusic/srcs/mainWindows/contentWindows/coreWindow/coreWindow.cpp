#include "coreWindow.h"

#include "../contentWindow.h"
CoreWindow::CoreWindow( ContentWindow *parent ) : QMainWindow( parent ), contentWindow( parent ) {

}
