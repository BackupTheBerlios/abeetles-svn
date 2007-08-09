#include "StdAfx.h"
#include "StatisticsEnv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Grid.h"
#include "assert.h"
//#include <QMessageBox>
#include <QFile>
#include <QString>
#include <QMessageBox>

#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>

#include <boost/graph/breadth_first_search.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include <boost/pending/integer_range.hpp>






CStatisticsEnv::CStatisticsEnv(void)
{
	TotalCleanup();
	
}

CStatisticsEnv::~CStatisticsEnv(void)
{
}

void CStatisticsEnv::TotalCleanup(void)
{
	MakeEmpty();
	startBuf=0;
	LastNumBirths=0;
	//remove old file of std name, if there is any. - otherwise would newly created env save its satists other then empty.
	//wouldn' it be better to create an empty .csv here??
	QString stdTstFN(STAT_TIME_FILE);
	QFile::remove(stdTstFN);
	
}
/**
* Public method <br>
* Description: This method is performed at the end of every time slice.<br>
* System dependence: no.<br>
* Usage comments: Called it the NextTime method of class CEnvironment.<br>
* @param Time [Time is the number of time slice, that is now finnished and its results should be recorded into this object Statist. ]
* @see reference : adds reference to the "See Also" section. The reference can be any of the following:
*          o HTML tag/text, which is added unmodified
*          o a quoted string (e.g., "Foo Bar"), the contents of which are added unmodified
*          o [project].[ class-name][#member] [text ], which adds a link to the given member in class class-name in project project . If project is omitted, the current entity's project is assumed. If class-name is omitted, the current class is assumed. If member is omitted, the link is to the class-file. If text is omitted, default display text is added, based on the actual link.
* {@link reference } replaced with a reference that is built using the exact same syntax as the @see tag (above). For example:
*/
void CStatisticsEnv::NextTime(int Time)
{	
	NumBirths-=LastNumBirths;

	if (Time==0) 
	{
		startBuf=0;
		endBuf=0;

		PastNumBeetles[0]=NumBeetles;
		PastNumBirths[0]=NumBirths; 
		PastNumFlowers[0]=NumFlowers;

		FILE * statTimeFile;		

		if ((statTimeFile= fopen(STAT_TIME_FILE,"w"))==0) 
		{
			fprintf(stdout,"Creation of file for time statistics was not successful - Error No.%d.\n",errno);
			return; //It is not a reason to finnish the program.
			//exit (EXIT_FAILURE);
		}
		else //adding to columns
			fprintf(statTimeFile,"Number of beetles;Number of births;Number of flowers\n");
	
		fclose(statTimeFile);
	}
	else //e.a. Time>0
	{
		endBuf=Time%BUF_SIZE;
		PastNumBeetles[endBuf]=NumBeetles;
		PastNumBirths[endBuf]=NumBirths;
		PastNumFlowers[endBuf]=NumFlowers;

		//After BUF_SIZE time slices add all time values into file.
		if (endBuf == (BUF_SIZE-1))
		{
			//SaveTimeStatist_InRowsAppend();
			SaveTimeStatist_InColumnsAppend();
			endBuf=-1;
		}

		if(Time%MAX_DATA_TO_TIME_STATS_FILE ==0) //if the file reached maximal number of lines visible in MS Excel
		{											//it is time to start new file
		//Store of old
			QString tstFN(STAT_TIME_FILE);
			QString storeFN= QString::number(Time)+tstFN  ; //filename for storing as an old file
			
			if(QFile::exists(storeFN)) QFile::remove(storeFN);//old store file must be removed
			if (false==QFile::copy(tstFN,storeFN)) //content of full file for saving is copied to be stored
				fprintf(stdout,"Storing of old time statististics was not successful.\n");
			QFile::remove(tstFN); //full file for saving of statistics is deleted
		//Creation of new
			FILE * statTimeFile;		

			if ((statTimeFile= fopen(STAT_TIME_FILE,"w"))==0) 
			{
				fprintf(stdout,"Creation of file for time statistics was not successful - Error No.%d.\n",errno);
				return; //It is not a reason to finnish the program.
				//exit (EXIT_FAILURE);
			}
			else //adding to columns
				fprintf(statTimeFile,"Number of beetles;Number of births;Number of flowers\n");
		
			fclose(statTimeFile);

		}		
	}
	
	//NumBirths=0;//!!Cannot be zeroed here, because this number is displayed after this saving. So I keep it as lastNumBirths
	LastNumBirths=NumBirths;
	SumAge=0;
	SumEnergy=0;
	SumNumChildren=0;

}

