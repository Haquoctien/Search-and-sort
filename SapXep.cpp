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

struct SortAlgorithm
{
	string name;
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
	Item keyItem;
	for (int key = 1, insert; key < n; key++)
	{
		keyItem = dat[key];
		for (insert = key - 1; insert >= 0 && (keyItem.word).compare(dat[insert].word) <= 0; insert--)
		{
			dat[insert + 1] = dat[insert];
		}
		dat[insert + 1] = keyItem;
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
	Item *data = new Item[13375];
	int n;
	SortAlgorithm list[5] = {
		{"Selection", 0},
		{"Insertion", 0},
		{"Interchange", 0},
		{"Bubble", 0},
		{"Heap", 0}
	};

	clock_t start;
	start = clock();
	cout << "Tai du lieu tu dien" << endl;
	loadData("mcomputer.txt", data, n);
	cout << "Tong so tu vung: " << n << endl;
	cout << "Thoi gian tai du lieu: " << (clock() - start) / 1e6 << " sec" << endl;

	start = clock();
	sortBySelection(data, n);
	list[0].time = clock() - start;
	cout << "Thoi gian sap xep dung " << list[0].name << " : " << list[0].time / 1e6 << " sec" << endl;

	loadData("mcomputer.txt", data, n);
	start = clock();
	sortByInsertion(data, n);
	list[1].time = clock() - start;
	cout << "Thoi gian sap xep dung " << list[1].name << " : " << list[1].time / 1e6 << " sec" << endl;

	loadData("mcomputer.txt", data, n);
	start = clock();
	sortByInterchange(data, n);
	list[2].time = clock() - start;
	cout << "Thoi gian sap xep dung " << list[2].name << " : " << list[2].time / 1e6 << " sec" << endl;

	loadData("mcomputer.txt", data, n);
	start = clock();
	sortByBubble(data, n);
	list[3].time = clock() - start;
	cout << "Thoi gian sap xep dung " << list[3].name << " : " << list[3].time / 1e6 << " sec" << endl;

	loadData("mcomputer.txt", data, n);
	start = clock();
	sortByHeap(data, n);
	list[4].time = clock() - start;
	cout << "Thoi gian sap xep dung " << list[4].name << " : " << list[4].time / 1e6 << " sec" << endl;

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

	cout << "Thoi gian chay xep giam dan: ";
	for (int i = 0; i < 5; i++)
		cout << list[i].name << " ";
	delete[] data;
	return 0;
}