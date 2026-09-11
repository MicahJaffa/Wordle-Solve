#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "WordleHeader.h"

runWordle::runWordle(const std::string& filename, double multiplierBase_, double multiplierPos_)
{
	multiplierBase = multiplierBase_;
	multiplierPos = multiplierPos_;
	reAssign(filename, multiplierBase_, multiplierPos_);
    loadWordsFromFile(filename);
}

void runWordle::loadWordsFromFile(const std::string& filename)
{
    std::ifstream wordFile(filename);

    if (!wordFile.is_open()) {
        std::cerr << "Error: Could not open word file: " << filename << std::endl;
        return;
    }

    std::string currentWord;
    while (std::getline(wordFile, currentWord)) {
        if (!currentWord.empty()) {
            Words.push_back(currentWord);
        }
    }
}

bool runWordle::isReady() const
{
    return !Words.empty();
}

void runWordle::setPoints(const std::vector<std::vector<double>>& newPoints)
{
    points = newPoints;
}

std::vector<std::vector<double>> runWordle::getPoints() const
{
    return points;
}

std::vector<std::vector<double>> runWordle::setWeight(double multiplierBase_, double multiplierPos_) {

    // SAFETY: Guarantee vectors are sized before accessing to prevent out-of-bounds crashes
    if (unscaledPoints.size() != 26) {
        unscaledPoints = std::vector<std::vector<double>>(26, std::vector<double>(6, 0.0));
    }
    if (points.size() != 26) {
        points = std::vector<std::vector<double>>(26, std::vector<double>(6, 0.0));
    }

    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (j == 0) {
                points[i][j] = (unscaledPoints[i][j] * 100.0) * multiplierBase_;
            }
            else {
                points[i][j] = (unscaledPoints[i][j] * 100.0) * multiplierPos_;
            }
        }
    }

    multiplierBase = multiplierBase_;
    multiplierPos = multiplierPos_;
    return points;
}

std::vector<std::vector<double>> runWordle::reAssign(const std::string& filename, double multiplierBase_, double multiplierPos_)
{
    multiplierBase = multiplierBase_;
    multiplierPos = multiplierPos_;
    std::vector<std::vector<double>> times = {
           { 0,   0,      0,     0,    0,  0  }, // a
           { 0,   0,      0,     0,    0,  0  }, // b
           { 0,   0,      0,     0,    0,  0  }, // c
           { 0,   0,      0,     0,    0,  0  }, // d
           { 0,   0,      0,     0,    0,  0  }, // e
           { 0,   0,      0,     0,    0,  0  }, // f
           { 0,   0,      0,     0,    0,  0  }, // g
           { 0,   0,      0,     0,    0,  0  }, // h
           { 0,   0,      0,     0,    0,  0  }, // i
           { 0,   0,      0,     0,    0,  0  }, // j
           { 0,   0,      0,     0,    0,  0  }, // k
           { 0,   0,      0,     0,    0,  0  }, // l
           { 0,   0,      0,     0,    0,  0  }, // m
           { 0,   0,      0,     0,    0,  0  }, // n
           { 0,   0,      0,     0,    0,  0  }, // o
           { 0,   0,      0,     0,    0,  0  }, // p
           { 0,   0,      0,     0,    0,  0  }, // q
           { 0,   0,      0,     0,    0,  0  }, // r
           { 0,   0,      0,     0,    0,  0  }, // s
           { 0,   0,      0,     0,    0,  0  }, // t
           { 0,   0,      0,     0,    0,  0  }, // u
           { 0,   0,      0,     0,    0,  0  }, // v
           { 0,   0,      0,     0,    0,  0  }, // w
           { 0,   0,      0,     0,    0,  0  }, // x
           { 0,   0,      0,     0,    0,  0  }, // y
           { 0,   0,      0,     0,    0,  0  }, // z
    };
    std::ifstream wordFile(filename);

    if (!wordFile.is_open()) {
        std::cerr << "Error: Could not open word file: " << filename << std::endl;
        return times;
    }

    std::string currentWord;
    int num = 0;
    while (std::getline(wordFile, currentWord)) {
        if (!currentWord.empty() && currentWord.size() == 5) {
            num++;
            for (std::size_t pos = 0; pos < 5; ++pos) {
                char ch = std::tolower(static_cast<unsigned char>(currentWord[pos]));
                std::size_t idx = ch - 'a';


                times[idx][0] += 1.0;

                times[idx][pos + 1] += 1.0;

            }
        }
    }
		for (int i = 0; i < 26; ++i) {
			for (int j = 0; j < 6; ++j) {
				if (num > 0) {
					(times[i][j] /= num);
				}
			}
		}
        unscaledPoints = times;

		points = setWeight(multiplierBase, multiplierPos);
    return points;
}


