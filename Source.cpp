/*
NAME: ÝBRAHÝM
SURNAME:KARAHAN
NUMBER:150160550
SSH: g++ Source.cpp -std=c++11
REFERENCES: LECTURE SLIDE USED AS REFERENCES AND PSUEDO CODES.
*/
#include <iostream>
#include <fstream>
#include <string>
#include<time.h>
#include <vector>

using namespace std;

string header; // reading head line at file

class File{  // File class is created for keeping value of csv file.
public:
	string time_stamp; 
	string emptyColum;
	float last_price;
	string emptyColum1;
};

vector<File> insertionSortLastPrice(vector<File> lastPrice, int size){  // insrtion sort for lastprice
	for (int i = 1; i <size; i++)
	{
		float key = lastPrice[i].last_price;   // finding key value 
		string emptyColum = lastPrice[i].emptyColum;
		string time_stamp = lastPrice[i].time_stamp;
		string emptyColum1 = lastPrice[i].emptyColum1;
		int j = i - 1;

		while (j >= 0 && lastPrice[j].last_price > key)
		{
			lastPrice[j + 1].last_price = lastPrice[j].last_price; // copying the object 
			lastPrice[j + 1].emptyColum = lastPrice[j].emptyColum;
			lastPrice[j + 1].time_stamp = lastPrice[j].time_stamp;
			lastPrice[j + 1].emptyColum1 = lastPrice[j].emptyColum1;
			j = j - 1;
		}
		lastPrice[j + 1].last_price = key;  // copying the object 
		lastPrice[j + 1].emptyColum = emptyColum;
		lastPrice[j + 1].emptyColum1 = emptyColum1;
		lastPrice[j + 1].time_stamp = time_stamp;
	}
	return lastPrice;
}

vector<File> insertionSortTimeStamp(vector<File> lastPrice, int size){ // // insrtion sort for timestamp
	for (int i = 1; i <size; i++)
	{
		string key = lastPrice[i].time_stamp;  // finding key value
		string emptyColum = lastPrice[i].emptyColum;
		float last_price = lastPrice[i].last_price;
		string emptyColum1 = lastPrice[i].emptyColum1;
		int j = i - 1;

		while (j >= 0 && lastPrice[j].time_stamp > key)
		{
			lastPrice[j + 1].last_price = lastPrice[j].last_price; // copying the object
			lastPrice[j + 1].emptyColum = lastPrice[j].emptyColum;
			lastPrice[j + 1].last_price = lastPrice[j].last_price;
			lastPrice[j + 1].emptyColum1 = lastPrice[j].emptyColum1;
			j = j - 1;
		}
		lastPrice[j + 1].time_stamp = key;  // copying the object 
		lastPrice[j + 1].emptyColum = emptyColum;
		lastPrice[j + 1].emptyColum1 = emptyColum1;
		lastPrice[j + 1].last_price = last_price;
	}
	return lastPrice;
}

void mergeLastPrice(vector<File>& lastPrice, int start, int size, int end)  // merge for lastprice
{
	File swap;  // creating object for copying 
	int i, j, k;
	int indexRight = size - start + 1; // determine the index 
	int indexleft = end - size;  // determine the index 
	vector<File> leftVector;  // creating leftvector
	vector<File> rightVector; // creating rightvector

	for (i = 0; i < indexRight; i++){       // copying the object to leftVector
		swap.time_stamp = lastPrice[start + i].time_stamp;
		swap.emptyColum = lastPrice[start + i].emptyColum;
		swap.last_price = lastPrice[start + i].last_price;
		swap.emptyColum1 = lastPrice[start + i].emptyColum1;
		leftVector.push_back(swap);
	}
	for (j = 0; j < indexleft; j++){    // copying the object to rightVector
		swap.time_stamp = lastPrice[size + 1 + j].time_stamp;
		swap.emptyColum = lastPrice[size + 1 + j].emptyColum;
		swap.last_price = lastPrice[size + 1 + j].last_price;
		swap.emptyColum1 = lastPrice[size + 1 + j].emptyColum1;
		rightVector.push_back(swap);
	}
	i = 0;
	j = 0;
	k = start;
	while (i < indexRight && j < indexleft)   
	{
		if (leftVector[i].last_price <= rightVector[j].last_price)  // compare value
		{
			lastPrice[k].time_stamp = leftVector[i].time_stamp;
			lastPrice[k].emptyColum = leftVector[i].emptyColum;
			lastPrice[k].last_price = leftVector[i].last_price;
			lastPrice[k].emptyColum1 = leftVector[i].emptyColum1;
			i++;
		}
		else
		{
			lastPrice[k].time_stamp = rightVector[j].time_stamp;
			lastPrice[k].emptyColum = rightVector[j].emptyColum;
			lastPrice[k].last_price = rightVector[j].last_price;
			lastPrice[k].emptyColum1 = rightVector[j].emptyColum1;
			j++;
		}
		k++;
	}
	while (i < indexRight)   // copying the rest of vector and written to prevent elements disappear
	{
		lastPrice[k].time_stamp = leftVector[i].time_stamp;
		lastPrice[k].emptyColum = leftVector[i].emptyColum;
		lastPrice[k].last_price = leftVector[i].last_price;
		lastPrice[k].emptyColum1 = leftVector[i].emptyColum1;
		i++;
		k++;
	}
	while (j < indexleft) // copying the rest of vector and written to prevent elements disappear
	{
		lastPrice[k].time_stamp = rightVector[j].time_stamp;
		lastPrice[k].emptyColum = rightVector[j].emptyColum;
		lastPrice[k].last_price = rightVector[j].last_price;
		lastPrice[k].emptyColum1 = rightVector[j].emptyColum1;
		j++;
		k++;
	}
}

