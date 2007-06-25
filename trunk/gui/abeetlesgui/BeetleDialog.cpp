#include "BeetleDialog.h"
#include "Beetle.h"
#include <QtGui>

BeetleDialog::BeetleDialog( CBeetle * beetle,QWidget * parent, Qt::WindowFlags f):QDialog(parent,f)
{
	AgeLabel=new QLabel("Age: "+QString::number(beetle->Age));
	DirectionLabel=new QLabel("Direction: "+QString::number(beetle->Direction));
	EnergyLabel=new QLabel("Energy: "+QString::number(beetle->Energy));
	HungryThresholdLabel=new QLabel("HungryThreshold: "+QString::number(beetle->HungryThreshold));
	IdLabel=new QLabel("Id: "+QString::number(beetle->Id));
	InvInChildLabel=new QLabel("InvInChild: "+QString::number(beetle->InvInChild));
	LearnAbilityLabel=new QLabel("LearnAbility: "+QString::number(beetle->LearnAbility));
	NumChildrenLabel=new QLabel("NumChildren: "+QString::number(beetle->NumChildren));
	QLabel  * eff=new QLabel("Eff: "+QString::number(beetle->EFF_Age[0])+" "+QString::number(beetle->EFF_Age[1])+" "+QString::number(beetle->EFF_Age[2]));

	QPushButton * okBut = new QPushButton(tr("OK"));
	connect(okBut,SIGNAL(clicked()),this,SLOT(accept()));

	EffField * effField =  new EffField();
	
    QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(AgeLabel);
	layout->addWidget(DirectionLabel);
	layout->addWidget(EnergyLabel);
	layout->addWidget(HungryThresholdLabel);
	layout->addWidget(IdLabel);
	layout->addWidget(InvInChildLabel);
	layout->addWidget(LearnAbilityLabel);
	layout->addWidget(NumChildrenLabel);
	layout->addWidget(effField);
	layout->addWidget(eff);
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
		
	//painter.setPen(Qt::NoPen);
	
	if (NULL != CBeetle::EffImg)
		painter.drawImage(CBeetle::EffImg->width(),CBeetle::EffImg->height(),*CBeetle::EffImg);
			
}