void CStatisticsEnv::MakeEmpty(void)
{
	SumAge=0;
	SumEnergy=0;
	SumHungryThreshold =0;
	SumInvInChild=0;
	SumLearnAbility=0;
	SumNumChildren=0;
	NumBeetles=0;
	NumBirths=0;
	NumFlowers=0;
}

double CStatisticsEnv::GetAvgAge(void)
{
	return (double)SumAge/NumBeetles;
}

double CStatisticsEnv::GetAvgEnergy(void)
{
	return (double)SumEnergy/NumBeetles;
}

double CStatisticsEnv::GetAvgHungryThreshold(void)
{
	return (double)SumHungryThreshold/NumBeetles;
}

double CStatisticsEnv::GetAvgInvInChild(void)
{
	return (double)SumInvInChild/NumBeetles;
}

double CStatisticsEnv::GetAvgLearnAbility(void)
{
	return (double)SumLearnAbility/NumBeetles;
}

double CStatisticsEnv::GetAvgNumChildren(void)
{
	return (double)SumNumChildren/NumBeetles;
}

/**
* Public method <br>
* Description: Saves {@link Abeetles.CStatisticsEnv} actual and agregated statistics<br>
* System dependence: no<br>
* Usage comments:<br>
* @return true - if successful, false - otherwise
* @param filename [name for file, where the statistics will be saved]
* @param time [Actual time to be writte](Parameters - meaning):
* @throws name [descrip](Exceptions - meaning)
* @see Abeetles.CStatisticsEnv #SaveTimeStatist_InColumnsAppend
* @see Abeetles.CStatisticsEnv #SaveTimeStatist_InRowsAppend
*/

bool CStatisticsEnv::SaveActAgrStatist(char * filename, int time)
{
	FILE * statFile;
	//int err;

	if ((statFile= fopen(filename,"w"))==0) 
	{
		fprintf(stdout,"File for saving of aggregated statistics was not openned, error: %d",errno);
		return false;
	}
	
	fprintf(statFile," ---------- \n");
	fprintf(statFile,"Time=%d\n",time);
	fprintf(statFile,"NumBeetles=%d;\n",NumBeetles);
	fprintf(statFile,"NumBirths=%d;\n",NumBirths);
	fprintf(statFile,"NumFlowers=%d;\n",NumFlowers);

	fprintf(statFile,"AvgAge=%f;\n",GetAvgAge());
	fprintf(statFile,"AvgEnergy=%f;\n",GetAvgEnergy());
	fprintf(statFile,"AvgHungryThreshold=%f;\n",GetAvgHungryThreshold());
	fprintf(statFile,"AvgInvInChild=%f;\n",GetAvgInvInChild());
	fprintf(statFile,"AvgLearnAbility=%f;\n",GetAvgLearnAbility());
	fprintf(statFile,"AvgNumChildren=%f;\n",GetAvgNumChildren());


	fprintf(statFile," ---------- \n");
	
	fclose(statFile);

	
	return true;
}
/*Not used any more
bool CStatisticsEnv::SaveTimeStatist_InRowsAppend()
{
		FILE * stTFOld;FILE * stTF;
		//int err;
		char chr=0;
		
		//rename file to some other name
		rename(STAT_TIME_FILE,STAT_TIME_FILE_OLD);
		//open old file for reading and new file for writing
		if ((stTFOld= fopen(STAT_TIME_FILE_OLD,"r"))==0) 
		{
			fprintf(stdout,"Error No.%d occured, opening of file %s unsuccessful.",errno,STAT_TIME_FILE);			
			return false;
		}
		if ((stTF= fopen(STAT_TIME_FILE,"w"))==0) 
		{
			fprintf(stdout,"Error No.%d occured, opening of file %s unsuccessful.",errno,STAT_TIME_FILE);			
			return false;
		}
		//rewrite old to new up to the end of the first line
		chr=getc(stTFOld);
		while(chr!='\n')
		{
			putc(chr,stTF);chr=getc(stTFOld);
		}
			
		int I;
		for (I=0;I<BUF_SIZE;I++)
			fprintf(stTF,"%d;",PastNumBeetles[I]);
		fprintf(stTF,"\n");

		chr=getc(stTFOld);
		while(chr!='\n')
		{
			putc(chr,stTF);chr=getc(stTFOld);
		}
					        
        for (I=0;I<BUF_SIZE;I++)
            fprintf(stTF,"%d;",PastNumBirths[I]);
        fprintf(stTF,"\n");

		chr=getc(stTFOld);
		while(chr!='\n')
		{
			putc(chr,stTF);chr=getc(stTFOld);
		}
					
		for (I=0;I<BUF_SIZE;I++)
			fprintf(stTF,"%d;",PastNumFlowers[I]);
		fprintf(stTF,"\n");

		fclose(stTF);fclose(stTFOld);
		remove (STAT_TIME_FILE_OLD);
	return true;
}
*/

