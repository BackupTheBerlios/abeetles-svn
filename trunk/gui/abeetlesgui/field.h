#include <QWidget>

class QTimer;
class QPushButton;


class CField : public QWidget
{
	Q_OBJECT
public:

	CField(QWidget * Parent=0);

	int angle();

public slots:
	void setAngle(int angle);
	void startstop();
	void moveRect();
	void setTypeView(const QString& type);

signals:
	void angleChanged(int angle);

protected:
    void paintEvent(QPaintEvent *evnt);
	

private:
    int currentAngle;
	QString typeView;
public:
	QTimer * autoShootTimer;
	int x;
	
};
