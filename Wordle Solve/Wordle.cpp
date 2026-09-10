#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "WordleHeader.h"

runWordle::runWordle(const std::string& filename)
{
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
                        Points -= (game.GetLetterPoints(Word[i], i) * 0.5);
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
    double ReturnValue = 0;
    switch (Letter)
    {
    case 'a':
        ReturnValue = 8.49;
        switch (Place)
        {
        case 0: ReturnValue += 6;        break;
        case 1: ReturnValue += 17;       break;
        case 2: ReturnValue += 9.722;    break;
        case 3: ReturnValue += 8.43892;  break;
        case 4: ReturnValue += 5.17381;  break;
        }
        return ReturnValue;
    case 'b':
        ReturnValue = 2.07;
        switch (Place)
        {
        case 0: ReturnValue += 7.38;    break;
        case 1: ReturnValue += 0.6416;  break;
        case 2: ReturnValue += 2.599;   break;
        case 3: ReturnValue += 1.85185; break;
        case 4: ReturnValue += 0.45;    break;
        }
        return ReturnValue;
    case 'c':
        ReturnValue = 4.5;
        switch (Place)
        {
        case 0: ReturnValue += 7.48863;  break;
        case 1: ReturnValue += 1.405;    break;
        case 2: ReturnValue += 2.99708;  break;
        case 3: ReturnValue += 3.20825;  break;
        case 4: ReturnValue += 0.958415; break;
        }
        return ReturnValue;
    case 'd':
        ReturnValue = 3.844;
        switch (Place)
        {
        case 0: ReturnValue += 5.56; break;
        case 1: ReturnValue += 0.66; break;
        case 2: ReturnValue += 3;    break;
        case 3: ReturnValue += 3.55; break;
        case 4: ReturnValue += 6.29; break;
        }
        return ReturnValue;
    case 'e':
        ReturnValue = 11.6;
        switch (Place)
        {
        case 0: ReturnValue += 2.46;   break;
        case 1: ReturnValue += 12.36;  break;
        case 2: ReturnValue += 6.8957; break;
        case 3: ReturnValue += 17.78;  break;
        case 4: ReturnValue += 11.93;  break;
        }
        return ReturnValue;
    case 'f':
        ReturnValue = 1.81;
        switch (Place)
        {
        case 0: ReturnValue += 4.85; break;
        case 1: ReturnValue += 0.18; break;
        case 2: ReturnValue += 1.34; break;
        case 3: ReturnValue += 1.75; break;
        case 4: ReturnValue += 0.64; break;
        }
        return ReturnValue;
    case 'g':
        ReturnValue = 2.47;
        switch (Place)
        {
        case 0: ReturnValue += 5.18; break;
        case 1: ReturnValue += 0.61; break;
        case 2: ReturnValue += 2.75; break;
        case 3: ReturnValue += 3.24; break;
        case 4: ReturnValue += 1.14; break;
        }
        return ReturnValue;
    case 'h':
        ReturnValue = 3.0;
        switch (Place)
        {
        case 0: ReturnValue += 3.97; break;
        case 1: ReturnValue += 4;    break;
        case 2: ReturnValue += 0.95; break;
        case 3: ReturnValue += 1.77; break;
        case 4: ReturnValue += 2.91; break;
        }
        return ReturnValue;
    case 'i':
        ReturnValue = 7.54;
        switch (Place)
        {
        case 0: ReturnValue += 1.34;    break;
        case 1: ReturnValue += 10.4451; break;
        case 2: ReturnValue += 8.15;    break;
        case 3: ReturnValue += 6.86;    break;
        case 4: ReturnValue += 2.2;     break;
        }
        return ReturnValue;
    case 'j':
        ReturnValue = 0.19;
        switch (Place)
        {
        case 0: ReturnValue += 1.64; break;
        case 1: ReturnValue += 0.08; break;
        case 2: ReturnValue += 8.15; break;
        case 3: ReturnValue += 6.86; break;
        case 4: ReturnValue += 2.23; break;
        }
        return ReturnValue;
    case 'k':
        ReturnValue = 1.1;
        switch (Place)
        {
        case 0: ReturnValue += 3.05; break;
        case 1: ReturnValue += 0.77; break;
        case 2: ReturnValue += 2.0;  break;
        case 3: ReturnValue += 3.66; break;
        case 4: ReturnValue += 2.2;  break;
        }
        return ReturnValue;
    case 'l':
        ReturnValue = 5.5;
        switch (Place)
        {
        case 0: ReturnValue += 4.68; break;
        case 1: ReturnValue += 5.63; break;
        case 2: ReturnValue += 6.29; break;
        case 3: ReturnValue += 5.9;  break;
        case 4: ReturnValue += 3.74; break;
        }
        return ReturnValue;
    case 'm':
        ReturnValue = 3;
        switch (Place)
        {
        case 0: ReturnValue += 5.62; break;
        case 1: ReturnValue += 1.51; break;
        case 2: ReturnValue += 3.95; break;
        case 3: ReturnValue += 3.11; break;
        case 4: ReturnValue += 1.41; break;
        }
        return ReturnValue;
    case 'n':
        ReturnValue = 6.65;
        switch (Place)
        {
        case 0: ReturnValue += 2.63; break;
        case 1: ReturnValue += 2.8;  break;
        case 2: ReturnValue += 7.27; break;
        case 3: ReturnValue += 6.18; break;
        case 4: ReturnValue += 4.1;  break;
        }
        return ReturnValue;
    case 'o':
        ReturnValue = 7.1;
        switch (Place)
        {
        case 0: ReturnValue += 2.12;  break;
        case 1: ReturnValue += 15.92; break;
        case 2: ReturnValue += 15.92; break;
        case 3: ReturnValue += 5.49;  break;
        case 4: ReturnValue += 2.9;   break;
        }
        return ReturnValue;
    case 'p':
        ReturnValue = 3.16;
        switch (Place)
        {
        case 0: ReturnValue += 6.97;  break;
        case 1: ReturnValue += 15.92; break;
        case 2: ReturnValue += 7.7;   break;
        case 3: ReturnValue += 5.5;   break;
        case 4: ReturnValue += 2.98;  break;
        }
        return ReturnValue;
    case 'q':
        ReturnValue = 0.1962;
        switch (Place)
        {
        case 0: ReturnValue += 0.63;  break;
        case 1: ReturnValue += 1.87;  break;
        case 2: ReturnValue += 0.1;   break;
        case 3: ReturnValue += 0.016; break;
        case 4: ReturnValue += 0.032; break;
        }
        return ReturnValue;
    case 'r':
        ReturnValue = 7.58;
        switch (Place)
        {
        case 0: ReturnValue += 5.1;  break;
        case 1: ReturnValue += 7.41; break;
        case 2: ReturnValue += 9.22; break;
        case 3: ReturnValue += 5.62; break;
        case 4: ReturnValue += 5.28; break;
        }
        return ReturnValue;
    case 's':
        ReturnValue = 5.73;
        switch (Place)
        {
        case 0: ReturnValue += 12.7; break;
        case 1: ReturnValue += 0.74; break;
        case 2: ReturnValue += 4.14; break;
        case 3: ReturnValue += 5.08; break;
        case 4: ReturnValue += 8.94; break;
        }
        return ReturnValue;
    case 't':
        ReturnValue = 6.95;
        switch (Place)
        {
        case 0: ReturnValue += 7.61; break;
        case 1: ReturnValue += 2.29; break;
        case 2: ReturnValue += 6.44; break;
        case 3: ReturnValue += 5.12; break;
        case 4: ReturnValue += 7.55; break;
        }
        return ReturnValue;
    case 'u':
        ReturnValue = 4.63;
        switch (Place)
        {
        case 0: ReturnValue += 2.19; break;
        case 1: ReturnValue += 9.52; break;
        case 2: ReturnValue += 5.58; break;
        case 3: ReturnValue += 3.82; break;
        case 4: ReturnValue += 0.82; break;
        }
        return ReturnValue;
    case 'v':
        ReturnValue = 1.01;
        switch (Place)
        {
        case 0: ReturnValue += 2.56; break;
        case 1: ReturnValue += 0.65; break;
        case 2: ReturnValue += 2.56; break;
        case 3: ReturnValue += 1.08; break;
        case 4: ReturnValue += 0.14; break;
        }
        return ReturnValue;
    case 'w':
        ReturnValue = 1.97;
        switch (Place)
        {
        case 0: ReturnValue += 4.96; break;
        case 1: ReturnValue += 2.07; break;
        case 2: ReturnValue += 1.43; break;
        case 3: ReturnValue += 1.37; break;
        case 4: ReturnValue += 0.64; break;
        }
        return ReturnValue;
    case 'x':
        ReturnValue = 0.15;
        switch (Place)
        {
        case 0: ReturnValue += 0.22; break;
        case 1: ReturnValue += 0.44; break;
        case 2: ReturnValue += 1.26; break;
        case 3: ReturnValue += 0.33; break;
        case 4: ReturnValue += 0.27; break;
        }
        return ReturnValue;
    case 'y':
        ReturnValue = 1.99;
        switch (Place)
        {
        case 0: ReturnValue += 2.72; break;
        case 1: ReturnValue += 3.03; break;
        case 2: ReturnValue += 2.1;  break;
        case 3: ReturnValue += 2.28; break;
        case 4: ReturnValue += 7.17; break;
        }
        return ReturnValue;
    case 'z':
        ReturnValue = 0.272;
        switch (Place)
        {
        case 0: ReturnValue += 0.02;   break;
        case 1: ReturnValue += 0.235;  break;
        case 2: ReturnValue += 1.064;  break;
        case 3: ReturnValue += 0.966;  break;
        case 4: ReturnValue += 0.2355; break;
        }
        return ReturnValue;
    default:
        return 0;
    }
}