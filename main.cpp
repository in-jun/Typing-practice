#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>
#include <cmath>
#include <sstream>

using namespace std;
using namespace std::chrono;

struct Style
{
    static const string ESC;
    static const string RESET;
    static const string BOLD;
    static const string DIM;
    static const string ITALIC;
    static const string UNDERLINE;
    static const string PRIMARY;
    static const string SECONDARY;
    static const string SUCCESS;
    static const string ERROR;
    static const string WARNING;
    static const string INFO;
    static const string MUTED;
    static const string HIDE_CURSOR;
    static const string SHOW_CURSOR;
    static const string CLEAR;

    static string gradient(int step, int total)
    {
        int r = 110 + (step * 20 / total);
        int g = 119 + (step * 15 / total);
        int b = 246 - (step * 30 / total);
        return ESC + "38;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m";
    }
};

const string Style::ESC = "\033[";
const string Style::RESET = ESC + "0m";
const string Style::BOLD = ESC + "1m";
const string Style::DIM = ESC + "2m";
const string Style::ITALIC = ESC + "3m";
const string Style::UNDERLINE = ESC + "4m";
const string Style::PRIMARY = ESC + "38;2;110;119;246m";
const string Style::SECONDARY = ESC + "38;2;165;180;252m";
const string Style::SUCCESS = ESC + "38;2;52;211;153m";
const string Style::ERROR = ESC + "38;2;248;113;113m";
const string Style::WARNING = ESC + "38;2;251;191;36m";
const string Style::INFO = ESC + "38;2;96;165;250m";
const string Style::MUTED = ESC + "38;2;156;163;175m";
const string Style::HIDE_CURSOR = ESC + "?25l";
const string Style::SHOW_CURSOR = ESC + "?25h";
const string Style::CLEAR = ESC + "2J" + ESC + "H";

class UI
{
private:
    static const int PREVIEW_COUNT = 3;
    static const int CONTENT_PADDING = 2;

    static string repeat(string str, int n)
    {
        string result;
        for (int i = 0; i < n; i++)
        {
            result += str;
        }
        return result;
    }

    static string createProgressBar(double progress, int width = 20)
    {
        int filledWidth = static_cast<int>(progress * width);
        string bar = repeat("━", filledWidth) + repeat("─", width - filledWidth);
        return Style::PRIMARY + bar + Style::RESET;
    }

public:
    static const int TERMINAL_WIDTH = 80;

    static string pad(int n)
    {
        return string(max(0, n), ' ');
    }

    static string center(const string &text, int width)
    {
        int padding = max(0, width - static_cast<int>(text.length()));
        return pad(padding / 2) + text + pad(padding - padding / 2);
    }

    static void clearScreen()
    {
        cout << Style::CLEAR;
    }

    static void printTopBar()
    {
        string title = "TYPING PRACTICE";
        string gradientTitle;

        for (size_t i = 0; i < title.length(); i++)
        {
            gradientTitle += Style::gradient(i, title.length()) + title[i];
        }

        cout << Style::BOLD
             << center(gradientTitle, TERMINAL_WIDTH)
             << Style::RESET << "\n\n";
    }

    static void printStats(int currentWord, int totalWords, double wpm, double cpm,
                           double accuracy, const string &time)
    {
        double progress = static_cast<double>(currentWord) / totalWords;

        stringstream ss;
        ss << Style::PRIMARY << setw(4) << (int)wpm << " WPM" << Style::RESET
           << "  "
           << Style::INFO << setw(4) << (int)cpm << " CPM" << Style::RESET
           << "  "
           << Style::SUCCESS << setw(3) << (int)accuracy << "%" << Style::RESET
           << "  "
           << Style::WARNING << time << Style::RESET
           << "  "
           << createProgressBar(progress, 20)
           << " "
           << Style::MUTED << "(" << (int)(progress * 100) << "%)" << Style::RESET;

        cout << pad(CONTENT_PADDING) << ss.str() << "\n\n";
    }

    static void printWordArea(const vector<string> &words, int currentIndex, bool error = false)
    {
        string currentStyle = error ? Style::ERROR : Style::PRIMARY;

        string content = pad(CONTENT_PADDING) + currentStyle + Style::BOLD + words[currentIndex] + Style::RESET;

        for (int i = 1; i <= PREVIEW_COUNT && currentIndex + i < static_cast<int>(words.size()); i++)
        {
            content += "  " + Style::MUTED + words[currentIndex + i] + Style::RESET;
        }

        cout << content << "\n\n"
             << pad(CONTENT_PADDING - 2)
             << Style::PRIMARY << "❯ " << Style::RESET;
    }

