#ifndef _OTHER_H
#define _OTHER_H

#include <vector>

struct process
{
	int Number;
	int Execution_time;//czas jaki jest potrzebny na wykonanie procesu
	int Arrival_time;//czas pojawienia sie procesu
	int Entry_time=0;//czas wejscia na procesor
	int Descent_time=0;//czas zejscia z procesora
};

////////////////////////////////////////////////////////////////////////////////////////////////////
bool time_comparator(const process &A,const process &B);
//porownanie dla funkcji sortujacej po czasie nadejscia procesu
bool rtime_comparator(const process &A,const process &B);
//robi to samo tylko na odwrut

bool length_comparator(const process &A,const process &B);
//porownanie dla funkcji sortujacej po czasie potrzebnym na wykonanie

////////////////////////////////////////////////////////////////////////////////////////////////////
void generator(int Average[],int Deviation[],int &Quantity,std::vector<process>&Queue);
void print_data(std::vector<process>&Data);
int find_start(std::vector<process>&Queue,const int &Stop,const int &Counter);
void move_to_performed(std::vector<process>&Queue,int &Size);
void remove_execution(std::vector<process>&Buffer,std::vector<process>&Queue,int &Indicator,const int &Counter);
void put_in_buffer(std::vector<process>&Queue,std::vector<process>&Buffer,const int &Quantity,int &Size,const int &Counter);
void saving_input_time(std::vector<process>&Queue,std::vector<process>&Buffer,const int &Indicator,const int &Counter);
void removing_with_buffer(std::vector<process>&Queue,std::vector<process>&Buffer,int &Indicator,int &Counter,int &Stop);

#endif
