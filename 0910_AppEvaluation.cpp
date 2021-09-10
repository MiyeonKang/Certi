#include <map>
#include <cmath>
#pragma warning(disable : 4996)

#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

#define MAX 10001
#define MAXCALL 100001

struct App {
	int idx;
	char name[16];
	int tscore; 
	int cnt;
	double average;
	char user[MAX];
}A[MAX];
int acnt;
map<string, App*> m;
bool isBan[MAX];


void init(int N, char mApp[][16]) {
	acnt = 0;
	for (register int i = 0; i < N; i++) {
		A[acnt].idx = i;
		strcpy(A[acnt].name, mApp[i]);
		memset(A[acnt].user, 'X', sizeof(A[acnt].user));
		m[mApp[i]] = &A[acnt++];
	}
	memset(isBan, 0, sizeof(isBan));
}


void addRating(int mUser, const char mApp[16], int mScore) {
	if (isBan[mUser]) return;
	map<string, App*>::iterator iter = m.find(mApp);
	int preScore = 0;
	int addUser = 1;
	if (iter->second->user[mUser]!='X') {
		preScore = iter->second->user[mUser];
		addUser = 0;
	}
	iter->second->user[mUser] = mScore;
	int addScore = mScore - preScore;

	iter->second->cnt += addUser;
	iter->second->tscore += addScore;
	iter->second->average = (double)iter->second->tscore / (double)iter->second->cnt;
}

void deleteRating(int mUser, const char mApp[16]) {
	if (isBan[mUser]) return;
	map<string, App*>::iterator iter = m.find(mApp);
	int preScore = iter->second->user[mUser];
	iter->second->user[mUser] = 0;
	
	iter->second->cnt--;
	iter->second->tscore -= preScore;
	iter->second->average = (double)iter->second->tscore / (double)iter->second->cnt;
}

void banUser(int mUser) {
	if (isBan[mUser]) return;
	isBan[mUser] = true;
	map<string, App*>::iterator iter;
	for (iter = m.begin(); iter != m.begin(); ++iter) {
		vector<char> temp(iter->first.begin(), iter->first.end());
		temp.push_back('\0');
		deleteRating(mUser, &temp[0]);
	}
}
int list[MAX];
void sortByScore() {
	register int i = 0;
	for (map<string, App*>::iterator iter = m.begin(); iter != m.end(); ++iter){
		list[i++] = iter->second->idx;
	}
	nth_element(list, list + 5, list + i, [&](int a, int b) {
	if (A[a].average != A[b].average) return A[a].average > A[b].average;
	return (string)A[a].name < (string)A[b].name;});

	//sort(list, list + i, [&](int a, int b) {
	//	if (A[a].average != A[b].average) return A[a].average > A[b].average;
	//	return (string)A[a].name < (string)A[b].name; });

}

void sortByNumber() {

}

int main() {
	char apps[6][16] = { "ABCD","AAAA", "CCCC","DDDD","ABAC","QQQQ" };
	init(6, &apps[0]);

	addRating(1, "ABCD", 5);
	addRating(1, "ABCD", 0);
	addRating(1, "ABCD", 4);
	addRating(1, "CCCC", 3);
	addRating(3, "CCCC", 4);
	sortByScore();
	return 0;

}