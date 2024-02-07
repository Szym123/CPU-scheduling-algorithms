#include <iostream>
#include <vector>
#include <algorithm>
#include "other.h"

void round_robin(std::vector<process> Queue,int Quantity,int Lenth,int Size)
{
	Size--;
	int Counter=0,Indicator=0,Stop=Size;
	std::vector<process>Buffer;

	while(Stop>-1)
	{
		if(Size>-1)
		{
			put_in_buffer(Queue,Buffer,Quantity,Size,Counter);
		}//sprawdza czy mozna wprowadzic procesy do bufora klowego

		if(size(Buffer)>0)
		{
			Indicator++;
			if(Indicator>=size(Buffer)){Indicator=0;}
			//przesuwa znacznik na kolejna komurke bufora kolowego

			if(Buffer[Indicator].Entry_time==0)
			{
				saving_input_time(Queue,Buffer,Indicator,Counter);
			}//zapisuje czas wejscia procesu na procesor
			
			//wykonywanie procesu
			Buffer[Indicator].Execution_time-=Lenth;
			Counter+=Lenth;

			if(Buffer[Indicator].Execution_time<=0)
			{	
				removing_with_buffer(Queue,Buffer,Indicator,Counter,Stop);
			}//sprawdza czy jakis proces sie aktualnie nie wykonal
		}
		else{Counter++;}
		//wykonuje procesy lub czeka 1 jednostke czasu
		//dziala tylko jezeli jakies procesy nadeszly

	}//petla glowna, dla niej jest liczony czas

	print_data(Queue);//wyswietla dane z symulacji
}

void shortest_job_first(std::vector<process> Queue,int Size)
{
	Size--;
	int Counter=0,Start=Size;

	do{
		Start=find_start(Queue,Size,Counter);
		//ustala zakres dla procesow, ktore juz nadeszly
		
		if(Start!=Size)
		{
			std::sort(Queue.begin()+Start,Queue.begin()+Size,&length_comparator);
		}//sortuje przybyle procesy po czasie potrzebnym na wykonanie

		if(Queue[Size].Arrival_time<=Counter)
		{
			Queue[Size].Entry_time=Counter;
			//zapisuje czas wejscia procesu na procesor
						
			//wykonywanie procesu
			Counter+=Queue[Size].Execution_time;

			Queue[Size].Descent_time=Counter;
			//zapisuje czas zejscia procesu z procesora
			Size--;//zmniejsza kolejke procesow 
		}
		else{Counter++;}
		//pobiera proces o najkrutszym czasie trwania, lub czeka 1 jednostke czasu
		//dziala tylko jezeli jakies procesy nadeszly

	}while((Size)>-1);
	//petla glowna, dla niej jest liczony czas

	print_data(Queue);//wyswietla dane z symulacji

}

int main()
{
	//int Quantity=50,Average[]={50,20},Deviation[]={5,5};
	//int Quantity=50,Average[]={50,20},Deviation[]={10,5};
	int Quantity=50,Average[]={50,20},Deviation[]={15,5};
	
	std::vector<process> Queue;
	generator(Average,Deviation,Quantity,Queue);
	
	std::cout<<"SJF:"<<std::endl;	
	shortest_job_first(Queue,Quantity);
	//symuluje dzialanie algorytmu SJF
	
	std::cout<<std::endl;
	
	std::cout<<"Round Robin:"<<std::endl;	
	round_robin(Queue,5,2,Quantity);
	//symuuje dzialanie algorytmu Round Robin

	return 0;
}