void mergeSortLastPrice(vector<File>& lastPrice, int start, int end)  // divide the vctor in two parts for lastprice
{
	if (start < end) // control for diveding 
	{
		int middle = (start + end) / 2;   // finding the mid point 

		mergeSortLastPrice(lastPrice, start, middle);  // recursive for building one elemnet vector 
		mergeSortLastPrice(lastPrice, middle + 1, end);  // recursive for building one elemnet vector 

		mergeLastPrice(lastPrice, start, middle, end); // sorting 
	}
}

void mergeTimeStamp(vector<File>& lastPrice, int start, int size, int end) // merge for timestamp
{
	File swap; // creating object for copying 
	int i, j, k;
	i = 0;
	j = 0;
	k = start;
	int indexRight = size - start + 1; // determine the index 
	int indexleft = end - size;   // determine the index 
	vector<File> left;   // creating leftvector
	vector<File> right;  // creating rightvector

	for (i = 0; i < indexRight; i++){ // copying the object to leftVector
		swap.time_stamp = lastPrice[start + i].time_stamp;
		swap.emptyColum = lastPrice[start + i].emptyColum;
		swap.last_price = lastPrice[start + i].last_price;
		swap.emptyColum1 = lastPrice[start + i].emptyColum1;
		left.push_back(swap);
	}
	for (j = 0; j < indexleft; j++){   // copying the object to rightVector
		swap.time_stamp = lastPrice[size + 1 + j].time_stamp;
		swap.emptyColum = lastPrice[size + 1 + j].emptyColum;
		swap.last_price = lastPrice[size + 1 + j].last_price;
		swap.emptyColum1 = lastPrice[size + 1 + j].emptyColum1;
		right.push_back(swap);
	}
	while (i < indexRight && j < indexleft)
	{
		if (left[i].time_stamp <= right[j].time_stamp)  // compare value
		{
			lastPrice[k].time_stamp = left[i].time_stamp;
			lastPrice[k].emptyColum = left[i].emptyColum;
			lastPrice[k].last_price = left[i].last_price;
			lastPrice[k].emptyColum1 = left[i].emptyColum1;
			i++;
		}
		else
		{
			lastPrice[k].time_stamp = right[j].time_stamp;
			lastPrice[k].emptyColum = right[j].emptyColum;
			lastPrice[k].last_price = right[j].last_price;
			lastPrice[k].emptyColum1 = right[j].emptyColum1;
			j++;
		}
		k++;
	}
	while (i < indexRight)  // copying the rest of vector and this written to prevent elements disappear
	{
		lastPrice[k].time_stamp = left[i].time_stamp;
		lastPrice[k].emptyColum = left[i].emptyColum;
		lastPrice[k].last_price = left[i].last_price;
		lastPrice[k].emptyColum1 = left[i].emptyColum1;
		i++;
		k++;
	}
	while (j < indexleft)  // copying the rest of vector and written to prevent elements disappear
	{
		lastPrice[k].time_stamp = right[j].time_stamp;
		lastPrice[k].emptyColum = right[j].emptyColum;
		lastPrice[k].last_price = right[j].last_price;
		lastPrice[k].emptyColum1 = right[j].emptyColum1;
		j++;
		k++;
	}
}

