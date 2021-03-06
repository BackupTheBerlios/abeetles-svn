#include "Field.h"
#include "Environment.h"
#include "Beetle.h"
#include "StatisticsEnv.h"
#include <assert.h>
#include <QtGui>
#include <QTimer>
#include <QDir>



CField::CField (CEnvironment * env,QWidget * parent): QWidget(parent)
{
	//1QMessageBox::information(NULL,"Field","Field is constructed");
	setPalette(QPalette(QColor(250, 250, 200)));
    setAutoFillBackground(true);

	Env = env;
	Zoom=INIT_ZOOM;
	//1QMessageBox::information(NULL,"FIELD",QString::number(Env->Grid.G_Width));
	
	ZoomToSqSize[0]=1;ZoomToGapSize[0]=0;
	ZoomToSqSize[1]=3;ZoomToGapSize[1]=1;
	ZoomToSqSize[2]=5;ZoomToGapSize[2]=1;
	ZoomToSqSize[3]=9;ZoomToGapSize[3]=1;
	ZoomToSqSize[4]=17;ZoomToGapSize[4]=3;
	
	
	if (false ==loadBeetleImages())
	{
		QErrorMessage errDlg;
		errDlg.showMessage(QString::fromAscii("Loading of images of beetles was not successful."));
		exit (EXIT_FAILURE);
	}

	setZoom(Zoom);
	/*
	if (Env->IsEmpty)setFixedSize(QSize(0,0));
	else setFixedSize(QSize(Env->Grid.G_Width,Env->Grid.G_Width));

	int fieldWidth=EMPTY_FIELD_SIZE;
	int fieldHeight=EMPTY_FIELD_SIZE;

	setFixedSize(QSize(fieldWidth,fieldHeight));*/

	update();
}
CField::~CField(void)
{
	
}

void CField::mousePressEvent ( QMouseEvent * evnt )
{
	 QPoint  * cell = getCellFromPoint(evnt->x(),evnt->y(),Zoom);
	 emit cellDetails(cell->x(), cell->y());
	 delete cell;
}


void CField::renewField()
{
	//QMessageBox::information(this,"MyApp","In function renew field Zoom: "+QString::number(Zoom));
	//fprintf(stdout,"\nIn Field::renewField ");
	//if (updatesEnabled()) fprintf(stdout,"\nIn Field::updatesEnabled");
	//if(isVisible())fprintf(stdout,"\nIn Field::isVisible");
	setZoom(Zoom); //It must be here, otherwise update() does not work.
	update();
}


void CField::paintEvent(QPaintEvent *evnt)
{

	//fprintf(stdout,"\n In Field::paintEvent");
	int I,J,what;
	CBeetle * beetle;
	if (Env==0) 
	{
		QMessageBox::information(this,"MyApp","3 - No Env");
		return;
	}
	else
	{
		//QMessageBox::information(this,"MyApp","Drawing field");

		QPainter painter(this);
		
		//painter.drawText(200,200,tr("Time: ")+QString::number(Env->Time));
		
		//squares have no border
		painter.setPen(Qt::NoPen);

		for(J=0;J<Env->Grid.G_Height;J++)//rows
		{
		for(I=0;I<Env->Grid.G_Width;I++)//cols
		{
			what = Env->Grid.GetCellContent(I,J,&beetle);			
			assert ((what==BEETLE)||(what==FLOWER)||(what==NOTHING)||(what==WALL));
			if (what==BEETLE)
			{
				painter.setBrush(QBrush(QColor("blue")));
				//painter.drawRect(*(this->getCellRect(I,J,Zoom)));			
				painter.drawImage((this->getCellRect(I,J,Zoom)),getBeetleImage(beetle,I,J,Zoom, TypeView));
				/*if ((beetle->Age)==0) putc('*',stdout);
				else
				{
					if (beetle->Direction == WEST)putc('<',stdout);
					if (beetle->Direction == NORTH)putc('A',stdout);
					if (beetle->Direction == EAST)putc('>',stdout);
					if (beetle->Direction == SOUTH)putc('V',stdout);
				}*/
				continue;
			}
			if (TypeView==5)//Growth of flowers
			{
				QRgb BackClr=qRgb(255-(int)(CfgMng.ColorFromFlowerProbability(Env->Grid.GetCellGrowingProbability(I,J))/(double)100*255),
									255,
									255-(int)(CfgMng.ColorFromFlowerProbability(Env->Grid.GetCellGrowingProbability(I,J))/(double)100*255) );
				if ((what==NOTHING)||(what==FLOWER))
					painter.setBrush(QBrush(QColor(BackClr)));
			}
			else
			{
				if (what==NOTHING) painter.setBrush(QBrush(QColor(COLOR_NOTHING)));						
				if (what==FLOWER) painter.setBrush(QBrush(QColor(COLOR_FLOWER)));		
			}
			if (what==WALL) painter.setBrush(QBrush(QColor(COLOR_WALL)));		
			painter.drawRect((this->getCellRect(I,J,Zoom)));
			continue;
			
		}
		}
	}
}


