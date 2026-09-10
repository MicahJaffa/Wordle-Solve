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
    std::vector<std::string> Words;
    std::vector<char> LettersWrong;
    std::vector<char> LettersRightWrong;
    std::vector<int>  LettersRightWrongPlace;
    std::vector<char> LettersRight;
    std::vector<int>  LettersRightPlace;
    double GetLetterPoints(char Letter, int Place);
    void loadWordsFromFile(const std::string& filename);

public:
    runWordle(const std::string& filename);
    void Reset();
    bool isReady() const;
    std::vector<std::string> PlayWordle(
        std::vector<char> NewLettersWrong,
        std::vector<char> NewLettersRightWrong,
        std::vector<int>  NewLettersRightWrongplace,
        std::vector<char> NewLettersRight,
        std::vector<int>  NewLettersRightPlace
    );
};