#include <iostream>
#include <string>
#include <ctime>
#include <cmath>


using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissor = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo {
    short roundNumber = 0;
    enGameChoice playerChoice;
    enGameChoice computerChoice;
    enWinner winner;
    string winnerName;
};

struct stGameResults {

    short gameRounds = 0;
    short playerWins = 0;
    short computerWins = 0;
    short drawTimes = 0;
    enWinner gameWinner;
    string WinnerName = "";
};

int RandomNumber(int from, int to) {

    int number = rand() % (to - from + 1) + from;

    return number;
}

string WinnerName(enWinner winner) {
    return (winner == enWinner::Draw) ? "Draw" : (winner == enWinner::Player) ? "Player" : "Computer";
}

enWinner WhoWonTheRound(stRoundInfo roundInfo) {

    if(roundInfo.playerChoice == roundInfo.computerChoice) {
        return enWinner::Draw;
    }

    if((roundInfo.playerChoice == enGameChoice::Stone && roundInfo.computerChoice == enGameChoice::Scissor) || (roundInfo.playerChoice == enGameChoice::Scissor && roundInfo.computerChoice == enGameChoice::Paper) || (roundInfo.playerChoice == enGameChoice::Paper && roundInfo.computerChoice == enGameChoice::Stone)) {
        return enWinner::Player;
    }
    
    return enWinner::Computer;
}

string ChoiceName(enGameChoice choice) {

    switch(choice) {

        case enGameChoice::Stone:
            return "Stone";
            break;
        
        case enGameChoice::Paper:
            return "Paper";
            break;

        case enGameChoice::Scissor:
            return "Scissor";
            break;

    }
}

void SetWinnerScreenColor(enWinner winner) {
    switch(winner) {

        case enWinner::Player:
            system("color 2F");
            break;

        case enWinner::Computer:
            system("color 4F");
            cout << "\a";
            break;

        case enWinner::Draw:
            system("color 6F");
            break;
    }
}

void PrintRoundResults(stRoundInfo roundInfo) {
    cout << "\n____________Round [" << roundInfo.roundNumber << "] ____________\n\n";
    cout << "Player choice: " << ChoiceName(roundInfo.playerChoice) << endl;
    cout << "Computer choice: " << ChoiceName(roundInfo.computerChoice) << endl;
    cout << "Round winner: " << roundInfo.winnerName << "] \n";
    cout << "__________________________\n";

    SetWinnerScreenColor(roundInfo.winner);

}

enWinner WhoWonTheGame(short playerWins, short computerWins) {
    if(playerWins > computerWins) {
        return enWinner::Player;
    } else if(playerWins < computerWins) {
        return enWinner::Computer;
    } else {
        return enWinner::Draw;
    }
}

stGameResults FillGameResults(int gameRounds, short playerWins, short computerWins, short drawTimes) {

    stGameResults gameResults;

    gameResults.gameRounds = gameRounds;
    gameResults.playerWins = playerWins;
    gameResults.computerWins = computerWins;
    gameResults.drawTimes = drawTimes;
    gameResults.gameWinner = WhoWonTheGame(playerWins, computerWins);
    gameResults.WinnerName = WinnerName(gameResults.gameWinner);

    return gameResults;

}

enGameChoice ReadPlayerChoice() {

    short choice;

    do {

        cout << "\nYour choice: [1]:stone, [2]:paper, [3]:scissor ? ";
        cin >> choice;

    } while(choice < 1 && choice > 3);

    return (enGameChoice)choice;
}

enGameChoice GetComputerChoice() {
    return (enGameChoice)RandomNumber(1, 3);
}

stGameResults PlayGame(short rounds) {
    stRoundInfo roundInfo;
    short playerWins = 0, computerWins = 0, drawTimes = 0;

    for(short gameRound = 1; gameRound <= rounds ; gameRound++) {
        cout << "\nRound[" << gameRound << "]" << " begins: \n";
        roundInfo.roundNumber = gameRound;
        roundInfo.playerChoice = ReadPlayerChoice();
        roundInfo.computerChoice = GetComputerChoice();
        roundInfo.winner = WhoWonTheRound(roundInfo);
        roundInfo.winnerName = WinnerName(roundInfo.winner);

        if(roundInfo.winner == enWinner::Player) {
            playerWins++;
        } else if(roundInfo.winner == enWinner::Computer) {
            computerWins++;
        } else {
            drawTimes++;
        }

        PrintRoundResults(roundInfo);
    }

    return FillGameResults(rounds, playerWins, computerWins, drawTimes);

}


string Tabs(short NumberOfTabs) {

    string tabs;

    for(int i= 0; i < NumberOfTabs; i++) {
        tabs += '\t';
    }

    return tabs;
}


void ShowGameOverScreen() {
    cout << Tabs(2) << "___________________________________________________________________________\n\n";
    cout << Tabs(2) << "                            +++ G a m e  O v e r +++\n";
    cout << Tabs(2) << "___________________________________________________________________________\n\n";
}


void ShowFinalGameResults(stGameResults GameResults) {

    cout << Tabs(2) << "_________________________ [Game Results] _________________________\n\n";
    cout << Tabs(2) << "Game rounds        : " << GameResults.gameRounds << endl;
    cout << Tabs(2) << "Player won times   : " << GameResults.playerWins << endl;
    cout << Tabs(2) << "Computer won times : " << GameResults.computerWins << endl;
    cout << Tabs(2) << "Draw times         : " << GameResults.drawTimes << endl;
    cout << Tabs(2) << "Final winner       : " << GameResults.WinnerName << endl;
    cout << Tabs(2) << "__________________________________________________________________";

    SetWinnerScreenColor(GameResults.gameWinner);
}


short ReadHowManyRounds() {

    short Number = 1;

    do {

        cout << "How many rounds from 1 to 10? ";
        cin >> Number;

    } while(Number < 1 && Number > 10);

    return Number;
}

void ResetScreen() {
    system("CLS");
    system("color 0F");
}

void StartGame() {

    char PlayAgain = 'y';

    do {

        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);

        cout << endl << Tabs(3) << "Do you want to play again? Y/N ";
        cin >> PlayAgain;

    } while(PlayAgain == 'Y' || PlayAgain == 'y');
}

int main() {

    srand((unsigned)time(NULL));

    StartGame();


    return 0;
}