void CField::setTypeView(const QString& type)
{
	if (type==TYPE_VIEW_1)TypeView=0;//"normal"
    if (type==TYPE_VIEW_2)TypeView=1;//age
    if (type==TYPE_VIEW_3)TypeView=2;//energy
    if (type==TYPE_VIEW_4)TypeView=3;//fertility
    if (type==TYPE_VIEW_5)TypeView=4;//Hunger
	if (type==TYPE_VIEW_6) TypeView=5;//"growth of flowers"
	if (type==TYPE_VIEW_7) 
	{
		TypeView=6;//"species"
		NumSpecies=Env->Statist.FindSpeciesOfBeetles(&Env->Grid);		
	}
	//if (type==TYPE_VIEW_8) TypeView=7;//"growth of flowers"

	update();
}

QImage CField::getBeetleImage(CBeetle * beetle,int x, int y, int zoom,int typeView)
{
	QRgb newBackClr=qRgb(255,255,255);
	//QImage * img = new QImage (*(ImgBeetle[zoom][(int)beetle->Direction])); //[typeView];
	QImage img(ImgBeetle[zoom][(int)beetle->Direction]); //[typeView];
	QPainter painter(&img);
	if (typeView==0);//"normal"
		//nothing
	if (typeView==1)//age...color: cyan=(_,255,255)
	{
		int age = beetle->Age; if (age>MAX_AGE) age=MAX_AGE; //Age must be somehow restricted.
		newBackClr= qRgb(255-(int)(((age)/(double)MAX_AGE)*255),255,255);
	}
	if (typeView==2)//energy..color: red=(255,_,_)
		newBackClr= qRgb(255,255-(int)(((beetle->Energy)/(double)MAX_ENERGY)*255),255-(int)(((beetle->Energy)/(double)MAX_ENERGY)*255));
	if (typeView==3)//fertility..color: magenta=(255,_,255)
		newBackClr= qRgb(255,255-(int)(((beetle->NumChildren)/(double)10)*255),255);
	if (typeView==4)//Hunger..color: red=(255,0,0)
		if (beetle->IsHungry()) newBackClr= qRgb(255,0,0);
	if (typeView==5)//"growth of flowers"..color: green=(_,255,_)
		newBackClr=qRgb(255-(int)(CfgMng.ColorFromFlowerProbability(Env->Grid.GetCellGrowingProbability(x,y))/(double)100*255),
					255,
					255-(int)(CfgMng.ColorFromFlowerProbability(Env->Grid.GetCellGrowingProbability(x,y))/(double)100*255) );
	if(typeView==6)//species
	{
		
		newBackClr=getSpeciesColor(beetle->Species);

	}
	//QMessageBox::information(this,"MyApp","Color: "+QString::number(newBackClr));
	change1ImgColor(&img,qRgb(255,255,255),newBackClr);
	return img;

}
bool CField::change1ImgColor(QImage * img, QRgb origColor, QRgb desiredColor)
{
	int I,J;
	for (I=0;I<img->width();I++)
		for (J=0;J<img->height();J++)		
			if (img->pixel(I, J) == origColor)
				img->setPixel( I, J, desiredColor);
	return true;
}


