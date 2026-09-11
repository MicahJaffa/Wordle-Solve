#pragma once
#include <string>
#include <vector>

#ifdef WORDLESOLVE_EXPORTS
#define WORDLE_API __declspec(dllexport)
#else
#define WORDLE_API __declspec(dllimport)
#endif

class WORDLE_API runWordle
{
private:
    struct WordInfo
    {
        std::string Word;
        double Points = 0;
        void GetPoints(runWordle& game);
    };
    int WordOn = 0;
	double multiplierBase = 0.3;
	double multiplierPos = 1.0;
    std::vector<std::vector<double>> points;
    std::vector<std::vector<double>> unscaledPoints;
    std::vector<std::string> Words;
    std::vector<char> LettersWrong;
    std::vector<char> LettersRightWrong;
    std::vector<int>  LettersRightWrongPlace;
    std::vector<char> LettersRight;
    std::vector<int>  LettersRightPlace;
    double GetLetterPoints(char Letter, int Place);
    void loadWordsFromFile(const std::string& filename);

public:
    runWordle(const std::string& filename, double multiplierBase_ = 0.4, double multiplierPos_ = 1.7);
    void Reset();
    bool isReady() const;
	void setPoints(const std::vector<std::vector<double>>& newPoints);
	std::vector<std::vector<double>> getPoints() const;
    std::vector<std::vector<double>> setWeight(double multiplierBase_, double multiplierPos_);
    std::vector<std::vector<double>> reAssign(const std::string& filename, double multiplierBase_ = 0.4, double multiplierPos_ = 1.7);
    std::vector<std::string> PlayWordle(
        std::vector<char> NewLettersWrong,
        std::vector<char> NewLettersRightWrong,
        std::vector<int>  NewLettersRightWrongplace,
        std::vector<char> NewLettersRight,
        std::vector<int>  NewLettersRightPlace
    );
};