/**
* Public method <br>
* Description: Writes last BUF_SIZE values to a .csv file. The name of the file is STAT_TIME_FILE. It adds every monitored variable into separate column. <br>
* System dependence: OS - no, lib-qt.<br>
* Usage comments: called for two different purposes - distinguished by value of parameter fname.<br>
* @param fname [ If null, the method saves into standard file. It also means, the method was called from CStatisticsEnv::NextTime() method. If not null, method saves into file of given name and nothing to standard file.](Parameters - meaning)
* @return True - if saving was successful and false, if opening of the file failed.
*/
bool CStatisticsEnv::SaveTimeStatist_InColumnsAppend(char * fname )
{
	FILE *  stTF;
	int I;

	//if (QFile::exists("`xs")) fprintf(stdout,"In open SaveTime, exists\n");	

	if (fname==0)//this call is from method CStatisticsEnv::NextTime()
	{
		if ((stTF= fopen(STAT_TIME_FILE,"a+"))==0) 
		{
			fprintf(stdout,"Error No.%d occured: %s, opening of file %s unsuccessful.",errno,strerror(errno),STAT_TIME_FILE);			
			return false;
		}
		
		if (-1!=endBuf) //there is nothing to save. It happens when if I am on just loaded time position, there is nothing to save.
			if (startBuf>0)//if I am short after last load of environment
			{
				if (startBuf<(BUF_SIZE-1)) //the startBuf index's value is the last value that already is in .csv file.
					for (I=(startBuf+1);I<=endBuf;I++)
								fprintf(stTF,"%d;%d;%d;\n",PastNumBeetles[I],PastNumBirths[I],PastNumFlowers[I]);
				startBuf=0; //after one incomplete turn of these arrays, next are already complete.
			}
			else
				for (I=0;I<=endBuf;I++)
					fprintf(stTF,"%d;%d;%d;\n",PastNumBeetles[I],PastNumBirths[I],PastNumFlowers[I]);
		fclose(stTF);

		//if (QFile::exists("`xs")) fprintf(stdout,"In SaveTime, exists\n");	
	}	
	else //e.a. (fname!= 0), this is not call from method CStatisticsEnv::NextTime() .
	{
		//remove old file of fname name:
		QString tstFN(fname);
		QFile::remove(tstFN);
		//QMessageBox::information(NULL,"",QString::fromAscii("Saving TimeStats to ")+fname);
		//if (QFile::exists("`xs")) fprintf(stdout,"In SaveTime, exists");
		//QDir::
		//non-overwriting copy of TStat file to file with std name STAT_TIME_FILE
		if (false== QFile::copy(QString(STAT_TIME_FILE),tstFN) ) 
		{
			fprintf(stdout,"No stat time found.");
			return false;
		}

		if ((stTF= fopen(fname,"a+"))==0) 
		{
			fprintf(stdout,"Error No.%d occured: %s, opening of file %s unsuccessful.",errno,strerror(errno),STAT_TIME_FILE);			
			return false;
		}
		//fprintf(stdout,(" "+QString::number(startBuf)+" "+QString::number(endBuf)+" ").toAscii().data());
		if (-1!=endBuf) //there is nothing to save. It happens when if I am on just loaded time position, there is nothing to save.
		{
			if (startBuf>0)//if I am short after last load of environment
			{
				if (startBuf<(BUF_SIZE-1)) //the startBuf index's value is the last value that already is in .csv file.
					for (I=(startBuf+1);I<=endBuf;I++)
								fprintf(stTF,"%d;%d;%d;\n",PastNumBeetles[I],PastNumBirths[I],PastNumFlowers[I]);
				startBuf=0; //after one incomplete turn of these arrays, next are already complete.
			}
			else
			{
				for (I=0;I<=endBuf;I++)
					fprintf(stTF,"%d;%d;%d;\n",PastNumBeetles[I],PastNumBirths[I],PastNumFlowers[I]);
			}
		}
		fclose(stTF);

		
	//if (QFile::exists("`xs")) fprintf(stdout,"In end SaveTime, exists\n");	
	
	}
	
	return true;
}

