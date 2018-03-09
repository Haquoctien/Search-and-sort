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
		//s //(
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

int linearSearch(string word, Item dat[], int n) {
	for (int i = 0; i < n; i++)
	{
		if (!(((dat[i]).word).compare(word)))
			return i;
	}
	return -1;
}

int binarySearch(string word, Item dat[], int n) {
	int high = n, low = 0, middle, compare;
	while (high >= low)
	{
		middle = (high + low)/2;
		compare = ((dat[middle]).word).compare(word); //  dat[middle].word - word
		if (!compare)
			return middle;
		else if (compare < 0)
			low = middle + 1;
		else
			high = middle - 1;
	}
	return -1;
}

int main() {
	Item *data = new Item[13375];
	int n, i, j;
	clock_t start;
	start = clock();
	cout << "Tai du lieu tu dien" << endl;
	loadData("computer.txt", data, n);
	cout << "Tong so tu vung: " << n << endl;
	cout << "Thoi gian tai du lieu: " << clock() - start << "ms" << endl;
	string word;
	while (1) {
		cout << "Nhap tu can tra (EXIT de thoat): ";
		getline(cin,word);
		if (word == "EXIT")
			break;
		start = clock();
		i = linearSearch(word, data, n);
		if (i >= 0)
			cout << data[i].meaning << endl;
		else
			cout << "Khong tim thay tu" << endl;

		cout << "Thoi gian tim bang linear: " << clock() - start << " microsec" << endl;
		start = clock();
		j = binarySearch(word, data, n);
		if (j >= 0)
			cout << data[j].meaning << endl;
		else
			cout << "Khong tim thay tu" << endl;
		cout << "Thoi gian tim bang binary: " << clock() - start << " microsec" << endl;
	}
	delete[] data;
	return 0;
}