#include "pathSettingWidget.h"

#include <QLabel>

#include "../optionStackWidget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
PathSettingWidget::PathSettingWidget( OptionStackWidget *parent ) : QWidget( parent ), optionStackWidget( parent ) {
	loadFileInfoPathEditInputLine = new QLineEdit( this );
	loadFileInfoPathSelectBtn = new QPushButton( tr( "路径选择..." ), this );
	loadFileInfoPathText = new QLabel( tr( "音乐列表保存路径" ) + ":", this );

	auto mainLayout = new QVBoxLayout( this );
	auto subWidget = new QWidget( this );
	mainLayout->addWidget( subWidget, 0, Qt::AlignmentFlag::AlignTop );
	auto subLayout = new QHBoxLayout( subWidget );
	subLayout->setSpacing( 0 );
	subLayout->setContentsMargins( 0, 0, 0, 0 );
	subLayout->addWidget( loadFileInfoPathText, 2 );
	subLayout->addWidget( loadFileInfoPathEditInputLine, 26 );
	subLayout->addWidget( loadFileInfoPathSelectBtn, 2 );
}
QString PathSettingWidget::getLoadFileInfoPath( ) const {
	return loadFileInfoPathEditInputLine->text( );
}
void PathSettingWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );

}
