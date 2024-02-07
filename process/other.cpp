#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "other.h"

bool time_comparator(const process &A,const process &B)
{
	return A.Arrival_time>B.Arrival_time;
}//porownanie dla funkcji sortujacej po czasie nadejscia procesu

bool rtime_comparator(const process &A,const process &B)
{
	return A.Arrival_time<B.Arrival_time;
}//robi to samo tylko na odwrut

////////////////////////////////////////////////////////////////////////////////////////////////////
bool length_comparator(const process &A,const process &B)
{
	return A.Execution_time>B.Execution_time;
}//porownanie dla funkcji sortujacej po czasie potrzebnym na wykonanie

////////////////////////////////////////////////////////////////////////////////////////////////////
void generator(int Average[],int Deviation[],int &Quantity,std::vector<process>&Queue)
{
	std::random_device Generator;
	std::normal_distribution<> Distr_execution(Average[0],Deviation[0]);
	std::normal_distribution<> Distr_arrival(Average[1],Deviation[1]);
	//czas nadejscia i potrzebny na wykonanie generowane sa z rozkladem normalnym
	
	for(int i=0;i<Quantity;i++)
	{
		process NewProcess={0,(int)Distr_execution(Generator),(int)Distr_arrival(Generator)};
		Queue.push_back(NewProcess);
	}//tworzy procesy o losowych parametrachi
	
	sort(Queue.begin(),Queue.end(),&rtime_comparator);
	//sortuje kolejke po czasach przybycia procesow
	//rosnaco
	
	for(int i=0;i<Quantity;i++){Queue[i].Number=i+1;}
	//indeksuje procesy
	
	sort(Queue.begin(),Queue.end(),&time_comparator);
	//sortuje kolejke po czasach przybycia procesow
	//malejaco
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void print_data(std::vector<process>&Data)
{
	sort(Data.begin(),Data.end(),&time_comparator);

	std::cout<<"N,	A,	E,	Ex,	D:"<<std::endl;
	for(int i=0;i<size(Data);i++)
	{
		std::cout<<Data[i].Number<<"	";
		std::cout<<Data[i].Arrival_time<<"	";
		std::cout<<Data[i].Entry_time<<"	";
		std::cout<<Data[i].Execution_time<<"	";
		std::cout<<Data[i].Descent_time<<std::endl;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int find_start(std::vector<process>&Queue,const int &Stop,const int &Counter)
{
	for(int i=0;i<=Stop;i++)
	{
		if(Queue[i].Arrival_time<=Counter){return i;}
	}
	return Stop;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void move_to_performed(std::vector<process>&Queue,int &Size)
{
	std::vector<process>::iterator Iterator=Queue.begin()+Size;

	Queue.push_back(Queue[Size]);
	Queue.erase(Iterator);
	
	Size--;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void remove_execution(std::vector<process>&Buffer,std::vector<process>&Queue,int &Indicator,const int &Counter)
{
	std::vector<process>::iterator Iterator=Buffer.begin()+Indicator;
	
	for(int i=0;i<size(Queue);i++)
	{
		if(Queue[i].Number==Buffer[Indicator].Number)
		{
			Queue[i].Descent_time=Counter;
			//zapisuje czas zakonczenia procesu
		}
	}//znajduje w kolejce wszystkich procesow aktualnie zakonczony proces

	Buffer.erase(Iterator);
	//usowa zakonczony proces z bufora kolowego

	Indicator--;
	if(Indicator<0 && size(Buffer)>0){Indicator=size(Buffer)-1;}
	else{Indicator=0;}
	//przesuwa wskaznik wraz z procesami w buforze kolowym
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void put_in_buffer(std::vector<process>&Queue,std::vector<process>&Buffer,const int &Quantity,int &Size,const int &Counter)
{
	while(Queue[Size].Arrival_time<=Counter && size(Buffer)<Quantity)
	{
		Buffer.push_back(Queue[Size]);
		//dodanie procesu do bufora klowego
		
		move_to_performed(Queue,Size);
		//przeniesienie procesu poza zakres kolejki oczekujacych
	}//laduje naraz tyle procesow ile moze

}

////////////////////////////////////////////////////////////////////////////////////////////////////
void saving_input_time(std::vector<process>&Queue,std::vector<process>&Buffer,const int &Indicator,const int &Counter)
{
	Buffer[Indicator].Entry_time=Counter;
	for(int i=0;i<size(Queue);i++)
	{
		if(Queue[i].Number==Buffer[Indicator].Number)
		{
			Queue[i].Entry_time=Counter;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void removing_with_buffer(std::vector<process>&Queue,std::vector<process>&Buffer,int &Indicator,int &Counter,int &Stop)
{
	if(Buffer[Indicator].Execution_time<0)
	{
		remove_execution(Buffer,Queue,Indicator,Counter+Buffer[Indicator].Execution_time);
	}
	else
	{
		remove_execution(Buffer,Queue,Indicator,Counter);
	}//ustala rzeczywisty czas zejscia procesu z procesora
	//zdejmuje proces z bufora kolowego

	Stop--;
	//zmniejsza kolejke procesow wykonywanych lub czekajacych

}
