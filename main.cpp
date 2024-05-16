#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "models.cpp"
using namespace std;

class QuizGame
{
private:
    int levelOfDifficulty;
    vector<Player> players;
    ofstream file;
    vector<Question> questions;

public:
    QuizGame() : levelOfDifficulty(0)
    {
        // file handling
        // exception handling for file opening
        try
        {
            file.open("scores.txt");
            if (!file.is_open())
            {
                // throwing error
                throw runtime_error("Failed to open scores file.");
            }
        }
        catch (const exception &e)
        {
            cerr << "Exception: " << e.what() << endl;
        }
    }

    // destructor
    ~QuizGame()
    {
        file.close();
    }

    void initializeQuestions()
    {
        SystemSettings::generateQuestions();

        // polymorphism
        // allows objects of different types to be treated as objects of a common superclass.
        for (int i = 0; i < 10; ++i)
        {
            if (levelOfDifficulty == 1)
            {
                questions.push_back(SystemSettings::firstLevelDifficultyQuestions[i]);
            }
            else if (levelOfDifficulty == 2)
            {
                questions.push_back(SystemSettings::secondLevelDifficultyQuestions[i]);
            }
            else if (levelOfDifficulty == 3)
            {
                questions.push_back(SystemSettings::thirdLevelDifficultyQuestions[i]);
            }
        }
    }

    void displayWelcomeMessage()
    {
        cout << "Hello. I am a quiz game. You can play and compete with other people. I have three levels of difficulty." << endl;
        cout << "Enter 1 to select first level of difficulty" << endl;
        cout << "Enter 2 to select second level of difficulty" << endl;
        cout << "Enter 3 to select third level of difficulty" << endl;
        cout << "Enter 0 to exit app" << endl;
    }

    int start()
    {
        displayWelcomeMessage();
        cin >> levelOfDifficulty;
        initializeQuestions();
        while (levelOfDifficulty != 0)
        {
            cout << endl
                 << "Welcome to the game." << endl;
            cout << "Enter 1 to add new player and start game for him/her" << endl;
            cout << "Enter 2 to end the game and print out results" << endl;
            int choice;
            cin >> choice;
            switch (choice)
            {
            case 1:
                addPlayer();
                break;
            case 2:
                printResults();
                return 0;
                break;
            default:
                cout << "Invalid choice." << endl;
                break;
            }
        }
        return 0;
    }

    void addPlayer()
    {
        string playerName;
        cout << endl
             << "Enter name of player: " << endl;
        cin >> playerName;
        Player newPlayer(playerName);
        players.push_back(newPlayer);
        cout << "Welcome to the game " << playerName << "." << endl;
        cout << "Let me introduce you to the rules of our game." << endl;
        cout << "You will be given " << questions.size() << " questions." << endl;
        cout << "At the end of the game, your score will be announced to you." << endl;
        cout << "When you select to end the whole game, your score will be compared with others and a leaderboard will be shown." << endl;
        cout << "We wish you luck. To start the game, press any number: ";
        int startGame;
        cin >> startGame;
        startGameForPlayer(newPlayer);
    }

    void startGameForPlayer(Player &player)
    {
        for (int i = 0; i < questions.size(); ++i)
        {
            cout << endl;
            Question &currentQuestion = questions[i];
            cout << "Question " << i + 1 << ": " << currentQuestion.getQuestionText() << endl;
            vector<OptionModel> options = currentQuestion.getOptions();
            int correctAnswer;
            for (size_t j = 0; j < options.size(); ++j)
            {
                cout << j + 1 << ". " << options[j].getOptionText() << endl;
                if (options[j].isCorrect() == 1)
                {
                    correctAnswer = j + 1;
                }
            }
            int answer;
            cout << "Enter your answer: ";
            cin >> answer;

            if (correctAnswer == answer)
            {
                player.increaseScore();
            }
        }
        printResults(player);
        players[players.size() - 1].setScore(player.getScore());
        file << player.getName() << ": " << player.getScore() << endl;
    }

    void printResults()
    {
        sort(players.begin(), players.end(), [](const Player &a, const Player &b)
             { return a.getScore() > b.getScore(); });
        cout << endl
             << "Leaderboard:" << endl;
        for (size_t j = 0; j < players.size(); ++j)
        {
            cout << players[j].getName() << ": " << players[j].getScore() << endl;
        }
    }

    // overloading
    void printResults(Player &player)
    {
        int score = player.getScore();
        cout << player.getName() << ", you got " << score << "/" << questions.size() << " correct answers." << endl;
        if (score >= 8)
        {
            cout << "We congratulate you! Keep up good work" << endl
                 << endl;
        }
        else if (score >= 5)
        {
            cout << "Good! Try harder" << endl
                 << endl;
        }
        else
        {
            cout << "Not bad! Try harder" << endl
                 << endl;
        }
    }
};

int main()
{
    QuizGame game;
    return game.start();
}
