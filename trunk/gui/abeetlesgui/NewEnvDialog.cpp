#include "NewEnvDialog.h"
#include "Beetle.h"
#include "defines.h"
#include "COneRun.h"
#include <QtGui>
#include <QTime>

NewEnvDialog::NewEnvDialog( QWidget * parent, Qt::WindowFlags f):QDialog(parent,f)
{
	MapFN=MAP_BMP_FILE;
	EffFN= EFF_BMP_FILE;
	BeetleFN = DEFAULT_BEETLES_FILE;
	RandomRadio = new QRadioButton(tr("Random beetles"));
		RandomRadio->setChecked(true);
	QLabel * seedLabel = new QLabel("Seed: ");
	SeedSpin = new QSpinBox(); 
		SeedSpin->setMaximum(MAX_INT); 
		SeedSpin->setValue(( QTime::currentTime().msec() * QTime::currentTime().minute() ) % MAX_INT);

	QLabel * numBeetlesLabel = new QLabel("Number of beetles: ");
	NumBeetlesSpin = new QSpinBox();
		NumBeetlesSpin->setMaximum(G_WIDTH_MAX * G_HEIGHT_MAX);
		NumBeetlesSpin->setMinimum(-1);
		NumBeetlesSpin->setValue(100);

	QLabel * stepOnFlowerLabel = new QLabel("Use rule \"Step On Flower\"");
	StepOnFlowerCheck = new QCheckBox();	
		StepOnFlowerCheck->setCheckState(Qt::Checked);

	QLabel * noExpectationsLabel = new QLabel("Initially widest expectations");
	NoExpectationsCheck= new QCheckBox();
		NoExpectationsCheck->setCheckState(Qt::Checked);
	
	QGridLayout * randomGrid = new QGridLayout();
	randomGrid->addWidget(seedLabel,0,0);
	randomGrid->addWidget(SeedSpin,0,1);
	randomGrid->addWidget(numBeetlesLabel,1,0);
	randomGrid->addWidget(NumBeetlesSpin,1,1);
	randomGrid->addWidget(StepOnFlowerCheck,2,0,Qt::AlignRight);
	randomGrid->addWidget(stepOnFlowerLabel,2,1,Qt::AlignLeft);
	randomGrid->addWidget(NoExpectationsCheck,3,0,Qt::AlignRight);
	randomGrid->addWidget(noExpectationsLabel,3,1,Qt::AlignLeft);

	QGroupBox * randomGroup = new QGroupBox();
	randomGroup->setLayout(randomGrid);



	BeetleFileRadio = new QRadioButton(tr("Beetles from file"));
		BeetleFileRadio->setChecked(false);
	BeetleFileBut= new QPushButton("File of beetles");
	BeetleFileLabel = new QLabel("Default");
	connect(BeetleFileBut,SIGNAL(pressed()),this,SLOT(setBeetleFN()));
	

	QHBoxLayout * beetleFileLayout = new QHBoxLayout();
	beetleFileLayout->addWidget(BeetleFileBut);
	beetleFileLayout->addWidget(BeetleFileLabel);

	QGroupBox * beetleFileGroup = new QGroupBox();
	beetleFileGroup->setEnabled (false);
	beetleFileGroup->setLayout(beetleFileLayout);


	connect(RandomRadio,SIGNAL(toggled(bool)),randomGroup,SLOT(setEnabled(bool))); 
	connect(BeetleFileRadio,SIGNAL(toggled(bool)),beetleFileGroup,SLOT(setEnabled(bool))); 


	MapLabel = new QLabel("Default");
	MapBut= new QPushButton("Map");
	connect(MapBut,SIGNAL(pressed()),this,SLOT(setMapFN()));
	EffLabel = new QLabel("Default");
	EffBut= new QPushButton("Energy From Flower");	
	connect(EffBut,SIGNAL(pressed()),this,SLOT(setEffFN()));

	QLabel * mutationLabel = new QLabel("Probability of mutation: ");
	MutationSpin = new QSpinBox();MutationSpin->setMaximum(10);MutationSpin->setMinimum(0);MutationSpin->setValue(MUTATION_PROB_DEFAULT);

	QLabel * costsLabel = new QLabel("Costs of Actions: ");
	QLabel * costStepLabel = new QLabel("Step: ");
	QLabel * costRotLabel = new QLabel("Rotation: ");
	QLabel * costCopulLabel = new QLabel("Copulation: ");
	QLabel * costWaitLabel = new QLabel("Waiting: ");
	CostStepSpin = new QSpinBox();CostStepSpin->setMaximum(10);CostStepSpin->setMinimum(1);CostStepSpin->setValue(1);
	CostRotSpin = new QSpinBox();CostRotSpin->setMaximum(10);CostRotSpin->setMinimum(1);CostRotSpin->setValue(1);
	CostCopulSpin = new QSpinBox();CostCopulSpin->setMaximum(10);CostCopulSpin->setMinimum(1);CostCopulSpin->setValue(1);
	CostWaitSpin = new QSpinBox();CostWaitSpin->setMaximum(10);CostWaitSpin->setMinimum(1);CostWaitSpin->setValue(1);

	QPushButton * okBut = new QPushButton(tr("OK"));
	connect(okBut,SIGNAL(clicked()),this,SLOT(accept()));
	okBut->setDefault(true);

	QPushButton * cancelBut = new QPushButton(tr("Cancel"));
	connect(cancelBut,SIGNAL(clicked()),this,SLOT(reject()));

	QGridLayout * bottomGrid = new QGridLayout ();
	bottomGrid->addWidget(MapBut,0,0);
	bottomGrid->addWidget(MapLabel,0,1);
	bottomGrid->addWidget(EffBut,1,0);
	bottomGrid->addWidget(EffLabel,1,1);
	bottomGrid->addWidget(mutationLabel,2,0);
	bottomGrid->addWidget(MutationSpin,2,1);
	bottomGrid->addWidget(costsLabel,3,0,1,2);
	bottomGrid->addWidget(costStepLabel,4,0);
	bottomGrid->addWidget(CostStepSpin,4,1);
	bottomGrid->addWidget(costRotLabel,5,0);
	bottomGrid->addWidget(CostRotSpin,5,1);
	bottomGrid->addWidget(costCopulLabel,6,0);
	bottomGrid->addWidget(CostCopulSpin,6,1);
	bottomGrid->addWidget(costWaitLabel,7,0);
	bottomGrid->addWidget(CostWaitSpin,7,1);
	bottomGrid->addWidget(okBut,8,0,Qt::AlignCenter);
	bottomGrid->addWidget(cancelBut,8,1,Qt::AlignCenter);



    QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(RandomRadio);
	layout->addWidget(randomGroup);
	layout->addWidget(BeetleFileRadio);
	layout->addWidget(beetleFileGroup);
	layout->addLayout(bottomGrid);


	setLayout(layout);
    setWindowTitle(tr("Settings of New Environment"));
}