bool CStatisticsEnv::LoadTimeStatist_FromColums(char * tst_filename)
{
	FILE * stTF;
	int numLines;

	if ((stTF= fopen(tst_filename,"r"))==0) 
	{
		QMessageBox::information(NULL,"MyApp","Loading of file of time statistics "+QString::fromAscii(tst_filename)+" was not successful."); 
		fprintf(stdout,"Error No.%d occured: %s, opening of file %s unsuccessful.",errno,strerror(errno),STAT_TIME_FILE);			
		return false;
	}
	
	int I=0;
	int p1,p2,p3; //helping variables for unimportant values;
	fscanf(stTF,"Number of beetles;Number of births;Number of flowers\n");
	while (!feof(stTF))
	{
		fscanf(stTF," %d ; %d ; %d ; ",&p1,&p2,&p3);
		I++;		
	}
	
	//I - now represents number of rows in the csv file.
	numLines=I;
	startBuf=numLines%BUF_SIZE;	
	endBuf=-1;
	
	fclose(stTF);

	//remove old file of std name:
	QString stdTstFN(STAT_TIME_FILE);
	QFile::remove(stdTstFN);

	//non-overwriting copy of TStat file to file with std name STAT_TIME_FILE
	if (false== QFile::copy ( tst_filename, QString(stdTstFN) ) ) return false;
		
	return true;
}

