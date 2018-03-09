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

typedef void (*sortFunction)(Item *, int); // sortFunction an alias for void <function pointer>(Item *, int)


struct SortAlgorithm
{
	string name;
	sortFunction fp;
	clock_t time;
};

void loadData(char file[], Item dat[], int &n)
{
	ifstream fi(file);
	if (!fi.is_open())
	{
		cout << "Khong mo duoc file de tu dien" << endl;
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

void saveData(char file[], Item dat[], int n)
{
	ofstream fo(file);
	if (!fo.is_open())
	{
		cout << "Khong mo duoc file de ghi" << endl;
		return;
	}
	string s;
	int b;
	for (int i = 0; i < n; i++)
	{
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

void sortBySelection(Item dat[], int n)
{
	int min;
	for (int key = 0; key < n - 1; key++)
	{
		min = key;
		for (int candidate = key + 1; candidate < n; candidate++)
		{
			if ((dat[min].word).compare(dat[candidate].word) > 0)
			{
				min = candidate;
			}
		}
		swap(dat[key], dat[min]);
	}
}

void sortByInsertion(Item dat[], int n)
{
	Item holder;
	for (int key = 1, insert; key < n; key++)
	{
		holder = dat[key];
		for (insert = key - 1; insert >= 0 && (holder.word).compare(dat[insert].word) <= 0; insert--)
		{
			dat[insert + 1] = dat[insert];
		}
		dat[insert + 1] = holder;
	}
}

void sortByInterchange(Item dat[], int n)
{
	for (int key = 0; key < n - 1; key++)
	{
		for (int candidate = key + 1; candidate < n; candidate++)
		{
			if ((dat[key].word).compare(dat[candidate].word) > 0)
				swap(dat[key], dat[candidate]);
		}
	}
}

void sortByBubble(Item dat[], int n)
{
	for (int key = 0; key < n - 1; key++)
	{
		for (int bubble = n - 1; bubble > key; bubble--)
		{
			if ((dat[bubble].word).compare(dat[bubble - 1].word) < 0)
			{
				swap(dat[bubble], dat[bubble - 1]);
			}
		}
	}
}

void maxHeapify(Item *arr, int head, int n)
{
	int largerChild = head * 2 + 1;
	while (largerChild < n)
	{
		if (largerChild + 1 < n)
		{
			if ((arr[largerChild].word).compare(arr[largerChild + 1].word) < 0)
				largerChild += 1;
		}
		if ((arr[largerChild].word).compare(arr[head].word) < 0)
			return;
		swap(arr[head], arr[largerChild]);
		head = largerChild;
		largerChild = head * 2 + 1;
	}
}
void initHeap(Item *arr, int n)
{
	for (int head = (n - 1) / 2; head >= 0; head--)
		maxHeapify(arr, head, n);
}
void sortByHeap(Item dat[], int n)
{
	initHeap(dat, n);
	while (n > 0)
	{
		swap(dat[0], dat[n - 1]);
		n--;
		maxHeapify(dat, 0, n);
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
	int n;
	SortAlgorithm list[5] = {
		{"Selection", Selection, 0},
		{"Insertion", Insertion, 0},
		{"Interchange", Interchange, 0},
		{"Bubble", Bubble, 0},
		{"Heap", Heap, 0}
	};

	Item *data = new Item[13375];
	clock_t start;
	start = clock();
	cout << "Tai du lieu tu dien" << endl;
	loadData("mcomputer.txt", data, n);
	cout << "Tong so tu vung: " << n << endl;
	cout << "Thoi gian tai du lieu: " << (clock() - start) / 1e6 << " sec" << endl;

	for (int i = 0; i < 5; i++)
	{
		clock_t temp = 0;
		for (int j = 0; j < 5; j++)
		{
			start = clock();
			list[i].fp(data, n);
			temp += clock() - start;
			if (i < 4 || j < 4)
				loadData("mcomputer.txt", data, n);
		}
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

	delete[] data;
	return 0;
}