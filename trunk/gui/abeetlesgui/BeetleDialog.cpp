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
	QLabel * effLabel = new QLabel("Energy from a flower according to age(up to age "+QString::number(CBeetle::EffImg.width())+"): ");
	EffField * effField =  new EffField();
	QLabel * brainLabel=new QLabel("Brain (N-nothing, W-wall, B-beetle,F-flower, S-step, L-rotate left, R-rotate right):");
	QLabel * frN = new QLabel("Front=nothing");
	QLabel * frW = new QLabel("Front=wall");
	QLabel * frB = new QLabel("Front=beetle");
	QLabel * frF = new QLabel("Front=flower");
	QLabel * isHun = new QLabel("Hungry");
	QLabel * notHun = new QLabel("Not \nhungry");


	int I,J,K,L;

	QGridLayout * gridBrain =  new QGridLayout;
	gridBrain->addWidget(frN,0,1);gridBrain->addWidget(frW,0,2);gridBrain->addWidget(frF,0,3);gridBrain->addWidget(frB,0,4);
	gridBrain->addWidget(notHun,1,0);gridBrain->addWidget(isHun,2,0);
	QTableWidgetItem *newItem=NULL;
	int left=0;int top=0;int right=0;int bottom=0; 

	for (I=0; I<BRAIN_D1;I++)//hunger
		for (K=0; K<BRAIN_D3;K++)//front
		{
			BrainTables[I][K]= new QTableWidget(BRAIN_D2,BRAIN_D4);
			for(J=0;J<BRAIN_D2;J++)//left
					for(L=0;L<BRAIN_D4;L++)//right
					{
						newItem= new QTableWidgetItem(QString(beetle->GetBrainItemShortcut(I,J,K,L)));//tr("%1").arg((row+1)*(column+1)));
						BrainTables[I][K]->setItem(J,L, newItem); 
					}
			QStringList headerList = (QStringList() << "N" << "B" << "F"<< "W"); 
			BrainTables[I][K]->setHorizontalHeaderLabels (headerList);
			BrainTables[I][K]->setVerticalHeaderLabels (headerList);
			BrainTables[I][K]->resizeColumnsToContents();
			BrainTables[I][K]->getContentsMargins ( &left, &top, &right, &bottom );
			//QMessageBox::information(this,"MyApp",QString::number(left)+" "+QString::number(top)+" "+QString::number(right)+" "+QString::number(bottom));
			left=BrainTables[I][K]->width();
			right=(BrainTables[I][K]->minimumSize()).width();
			//QMessageBox::information(this,"MyApp",QString::number(BrainTables[I][K]->geometry().width())+" " +QString::number(right));
			BrainTables[I][K]->resize(80,150);//(BrainTables[I][K]->width()-left-right,BrainTables[I][K]->height()-top-bottom);
			BrainTables[I][K]->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred); 
			//QMessageBox::information(this,"MyApp",QString::number(BrainTables[I][K]->geometry().width())+" " +QString::number(right));
			gridBrain->addWidget(BrainTables[I][K],I+1,K+1);

		}

	//  ExpectOnPartner - Age [2] = 2B how much   younger /old ercan be the partner
	//	ExpectOnPartner - Energy = 1B how much more than ExpectOnPartner - InvInChild
	//	ExpectOnPartner - InvInChild = 1B how much at least
	//	ExpectOnPartner - LearningAbility [2]= how much less/more can have the parter 		
	QLabel * expLabel = new QLabel("Expectation on partner");
	int num1=(beetle->Age - beetle->ExpectOnPartner[0]); if (num1<0) num1=0;
	int num2=beetle->Age + beetle->ExpectOnPartner[1];
	QLabel * expAgeLabel = new QLabel("\tAge: "+QString::number(num1)+" - "+QString::number(num2));	
	num1=beetle->ExpectOnPartner[2]+beetle->ExpectOnPartner[3]; if (num1>MAX_ENERGY) num1=MAX_ENERGY;
	QLabel * expEnergyLabel = new QLabel("\tEnergy: "+QString::number(num1)+" - "+QString::number(MAX_ENERGY));
	QLabel * expInvInChildLabel = new QLabel("\tInvestment in child: "+QString::number(beetle->ExpectOnPartner[3])+" - "+QString::number(MAX_ENERGY));
	num1=beetle->LearnAbility-beetle->ExpectOnPartner[4];if (num1<0) num1=0;
	num2=beetle->LearnAbility+beetle->ExpectOnPartner[5];if (num2>MAX_LEARN_ABILITY) num2=MAX_LEARN_ABILITY;
	QLabel * expLearnAbilityLabel = new QLabel("\tLearning Ability: "+QString::number(num1)+" - "+QString::number(num2));


	

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
	layout->addWidget(expLabel);
	layout->addWidget(expAgeLabel);
	layout->addWidget(expEnergyLabel);
	layout->addWidget(expInvInChildLabel);
	layout->addWidget(expLearnAbilityLabel);
	layout->addWidget(brainLabel);
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
	if (CBeetle::EffImg.isNull())
		setFixedSize(QSize(0,0));
	else setFixedSize(CBeetle::EffImg.width(),CBeetle::EffImg.height());
	update();
}

void EffField::paintEvent(QPaintEvent *evnt)
{
	QPainter painter(this);
	
	//painter.drawText(5,5,tr("Time: "));

	painter.setPen(Qt::NoPen);
	
	if (!(CBeetle::EffImg.isNull()))	
		painter.drawImage(0,0,CBeetle::EffImg);
			
}

