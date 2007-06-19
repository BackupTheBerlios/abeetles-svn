#include <QWidget>


class QTimer;
class QPushButton;
class CEnvironment;


class CField : public QWidget
{
	Q_OBJECT
public:

	CField(CEnvironment * env,QWidget * parent=0);


public slots:
	void setTypeView(const QString& type);
	void renewField();

//signals:

protected:
    void paintEvent(QPaintEvent *evnt);
	

private:
	QString typeView;
	CEnvironment * Env;
	int Zoom;
public:
	
};