    static void printResults(const vector<pair<string, string>> &stats)
    {
        clearScreen();

        cout << Style::BOLD
             << "FINAL RESULTS"
             << Style::RESET << "\n\n";

        cout << Style::MUTED
             << repeat("─", 20)
             << Style::RESET << "\n\n";

        for (const auto &[key, value] : stats)
        {
            string arrow = " → ";
            cout << Style::PRIMARY << key
                 << Style::MUTED << arrow
                 << Style::SUCCESS << value
                 << Style::RESET << "\n";
        }

        cout << "\n"
             << Style::MUTED
             << "Press Enter to exit"
             << Style::RESET;

        cin.get();
    }

    static void printInstructions()
    {
        cout << Style::MUTED << "Instructions:"
             << Style::RESET << "\n\n"
             << Style::INFO << "• " << Style::RESET
             << "Type each word exactly as shown\n"
             << Style::INFO << "• " << Style::RESET
             << "Press Enter after each word\n"
             << Style::INFO << "• " << Style::RESET
             << "Press Enter with no input to quit\n\n";
    }
};

class TypingPractice
{
private:
    vector<string> words;
    int wordCount;
    int currentWordIndex;
    int typos;
    int totalChars;
    high_resolution_clock::time_point startTime;
    duration<double> elapsedTime;
    bool practiceActive;

    void shuffleWords()
    {
        random_device rd;
        mt19937 gen(rd());
        shuffle(words.begin(), words.end(), gen);
    }

    string formatTime(double seconds)
    {
        int mins = static_cast<int>(seconds) / 60;
        int secs = static_cast<int>(seconds) % 60;
        stringstream ss;
        ss << setfill('0') << setw(2) << mins << ":"
           << setfill('0') << setw(2) << secs;
        return ss.str();
    }

    void updateDisplay(bool error = false)
    {
        UI::clearScreen();
        UI::printTopBar();

        auto currentTime = high_resolution_clock::now();
        elapsedTime = duration_cast<duration<double>>(currentTime - startTime);

        double wpm = currentWordIndex / max(elapsedTime.count() / 60, 0.01);
        double cpm = totalChars / max(elapsedTime.count() / 60, 0.01);
        double accuracy = 100.0 - (static_cast<double>(typos) / max(currentWordIndex, 1) * 100);

        UI::printStats(currentWordIndex, wordCount, wpm, cpm, accuracy,
                       formatTime(elapsedTime.count()));
        UI::printWordArea(words, currentWordIndex, error);
    }

    void displayFinalResults()
    {
        double wpm = wordCount / elapsedTime.count() * 60;
        double cpm = totalChars / elapsedTime.count() * 60;
        double accuracy = 100.0 - (static_cast<double>(typos) / wordCount * 100);

        vector<pair<string, string>> stats = {
            {"Total Keystrokes", to_string(totalChars)},
            {"Words Completed ", to_string(wordCount)},
            {"Errors          ", to_string(typos)},
            {"Accuracy        ", to_string(accuracy).substr(0, 5) + "%"},
            {"WPM             ", to_string(wpm).substr(0, 6)},
            {"CPM             ", to_string(cpm).substr(0, 6)},
            {"Time            ", formatTime(elapsedTime.count())}};

        UI::printResults(stats);
    }

public:
    TypingPractice(const vector<string> &wordList, int count)
        : words(wordList),
          wordCount(min(count, static_cast<int>(wordList.size()))),
          currentWordIndex(0), typos(0), totalChars(0), practiceActive(true)
    {
        shuffleWords();
    }

