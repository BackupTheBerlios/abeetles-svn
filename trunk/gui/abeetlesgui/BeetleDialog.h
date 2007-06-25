#include <QDialog>
#include <QWidget>

class QLabel;
class CBeetle;

class BeetleDialog:public QDialog
{
	Q_OBJECT

public:
	BeetleDialog(CBeetle * beetle=0,QWidget * parent = 0, Qt::WindowFlags f = 0);
public:
	~BeetleDialog(void);

protected:
	QLabel * AgeLabel;
	QLabel * DirectionLabel;
	QLabel * EnergyLabel;
	//QLabel * Label;
	QLabel * HungryThresholdLabel;
	QLabel * IdLabel;
	QLabel * InvInChildLabel;
	QLabel * LearnAbilityLabel;
	QLabel * NumChildrenLabel;

};
