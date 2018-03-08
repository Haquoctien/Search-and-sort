#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Item {
	string word;
	string meaning;
};

void loadData(char file[], Item dat[], int &n) {
	ifstream fi(file);
	if (!fi.is_open()) {
		cout << "Khong mo duoc file de tu dien" << endl;
		return;
	}
	string s;
	int b, e;
	n = 0;
	while(!fi.eof()) {
		getline(fi, s);
		b = s.find("\t");
		if (b < 0)
			continue;		
		dat[n].word = s.substr(0, b);
		s = s.substr(b + 1);
		while ((b = s.find("|=")) > -1) {
			s.replace(b, 2, "\n");
		}
		dat[n].meaning = s;
		n++;
	}
	fi.close();
}

void saveData(char file[], Item dat[], int n) {
	ofstream fo(file);
	if (!fo.is_open()) {
		cout << "Khong mo duoc file de ghi" << endl;
		return;
	}
	string s;
	int b;
	for (int i = 0; i < n; i++) {
		while ((b = dat[i].meaning.find("\n")) > -1)
			dat[i].meaning.replace(b, 2, "|=");
		fo << dat[i].word << "\t" << dat[i].meaning << endl;
	}
	fo.flush();
	fo.close();
}

void swap(Item &i1, Item &i2)
{
	Item temp = i1;
	i1 = i2;
	i2 = temp;
}

void sortBySelection(Item dat[], int n) {
	int min;
	for (int i = 0; i < n-1; i++)
	{
		min = i;
		for (int j = i + 1; j < n; j++)
		{
			if ((dat[min].word).compare(dat[j].word) > 0)
			{
				min = j;
			}
		}
		swap(dat[i], dat[min]);
	}
}

void sortByInsertion(Item dat[], int n) {
	Item key;
	for(int i = 1, k; i < n; i++)
	{
		key = dat[i];
		for (k = i-1; k >= 0 && (key.word).compare(dat[k].word) <= 0; k--)
		{
			dat[k+1] = dat[k];
		}
		dat[k+1] = key;
	}
}

void sortByInterchange(Item dat[], int n) {
	for(int i = 0; i < n-1; i++)
	{
		for(int j = i + 1; j < n; j++)
		{
			if ((dat[i].word).compare(dat[j].word) > 0)
				swap(dat[i], dat[j]);
		}
	}
}

void sortByBubble(Item dat[], int n) {
	for(int i = 0; i < n-1; i++)
	{
		for(int j = n-1; j > i; j--)
		{
			if ((dat[j].word).compare(dat[j-1].word) < 0)
			{
				swap(dat[j], dat[j-1]);
			}
		}
	}
}
void maxHeapify(Item *arr, int headIndex, int n)
{
	int largerChildIndex = headIndex*2 + 1;
	while(largerChildIndex < n)
	{
		if ((arr[largerChildIndex].word).compare(arr[largerChildIndex+ 1].word) < 0)
			largerChildIndex += 1;
		if ((arr[largerChildIndex].word).compare(arr[headIndex].word) < 0)
				return;
		swap(arr[headIndex], arr[largerChildIndex]);
		headIndex = largerChildIndex;
		largerChildIndex = headIndex*2 + 1;
		
	}
}
void initHeap(Item *arr, int n)
{
	for(int headIndex = (n-1)/2; headIndex >= 0; headIndex--)
		maxHeapify(arr, headIndex, n);
}
void sortByHeap(Item dat[], int n) {
	initHeap(dat, n);
	while(n > 0)
	{
		swap(dat[0], dat[n-1]);
		n--;
		maxHeapify(dat,0,n);
	}
}

void sortByMerge(Item dat[], int n) {
	// Cai dat code Sap xep Tron o day

	// ---------------------------
}

void sortByQuick(Item dat[], int n) {
	// Cai dat code Sap xep Nhanh o day

	// ---------------------------
}

void sortByShell(Item dat[], int n) {
	// Cai dat code Sap xep Chen Voi Buoc Nhay Giam Dan o day

	// ---------------------------
}

void sortByRadix(Item dat[], int n) {
	// Cai dat code Sap xep Co So o day

	// ---------------------------
}

int main() {
	Item *data = new Item[13375];
	int n;
	clock_t start;
	start = clock();
	cout << "Tai du lieu tu dien" << endl;
	loadData("mcomputer.txt", data, n);
	cout << "Tong so tu vung: " << n << endl;
	cout << "Thoi gian tai du lieu: " << (clock() - start)/1e6 << " sec" << endl;
	string word;
	start = clock();
	sortByHeap(data, n);
	cout << "Thoi gian sap xep: " << (clock() - start)/1e6 << " sec" << endl;
	saveData("rcomputer.txt", data, n);
	delete []data;
	return 0;
}