#include <iostream>
#include <string>
#include <ctime>
#include <cmath>


using namespace std;

enum enLevel { Easy = 1, Medium = 2, Hard = 3, Mix = 4 };
enum enOperationType { Addition = 1, Subtraction = 2, Multiplication = 3, Division = 4, Mixed = 5 };

string GetQuestionsLevel(enLevel level) {
    string arrLevel[4] = { "Easy","Medium","Hard","Mix" };
    return arrLevel[level - 1];
}


string GetOperationType(enOperationType operation) {
    string arrOperations[5] = { "Addition","Subtraction","Multiplication","Division", "Mix" };
    return arrOperations[operation - 1];
}

int RandomNumber(int from, int to) {

    int number = rand() % (to - from + 1) + from;

    return number;
}

void ResetScreen() {
    system("CLS");
    system("color 0F");
}

void SetScreenColor(bool answer) {
    if(answer)
        system("color 2F");
    else 
        system("color 4F");
}

struct stQuestion {
    int number1 = 0;
    int number2 = 0;
    enLevel questionLevel;
    enOperationType questionOperation;
    float correctAnswer = 0;
    int playerAnswer = 0;
    bool answerResult = false;
};

struct stQuiz {

    stQuestion questions[100];
    short numQuestions;
    enLevel level;
    enOperationType operation;
    short wrongAnswers = 0;
    short rightAnswers = 0;
    bool isPass = false;
};


int getNumberByLevel(enLevel level) {
    switch (level)
    {
        case enLevel::Easy :
            return RandomNumber(0, 10);
            break;

        case enLevel::Medium :
            return RandomNumber(11, 50);
            break;

        case enLevel::Hard :
            return RandomNumber(51, 100);
            break;
        
        default:
            return RandomNumber(0, 100);
            break;
    }
}


enLevel ReadQuestionsLevel(short level) {
    switch (level)
    {
        case 1:
            return enLevel::Easy;
            break;

        case 2:
            return enLevel::Medium;
            break;

        case 3:
            return enLevel::Hard;
            break;
        
        case 4:
            return enLevel::Mix;
            break;
    }
}



enOperationType ReadOperationType(short operation) {
    switch (operation)
    {
        case 1:
            return enOperationType::Addition;
            break;

        case 2:
            return enOperationType::Subtraction;
            break;

        case 3:
            return enOperationType::Multiplication;
            break;
        
        case 4:
            return enOperationType::Division;
            break;
        
        case 5:
            return enOperationType::Mixed;
            break;
    }
}


enOperationType RandomOperation() {
    return ReadOperationType(RandomNumber(1, 4));
}

short ReadHowManyQuestions(string message) {

    short Number = 1;

    do {

        cout << message;
        cin >> Number;

    } while(Number < 1 || Number > 10);

    return Number;
}

enLevel ReadLevel(string message) {

    short level = 1;

    do {

        cout << message;
        cin >> level;

    } while(level < 1 || level > 4);

    return (enLevel)level;
}

enOperationType ReadOperation(string message) {

    short operation = 1;

    do {

        cout << message;
        cin >> operation;

    } while(operation < 1 || operation > 5);

    return (enOperationType)operation;
}

string GetOperationSymbol(enOperationType operation) {
    string arrOperations[4] = { "+","-","x","/" };
    return arrOperations[operation - 1];
}

float SimpleCalculator(int num1, int num2, enOperationType operation) {
    switch (operation)
    {
        case enOperationType::Addition :
            return num1 + num2;
            break;
        
        case enOperationType::Subtraction :
            return num1 - num2;
            break;
        
        case enOperationType::Multiplication :
            return num1 * num2;
            break;
        
        case enOperationType::Division :
            return num1 / num2;
            break;
    
    }
}

stQuestion GenerateQuestion(enLevel level, enOperationType operation) {
    
    stQuestion question;

    if(operation == enOperationType::Mixed)
        operation = RandomOperation();

    question.number1 = getNumberByLevel(level);
    question.number2 = getNumberByLevel(level);
    question.questionLevel = level;
    question.questionOperation = operation;
    question.correctAnswer = SimpleCalculator(question.number1, question.number2, operation);
    question.playerAnswer = 0;
    question.answerResult = false;

    return question;

}

void GenerateQuizQuestions(stQuiz & quiz) {
    for(int i = 0; i < quiz.numQuestions; i++) {
        quiz.questions[i] = GenerateQuestion(quiz.level, quiz.operation);
    }
}


int ReadQuestionAnswer() {
    int answer;
    cin >> answer;
    return answer;
}

void PrintTheQuestion(stQuiz & quiz, short questionNumber) {
    cout << "\n\nQuestion [" << questionNumber + 1 << "] :\n" << endl;
    cout << quiz.questions[questionNumber].number1 << endl;
    cout << quiz.questions[questionNumber].number2 << " " << GetOperationSymbol(quiz.questions[questionNumber].questionOperation) << endl;
    cout << "___________________________________" << endl;

}

void CorrectTheQuestionAnswer(stQuiz & quiz, short questionNumber) {
    if(quiz.questions[questionNumber].correctAnswer == quiz.questions[questionNumber].playerAnswer) {
        cout << "\nRight Answer :)";
        quiz.questions[questionNumber].answerResult = true;
        quiz.rightAnswers++;
    } else {
        cout << "\nWrong Answer :( , the correct answer is : " << quiz.questions[questionNumber].correctAnswer;
        quiz.questions[questionNumber].answerResult = false;
        quiz.wrongAnswers++;
    }
}

void AskAndCorrectQuestions(stQuiz & quiz) {
    for(int i = 0; i < quiz.numQuestions; i++) {
        PrintTheQuestion(quiz, i);
        quiz.questions[i].playerAnswer = ReadQuestionAnswer();
        CorrectTheQuestionAnswer(quiz, i);
    }
}

string GetFinalResult(bool pass) {
    if(pass)
        return "PASS";
    else
        return "FAIL";
}

void PrintQuizResults(stQuiz quiz) {
     cout << "\n\n_____________________________________________________________\n\n";
    cout << "Final Results is " << GetFinalResult(quiz.isPass);
    cout << "\n_____________________________________________________________\n\n";

    cout << "Number of questions     : " << quiz.numQuestions << endl;
    cout << "Questions Level         : " << GetQuestionsLevel(quiz.level) << endl;
    cout << "Operation Type          : " << GetOperationType(quiz.operation) << endl;
    cout << "Number of Right answers : " << quiz.rightAnswers << endl;
    cout << "Number of Wrong answers : " << quiz.wrongAnswers << endl;
    cout << "\n\n_____________________________________________________________\n\n";
}

void PlayMathGame() {

        stQuiz quiz;

        quiz.numQuestions = ReadHowManyQuestions("How many questions do you want to answer? ");
        quiz.level = ReadLevel("Enter questions level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ");
        quiz.operation = ReadOperation("Enter operation type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ");

        GenerateQuizQuestions(quiz);
        AskAndCorrectQuestions(quiz);
        PrintQuizResults(quiz);
}

void StartGame() {

    char PlayAgain = 'y';

    do {

        ResetScreen();
        PlayMathGame();

        cout << endl << "Do you want to play again? Y/N ";
        cin >> PlayAgain;

    } while(PlayAgain == 'Y' || PlayAgain == 'y');

}

int main() {

    srand((unsigned)time(NULL));

    StartGame();


    return 0;
}