void runWordle::WordInfo::GetPoints(runWordle& game)
{
    bool DoNotUse = false;

    if (game.WordOn < game.Words.size())
    {
        Word = game.Words[game.WordOn];
        game.WordOn++;

        if (Word.length() != 5)
        {
            DoNotUse = true;
            Points = 0;
        }
        else
        {
            for (int i = 0; i < (int)Word.length(); i++)
            {
                Points += game.GetLetterPoints(Word[i], i);


                for (int j = 0; j < i; j++)
                {
                    if (Word[i] == Word[j])
                    {
                        Points -= (game.GetLetterPoints(Word[i], i) * 0.7);
                    }
                }


                for (int j = 0; j < (int)game.LettersWrong.size(); j++)
                {
                    if (Word[i] == game.LettersWrong[j])
                    {
                        Points = 0;
                        return;
                    }
                }
            }

            for (int i = 0; i < (int)game.LettersRightWrong.size(); i++)
            {
                bool Used = false;
                for (int j = 0; j < (int)Word.length(); j++)
                {
                    if (Word[j] == game.LettersRightWrong[i] &&
                        Word[game.LettersRightWrongPlace[i]] != game.LettersRightWrong[i])
                    {
                        Used = true;
                    }
                }
                if (!Used)
                {
                    Points = 0;
                    return;
                }
            }

            for (int i = 0; i < (int)game.LettersRight.size(); i++)
            {
                if (Word[game.LettersRightPlace[i]] != game.LettersRight[i])
                {
                    Points = 0;
                    return;
                }
            }
        }
    }

    if (DoNotUse)
    {
        Points = 0;
    }
}

void runWordle::Reset()
{
    WordOn = 0;
    LettersWrong.clear();
    LettersRightWrong.clear();
    LettersRightWrongPlace.clear();
    LettersRight.clear();
    LettersRightPlace.clear();
}

std::vector<std::string> runWordle::PlayWordle(
    std::vector<char> NewLettersWrong,
    std::vector<char> NewLettersRightWrong,
    std::vector<int>  NewLettersRightWrongplace,
    std::vector<char> NewLettersRight,
    std::vector<int>  NewLettersRightPlace)
{
    WordOn = 0;

    for (char NewLetter : NewLettersWrong)
        LettersWrong.push_back(NewLetter);

    for (int i = 0; i < (int)NewLettersRightWrong.size(); i++)
    {
        LettersRightWrong.push_back(NewLettersRightWrong[i]);
        LettersRightWrongPlace.push_back(NewLettersRightWrongplace[i]);
    }

    for (int i = 0; i < (int)NewLettersRight.size(); i++)
    {
        LettersRight.push_back(NewLettersRight[i]);
        LettersRightPlace.push_back(NewLettersRightPlace[i]);
    }

    std::vector<WordInfo> InfoWords;
    for (int i = 0; i < (int)Words.size(); i++)
    {
        WordInfo NewWord;
        NewWord.GetPoints(*this);
        InfoWords.push_back(NewWord);
    }

    WordInfo BestWord, SecondWord, ThirdWord;

    for (int i = 0; i < (int)InfoWords.size(); i++)
    {
        if (InfoWords[i].Points > BestWord.Points)
            BestWord = InfoWords[i];
    }

    for (int i = 0; i < (int)InfoWords.size(); i++)
    {
        if (InfoWords[i].Word != BestWord.Word &&
            InfoWords[i].Points > SecondWord.Points)
            SecondWord = InfoWords[i];
    }

    for (int i = 0; i < (int)InfoWords.size(); i++)
    {
        if (InfoWords[i].Word != BestWord.Word &&
            InfoWords[i].Word != SecondWord.Word &&
            InfoWords[i].Points > ThirdWord.Points)
            ThirdWord = InfoWords[i];
    }

    return { BestWord.Word, SecondWord.Word, ThirdWord.Word };
}

double runWordle::GetLetterPoints(char Letter, int Place)
{
    char lower = std::tolower((unsigned char)Letter);
    if (lower < 'a' || lower > 'z') return 0.0;
    if (Place < 0 || Place > 4)   return 0.0;

    int idx = lower - 'a';
    return points[idx][0] + points[idx][Place + 1];
}