    void start()
    {
        cout << Style::HIDE_CURSOR;

        for (int i = 3; i > 0; i--)
        {
            UI::clearScreen();
            UI::printTopBar();

            string countdown = "Starting in " + to_string(i) + "...";
            string circle = "◜◝◞◟"s;

            cout << Style::gradient(i, 3) << Style::BOLD
                 << UI::center(countdown, UI::TERMINAL_WIDTH) << "\n"
                 << UI::center(string(1, circle[i % 4]), UI::TERMINAL_WIDTH)
                 << Style::RESET;

            this_thread::sleep_for(chrono::milliseconds(800));
        }

        startTime = high_resolution_clock::now();

        while (currentWordIndex < wordCount && practiceActive)
        {
            updateDisplay();

            string input;
            getline(cin, input);

            if (input.empty())
            {
                practiceActive = false;
                break;
            }

            if (input == words[currentWordIndex])
            {
                totalChars += words[currentWordIndex].length();
                currentWordIndex++;
            }
            else
            {
                typos++;
                updateDisplay(true);
                this_thread::sleep_for(chrono::milliseconds(500));
            }
        }

        if (practiceActive)
        {
            displayFinalResults();
        }

        cout << Style::SHOW_CURSOR;
    }
};

int main()
{
    vector<string> words = {
        // 자주 사용되는 기본 키워드
        "if", "else", "for", "while", "do", "break", "continue", "return", "switch", "case",
        "class", "struct", "enum", "union", "typedef", "namespace", "using", "template",
        "public", "private", "protected", "virtual", "override", "default", "delete",
        "true", "false", "null", "nullptr", "void", "const", "static", "volatile",
        "try", "catch", "throw", "throws", "finally", "new", "this", "super",

        // 자료형
        "int", "long", "float", "double", "char", "bool", "byte", "short",
        "string", "array", "vector", "list", "map", "set", "queue", "stack",
        "unsigned", "signed", "size_t", "uint8_t", "uint16_t", "uint32_t", "uint64_t",

        // 함수와 관련된 키워드
        "function", "lambda", "callback", "async", "await", "yield", "promise",

        // 변수 선언
        "let", "var", "val", "const", "final", "mut", "auto",

        // 접근 제어와 스코프
        "export", "import", "from", "as", "extends", "implements", "interface",

        // 연산자 관련
        "operator", "sizeof", "typeof", "instanceof", "is", "in",

        // 모던 프로그래밍 개념
        "async", "await", "yield", "static", "final", "abstract", "synchronized",

        // 자주 사용되는 메서드명
        "toString", "valueOf", "length", "size", "push", "pop", "shift", "unshift",
        "map", "filter", "reduce", "forEach", "find", "some", "every", "includes",

        // 예외처리
        "error", "exception", "throw", "throws", "try", "catch", "finally",

        // 타입스크립트 관련
        "type", "interface", "enum", "implements", "declare", "readonly",

        // 러스트 관련
        "fn", "impl", "trait", "mod", "pub", "use", "where", "move",

        // 파이썬 관련
        "def", "class", "self", "pass", "raise", "with", "as", "import",
        "from", "global", "nonlocal", "lambda", "yield", "assert",

        // 자바스크립트 관련
        "undefined", "NaN", "Infinity", "prototype", "constructor",
        "addEventListener", "removeEventListener", "setTimeout", "setInterval",

        // SQL 관련
        "select", "from", "where", "group", "having", "order", "by", "join",
        "insert", "update", "delete", "create", "alter", "drop", "table",

        // Git 관련 명령어
        "git", "commit", "push", "pull", "merge", "branch", "checkout", "rebase",

        // 프로그래밍 패러다임 관련
        "class", "object", "function", "method", "property", "attribute",

        // 자주 사용되는 변수명
        "index", "count", "total", "result", "value", "data", "item", "element",
        "key", "name", "type", "id", "code", "status", "message", "error",

        // 웹 개발 관련
        "fetch", "response", "request", "header", "body", "params", "query",
        "router", "route", "middleware", "controller", "service", "model",

        // 테스트 관련
        "test", "expect", "assert", "describe", "it", "should", "mock", "spy"};

    UI::clearScreen();

    string welcome = "Welcome to Typing Practice";
    for (size_t i = 0; i < welcome.length(); i++)
    {
        cout << Style::gradient(i, welcome.length()) << Style::BOLD << welcome[i];
        this_thread::sleep_for(chrono::milliseconds(30));
    }
    cout << Style::RESET << "\n\n";

    UI::printInstructions();

    cout << Style::MUTED
         << UI::center("Press Enter to start...", UI::TERMINAL_WIDTH)
         << Style::RESET;

    cin.get();

    TypingPractice practice(words, words.size());
    practice.start();

    return 0;
}