#include <QWidget>
#include "defines.h"

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
	void setEnvRef(CEnvironment * env);
	void setZoom(int);

//signals:

protected:
    void paintEvent(QPaintEvent *evnt);
	QImage * getBeetleImage(int zoom, char direction, QString & typeView);
	QRect * getCellRect(int x, int y, int zoom);

private:
	QString TypeView;
	CEnvironment * Env;
	int Zoom;

	int ZoomToSqSize[NUM_ZOOM] ;
	int ZoomToGapSize[NUM_ZOOM];

	
};
