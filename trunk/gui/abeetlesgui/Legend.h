#include <QWidget>
#include "defines.h"

class QPushButton;
class QImage;


class CLegend : public QWidget
{
	Q_OBJECT
public:

	CLegend(QWidget * parent=0);


public slots:
	void setTypeView(const QString& type);

//signals:

protected:
    void paintEvent(QPaintEvent *evnt);

private:
	int TypeView;
	
};
