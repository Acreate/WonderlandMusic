#include "aboutWidget.h"
#include <QDir>
#include <QLabel>
#include <qstyle.h>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QLibraryInfo>
#include "../application/appDataJsonKey.h"
#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/applicationManage.h"
#include "../application/jsonKey/aboutWidgetJsonKey.h"
#include "../application/translate/aboutWidgetTranslate.h"

#include "../head/release_macro.h"

#include "../msgInfo/messageErrorOut.h"
#include "../tools/appTranslateTools.h"

AboutWidget::AboutWidget( OptionWindow *parent ) : OptionPanel( ) {
}

bool AboutWidget::init( ) {
	auto applicationInstance = AppInstance::getAppInstance( );

	bool aboutWidget = AppTranslateTools::getAboutWidget( [this, applicationInstance] ( AboutWidgetTranslate &translate ) {
		auto &titleName = translate.getTitleName( );
		setName( titleName );
		setWindowTitle( QString( applicationInstance->getApplicationManage( )->applicationName( ) + " " + titleName ) );
	} );
	if( aboutWidget == false ) {
		auto titleName = tr( "关于" );
		setName( titleName );
		setWindowTitle( QString( applicationInstance->getApplicationManage( )->applicationName( ) + " " + titleName ) );
	}
	mainLayout->setContentsMargins( 0, 0, 0, 0 );
	mainLayout->setSpacing( 0 );
	QStyle *stylePtr = style( );
	auto icon = stylePtr->standardPixmap( QStyle::SP_TitleBarMenuButton );
	icon = icon.scaled( 64, 64 );
	qtIco->setPixmap( icon );

	auto jsonFileKey = applicationInstance->getAppDataManage( )->getAppDataJsonKey( );
	auto aboutWidgetJsonFileKey = jsonFileKey->getAboutWidget( );
	auto logoIconPath = aboutWidgetJsonFileKey->getQtLogoIconPath( );
	QFileInfo fileInfo( logoIconPath );
	QImage qImage;
	if( fileInfo.exists( ) == false ) {
		Message_Error_Out << tr( "Qt 标识图像不存在" ) + " : " + logoIconPath;
		qImage.load( ":/qt-project.org/qmessagebox/images/qtlogo-64.png" );
	} else if( qImage.load( logoIconPath ) == false ) {
		Message_Error_Out << tr( "Qt 标识图像加载失败，重新使用 .rc 资源" ) + " : " + logoIconPath;
		qImage.load( ":/qt-project.org/qmessagebox/images/qtlogo-64.png" );
	}

	auto pixmap = QPixmap::fromImage( qImage );
	qtIco->setPixmap( pixmap );
	textBox->setReadOnly( true );
	textBox->setText( getSoftwareProtocolInfo( ) );
	textBox->setAutoFormatting( QTextEdit::AutoAll );
	return true;
}

AboutWidget::~AboutWidget( ) {
	deleteResource( );
}

bool AboutWidget::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( textBox );
	Delete_Resource_App_Core_Ptr( qtIco );
	Delete_Resource_App_Core_Ptr( mainLayout );
	return true;
}
QWidget * AboutWidget::toWidget( ) {
	return this;
}

bool AboutWidget::initBefore( ) {
	deleteResource( );
	mainLayout = new QHBoxLayout( this );

	qtIco = new QLabel( this );

	mainLayout->addWidget( qtIco, 0, Qt::AlignTop );

	textBox = new QTextEdit( this );
	mainLayout->addWidget( textBox );

	return true;
}

bool AboutWidget::initAfter( ) {
	return true;
}

bool AboutWidget::getJsonData( QJsonObject &get_json_object ) const {
	return true;
}

bool AboutWidget::setJsonData( const QJsonObject &set_json_object ) {
	return true;
}

