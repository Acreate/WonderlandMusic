#include "settingWidgetTranslate.h"

#include <QObject>

bool SettingWidgetTranslate::init( ) {
	okBtnTxt = QObject::tr( "确定" );
	cancelBtnTxt = QObject::tr( "取消" );
	selectFileBtnTxt = QObject::tr( "选择文件..." );
	selectDirBtnTxt = QObject::tr( "选择目录..." );
	selectDirLinePlaceholderTxt = QObject::tr( "软件配置路径" );
	setectPathGroupTitle = QObject::tr( "配置路径" );
	selectDirPathDialogTitle = QObject::tr( "选择目录" );
	return true;
}

const QString & SettingWidgetTranslate::getOkBtnTxt( ) const {
	return okBtnTxt;
}

const QString & SettingWidgetTranslate::getCancelBtnTxt( ) const {
	return cancelBtnTxt;
}

const QString & SettingWidgetTranslate::getSelectFileBtnTxt( ) const {
	return selectFileBtnTxt;
}

const QString & SettingWidgetTranslate::getSelectDirBtnTxt( ) const {
	return selectDirBtnTxt;
}

const QString & SettingWidgetTranslate::getSelectDirLinePlaceholderTxt( ) const {
	return selectDirLinePlaceholderTxt;
}

const QString & SettingWidgetTranslate::getSetectPathGroupTitle( ) const {
	return setectPathGroupTitle;
}

const QString & SettingWidgetTranslate::getSelectDirPathDialogTitle( ) const {
	return selectDirPathDialogTitle;
}
