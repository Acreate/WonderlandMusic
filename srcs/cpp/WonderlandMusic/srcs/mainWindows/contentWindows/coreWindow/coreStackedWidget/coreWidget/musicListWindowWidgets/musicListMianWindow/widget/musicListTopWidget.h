#ifndef MUSICLISTTOPWIDGET_H_H_HEAD__FILE__
#define MUSICLISTTOPWIDGET_H_H_HEAD__FILE__

#include <base/baseWidget/baseWidget.h>
class PlayerListItem;
class FontRender;
class StringFontSize;
class MusicListTopWidget : public BaseWidget {
	Q_OBJECT;
public:
	class ItemInfo {
		friend class MusicListTopWidget;
	private:
		FontRender *fontRender;
		int offsetX;
	protected:
		ItemInfo( const QString &txt );
	public:
		ItemInfo( const ItemInfo &other ) = delete;
		ItemInfo( ItemInfo &&other ) = delete;
		ItemInfo & operator=( const ItemInfo &other ) = delete;
		ItemInfo & operator=( ItemInfo &&other ) = delete;
		virtual ~ItemInfo( );
		virtual FontRender * getFontRender( ) const;
		virtual int getWidth( ) const;
		virtual int getHeight( ) const;
		virtual int getOffsetX( ) const;
	};
protected:
	PlayerListItem *playerListItem;
	/// @brief 整体绘制
	QImage *drawBuff;
private:
	void initItemSize( const FontRender &font_render, int &result_width, int &result_height ) const;
public:
	MusicListTopWidget( QWidget *parent );
	~MusicListTopWidget() override;
protected:
	void resizeEvent( QResizeEvent *event ) override;
	void paintEvent( QPaintEvent *event ) override;
};

#endif // MUSICLISTTOPWIDGET_H_H_HEAD__FILE__
