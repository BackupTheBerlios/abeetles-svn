#include <QWidget>
#include "defines.h"

class QTimer;
class QPushButton;
class CEnvironment;
class QMouseEvent;
class QImage;
class CBeetle;
//typedef QRgb;


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
signals:
	void cellDetails(int x, int y);

protected:
    void paintEvent(QPaintEvent *evnt);
	QImage * getBeetleImage(CBeetle * beetle,int x, int y, int zoom,int typeView);
	QRect * getCellRect(int col, int row, int zoom);
	QPoint * getCellFromPoint(int x, int y, int zoom);
	virtual void mousePressEvent ( QMouseEvent * evnt );
	bool loadBeetleImages();
	bool change1ImgColor(QImage *, QRgb origColor, QRgb desiredColor);

private:
	int TypeView;
	CEnvironment * Env;
	int Zoom;

	int ZoomToSqSize[NUM_ZOOM] ;
	int ZoomToGapSize[NUM_ZOOM];
	QImage * ImgBeetle[NUM_ZOOM][4/*number of directions:W,N,E,S*/];//[NUM_TYPE_VIEW];

	
};