bool CField::loadBeetleImages()
{
	int z,d; //,v;

	QString fname;
	//QImage * img;
	for(z=0;z<NUM_ZOOM;z++)
		for(d=WEST;d<=SOUTH;d++)
			//for (v=0;v<NUM_TYPE_VIEW;v++)
			{
					fname = "beetle_";
					fname+=QString::number(z);
					fname+="_";
					fname+=QString::number(d);
					fname+=".bmp";
					if (false==QDir::setCurrent ("imgs")) return false;
					
					if (false==ImgBeetle[z][d].load(fname)) return false;
					//if (0== (img= new QImage(fname))) return false;
					ImgBeetle[z][d] = ImgBeetle[z][d].convertToFormat(QImage::Format_RGB32);
					//fprintf(stdout,QString::number(ImgBeetle[z][d].format()).toAscii().data());
					if (false==QDir::setCurrent ("..")) return false;
					//ImgBeetle[z][d]=img;
			}
	//if (img==0) QMessageBox::information(this,"MyApp","No image");
	return true;
}
QRect CField::getCellRect(int col, int row, int zoom) //x,y are zero based!!
{
	int sizeSq= ZoomToSqSize[zoom];
	int sizeGap=ZoomToGapSize[zoom];
	int x=sizeGap+(col*(sizeSq+sizeGap));
	int y=sizeGap+(row*(sizeSq+sizeGap));

	QRect rect(x,y,sizeSq,sizeSq);
	return rect;
}

QPoint * CField::getCellFromPoint(int x, int y, int zoom)
{
	int sizeSq= ZoomToSqSize[zoom];
	int sizeGap=ZoomToGapSize[zoom];
	int col=(x-sizeGap)/(sizeSq+sizeGap);
	int row=(y-sizeGap)/(sizeSq+sizeGap);

	QPoint * point= new QPoint(col,row);
	return point;

}

/*
void CField::setEnvRef(CEnvironment *env)
{
	Env=env;
	QMessageBox::information(NULL,"MyApp","Reference is assigned"); //ch1

	int fieldWidth=EMPTY_FIELD_SIZE;
	if (Env) fieldWidth= ZoomToGapSize[Zoom]+((Env->Grid.G_Width)*(ZoomToSqSize[Zoom]+ZoomToGapSize[Zoom]));
	int fieldHeight=EMPTY_FIELD_SIZE;
	if (Env) fieldHeight= ZoomToGapSize[Zoom]+((Env->Grid.G_Height)*(ZoomToSqSize[Zoom]+ZoomToGapSize[Zoom]));

	setFixedSize(QSize(fieldWidth,fieldHeight));
	
	update();
}*/

void CField::setZoom(int zoom)
{
	if ((zoom<0) || (zoom >=NUM_ZOOM) ) return; //|| (zoom==Zoom)
	else
	{
		Zoom=zoom;
		if (Env->IsEmpty)setFixedSize(QSize(EMPTY_FIELD_SIZE,EMPTY_FIELD_SIZE));
		else
		{
			int fieldWidth= ZoomToGapSize[Zoom]+((Env->Grid.G_Width)*(ZoomToSqSize[Zoom]+ZoomToGapSize[Zoom]));
			int fieldHeight= ZoomToGapSize[Zoom]+((Env->Grid.G_Height)*(ZoomToSqSize[Zoom]+ZoomToGapSize[Zoom]));
			setFixedSize(QSize(fieldWidth,fieldHeight));
		}
		update();
	}

}

QRgb CField::getSpeciesColor(int species)
{
	if (species==NO_SPECIES) return qRgb(255,255,255);
	if (species%10==0) return qRgb(165, 42, 42); //brown 
	if (species%10==1) return qRgb(222, 184, 135); //burlywood 
	if (species%10==2) return qRgb(127, 255, 0); //chartreuse
	if (species%10==3) return qRgb(255, 127, 80); //cornsilk 
	if (species%10==4) return qRgb(220, 20, 60); //crimson 
	if (species%10==5) return qRgb(238, 232, 170); //palegoldenrod 
	if (species%10==6) return qRgb(152, 251, 152); //palegreen
	if (species%10==7) return qRgb(175, 238, 238); //paleturquoise 
	if (species%10==8) return qRgb(219, 112, 147); //palevioletred
	if (species%10==9) return qRgb(221, 160, 221); //plum 

	return qRgb(255,255,255);
}


