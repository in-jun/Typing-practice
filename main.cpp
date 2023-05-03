#include <iostream>
#include <unistd.h>
using std::cin;
using std::cout;
using std::string;

string words[] = {
    "auto", "double", "int", "struct", "break", "else", "long", "switch",
    "case", "enum", "register", "typedef", "char", "extern", "return", "union",
    "continue", "for", "signed", "void", "do", "if", "static", "while",
    "default", "goto", "sizeof", "volatile", "const", "float", "short",
    "unsigned", "class", "new", "this", "delete", "operator", "throw",
    "except", "private", "public", "finally", "protected", "virtual",
    "friend", "try", "is", "with", "assert", "range", "import", "failthrough",
    "defer", "func", "select", "interface", "package", "true", "false",
    "print", "var", "as", "get", "part", "set", "lambda", "yield", "async",
    "await", "constexpr", "static_assert", "decltype", "nullptr", "override",
    "final", "export", "inline", "noexcept", "namespace", "using", "template",
    "typename", "mutable", "explicit", "alignof", "alignas",
    "thread_local", "catch", "typeid", "type_info",
    "unique_ptr", "shared_ptr", "weak_ptr", "make_shared", "make_unique", "begin",
    "end", "reverse", "emplace", "emplace_back", "push_back", "pop_back", "front",
    "back", "insert", "erase", "find", "count", "lower_bound", "upper_bound",
    "equal_range", "empty", "size", "max_size", "reserve", "capacity", "shrink_to_fit",
    "sort", "stable_sort", "merge", "unique", "rotate", "next_permutation",
    "prev_permutation", "min", "max", "clamp", "abs", "fabs", "pow", "sqrt",
    "exp", "log", "log10", "sin", "cos", "tan", "asin", "acos", "atan",
    "rand", "srand", "time", "clock", "chrono", "system_clock", "steady_clock",
    "high_resolution_clock", "duration", "time_point", "async", "future", "promise",
    "packaged_task", "condition_variable", "mutex", "lock_guard", "unique_lock",
    "shared_lock", "recursive_mutex", "recursive_lock", "atomic", "memory_order",
    "thread", "this_thread", "chrono_literals", "type_traits", "tuple",
    "array", "vector", "deque", "list", "forward_list", "stack", "queue", "priority_queue",
    "map", "set", "unordered_map", "unordered_set", "bitset", "algorithm",
    "functional", "iterator", "numeric", "random", "regex", "iostream", "fstream",
    "sstream", "cstdio", "cstring", "string", "initializer_list",
    "exception", "stdexcept", "cmath", "cctype", "cwctype", "locale", "limits"};

int main()
{
    string input;
    int typo;
    while (true)
    {
        for (int i = 3; i > 0; i--)
        {
            cout << "\033[2J\033[H";
            cout << i << '\n';
            sleep(1);
        }
        typo = 0;
        cout << "\033[2J\033[H";
        for (int i = sizeof(words) / sizeof(*words) - 1; i >= 0; i--)
        {
            string word = words[i];
            while (true)
            {
                cout << " \033[0m" << word << " \033[36m" << i << "\n \033[32m";
                for (int i = 0; i < word.length(); i++)
                    cout << "─";
                cout << "\n:";
                getline(cin, input);
                cout << "\033[2J\033[H";
                if (input == word)
                    break;
                if (!input.empty())
                    typo++;
            }
        }
        cout << "\033[2J\033[H";
        cout << "typo: " << typo << '\n';
        sleep(5);
    }
    return 0;
}