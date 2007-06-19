#ifndef LABELEDLCD_H
#define LABELEDLCD_H

#include <QWidget>

//class QSlider; //preliminary declaration, file will be included later.
class QLabel;

class LabeledLCD : public QWidget
{
	Q_OBJECT

	public:
	LabeledLCD(QWidget*parent=0);
	LabeledLCD(const QString &labelText,QWidget*parent=0);
	int value() const;

	public  slots:
	void setValue(int newValue);

	signals:    //are alway protected
	void valueChanged(int newValue);

	private:
	void init(const QString & labelText);

	private:
	QLabel *Label; 
	int Value;


};

#endif
