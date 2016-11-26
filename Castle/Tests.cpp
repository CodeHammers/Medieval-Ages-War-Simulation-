#include "file_IO.h"
void PrintEnemy1(enemy*head) {
	cout << endl;
	while (head != NULL) {
		cout << head->ID << " ";
		cout << head->Type << " ";
		cout << head->ArrivalTime << " ";
		cout << head->Health << " ";
		cout << head->FirePower << " ";
		cout << head->ReloadPeriod<< " ";
		cout << head->Region << " ";
		cout<<endl;
		head = head->next;
	}
	cout << endl;
}
int selectAndKillTesting(){
	/* -------- TEST 1 -------*/
	cout<<"case1 list1 > 2 nodes , list2 > 2 nodes , list3 > empty";
	enemy* list1=NULL;
	enemy* list2=NULL;
	enemy* list3=NULL;
	InsertEnemy(list1,1,PVR,323,2,2,2,A_REG);
	InsertEnemy(list1,1,PVR,424,1,1,1,C_REG);
	InsertEnemy(list2,1,PVR,525,4,4,4,D_REG);
	InsertEnemy(list2,1,PVR,626,6,6,6,B_REG);
	selectAndKill(list1,list2,list3);
	cout<<"printing list3";
	PrintEnemy1(list3);
	if(list2==NULL&&list1==NULL)
		cout<<"list1/2 is empty";
	/* -------- TEST 1 -------*/
	list1=NULL;
	list2=NULL;
	list3=NULL;
	/* -------- TEST 2 -------*/
	cout<<"case2 list1 > 1 node , list2 > 1 node , list3 > empty";
	InsertEnemy(list1,1,PVR,323,2,2,2,A_REG);
	InsertEnemy(list2,1,PVR,525,4,4,4,D_REG);
	selectAndKill(list1,list2,list3);
	cout<<"printing list3";
	PrintEnemy1(list3);
	if(list2==NULL&&list1==NULL)
		cout<<"list1/2 is empty\n";
	/* -------- TEST 2 -------*/
	list1=NULL;
	list2=NULL;
	list3=NULL;
	/* -------- TEST 3 -------*/
	cout<<"\n case3 all empty\n";
	selectAndKill(list1,list2,list3);
	if(list2==NULL&&list1==NULL&&list3==NULL)
		cout<<"all empty";
	/* -------- TEST 3 -------*/
	list1=NULL;
	list2=NULL;
	list3=NULL;
	/* -------- TEST 4 -------*/
	cout<<"\ncase4 list1 > 3 nodes , list2 > 3 nodes , list3 > 2 nodes\n";
	InsertEnemy(list1,1,PVR,222,2,2,2,A_REG);
	InsertEnemy(list1,1,PVR,424,1,1,1,C_REG);
	InsertEnemy(list1,1,PVR,323,3,3,3,A_REG);
	InsertEnemy(list2,1,PVR,525,5,5,5,D_REG);
	InsertEnemy(list2,1,PVR,626,6,6,6,B_REG);
	InsertEnemy(list2,1,PVR,727,7,7,7,B_REG);
	InsertEnemy(list3,1,PVR,828,8,8,8,B_REG);
	InsertEnemy(list3,1,PVR,929,9,9,9,B_REG);
	selectAndKill(list1,list2,list3);
	cout<<"printing list1";
	PrintEnemy1(list1);
	cout<<"printing list2";
	PrintEnemy1(list2);
	cout<<"printing list3";
	PrintEnemy1(list3);
	/* -------- TEST 4 -------*/
	cin.get();
	return 0;
}
int moveFromToTesting()
{
	/* -------- TEST 1 -------*/
    cout<< "testing case#1 list2>empty && list1 has +2 nodes \n";
	enemy* list1=NULL;
	enemy* list2=NULL;
	InsertEnemy(list1,1,PVR,323,2,2,2,A_REG);
	InsertEnemy(list1,1,PVR,3,1,1,1,B_REG);
	moveFromTo(list1,list2);
	cout<<"printing for list 2";
	PrintEnemy1(list2);
	cout<<"printing for list 1";
	PrintEnemy1(list1);
	//found bug in handling list2 NULL case , node still pointing to the 
	//next one in the original list
	/* -------- TEST 1 -------*/
	/* -------- TEST 2 -------*/
	enemy* list3=NULL;
	enemy* list4=NULL;
	cout<<"\n testing case#2 list4>empty && list3 has one node \n";
	InsertEnemy(list3,1,PVR,323,2,2,2,A_REG);
	moveFromTo(list3,list4);
	cout<<"printing for list 4";
	PrintEnemy1(list4);
	if(list3==NULL)
		cout<<"list3 is empty";
	/* -------- TEST 2 -------*/
	/* -------- TEST 3 -------*/
	cout<<"\n testing case#3 list5>one node && list6 has one node \n";
	enemy* list5=NULL;
	enemy* list6=NULL;
	InsertEnemy(list5,1,PVR,323,2,2,2,A_REG);
	InsertEnemy(list6,1,PVR,3,1,1,1,B_REG);
	moveFromTo(list5,list6);
	cout<<"printing for list 6";
	PrintEnemy1(list6);
	if(list5==NULL)
		cout<<"list 5 is empty";
	/* -------- TEST 3 -------*/

	cin.get();
	return 0;
}


