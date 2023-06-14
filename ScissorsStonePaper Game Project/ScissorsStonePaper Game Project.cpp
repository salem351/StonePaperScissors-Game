#include <iostream>
#include <cstdlib>
using namespace std;

enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };
enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };

struct stRoundInfo {
	short RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
};

struct stGameResults {
	short GameRounds = 0;
	short Player1WinTimes = 0;
	short Computer2WinTimes = 0;
	short DrawTime = 0;
	enWinner GameWinner;
	string WinnerName = " ";
};

int RoundomNumber(int from, int to) {
	int RandNumber = rand() % (to - from + 1) + from;
	return RandNumber;
}

void SetWinnerScreencolor(enWinner Winner) {
	switch (Winner) {
	case enWinner::Player1:
		system("color 2F");
		break;
	case enWinner::Computer:
		system("color 4F");
		cout << "\a";
		break;
	default:
		system("color 6F");
		break;


	}
}

string ChoiceName(enGameChoice Choice) {
	string arrChoiceName[3] = { "Stone" , "Paper" , "Scissors" };
	return arrChoiceName[Choice - 1];
}

void PrintRoundReaults(stRoundInfo RoundInfo) {
	cout << "\n------------Round[" << RoundInfo.RoundNumber << "]--------\n\n";
	cout << "Player Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner: " << RoundInfo.WinnerName << endl;
	cout << "------------------------------------------------------------\n\n";

	SetWinnerScreencolor(RoundInfo.Winner);
}

string WinnerName(enWinner Winner) {
	string arrWinnerName[3] = { "Player1" , "Computer" , "No Winner" };
	return arrWinnerName[Winner - 1];
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo) {
	if (RoundInfo.ComputerChoice == RoundInfo.Player1Choice) {
		return enWinner::Draw;
	}
	switch (RoundInfo.Player1Choice) {
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper) {
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissors) {
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Scissors:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone) {
			return enWinner::Computer;
		}
		break;
	}

	return enWinner::Player1;


}

enGameChoice GetComputerChoice() {
	return (enGameChoice)RoundomNumber(1, 3);
}

enGameChoice ReadPlayer1Choice() {
	short Choice = 1;
	do {
		cout << "\nYour choice:[1]:stone,[2]:Paper,[3]:Scissors?";
		cin >> Choice;
	} while (Choice < 1 || Choice > 3);

	return (enGameChoice)Choice;
}

enWinner WhoWhoTheGame(short Player1WinTimes, short Computer2WinTimes) {
	if (Player1WinTimes > Computer2WinTimes)
		return enWinner::Player1;
	else if (Computer2WinTimes > Player1WinTimes)
		return enWinner::Computer;
	else
		enWinner::Draw;
}

stGameResults FillGameResults(int GameRounds, short Player1WinTimes, short Computer2WinTimes, short DrawTime) {
	stGameResults GameResults;
	GameResults.GameRounds = GameRounds;
	GameResults.Player1WinTimes = Player1WinTimes;
	GameResults.Computer2WinTimes = Computer2WinTimes;
	GameResults.DrawTime = DrawTime;
	GameResults.GameWinner = WhoWhoTheGame(Player1WinTimes, Computer2WinTimes);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);

	return GameResults;
}

stGameResults PlayGame(short HowManyRounds) {
	stRoundInfo RoundInfo;
	short Player1WinTimes = 0, Computer2WinTimes = 0, DrawTime = 0;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++) {
		cout << "\n Round [" << GameRound << "] begins:\n";

		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Computer) {
			Computer2WinTimes++;
		}
		else if (RoundInfo.Winner == enWinner::Player1) {
			Player1WinTimes++;
		}
		else {
			DrawTime++;
		}

		PrintRoundReaults(RoundInfo);

	}
	return FillGameResults(HowManyRounds, Player1WinTimes, Computer2WinTimes, DrawTime);
}

short HowManyRounds() {
	short GameRounds = 0;
	do {
		cout << "How Many Rounds 1 to 10?\n";
		cin >> GameRounds;
	} while (GameRounds < 1 || GameRounds > 10);

	return GameRounds;
}

string Tabs(short NumberofTabs) {
	string t = " ";
	for (int i = 1; i < NumberofTabs; i++) {
		t = t + "\t";
		cout << t;
	}
	return t;
}

void ShowGameOverScreen() {
	cout << Tabs(2) << "-----------------------------------------------\n\n";
	cout << Tabs(2) << "           ++++Game Over+++                      \n";
	cout << Tabs(2) << "-----------------------------------------------\n\n";
}

void showFinalresults(stGameResults GameResults) {
	cout << Tabs(2) << "---------------[Game Results]-----------------\n\n";
	cout << Tabs(2) << "Game Rounds        :" << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player1 Won Times  :" << GameResults.Player1WinTimes << endl;
	cout << Tabs(2) << "Computer Won Times :" << GameResults.Computer2WinTimes << endl;
	cout << Tabs(2) << "Draw Times         :" << GameResults.DrawTime << endl;
	cout << Tabs(2) << "Final Winner       :" << GameResults.WinnerName << endl;

	cout << Tabs(2) << "----------------------------------------------\n";

	SetWinnerScreencolor(GameResults.GameWinner);

}

void ResetScreen() {
	system("cls");
	system("color 0F");
}

void StartGame() {
	char PlayAgain = 'Y';
	do {
		ResetScreen();
		stGameResults GameResults = PlayGame(HowManyRounds());
		ShowGameOverScreen();
		showFinalresults(GameResults);

		cout << endl << Tabs(3) << "Do you want to play again? Y/N?\n";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}
int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}
