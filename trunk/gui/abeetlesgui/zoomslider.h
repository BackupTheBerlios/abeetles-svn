#ifndef SLIDCOMP_H
#define SLIDCOMP_H

#include <QWidget>

class QSlider; //predbezna deklarace, soubor je includovan pozdeji.
class QLabel;

class ZoomSlider : public QWidget
{
	Q_OBJECT

	public:
	ZoomSlider(QWidget*parent=0);
	ZoomSlider(const QString & labelText,QWidget*parent=0);
	int value() const;

	public  slots:
	void setValue(int newValue);
	void setDisabled(bool isDis);

	signals:    //are alway protected
	void valueChanged(int newValue);

	private:
	void init(const QString & labelText);

	private:
	QSlider * Slider;
	QLabel *Label; 
	int counterDisable;


};

#endif