bool CStatisticsEnv::SaveActHistStatist(char * filename, int time,CGrid * grid)
{
	
	FILE *  statFile;
	//int err;
	int I,J;
	
	int Ages [MAX_HIST];
	for (I=0;I<MAX_HIST;I++) Ages[I]=0;
	int LearnAbilities[MAX_HIST];
	for (I=0;I<MAX_HIST;I++) LearnAbilities[I]=0;
	int InvInChilds[MAX_HIST];
	for (I=0;I<MAX_HIST;I++) InvInChilds[I]=0;
	int	Energies[MAX_HIST];
	for (I=0;I<MAX_HIST;I++) Energies[I]=0;
	int NumsChildren[MAX_HIST];
	for (I=0;I<MAX_HIST;I++) NumsChildren[I]=0;
	int HungryThresholds[MAX_HIST];
	for (I=0;I<MAX_HIST;I++) HungryThresholds[I]=0;
	int AgeExpectations[MAX_HIST];
	for (I=0;I<MAX_HIST;I++) AgeExpectations[I]=0;
	int EnergyExpectations[MAX_HIST];
	for (I=0;I<MAX_HIST;I++) EnergyExpectations[I]=0;
	int InvInChildExpectations[MAX_HIST];
	for (I=0;I<MAX_HIST;I++) InvInChildExpectations[I]=0;
	int LearnAbilityExpectations[MAX_HIST];
	for (I=0;I<MAX_HIST;I++) LearnAbilityExpectations[I]=0;



	CBeetle * beetle=NULL;
	int b1,b2,L;

	for(I=0;I<grid->G_Width;I++)
	for(J=0;J<grid->G_Height;J++)
	{
		if (grid->GetCellContent(I,J,&beetle)==BEETLE) 
		{
			if (beetle->Age <MAX_HIST)
				Ages[beetle->Age]++;

			assert(beetle->LearnAbility<MAX_HIST);
			LearnAbilities[beetle->LearnAbility]++;

			assert(beetle->InvInChild<MAX_HIST);
			InvInChilds[beetle->InvInChild]++;
			assert(beetle->Energy<MAX_HIST);			
			Energies[beetle->Energy]++;

			if (beetle->NumChildren < MAX_HIST)
				NumsChildren[beetle->NumChildren]++;

			assert(beetle->HungryThreshold<MAX_HIST);			
			HungryThresholds[beetle->HungryThreshold]++;
			
			//Age Expectations
			b1=(beetle->Age - beetle->ExpectOnPartner[0]);
			if (b1<0) b1=0;
			b2=(beetle->Age + beetle->ExpectOnPartner[1]);
			if (b2>=MAX_HIST) b2=MAX_HIST-1;
			for (L=b1;L<=b2;L++)
				AgeExpectations[L]++;

			//Energy Expectations
			b1=(beetle->ExpectOnPartner[2] + beetle->ExpectOnPartner[3]);
			if (b1>MAX_ENERGY) b1=MAX_ENERGY;			
			for (L=b1;L<=MAX_ENERGY;L++)
				EnergyExpectations[L]++;

			//InvInChild Expectations
			b1=(beetle->ExpectOnPartner[3]);
			if (b1>MAX_ENERGY) b1=MAX_ENERGY;			
			for (L=b1;L<=MAX_ENERGY;L++)
				InvInChildExpectations[L]++;

			//LearnAbility Expectations
			b1=(beetle->LearnAbility - beetle->ExpectOnPartner[4]);
			if (b1<0) b1=0;
			b2=(beetle->LearnAbility + beetle->ExpectOnPartner[5]);
			if (b2>=MAX_LEARN_ABILITY) b2=MAX_LEARN_ABILITY-1;
			for (L=b1;L<=b2;L++)
				LearnAbilityExpectations[L]++;

		}

	}

	if ((statFile= fopen(filename,"w"))==0) 
	{
		fprintf(stdout,"Error No.%d occured: %s, opening of file %s unsuccessful.",errno,strerror(errno),filename);			
		return false;
	}

	fprintf(statFile,"Ages;LearnAbilities;InvInChilds;Energies;NumsChildren;HungryThresholds;AgeExpectations;EnergyExpectations;InvInChildExpectations;LearnAbilityExpectations\n");
	for (I=0;I<=MAX_ENERGY;I++)
	{
		fprintf(statFile,"%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n",Ages[I],LearnAbilities[I],InvInChilds[I],Energies[I],NumsChildren[I],HungryThresholds[I],AgeExpectations[I],EnergyExpectations[I],InvInChildExpectations[I],LearnAbilityExpectations[I]);
	}
	for (I=MAX_ENERGY+1;I<MAX_HIST;I++)
	{
		fprintf(statFile,"%d;;;;;;;;;\n",Ages[I]);
	}
	
	fclose(statFile);
	return true;
}