QString AboutWidget::getSoftwareProtocolInfo( ) {
	QString softInfo;
	// ===== 1. 软件基础信息（自定义）
	softInfo += "<h3 style='color:#2980b9;margin:0;padding:0;'>" + tr( "📄 软件编译&运行协议信息" ) + "</h3><hr/>";
	softInfo += "<p><b>" + tr( "软件版本：" ) + QString( "</b>%1</p>" ).arg( QString( "V0.0.1" ) );

	auto compileDateTime = QDateTime(
		QDate::fromString( __DATE__, QString( "MMM dd yyyy" ) ),
		QTime::fromString( __TIME__, QString( "hh:mm:ss" ) )
		);
	softInfo += "<p><b>" + tr( "编译时间：" ) + QString( "</b>%1</p>" ).arg( compileDateTime.toString( "yyyy" + tr( "年" ) + "MM" + tr( "月" ) + "dd" + tr( "日" ) + " hh" + tr( "时" ) + "mm" + tr( "分" ) + "ss" + tr( "秒" ) + ".zzz" ) );

	// ===== 2. Qt核心协议/版本信息（重中之重）
	softInfo += "<p><b>▷ " + tr( "Qt 编译协议信息" ) + "</b></p>";
	softInfo += "<p>" + tr( "Qt库版本" ) + QString( "：</p><p style='padding-left:20px;'>%1</p>" ).arg( QT_VERSION_STR );
#ifdef QT_DEBUG
	softInfo += "<p>" + tr( "Qt编译模式" ) + "：</p><p style='padding-left:20px;color:red;'>" + tr( "调试版" ) + "</p>";
#else
	softInfo += "<p>" + tr( "Qt编译模式" ) + "：</p><p style='padding-left:20px;color:red;'>" + tr( "发布版" ) + "</p>";
#endif
	softInfo += "<p>" + tr( "Qt构建架构" ) + QString( "：</p><p style='padding-left:20px;'>%1 位</p>" ).arg( QSysInfo::WordSize );
	softInfo += "<p>" + tr( "Qt 库构建架构类型" ) + QString( "：</p><p style='padding-left:20px;'>%1</p>" ).arg( QLibraryInfo::isSharedBuild( ) ? tr( "动态库" ) : tr( "静态库" ) );

	// ===== 3. 编译器协议/版本信息（软件编译核心协议）
	softInfo += "<p><b>▷" + tr( " 编译器协议信息" ) + "</b></p>";
#ifdef _MSC_VER
	softInfo += "<p>" + tr( "编译器" ) + QString( "：</p><p style='padding-left:20px;'>MSVC %1</p>" ).arg( QString::number( _MSC_VER / 100.0, 'f', 1 ) );
	softInfo += "<p>" + tr( "编译协议" ) + "：</p><p style='padding-left:20px;'>" + tr( "VC++ 运行时协议" ) + "</p>";
#elif __GNUC__
	softInfo += "<p>" + tr( "编译器)" + QString( "：</p><p style='padding-left:20px;'>GCC %1.%2</p>" ).arg( __GNUC__ ).arg( __GNUC_MINOR__ );
	softInfo += "<p>" + tr( "编译协议" ) + "：</p><p style='padding-left:20px;'>GNU 开源协议 (GPL)</p>";
#elif __clang__
	softInfo += "<p>" + tr( "编译器" ) + "：</p><p style='padding-left:20px;'>Clang</p>";
	softInfo += "<p>" + tr( "编译协议" ) + "：</p><p style='padding-left:20px;'>LLVM " + tr( "开源协议" ) + "</p>";
#else
	softInfo += "<p>" + tr( "编译器" ) + "：</p><p style='padding-left:20px;'>" + tr( "未知编译器" ) + "</p>";
#endif

	// ===== 4. 系统运行协议/环境信息
	softInfo += "<p><b>▷ " + tr( "系统运行协议信息" ) + "</b></p>";
	softInfo += "<p>" + tr( "操作系统" ) + QString( "：</p><p style='padding-left:20px;'>%1</p>" ).arg( QSysInfo::prettyProductName( ) );
	softInfo += "<p>" + tr( "系统架构" ) + QString( "：</p><p style='padding-left:20px;'>%1</p>" ).arg( QSysInfo::currentCpuArchitecture( ) );
	softInfo += "<p>" + tr( "系统内核" ) + QString( "：</p><p style='padding-left:20px;'>%1</p>" ).arg( QSysInfo::kernelType( ) + " " + QSysInfo::kernelVersion( ) );
	softInfo += "<p>" + tr( "运行协议" ) + "：</p><p style='padding-left:20px;'>" + tr( "本地系统原生协议" ) + "</p>";

	// ===== 5. 软件版权协议（必加）

	QStringList stringList;
	QString pStyle( "style='color:#3c8e51;text-align:center;'" );
	stringList.append( QString( "<p %2 >%1</p>" ).arg( tr( "©2025 本软件包含的贡献均属于其各自所有者的版权。" ) ).arg( pStyle ) );
	stringList.append( QString( "<p %2 >%1</p>" ).arg( tr( "Qt 及其相应标识均为 Qt 公司有限公司在芬兰及其他国家/地区的商标。" ) ).arg( pStyle ) );
	stringList.append( QString( "<p %2 >%1</p>" ).arg( tr( "所提供的 QT 库受 %1 许可证限制。" ).arg( "LGPL 3.0" ) ).arg( pStyle ) );
	stringList.append( QString( "<p %2 >%1</p>" ).arg( tr( "所有其他商标均归其各自所有者所有。" ) ).arg( pStyle ) );
	pStyle = QStringLiteral( "style='color:#0079ff;text-align:center;'" );
	stringList.append( QString( "<p %2 >%1</p>" ).arg( QString( "gitee : <a href='https://gitee.com/ChenYLhuman/WonderlandMusic'>https://gitee.com/ChenYLhuman/WonderlandMusic</a>" ) ).arg( pStyle ) );
	stringList.append( QString( "<p %2 >%1</p>" ).arg( QString( "github : <a href='https://github.com/Acreate/WonderlandMusic'>https://github.com/Acreate/WonderlandMusic</a>" ) ).arg( pStyle ) );
	softInfo += QString( "<hr/>" ) + stringList.join( QString( "\n" ) );

	return softInfo;
}
