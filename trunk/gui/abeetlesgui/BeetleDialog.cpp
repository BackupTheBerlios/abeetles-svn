#include "BeetleDialog.h"
#include "Beetle.h"
#include "defines.h"
#include <QtGui>

BeetleDialog::BeetleDialog( CBeetle * beetle,QWidget * parent, Qt::WindowFlags f):QDialog(parent,f)
{
	AgeLabel=new QLabel("Age: "+QString::number(beetle->Age));
	DirectionLabel=new QLabel("Direction: "+CBeetle::GetWordDirection(beetle->Direction));
	EnergyLabel=new QLabel("Energy: "+QString::number(beetle->Energy));
	HungryThresholdLabel=new QLabel("HungryThreshold: "+QString::number(beetle->HungryThreshold));
	IdLabel=new QLabel("Id: "+QString::number(beetle->Id));
	InvInChildLabel=new QLabel("InvInChild: "+QString::number(beetle->InvInChild));
	LearnAbilityLabel=new QLabel("LearnAbility: "+QString::number(beetle->LearnAbility));
	NumChildrenLabel=new QLabel("NumChildren: "+QString::number(beetle->NumChildren));
	QLabel  * effLabel=new QLabel("Energy from a flower according to age(up to age "+QString::number(CBeetle::EffImg->width())+"): ");
	EffField * effField =  new EffField();

	int I,J;
	QGridLayout * gridBrain =  new QGridLayout;
	for (I=0; I<BRAIN_D1;I++)
		for(J=0;J<BRAIN_D2;J++)
		{
			BrainTables[I][J]= new QTableWidget(BRAIN_D3,BRAIN_D4);
			gridBrain->addWidget(BrainTables[I][J],I,J);
		}
			
	
	

	QPushButton * okBut = new QPushButton(tr("OK"));
	connect(okBut,SIGNAL(clicked()),this,SLOT(accept()));

	
    QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(AgeLabel);
	layout->addWidget(DirectionLabel);
	layout->addWidget(EnergyLabel);
	layout->addWidget(HungryThresholdLabel);
	layout->addWidget(IdLabel);
	layout->addWidget(InvInChildLabel);
	layout->addWidget(LearnAbilityLabel);
	layout->addWidget(NumChildrenLabel);
	layout->addWidget(effLabel);
	layout->addWidget(effField);
	layout->addLayout(gridBrain);
	layout->addWidget(okBut);

	setLayout(layout);
    setWindowTitle(tr("Beetle's Details Dialog"));
}

BeetleDialog::~BeetleDialog(void)
{
}


//******************************EffField methods*********************************
EffField::EffField(QWidget *parent):QWidget(parent)
{
	setPalette(QPalette(QColor(250, 250, 200)));
    setAutoFillBackground(true);
	if (CBeetle::EffImg==NULL)
		setFixedSize(QSize(0,0));
	else setFixedSize(CBeetle::EffImg->width(),CBeetle::EffImg->height());
	update();
}

void EffField::paintEvent(QPaintEvent *evnt)
{
	QPainter painter(this);
	
	//painter.drawText(5,5,tr("Time: "));

	painter.setPen(Qt::NoPen);
	
	if (NULL != CBeetle::EffImg)	
		painter.drawImage(0,0,*CBeetle::EffImg);
			
}