int CStatisticsEnv::FindSpeciesOfBeetles(CGrid * grid)
{
  using namespace std;
  using namespace boost;

	

  {
 
    typedef adjacency_list <vecS, vecS, undirectedS> Graph;

    Graph G;

    //Create graph

	CBeetle* beetle=0;
	//typedef CBeetle* BeetleRef; 
	 CBeetle ** beetleArr = new CBeetle* [NumBeetles];
	
	int iB=0;
	int I,J,K;
	for (I=0;I<grid->G_Width;I++)
		for (J=0;J<grid->G_Height;J++)
		{
			if (BEETLE==grid->GetCellContent(I,J,&beetle))
			{
				assert(iB<NumBeetles);
				beetleArr[iB]=beetle;
				
				for(K=0;K<iB;K++)
				{
					if (beetle->IsExpectOnPartnerPossibleToSatisfy(beetleArr[K]) &&
						beetleArr[K]->IsExpectOnPartnerPossibleToSatisfy(beetle))
						add_edge(K,iB,G);
				}
				iB++;

			}

		}



    std::vector<int> component(num_vertices(G));
    int num = connected_components(G, &component[0]);
    
    std::vector<int>::size_type i;
    //cout << "Total number of components: " << num << endl;
    for (i = 0; i != component.size(); ++i)
	{
		//cout << "Beetle " << i <<" is in component " << component[i] << endl;
		beetleArr[i]->Species=component[i];
	}
    //cout << endl;
	
	delete [] beetleArr;

	return num;
	}
}
/*
int CStatisticsEnv::FindGendersOfBeetles(CGrid * grid)
{
	

using namespace boost;
template < typename TimeMap > class bfs_time_visitor:public default_bfs_visitor 
{
  typedef typename property_traits < TimeMap >::value_type T;
public:

  bfs_time_visitor(TimeMap tmap, T & t):m_timemap(tmap), m_time(t)
  { }

  template < typename Vertex, typename Graph > void discover_vertex(Vertex u, const Graph & g) const
  {
    put(m_timemap, u, m_time++);
  }
  TimeMap m_timemap;
  T & m_time;
};


int
main()
{
  using namespace boost;
  // Select the graph type we wish to use
  typedef adjacency_list < vecS, vecS, undirectedS > graph_t;
  // Set up the vertex IDs and names
  enum { r, s, t, u, v, w, x, y, N };
  const char *name = "rstuvwxy";
  // Specify the edges in the graph
  typedef std::pair < int, int >E;
  E edge_array[] = { E(r, s), E(r, v), E(s, w), E(w, r), E(w, t),
    E(w, x), E(x, t), E(t, u), E(x, y), E(u, y)
  };
  // Create the graph object
  const int n_edges = sizeof(edge_array) / sizeof(E);
#if defined(BOOST_MSVC) && BOOST_MSVC <= 1300
  // VC++ has trouble with the edge iterator constructor
  graph_t g(N);
  for (std::size_t j = 0; j < n_edges; ++j)
    add_edge(edge_array[j].first, edge_array[j].second, g);
#else
  typedef graph_traits<graph_t>::vertices_size_type v_size_t;
  graph_t g(edge_array, edge_array + n_edges, v_size_t(N));
#endif

  // Typedefs
  typedef graph_traits < graph_t >::vertex_descriptor Vertex;
  typedef graph_traits < graph_t >::vertices_size_type Size;
  typedef Size* Iiter;

  // a vector to hold the discover time property for each vertex
  std::vector < Size > dtime(num_vertices(g));

  Size time = 0;
  bfs_time_visitor < Size * >vis(&dtime[0], time);
  breadth_first_search(g, vertex(s, g), visitor(vis));

  // Use std::sort to order the vertices by their discover time
  std::vector<graph_traits<graph_t>::vertices_size_type > discover_order(N);
  integer_range < int >range(0, N);
  std::copy(range.begin(), range.end(), discover_order.begin());
  std::sort(discover_order.begin(), discover_order.end(),
            indirect_cmp < Iiter, std::less < Size > >(&dtime[0]));

  std::cout << "order of discovery: ";
  for (int i = 0; i < N; ++i)
    std::cout << name[discover_order[i]] << " ";
  std::cout << std::endl;

  return EXIT_SUCCESS;

}*/
