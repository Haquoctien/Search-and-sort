#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;
struct Item
{
	string word;
	string meaning;
};

typedef void (*sortFunction)(Item *, int, int*&); // sortFunction an alias for void <function pointer>(Item *, int)

struct SortAlgorithm
{
	char name[32];
	sortFunction fp;
	clock_t time;
};

void loadData(char file[], Item dat[], int &n)
{
	ifstream fi(file);
	if (!fi.is_open())
	{
		cout << "Khong mo duoc file de doc" << endl;
		return;
	}
	string s;
	int b, e;
	n = 0;
	while (!fi.eof())
	{
		getline(fi, s);
		b = s.find("\t");
		if (b < 0)
			continue;
		dat[n].word = s.substr(0, b);
		s = s.substr(b + 1);
		while ((b = s.find("|=")) > -1)
		{
			s.replace(b, 2, "\n");
		}
		dat[n].meaning = s;
		n++;
	}
	fi.close();
}

void saveData(char file[], Item dat[], int actualIndices[], int n)
{
	ofstream fo(file);
	if (!fo.is_open())
	{
		cout << "Khong mo duoc file de ghi" << endl;
		return;
	}
	string s;
	int b;
	for (int i = 0, ip; i < n; i++)
	{
		ip = actualIndices[i];
		while ((b = dat[ip].meaning.find("\n")) > -1)
			dat[ip].meaning.replace(b, 2, "|=");
		fo << dat[ip].word << "\t" << dat[ip].meaning << endl;
	}
	fo.flush();
	fo.close();
}


void sortBySelection(Item dat[], int n, int *&actualIndices)
{
	actualIndices = new int[n];
	for(int i = 0; i < n; actualIndices[i] = i++);
	int min;
	for (int key = 0; key < n - 1; key++)
	{
		min = key;
		for (int candidate = key + 1; candidate < n; candidate++)
		{
			if ((dat[(actualIndices[min])].word).compare(dat[(actualIndices[candidate])].word) > 0)
			{
				min = candidate;
			}
		}
		swap(actualIndices[key], actualIndices[min]);
	}
}

void sortByInsertion(Item dat[], int n, int *&actualIndices)
{
	actualIndices = new int[n];
	for(int i = 0; i < n; actualIndices[i] = i++);
	Item holder;
	for (int key = 1, insert, sortedKey; key < n; key++)
	{
		sortedKey = actualIndices[key];
		for (insert = key - 1; insert >= 0 && (dat[sortedKey].word).compare(dat[actualIndices[insert]].word) <= 0; insert--)
		{
			actualIndices[insert + 1] = actualIndices[insert]; 
		}
		actualIndices[insert+ 1] = sortedKey;
	}
}

void sortByInterchange(Item dat[], int n, int *&actualIndices)
{
	actualIndices = new int[n];
	for(int i = 0; i < n; actualIndices[i] = i++);
	for (int key = 0; key < n - 1; key++)
	{
		for (int candidate = key + 1; candidate < n; candidate++)
		{
			if ((dat[actualIndices[key]].word).compare(dat[actualIndices[candidate]].word) > 0)
				swap(actualIndices[key], actualIndices[candidate]);
		}
	}
}

void sortByBubble(Item dat[], int n, int *&actualIndices)
{
	actualIndices = new int[n];
	for(int i = 0; i < n; actualIndices[i] = i++);
	for (int key = 0, actualKey; key < n - 1; key++)
	{
		actualKey = actualIndices[key];
		for (int bubble = n - 1, actualBubble; bubble > actualKey; bubble--)
		{
			if ((dat[actualIndices[bubble]].word).compare(dat[actualIndices[bubble - 1]].word) < 0)
			{
				swap(actualIndices[bubble], actualIndices[bubble - 1]);
			}
		}
	}
}

void maxHeapify(Item *arr, int head, int n, int *&actualIndices)
{
	int largerChild;
	// while head has child(ren)
	while (head*2 + 1 < n)
	{
		// assume larger child is left child
		largerChild = head*2 + 1;
		// if right child exists
		if (largerChild + 1 < n)
		{
			// if right child is larger, let it be larger child
			if ((arr[actualIndices[largerChild]].word).compare(arr[actualIndices[largerChild + 1]].word) < 0)
				largerChild += 1;
		}
		// if larger child smaller than head
		if ((arr[actualIndices[largerChild]].word).compare(arr[actualIndices[head]].word) < 0)
			return;
		// else swap head and larger child
		swap(actualIndices[head], actualIndices[largerChild]);
		// move on to next head, being previous head's larger child
		head = largerChild;
	}
}
void initHeap(Item dat[], int n, int *&actualIndices)
{ 
	for (int head = (n - 1) / 2; head >= 0; head--)
		maxHeapify(dat, head, n, actualIndices);
}
void sortByHeap(Item dat[], int n, int *&actualIndices)
{
	actualIndices = new int[n];
	for(int i = 0; i < n; actualIndices[i] = i++);
	initHeap(dat, n, actualIndices);
	while (n > 0)
	{
		swap(actualIndices[0], actualIndices[n-1]);
		n--;
		maxHeapify(dat, 0, n, actualIndices);
	}
}

void sortByMerge(Item dat[], int n)
{
	// Cai dat code Sap xep Tron o day

	// ---------------------------
}

void sortByQuick(Item dat[], int n)
{
	// Cai dat code Sap xep Nhanh o day

	// ---------------------------
}

void sortByShell(Item dat[], int n)
{
	// Cai dat code Sap xep Chen Voi Buoc Nhay Giam Dan o day

	// ---------------------------
}

void sortByRadix(Item dat[], int n)
{
	// Cai dat code Sap xep Co So o day

	// ---------------------------
}

int main()
{
	sortFunction Selection = &sortBySelection, \
				Insertion = &sortByInsertion, \
				Interchange = &sortByInterchange, \
				Bubble = &sortByBubble, \
				Heap = &sortByHeap;
	SortAlgorithm list[5] = {
		{"Selection", Selection, 0},
		{"Insertion", Insertion, 0},
		{"Interchange", Interchange, 0},
		{"Bubble", Bubble, 0},
		{"Heap", Heap, 0}
	};
	int n;
	Item *data = new Item[13375];
	clock_t start;
	start = clock();
	cout << "Tai du lieu tu dien" << endl;
	loadData("mcomputer.txt", data, n);
	cout << "Tong so tu vung: " << n << endl;
	cout << "Thoi gian tai du lieu: " << (clock() - start) / 1e6 << " sec" << endl;
	start = clock();
	int * actualIndices;

	cout << "Dang chay cac thuat toan sap xep de danh gia, vui long doi..." << endl;
	for (int i = 0; i < 5; i++)
	{
		clock_t temp = 0;
		for (int j = 0; j < 5; j++)
		{
			start = clock();
			list[i].fp(data, n, actualIndices);
			temp += clock() - start;
		}
		saveData(list[i].name, data, actualIndices, n);
		list[i].time = temp/5;
	}

	for (int key = 0, min; key < 4; key++)
	{
		min = key;
		for(int candidate = key +1; candidate < 5; candidate++)
		{
			if (list[key].time > list[candidate].time)
				min = candidate;
		}
		swap(list[min], list[key]);
	}

	cout << "Nhung thuat toan sap xep theo thoi gian tang dan: " << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << list[i].name << " " << list[i].time/1e6 << " sec" << endl;
	}

	delete[] actualIndices;
	delete[] data;
	return 0;
}