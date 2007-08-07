#include <QDialog>
#include <QWidget>
#include "defines.h"
#include "COneRun.h"

class QLabel;
class QSpinBox;
class QPushButton;
class QCheckBox;
class QRadioButton;

class NewEnvDialog:public QDialog
{
	Q_OBJECT

public:
	NewEnvDialog( QString mapFilePath, QString effFilePath ,QString beetlesFilePath , QWidget * parent=0, Qt::WindowFlags f= 0);
public:
	~NewEnvDialog(void);

private slots:
	void setBeetleFN();
	void setMapFN();
	void setEffFN();

public:
	
	void getData(COneRun * oneRun);

	QLabel * MapLabel;
	QLabel * EffLabel;
	QLabel * BeetleFileLabel;
	QLabel * EnergyLabel;
	QSpinBox * SeedSpin;
	QSpinBox * CostStepSpin;
	QSpinBox * CostRotSpin;
	QSpinBox * CostCopulSpin;
	QSpinBox * CostWaitSpin;
	QSpinBox * NumBeetlesSpin;
	QSpinBox * MutationSpin;
	QPushButton * MapBut;
	QPushButton * EffBut;
	QPushButton * BeetleFileBut;
	QCheckBox * StepOnFlowerCheck;	
	QCheckBox * NoExpectationsCheck;
	QRadioButton * RandomRadio;
	QRadioButton * BeetleFileRadio;

	QString BeetleFN;
	QString MapFN;
	QString EffFN;

};
