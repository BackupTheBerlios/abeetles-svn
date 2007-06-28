#include "Field.h"
#include "Environment.h"
#include "Beetle.h"
#include <QtGui>


CField::CField (CEnvironment * env,QWidget * parent): QWidget(parent)
{
	setPalette(QPalette(QColor(250, 250, 200)));
    setAutoFillBackground(true);

	Env = env;
	
	
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

	int fieldWidth=EMPTY_FIELD_SIZE;
	int fieldHeight=EMPTY_FIELD_SIZE;

	setFixedSize(QSize(fieldWidth,fieldHeight));
}

void CField::mousePressEvent ( QMouseEvent * evnt )
{
	 QPoint  * cell = getCellFromPoint(evnt->x(),evnt->y(),Zoom);
	 emit cellDetails(cell->x(), cell->y());
}


void CField::renewField()
{
	//QMessageBox::information(this,"MyApp","2");
	update();
}


void CField::paintEvent(QPaintEvent *evnt)
{


	int I,J,what;
	CBeetle * beetle;
	if (Env==0) 
	{
		//QMessageBox::information(this,"MyApp","3 - No Env");
		return;
	}
	else
	{
		//QMessageBox::information(this,"MyApp","3 - Drawing field");

		QPainter painter(this);
		
		//painter.drawText(200,200,tr("Time: ")+QString::number(Env->Time));
		
		//squares have no border
		painter.setPen(Qt::NoPen);

		for(J=0;J<Env->Grid.G_Height;J++)//rows
		{
		for(I=0;I<Env->Grid.G_Width;I++)//cols
		{
			what = Env->Grid.GetCellContent(I,J,&beetle);
			if (what==BEETLE)
			{
				painter.setBrush(QBrush(QColor("blue")));
				//painter.drawRect(*(this->getCellRect(I,J,Zoom)));
				painter.drawImage(*(this->getCellRect(I,J,Zoom)),*(getBeetleImage(beetle,Zoom, TypeView)));
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
			if (what==NOTHING) painter.setBrush(QBrush(QColor(COLOR_NOTHING)));						
			if (what==FLOWER) painter.setBrush(QBrush(QColor(COLOR_FLOWER)));		
			if (what==WALL) painter.setBrush(QBrush(QColor(COLOR_WALL)));		
			painter.drawRect(*(this->getCellRect(I,J,Zoom)));
			continue;
			
		}
		}
	}
}


void CField::setTypeView(const QString& type)
{
	if (type==TYPE_VIEW_1)TypeView=0;
    if (type==TYPE_VIEW_2)TypeView=1;
    if (type==TYPE_VIEW_3)TypeView=2;
    if (type==TYPE_VIEW_4)TypeView=3;
    if (type==TYPE_VIEW_5)TypeView=4;
	if (type==TYPE_VIEW_6) TypeView=5;
	update();
}

QImage * CField::getBeetleImage(CBeetle * beetle,int zoom,int typeView)
{
	QRgb newBackClr=qRgb(255,255,255);
	QImage * img = new QImage (*(ImgBeetle[zoom][(int)beetle->Direction])); //[typeView];
	QPainter painter(img);
	if (typeView==0)//"normal"
		//nothing
	if (typeView==1)//age
		newBackClr= qRgb(255,(int)(((beetle->Age)/(double)MAX_AGE)*255),(int)(((beetle->Age)/(double)MAX_AGE)*255));
	if (typeView==2)//energy
		newBackClr= qRgb(255,(int)(((beetle->Energy)/(double)MAX_ENERGY)*255),255);
	if (typeView==3)//fertility
		newBackClr= qRgb((int)(((beetle->NumChildren)/(double)10)*255),255,255);
	if (typeView==4)//Hunger
		if (beetle->IsHungry()) newBackClr= qRgb(255,0,0);
	if (typeView==5);//"growth of flowers"
			
//	QMessageBox::information(this,"MyApp","Color: "+QString::number(newBackClr));
	change1ImgColor(img,qRgb(255,255,255),newBackClr);
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
	QImage * img;
	for(z=0;z<NUM_ZOOM;z++)
		for(d=WEST;d<=SOUTH;d++)
			//for (v=0;v<NUM_TYPE_VIEW;v++)
			{
					fname = "beetle_";
					fname+=QString::number(z);
					fname+="_";
					fname+=QString::number(d);
					fname+=".gif";
					QDir::setCurrent ("imgs");
					if (0== (img= new QImage(fname))) return false;
					QDir::setCurrent ("..");
					ImgBeetle[z][d]=img;
			}
	//if (img==0) QMessageBox::information(this,"MyApp","No image");
	return true;
}
QRect * CField::getCellRect(int col, int row, int zoom) //x,y are zero based!!
{
	int sizeSq= ZoomToSqSize[zoom];
	int sizeGap=ZoomToGapSize[zoom];
	int x=sizeGap+(col*(sizeSq+sizeGap));
	int y=sizeGap+(row*(sizeSq+sizeGap));

	QRect * rect = new QRect (x,y,sizeSq,sizeSq);
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


void CField::setEnvRef(CEnvironment *env)
{
	Env=env;

	int fieldWidth=EMPTY_FIELD_SIZE;
	if (Env) fieldWidth= ZoomToGapSize[Zoom]+((Env->Grid.G_Width)*(ZoomToSqSize[Zoom]+ZoomToGapSize[Zoom]));
	int fieldHeight=EMPTY_FIELD_SIZE;
	if (Env) fieldHeight= ZoomToGapSize[Zoom]+((Env->Grid.G_Height)*(ZoomToSqSize[Zoom]+ZoomToGapSize[Zoom]));

	setFixedSize(QSize(fieldWidth,fieldHeight));
	
	update();
}

void CField::setZoom(int zoom)
{
	if ((zoom<0) || (zoom >=NUM_ZOOM) || (zoom==Zoom)) return;
	else
	{
		Zoom=zoom;
		int fieldWidth=EMPTY_FIELD_SIZE;
		if (Env) fieldWidth= ZoomToGapSize[Zoom]+((Env->Grid.G_Width)*(ZoomToSqSize[Zoom]+ZoomToGapSize[Zoom]));
		int fieldHeight=EMPTY_FIELD_SIZE;
		if (Env) fieldHeight= ZoomToGapSize[Zoom]+((Env->Grid.G_Height)*(ZoomToSqSize[Zoom]+ZoomToGapSize[Zoom]));

		setFixedSize(QSize(fieldWidth,fieldHeight));
		update();
	}

}
