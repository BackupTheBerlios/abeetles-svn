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
	layout->addWidget(okBut);

	setLayout(layout);
    setWindowTitle(tr("Beetle's Details Dialog"));
}

BeetleDialog::~BeetleDialog(void)
{
}
