#include <iostream>
#include <vector>
#include <string>
#include "function.h"
using namespace std;
#define CLEARNUM 13   //��Ҫ��յ�����

struct ListNode {  //һ������������ѷ�������Ľڵ�
	int start;     //ʼֵ
	int length;    //����
	string status; //��־

	ListNode(int a = -1, int b = -1, string c = "\0") {
		start = a;
		length = b;
		status = c;
	}
};
struct Process {  //һ������
	string name;  //���̱�ʶ��
	int size;     //��Ҫ���ڴ��С
	Process(string a, int b) {
		name = a;
		size = b;
	}
};
void SortAddress(vector<ListNode>* array) //���ѷ��������нڵ㰴��ʼֵ��������
{
	int len = array->size();
	for (int i = 1; i < len; i++)
	{
		ListNode temp = (*array)[i];
		int j = i;
		while (j > 0 && temp.start < (*array)[j - 1].start)
		{
			(*array)[j] = (*array)[j - 1];
			j--;
		}
		if (j != i)
			(*array)[j] = temp;
	}
}
void InsertSort(vector<ListNode>* array,string flag="up")//�������������нڵ㰴�ճ�������
{                                                        //��������㷨����������
	int len = array->size();                             //������㷨��������
	for (int i = 1; i < len; i++)
	{
		ListNode temp = (*array)[i];
		int j = i;
		if (flag == "up") {
			while (j > 0 && temp.length < (*array)[j - 1].length)
			{
				(*array)[j] = (*array)[j - 1];
				j--;
			}
			if (j != i)
				(*array)[j] = temp;
		}
		else {
			while (j > 0 && temp.length > (*array)[j - 1].length)
			{
				(*array)[j] = (*array)[j - 1];
				j--;
			}
			if (j != i)
				(*array)[j] = temp;
		}
	}
}
void worstFit(vector<ListNode>* EList, vector<ListNode>* BList, Process* process) { //������㷨
	if (EList->size() == 0)               //�����������ճ��Ƚ������У����Ƚ����̷������Ŀ�����
		return;
	int num = EList->size();
	InsertSort(EList,"down");
	if ((*EList)[0].length >= process->size) {
		BList->push_back(ListNode((*EList)[0].start, process->size, process->name));
		if ((*EList)[0].length == process->size) {
			EList->erase(EList->begin() + 0, EList->begin() + 1);
		}
		else {
			(*EList)[0].start += process->size;
			(*EList)[0].length -= process->size;
		}
	}
	SortAddress(BList);
}
void bestFit(vector<ListNode>* EList, vector<ListNode>* BList, Process* process) { //��������㷨
	if (EList->size() == 0)     //�����������ճ����������У����Ƚ����̷����һ����С����������ռ�Ŀ�����
		return;
	if (EList->size() == 1) {
		if ((*EList)[0].length >= process->size) {
			BList->push_back(ListNode((*EList)[0].start, process->size, process->name));
			if ((*EList)[0].length == process->size) {
				EList->erase(EList->begin() + 0, EList->begin() + 1);
			}
			else {
				(*EList)[0].start += process->size;
				(*EList)[0].length -= process->size;
			}
		}
		SortAddress(BList);
		return;
	}
	int num = EList->size();
	InsertSort(EList,"up");
	int location = -1;
	for (int i = 0; i < num; ++i) {
		if ((*EList)[i].length >= (*process).size) {
			location = i;
			break;
		}
	}
	if (location != -1) {
		BList->push_back(ListNode((*EList)[location].start, process->size, process->name));
		if ((*EList)[location].length == process->size) {
			EList->erase(EList->begin() + location, EList->begin() + location + 1);
		}
		else {
			(*EList)[location].start += process->size;
			(*EList)[location].length -= process->size;
		}
	}
	SortAddress(BList);
}
void killProcess(vector<ListNode>* EList, vector<ListNode>* BList,string flag) { //�����㷨
	int bnum = BList->size();                //��һ�����̽���֮����Ҫ�ͷ���ռ�õ��ڴ�ռ�
	int location = -1;                       //������Ҫ�ͷŵĿռ���Ժ�δ����Ŀ�����������
	int start = -1;                          //����������ϲ����γ�һ���ϴ������Ŀ�������
	int length = -1;
	int end = -1;
	if (bnum == 0) {
		return;
	}
	for (int i = 0; i < bnum; ++i) {
		if ((*BList)[i].status == flag) {
			location = i;
			break;
		}
	}
	if (location != -1) {
		start = (*BList)[location].start;
		length = (*BList)[location].length;
		end = start + length;
		BList->erase(BList->begin() + location, BList->begin() + location + 1);
		for (unsigned int i = 0; i < EList->size(); ++i) {
			if ((*EList)[i].start == end) {
				length += (*EList)[i].length;
				end += (*EList)[i].length;
				EList->erase(EList->begin() + i, EList->begin() + i + 1);
				--i;
			}
			else if ((*EList)[i].start + (*EList)[i].length == start) {
				start = (*EList)[i].start;
				length += (*EList)[i].length;
				EList->erase(EList->begin() + i, EList->begin() + i + 1);
				--i;
			}
		}
		EList->push_back(ListNode(start, length, flag));
	}
	SortAddress(BList);
}
void clear() { //�������Ϣ����������
	cct_gotoxy(0, 13);
	for (int j = 0; j < CLEARNUM; ++j) {
		for (int k = 0; k < 8; ++k) {
			cout << "          "; //10���ո�
		}
		cout << endl;
	}
	cct_gotoxy(0, 13);
}
void upDateBuffer(vector<ListNode>* BusyList) {  //�����ڴ�ռ�Ļ���
	int len = BusyList->size();
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);     //����������ɵĻ���
	cct_gotoxy(3, 5);
	for (int i = 0; i < 7; ++i) {
		cout << "          ";  //10���ո�
	}
	cout << "         ";  //9���ո�
	cct_gotoxy(3, 6);
	for (int i = 0; i < 7; ++i) {
		cout << "          ";  //10���ո�
	}
	cout << "         ";  //9���ո�
	cct_gotoxy(3, 7);
	for (int i = 0; i < 7; ++i) {
		cout << "          ";  //10���ո�
	}
	cout << "         ";  //9���ո�
	cct_gotoxy(3, 9);
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	for (int i = 0; i < 7; ++i) {
		cout << "          ";  //10���ո�
	}
	cout << "         ";  //9���ո�
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);       //���������»滭�µĻ���
	for (int i = 1; i <= len; ++i) {
		cct_gotoxy(2 + ((*BusyList)[i - 1].start) / 32 * 4, 5);
		cout << "��";
		cct_gotoxy(2 + ((*BusyList)[i - 1].start) / 32 * 4, 6);
		cout << "��";
		cct_gotoxy(2 + ((*BusyList)[i - 1].start) / 32 * 4, 7);
		cout << "��";
		cct_gotoxy(2 + ((*BusyList)[i - 1].start) / 32 * 4, 9);
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		cout << (*BusyList)[i - 1].start;
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cct_gotoxy(2 + ((*BusyList)[i-1].start*2+ (*BusyList)[i - 1].length)*4/64+1, 6);
		cout << (*BusyList)[i - 1].status;
		cct_gotoxy(2 + ((*BusyList)[i - 1].start + (*BusyList)[i - 1].length) / 32 * 4, 5);
		cout<< "��";
		cct_gotoxy(2 + ((*BusyList)[i - 1].start + (*BusyList)[i - 1].length) / 32 * 4, 6);
		cout << "��";
		cct_gotoxy(2 + ((*BusyList)[i - 1].start + (*BusyList)[i - 1].length) / 32 * 4, 7);
		cout << "��";
		cct_gotoxy(2 + ((*BusyList)[i - 1].start + (*BusyList)[i - 1].length) / 32 * 4, 9);
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		cout << (*BusyList)[i - 1].start + (*BusyList)[i - 1].length;
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}
string chooseAlgorithm() { //���û�ѡ��Ҫʹ�õĶ�̬�����㷨����
	clear();
	string choice;
	cct_gotoxy(0, 12);
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	cout << "ѡ��������㷨������1���ûس�����ѡ����������㷨������2���ûس�����������������������3���ûس���:";
	while (1) {
		getline(cin,choice);
		if (choice != "1" && choice != "2" && choice != "3") { //�Ƿ�����Ч���룬������Ӧ
			cct_gotoxy(0, 12);
			for (int i = 0; i < 12; ++i) {
				cout << "          "; //10���ո�
			}
			cct_gotoxy(0, 12);
			cout << "ѡ��������㷨������1���ûس�����ѡ����������㷨������2���ûس�����������������������3���ûس���:";
		}
		else {
			cct_gotoxy(0, 12);
			for (int i = 0; i < 12; ++i) {
				cout << "          "; //10���ո�
			}
			cct_gotoxy(0, 12);
			if (choice == "1") {
				cout << "������㷨ģ����ʾ:";
			}
			else if (choice == "2") {
				cout << "��������㷨ģ����ʾ:";
			}
			break;
		}
	}
	cct_setcursor(CURSOR_INVISIBLE);
	return choice;
}
int main() {
	cout << "����ϵͳ�ڴ����֮��̬��������ģ����ʾ����(�����ڴ�ռ��ʼֵ��640K)"<<endl;
	int capacity = 0;
	vector<ListNode> EmptyList;
	vector<ListNode> BusyList;
	vector<Process> ProcessList;               //Ϊ�˷�����������ʾ��������һ����������
	ProcessList.push_back(Process("A", 64));   //A--64K,B--320K,C--128K,D--128K,E--160K,F--32K,G--64K,H--32K,I--224K
	ProcessList.push_back(Process("B", 320));
	ProcessList.push_back(Process("C", 128));
	ProcessList.push_back(Process("D", 128));
	ProcessList.push_back(Process("E", 160));
	ProcessList.push_back(Process("F", 32));
	ProcessList.push_back(Process("G", 64));
	ProcessList.push_back(Process("H", 32));
	ProcessList.push_back(Process("I", 224));
	cout << "��������: ";
	for (unsigned int i = 0; i < ProcessList.size(); ++i) {
		cout << ProcessList[i].name << "--" << ProcessList[i].size << "K  ";
	}
	cout << endl;
	cct_setcolor(COLOR_BLACK, COLOR_HGREEN);
	cout << "�û��س���һ�Σ����򵥲�ִ��,����һ������";
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	draw_buffer();
	int num = ProcessList.size();
	while (1) {
		EmptyList.clear();
		BusyList.clear();
		EmptyList.push_back(ListNode(0, 640));
		string choice = chooseAlgorithm();
		if (choice == "3") {
			break;
		}
		for (int i = 0; i < num; ++i) { //�����û�ѡ��ķ����㷨˳��������
			if (choice == "1") {
				worstFit(&EmptyList, &BusyList, &(ProcessList[i]));
				InsertSort(&EmptyList, "down");
			}
			else {
				bestFit(&EmptyList, &BusyList, &(ProcessList[i]));
				InsertSort(&EmptyList, "up");
			}
			upDateBuffer(&BusyList);
			clear();
			cout << "��������"; //��ʾδ����Ŀ�������
			if (i < num - 1) {
				cout << "(��������:" << ProcessList[i + 1].name << "---" << ProcessList[i + 1].size << "K)" << endl;
			}
			else {
				cout << "���̷������" << endl;
			}
			cout << "ʼַ    ����      ��־" << endl;
			for (unsigned int j = 0; j < EmptyList.size(); ++j) {
				if (EmptyList[j].start < 10) {
					cout << "  ";
				}
				else if (EmptyList[j].start < 100) {
					cout << ' ';
				}
				cout << EmptyList[j].start << (EmptyList[j].length < 100 ? "      " : "     ") << EmptyList[j].length << "      δ����" << endl;
			}
			if (i == 2) {  //B���̽������ͷ�B������ռ�õ��ڴ�ռ�
				int _ = getchar();
				killProcess(&EmptyList, &BusyList, "B");
				if (choice == "1") {
					InsertSort(&EmptyList, "down");
				}
				else{
					InsertSort(&EmptyList, "up");
				}
				upDateBuffer(&BusyList);
				clear();
				cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
				cout << "��������(B���̽���)" << endl; //������ʾδ����Ŀ�������
				cct_setcolor(COLOR_BLACK, COLOR_WHITE);
				cout << "ʼַ    ����      ��־" << endl;
				for (unsigned int j = 0; j < EmptyList.size(); ++j) {
					if (EmptyList[j].start < 10) {
						cout << "  ";
					}
					else if (EmptyList[j].start < 100) {
						cout << ' ';
					}
					cout << EmptyList[j].start << (EmptyList[j].length < 100 ? "      " : "     ") << EmptyList[j].length << "      δ����" << endl;
				}
			}
			else if (i == 3) {
				cct_gotoxy(0, 11);
				cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
				cout << "�ڲ������滻ʱ��������㷨���޷����䳬��192K�Ľ��̣�����������㷨���Է��䲻����320K�Ľ���";
				cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			}
			else if (i == 6) {
				int _ = getchar();     //A���̽������ͷ�A������ռ�õ��ڴ�ռ�
				killProcess(&EmptyList, &BusyList, "A");
				if (choice == "1") {
					InsertSort(&EmptyList, "down");
				}
				else {
					InsertSort(&EmptyList, "up");
				}
				upDateBuffer(&BusyList);
				clear();
				cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
				cout << "��������(A���̽���)" << endl;  //������ʾδ����Ŀ�������
				cct_setcolor(COLOR_BLACK, COLOR_WHITE);
				cout << "ʼַ    ����      ��־" << endl;
				for (unsigned int j = 0; j < EmptyList.size(); ++j) {
					if (EmptyList[j].start < 10) {
						cout << "  ";
					}
					else if (EmptyList[j].start < 100) {
						cout << ' ';
					}
					cout << EmptyList[j].start << (EmptyList[j].length < 100 ? "      " : "     ") << EmptyList[j].length << "      δ����" << endl;
				}
			}
			else if (i == 7) {
				int _ = getchar();          //D��E���̽������ͷ�D��E������ռ�õ��ڴ�ռ�
				killProcess(&EmptyList, &BusyList, "D");
				killProcess(&EmptyList, &BusyList, "E");
				if (choice == "1") {
					InsertSort(&EmptyList, "down");
				}
				else {
					InsertSort(&EmptyList, "up");
				}
				upDateBuffer(&BusyList);
				clear();
				cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
				cout << "��������(DE���̽���)" << endl;  //������ʾδ����Ŀ�������
				cct_setcolor(COLOR_BLACK, COLOR_WHITE);
				cout << "ʼַ    ����      ��־" << endl;
				for (unsigned int j = 0; j < EmptyList.size(); ++j) {
					if (EmptyList[j].start < 10) {
						cout << "  ";
					}
					else if (EmptyList[j].start < 100) {
						cout << ' ';
					}
					cout << EmptyList[j].start << (EmptyList[j].length < 100 ? "      " : "     ") << EmptyList[j].length << "      δ����" << endl;
				}
			}
			else if (i == 8) {
				cct_gotoxy(0, 11);
				cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
				cout << "�ո�������㷨ֻ��Ҫ����1�Σ�����������㷨��Ҫ3��";
				cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			}
			int _ = getchar();
			cct_gotoxy(0, 11);
			for (int j = 0; j < 12; ++j) {
				cout << "          ";  //10���ո�
			}
		}
	}
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	system("pause");
	return 0;
}