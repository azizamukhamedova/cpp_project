#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class OptionModel
{
private:
    string optionText;
    bool isCorrectOption;

public:
    // default constructor
    OptionModel() : optionText(""), isCorrectOption(false) {}

    // named constructor
    OptionModel(const string &text, bool isCorrect) : optionText(text), isCorrectOption(isCorrect) {}

    // abstraction
    string getOptionText() const
    {
        return optionText;
    }

    bool isCorrect() const
    {
        return isCorrectOption;
    }
};

class Question
{
private:
    string questionText;
    vector<OptionModel> options;

public:
    Question() : questionText(""), options(vector<OptionModel>()) {}

    Question(const string &text, const vector<OptionModel> &opts) : questionText(text), options(opts) {}

    // const
    string getQuestionText() const
    {
        return questionText;
    }

    // final
    virtual vector<OptionModel> getOptions() final
    {
        return options;
    }
};

// inheritance
class FirstLevelOfDifficultyQuestion : public Question
{
public:
    FirstLevelOfDifficultyQuestion(const string &text, const vector<OptionModel> &opts) : Question(text, opts) {}
};

class SecondLevelOfDifficultyQuestion : public Question
{
public:
    SecondLevelOfDifficultyQuestion(const string &text, const vector<OptionModel> &opts) : Question(text, opts) {}
};

class ThirdLevelOfDifficultyQuestion : public Question
{
public:
    ThirdLevelOfDifficultyQuestion(const string &text, const vector<OptionModel> &opts) : Question(text, opts) {}
};

class Player
{
private:
    string name;
    int score;

public:
    Player() : name(""), score(0) {}

    Player(const string &playerName) : name(playerName), score(0) {}

    void setName(const string &playerName)
    {
        name = playerName;
    }

    void increaseScore()
    {
        score++;
    }

    void setScore(int val)
    {
        score = val;
    }

    int getScore() const
    {
        return score;
    }

    string getName() const
    {
        return name;
    }
};

class SystemSettings
{
public:
    // Static fields for questions of different difficulty levels
    inline static vector<FirstLevelOfDifficultyQuestion> firstLevelDifficultyQuestions;
    inline static vector<SecondLevelOfDifficultyQuestion> secondLevelDifficultyQuestions;
    inline static vector<ThirdLevelOfDifficultyQuestion> thirdLevelDifficultyQuestions;

    // Generate questions for each difficulty level
    static void generateQuestions()
    {
        generateFirstLevelQuestions();
        generateSecondLevelQuestions();
        generateThirdLevelQuestions();
    }

private:
    // Generate questions for first level of difficulty (addition)
    static void generateFirstLevelQuestions()
    {
        srand(time(nullptr)); // Seed the random number generator

        for (int i = 0; i < 10; ++i)
        {
            // Generate random numbers for the question
            int num1 = rand() % 50; // Random number between 0 and 50
            int num2 = rand() % 50; // Random number between 0 and 50
            string questionText = to_string(num1) + " + " + to_string(num2) + " = ?";
            vector<OptionModel> options = {OptionModel(to_string(num1 + num2), true), OptionModel(to_string(num1 + num2 + 1), false), OptionModel(to_string(num1 + num2 - 1), false)};
            firstLevelDifficultyQuestions.push_back(FirstLevelOfDifficultyQuestion(questionText, options));
        }
    }

    // Generate questions for second level of difficulty (multiplication)
    static void generateSecondLevelQuestions()
    {
        srand(time(nullptr)); // Seed the random number generator

        for (int i = 0; i < 10; ++i)
        {
            // Generate random numbers for the question
            int num1 = rand() % 10; // Random number between 0 and 10
            int num2 = rand() % 10; // Random number between 0 and 10
            string questionText = to_string(num1) + " * " + to_string(num2) + " = ?";
            vector<OptionModel> options = {OptionModel(to_string(num1 * num2), true), OptionModel(to_string(num1 * num2 + 1), false), OptionModel(to_string(num1 * num2 - 1), false)};
            secondLevelDifficultyQuestions.push_back(SecondLevelOfDifficultyQuestion(questionText, options));
        }
    }

    // Generate questions for third level of difficulty (addition, subtraction, and parentheses)
    static void generateThirdLevelQuestions()
    {
        srand(time(nullptr)); // Seed the random number generator

        for (int i = 0; i < 10; ++i)
        {
            // Generate random numbers for the question
            int num1 = rand() % 10; // Random number between 0 and 10
            int num2 = rand() % 10; // Random number between 0 and 10
            int num3 = rand() % 10; // Random number between 0 and 10
            int num4 = rand() % 10; // Random number between 0 and 10
            string questionText = "(" + to_string(num1) + " + " + to_string(num2) + ") - (" + to_string(num3) + " + " + to_string(num4) + ") = ?";
            vector<OptionModel> options = {OptionModel(to_string((num1 + num2) - (num3 + num4)), true), OptionModel(to_string((num1 + num2) - (num3 + num4) + 1), false), OptionModel(to_string((num1 + num2) - (num3 + num4) - 1), false)};
            thirdLevelDifficultyQuestions.push_back(ThirdLevelOfDifficultyQuestion(questionText, options));
        }
    }
};