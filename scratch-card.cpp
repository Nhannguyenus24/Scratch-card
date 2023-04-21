#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <algorithm>
using namespace std;
void drawCard(int cardnumber[], bool status);
void randomCard(int playercard[], int computercard[]);
void displayCard(string playerName, int playercard[], int computercard[], bool computerstatus, int &balance, int betting, int stake ,char follow,int match);
int point(int cardnumber[]);
bool checkRandom(int a[], int index, int number);
bool checkWax(int cardnumber[]); // kiem tra sap 
bool checkSacred(int cardnumber[]); // kiem tra lieng
bool checkThreewest(int cardnumber[]); //kiem tra ba tay
int checkplayerWin(int playercard[], int computercard[]);
int findmax(int cardnumber[]);
void rules();
int main() {  
	bool computerStatus;
	string playerName ;
	int balance = 1000;
	int betting, stake;
	int match = 1;
	char follow = ' ';
	char choice;
	int playerCard[3] ;
	int computerCard[3] ;
	cout << "\n\t\t========WELCOME TO CASINO ARENA=======\n\n";
	cout << "\n\nWhat's your Name : ";
	getline(cin, playerName);
	do {
		rules();
		computerStatus = 0;
		randomCard(playerCard, computerCard);
		do
		{
			cout << "Hey, " << playerName << ", you have "<<balance<<"$, enter amount to bet : $";
			cin >> betting;
			if (betting > balance || betting > (float(balance / 2)))
				cout << "Betting balance can't be more than current balance or more than half of balance!\n"<< "\nRe-enter balance\n ";
			if (betting==0)
				cout<<"You should enter a betting!" << "\nRe-enter balance\n ";
		} while (betting > balance||betting>(float(balance/2))||betting==0);
		stake = betting * 3;
		balance -= betting;
		displayCard(playerName, playerCard, computerCard, computerStatus, balance, betting, stake,follow,match);
			cout << "Follow or leave? (f/l): "; cin >> follow;
			if (follow == 'f') {
				balance -= betting;
				stake = stake + betting ;
				displayCard(playerName, playerCard, computerCard, computerStatus, balance, betting, stake, follow,match);
				cout << "Press any letter to continue: "; cin >> choice;
				computerStatus = 1;
				displayCard(playerName, playerCard, computerCard, computerStatus, balance, betting, stake, follow,match);
			}
			else {
				system("cls");
				cout << "Computer's card: " << endl;
				computerStatus = 1;
				drawCard(computerCard, computerStatus);
				cout << "You lose " << betting << "$." << endl;
				cout << "Current balance: " << balance << "$." << endl;
			}
		match++;
		if (balance == 0)
		{
			cout << "You have no money to play ";
			break;
		}
		cout << "\n\n-->Do you want to play again (y/n)? ";
		cin >> choice;
	} while (choice == 'y' || choice == 'Y');
	cout << "\n\n\n";
	cout << "\n\nThanks for playing the game. Your balance is $ " << balance << "\n\n";
	return 0;
}
int checkplayerWin(int playercard[], int computercard[]) {
	if (checkWax(playercard) && checkWax(computercard)) {
		if (findmax(playercard) > findmax(computercard))
			return 1;
		else
			return 0;
	}
	else if (checkWax(playercard))
		return 1;
	else if (checkWax(computercard))
		return 0;
	else {
		if (checkSacred(playercard) && checkSacred(computercard)) {
			if (findmax(playercard) > findmax(computercard))
				return 1;
			else
				return 0;
		}
		else if (checkSacred(playercard))
			return 1;
		else if (checkSacred(computercard))
			return 0;
		else {
			if (checkThreewest(playercard) && checkThreewest(computercard)) {
				if (findmax(playercard) > findmax(computercard))
					return 1;
				else
					return 0;
			}
			else if (checkThreewest(playercard))
				return 1;
			else if (checkThreewest(computercard))
				return 0;
			else {
				if (point(playercard) == point(computercard))
					return -1;
				else if (point(playercard) > point(computercard))
					return 1;
				else
					return 0;
			}
		}
	}
}
int findmax(int numbercard[]) {
	int max = numbercard[0];
	for (int i = 0; i < 3; i++) {
		if (numbercard[i] > max)
			max = numbercard[i];
	}
	return max;
}
void displayCard(string playername, int playercard[], int computercard[], bool computerstatus, int &balance, int betting, int stake,char follow,int match) {
	system("cls");
	bool player = 1;
	cout << "Computer's card: " << endl;
	drawCard(computercard, computerstatus);
	if (computerstatus == 1) {
		if (checkWax(computercard))
			cout << "Computer's card is wax." << endl;
		else if (checkSacred(computercard))
			cout << "Computer's card is sacred." << endl;
		else if (checkThreewest(computercard))
			cout << "Computer's card is three west." << endl;
		else
			cout << "Computer's card has " << point(computercard) << " point." << endl;
	}
	else {
			cout << "Computer continues with " << betting << "$." << endl; 
	}
	cout << "Total stake: " << stake << "$ \n" << endl;
	cout << "\t========MATCH " << match << "========" << endl;
	cout << playername << "'s card: " << endl;
	drawCard(playercard, player);
	if (computerstatus == 1) {
		if (checkWax(playercard))
			cout << playername << "'s card is wax." << endl;
		else if (checkSacred(playercard))
			cout << playername << "'s card is sacred." << endl;
		else if (checkThreewest(playercard))
			cout << playername << "'s card is three west." << endl;
		else
			cout << playername << "'s card has " << point(playercard) << " point." << endl;
	}
	if (computerstatus == 0)
		cout << "Current balance: " << balance << "$." << endl;
	else {
		if (checkplayerWin(playercard, computercard) == -1) {
			cout << "DRAW MATCH!!" << endl;
			balance += betting;
			if (follow == 'f' || follow == 'F')
				balance += betting;
			cout << "Current balance: " << balance << "$." << endl;
		}
		else if (checkplayerWin(playercard, computercard) == 0) {
			cout << "BETTER LUCK NEXT TIME. YOU LOSE!!" << endl;
			cout << "Current balance: " << balance << "$." << endl;
		}
		else {
			cout << "GOOD LUCK. YOU WIN!!!" << endl;
			balance = balance + stake;
			cout << "Current balance: " << balance << "$." << endl;
		}
	}
}
bool checkRandom(int a[], int index, int number) {
	for (int i = 0; i < index; i++)
	{
		if (a[i] == number)
			return false;
	}
	return true;
}
void randomCard(int playercard[], int computercard[]) {
	srand(time(0));
	int a[6] = { 0,0,0,0,0,0 }, number;
	for (int i = 0; i < 3; i++) {
		number = rand() % 52 + 1;
		if (checkRandom(a, i, number)) {
			a[i] = number;
			playercard[i] = number;
		}
		else {
			i--;
			continue;
		}
	}
	for (int i = 3; i < 6; i++) {
		number = rand() % 52 + 1;
		if (checkRandom(a, i, number)) {
			a[i] = number;
			computercard[i - 3] = number;
		}
		else {
			i--;
			continue;
		}
	}
}
bool checkWax(int cardnumber[]) {
	int number[3];
	number[0] = cardnumber[0] / 4;
	number[1] = cardnumber[1] / 4;
	number[2] = cardnumber[2] / 4;
	if (number[0] == number[1] && number[1] == number[2])
		return true;
	return false;
}
bool checkSacred(int cardnumber[]) {
	int number[3];
	number[0] = cardnumber[0] / 4;
	number[1] = cardnumber[1] / 4;
	number[2] = cardnumber[2] / 4;
	sort(number, number + 3);
	if ((number[1] - number[0] == 1) && (number[2] - number[1] == 1)&&number[0]!=0)
		return true;
	int a[3] = { 0,0,0 }; //check QKA
	for (int i = 0; i < 3; i++) {
		if (cardnumber[i] < 4) 
			a[0] = 1;
		if (cardnumber[i] >= 48) 
			a[1] = 1;
		if (cardnumber[i] >= 44 && cardnumber[i] <= 47) 
			a[2] = 1;
	}
	if (a[0] == 1 && a[1] == 1 && a[2] == 1)
		return true;
	return false;
}
bool checkThreewest(int cardnumber[]) {
	if (cardnumber[0] > 39 && cardnumber[1] > 39 && cardnumber[2] > 39)
		return true;
	return false;
}
int point(int cardnumber[]) {
	int point = 0;
	int card[3];
	for (int i = 0; i < 3; i++) {
		if (cardnumber[i] <= 35)
			card[i] = (cardnumber[i] / 4) + 1;
		else
			card[i] = 0;
		point += card[i];
	}
	return point % 10;
}
void drawCard(int cardnumber[], bool status) {
	string up[52] = { "A ","A ","A ","A ","2 ","2 " ,"2 " ,"2 ","3 ","3 ","3 ","3 ","4 ","4 ","4 ","4 ","5 ","5 ","5 ","5 ","6 ","6 " ,"6 " ,"6 ","7 ","7 ","7 ","7 ","8 ","8 " ,"8 " ,"8 ","9 ","9 ","9 ","9 ","10","10","10","10","J ","J ","J ","J ","Q ","Q ","Q ","Q ","K ","K ","K ","K " };
	string down[52] = { "_A","_A","_A","_A","_2","_2" ,"_2" ,"_2","_3","_3","_3","_3","_4","_4","_4","_4","_5","_5","_5","_5","_6","_6" ,"_6" ,"_6","_7","_7","_7","_7","_8","_8" ,"_8" ,"_8","_9","_9","_9","_9","10","10","10","10","_J","_J","_J","_J","_Q","_Q","_Q","_Q","_K","_K","_K","_K" };
	string namecard[4] = { " bich"," tep "," ro  "," co  " };
	int card[3];
	card[0] = cardnumber[0] % 4;
	card[1] = cardnumber[1] % 4;
	card[2] = cardnumber[2] % 4;
	if (status == 0) {
		cout << "   _____   _____   _____ " << endl;
		cout << "  |#    | |#    | |#    | " << endl;
		cout << "  |     | |     | |     | " << endl;
		cout << "  |     | |     | |     | " << endl;
		cout << "  |____#| |____#| |____#| " << endl;
		cout << "    non     non     non" << endl;
	}
	else {
		cout << "   _____   _____   _____ " << endl;
		cout << "  |" << up[cardnumber[0]] << "   | |" << up[cardnumber[1]] << "   | |" << up[cardnumber[2]] << "   | " << endl;
		cout << "  |     | |     | |     | " << endl;
		cout << "  |     | |     | |     | " << endl;
		cout << "  |___" << down[cardnumber[0]] << "| |___" << down[cardnumber[1]] << "| |___" << down[cardnumber[2]] << "| " << endl;
		cout << "   " << namecard[card[0]] << "   " << namecard[card[1]] << "   " << namecard[card[2]] << endl;
	}
}
void rules() {
	system("cls");
	cout << "\t\t======CASINO THREE POKER CARD RULES!======\n";
	cout << "\t1. You will have 1000$ to start.\n";
	cout << "\t2. Decide an amount to bet.\n";
	cout << "\t3. Winner gets 2 times of the money bet.\n";
	cout << "\t4. Follow to double you bet and reward, leave to start a new match.\n";
	cout << "\t5. Lose the computer, and you lose the amount you bet.\n\n";
}