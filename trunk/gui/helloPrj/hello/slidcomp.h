#ifndef SLIDCOMP_H
#define SLIDCOMP_H

#include <QWidget>

class QSlider; //predbezna deklarace, soubor je includovan pozdeji.
class QLabel;

class SlidComp : public QWidget
{
	Q_OBJECT

	public:
	SlidComp(QWidget*parent=0);
	SlidComp(QString & labelText,QWidget*parent=0);
	int value() const;

	public  slots:
	void setValue(int newValue);

	signals:    //are alway protected
	void valueChanged(int newValue);

	private:
	void init(const QString & labelText);

	private:
	QSlider * Slider;
	QLabel *Label; 


};

#endif