void mergeSortTimeStamp(vector<File>& lastPrice, int start, int end) // divide the vctor in two parts for timestamp
{
	if (start < end) // control for diveding 
	{
		int middle = (start + end) / 2; // finding the mid point

		mergeSortTimeStamp(lastPrice, start, middle); // recursive for building one elemnet vector 
		mergeSortTimeStamp(lastPrice, middle + 1, end); // recursive for building one elemnet vector 

		mergeTimeStamp(lastPrice, start, middle, end); // sorting
	}
}

void printVector(vector<File> lastPrice, int size){
	for (int i = 0; i < size; i++)
	{
		cout << lastPrice[i].emptyColum << " " << lastPrice[i].last_price << " " << lastPrice[i].time_stamp << " " << lastPrice[i].emptyColum1 << endl;
	}
}

void writeToFile(vector<File> LastPrice,int size){ // write to sorted.csv
	ofstream excellFile("sorted.csv"); // open the file for writing
	if (excellFile.is_open())
	{
		excellFile << header << endl; // write headers 
		for (int i = 0; i < size; i++)
		{
			excellFile << LastPrice[i].time_stamp << LastPrice[i].emptyColum << LastPrice[i].last_price <<LastPrice[i].emptyColum1<<endl; // write sorted value
		}
		excellFile.close();
	}
	else cout << "Excel file can not opened.";
}

int main(int argc,char *argv[]) {
	vector<File> lastPrice; // object kept in vector
	clock_t start_insertion, end_insertion,start_merge, end_merge;
	double total_insertion, total_merge;
	string last_price,algo_type,feature;
	string algo_type1 = "m";
	string algo_type2 = "i";
	string feature_type1 = "p";
	string feature_type2 = "t";
	int size; // argumnet -size 
	algo_type = argv[2];
	feature = argv[4];
	size = atoi(argv[6]);

	File *sort=new File[size];  // object is created 

	ifstream excelFile("log_inf.csv");
	if (excelFile.is_open())
	{
		getline(excelFile,header); //taking the header to emptyLine
		for (int i = 0; i < size; i++)
		{
			getline(excelFile,sort[i].time_stamp, ','); // taking timeStamp value 
			getline(excelFile, sort[i].emptyColum, ','); 
			getline(excelFile, last_price, ','); // taking the lastPrice value
			getline(excelFile, sort[i].emptyColum1);
			sort[i].last_price = strtof((last_price).c_str(), 0); // converting string to float
			lastPrice.push_back(sort[i]); // adding object to vector
		}
		excelFile.close();
	}
	else {
		cout << "Excel file can not opened."<<endl;
	}

	cout << algo_type << " " << feature << " " << size << endl;

	if (algo_type == algo_type1 && feature == feature_type1){    // if argument type -algo m -feature p
		
		start_merge = clock();
		mergeSortLastPrice(lastPrice, 0, lastPrice.size() - 1);
		end_merge = clock();
		total_merge = (double)(end_merge - start_merge) / CLOCKS_PER_SEC;

		writeToFile(lastPrice, size);
		cout << total_merge << endl;
	}
	else if (algo_type == algo_type1 && feature ==feature_type2){    // if argument type -algo m -feature t
		
		start_merge = clock();
		mergeSortTimeStamp(lastPrice, 0, lastPrice.size() - 1);
		end_merge = clock();
		total_merge = (double)(end_merge - start_merge) / CLOCKS_PER_SEC;

		writeToFile(lastPrice, size);
		cout << total_merge << endl;
	}
	else if (algo_type == algo_type2 && feature == feature_type2){   // if argument type -algo i -feature t
		
		start_insertion = clock();
		insertionSortTimeStamp(lastPrice, size);
		end_insertion = clock();
		total_insertion = (double)(end_insertion - start_insertion) / CLOCKS_PER_SEC;
		
		writeToFile(lastPrice, size);
		cout << total_insertion << endl;
	}
	else if (algo_type == algo_type2 && feature == feature_type1){    // if argument type -algo i -feature p
		
		start_insertion = clock();
		insertionSortLastPrice(lastPrice, size);
		end_insertion = clock();
		total_insertion = (double)(end_insertion - start_insertion) / CLOCKS_PER_SEC;

		writeToFile(lastPrice, size);
		cout << total_insertion << endl;
	}
	
	return 0;
}