NewEnvDialog::~NewEnvDialog(void)
{
}


void NewEnvDialog::setBeetleFN()
{
	QFileDialog openDlg;
	openDlg.setFilter("(*.txt)");
	openDlg.setFilter("All files (*.*)");
    if (!(BeetleFN = openDlg.getOpenFileName(this)).isNull());
		BeetleFileLabel->setText(BeetleFN);
}

void NewEnvDialog::setMapFN()
{
	QFileDialog openDlg;
	openDlg.setFilter("(*.bmp)");
	openDlg.setFilter("All files (*.*)");
    if (!(MapFN = openDlg.getOpenFileName(this)).isNull());
		MapLabel->setText(MapFN);
}

void NewEnvDialog::setEffFN()
{
	QFileDialog openDlg;
	openDlg.setFilter("(*.bmp)");
	openDlg.setFilter("All files (*.*)");
    if (!(EffFN = openDlg.getOpenFileName(this)).isNull());
		EffLabel->setText(EffFN);
}

void NewEnvDialog::getData(COneRun * oneRun)
{
	if (RandomRadio->isChecked()==true)
	{
		oneRun->IsBtlRandom=true;
		oneRun->Seed = SeedSpin->value();
		oneRun->NumRandBeetles = NumBeetlesSpin->value();
		if (StepOnFlowerCheck->checkState()==Qt::Checked) oneRun->IsStepOnFlower=true;
		else oneRun->IsStepOnFlower=false;
		oneRun->BeetlesFN="";
		if (NoExpectationsCheck->checkState()==Qt::Checked) oneRun->IsNoExpectations=true;
		else oneRun->IsNoExpectations=false;
	}
	else
	{
		oneRun->IsBtlRandom=false;
		oneRun->BeetlesFN = BeetleFN;
	}

	oneRun->EffFN = EffFN;
	oneRun->MapFN = MapFN;
	oneRun->MutationProb = MutationSpin->value();
	oneRun->StepCost =CostStepSpin->value();
	oneRun->RotCost = CostRotSpin->value();
	oneRun->CopulCost = CostCopulSpin->value();
	oneRun->WaitCost = CostWaitSpin->value();

}

