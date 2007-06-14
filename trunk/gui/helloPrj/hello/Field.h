#include <QWidget>

class QTimer;
class QPushButton;


class Field : public QWidget
{
	Q_OBJECT
public:

	Field(QWidget * Parent=0);

	int angle();

public slots:
	void setAngle(int angle);
	void startstop();
	void moveRect();

signals:
	void angleChanged(int angle);

protected:
    void paintEvent(QPaintEvent *evnt);
	

private:
    int currentAngle;
public:
	QTimer * autoShootTimer;
	int x;
	
};
