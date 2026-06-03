#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__
#include <QMainWindow>

class MusicWidget;
class MainWindow : public QMainWindow {
	Q_OBJECT;
private:
	MusicWidget *musicWidget;
public:
	MainWindow( );
	~MainWindow( ) override;
	/// @brief 建议坐标与大小
	/// @param move_to_x 建议移动到横向坐标
	/// @param move_to_y 建议移动到纵向坐标
	/// @param reset_size_width 建议修改到宽度
	/// @param reset_size_height 建议修改到长度
	void suggestGeometry( int move_to_x, int move_to_y, int reset_size_width, int reset_size_height );
	/// @brief 获取建议坐标与大小
	/// @param move_to_x 返回建议移动到横向坐标
	/// @param move_to_y 返回建议移动到纵向坐标
	/// @param reset_size_width 返回建议修改到宽度
	/// @param reset_size_height 返回建议修改到长度
	void getSuggestGeometry( int &move_to_x, int &move_to_y, int &reset_size_width, int &reset_size_height ) const;
};

#endif // MAINWINDOW_H_H_HEAD__FILE__
