#include <iostream>
#include <unistd.h>
#include <string>
#include <chrono>
using std::cin;
using std::cout;
using std::stoi;
using std::string;
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;

const string ESC = "\033[";
const string CLEAR_SCREEN = ESC + "2J" + ESC + "H";
const string RESET_FORMATTING = ESC + "0m";
const string TEXT_BOLD = ESC + "1m";
const string TEXT_COLOR_GREEN = ESC + "32m";
const string TEXT_COLOR_CYAN = ESC + "36m";
const string HIDE_CURSOR = ESC + "?25l";

string words[] = {"AES", "API", "AR", "AWS", "Actuator", "Actuators", "Aerodynamics", "Aerospace", "Agile", "Aircraft design", "Alt text", "Android", "Angular", "Arc", "Arduino", "Aria roles", "Array", "ArrayList", "Artifact", "AsMut", "AsRef", "Atom", "AtomicBool", "Azure", "BERT", "Big data", "Bioinformatics", "Bitbucket", "Blockchain", "Box", "BufRead", "C", "C++", "CI/CD", "CSS", "CSS3", "Cartography", "Cell", "CircleCI", "Clone", "Code generation", "Collections", "Collision detection", "Comparable", "Comparator", "Computer vision", "Containerization", "Copy", "Cow", "Cryptocurrency", "Cryptography", "Cypress", "DELETE", "DNS", "DOCTYPE", "DOM", "Data analysis", "Data visualization", "Debug", "Decentralized", "Declarative", "Decorator", "Decryption", "Default", "Deployment", "Deref", "DigitalOcean", "Django", "Docker", "Drop", "ES6", "Eclipse", "Embedded system", "Encryption", "Entanglement", "Eq", "Err", "Err(_)", "Ethereum", "Exception", "Express", "FALSE", "FIFO", "FROM", "Factory", "False", "Firebase", "Firewall", "Firmware", "Flask", "Flutter", "Fn", "FnMut", "FnOnce", "From", "Functional", "GIS", "GPS", "GROUP BY", "GUI", "Game design", "Game loop", "Genomics", "Git", "GitHub", "GitLab", "GitLab CI", "Go", "Google Cloud Platform", "GraphQL", "HCI", "HMI", "HTML", "HTML5", "HTTP", "HTTPS", "Hash", "HashMap", "HashSet", "Heroku", "Hololens", "Hypervisor", "IDE", "INSERT", "Imperative", "Industrial control system", "Infinity", "IntelliJ IDEA", "Interaction design", "Into", "Intrusion detection", "IoT", "Iterator", "JOIN", "JSON", "JUnit", "Java", "JavaScript", "Jenkins", "Jest", "Kanban", "Keras", "Keyboard navigation", "Kotlin", "Kubernetes", "Laravel", "Lexer", "LinkedList", "Linux", "MATLAB", "MXNet", "Machine learning", "Malware", "Markdown", "Microcontroller", "Microservices", "Mocha", "MongoDB", "Monolithic", "Mutex", "MySQL", "NLP", "NULL", "NaN", "Named entity recognition", "Node.js", "None", "ORDER BY", "Object-oriented", "Observer", "Oculus", "Ok", "Ok(())", "Optimization", "Option", "Orbital mechanics", "Ord", "PHP", "PID control", "PLC", "POS tagging", "Parser", "PartialEq", "PartialOrd", "Phylogenetics", "Pipeline", "PostgreSQL", "Proteomics", "Prototyping", "PyCharm", "PyTorch", "Pytest", "Python", "Quantum", "Quantum entanglement", "Quantum gate", "Quantum mechanics", "Quantum superposition", "Qubit", "R", "RAD", "REST", "RESTful", "ROS", "RSA", "RTOS", "Raspberry Pi", "Rc", "React", "React Native", "Redis", "RefCell", "Remote sensing", "Result", "Robot", "Rollback", "Router", "Ruby", "Ruby on Rails", "Runnable", "RwLock", "SCADA", "SELECT", "SOAP", "SQL", "SQLite", "Scikit-learn", "Screen reader", "Scrum", "Selenium", "Self", "Semantic analysis", "Sensor", "Sensors", "Sequence alignment", "Serverless", "Singleton", "Smart contract", "Some", "Spacecraft", "Spatial analysis", "Spring", "Spring Boot", "Statistics", "Strategy", "String", "Sublime Text", "Superposition", "Swift", "SwiftUI", "TCP/IP", "TRUE", "TensorFlow", "Thread", "Tokenization", "Travis CI", "True", "TypeScript", "UDP", "UNIX", "UPDATE", "URI", "URL", "Unicode", "Unity", "Unity XR", "Unreal Engine", "Usability", "User experience", "User interface", "User testing", "User-centered design", "VMware", "VPN", "VR", "VSCode", "Vec", "Virtual machine", "VirtualBox", "Virus", "Vive", "Vue", "WCAG", "WHERE", "Waterfall", "Wave-particle duality", "Web", "WebAssembly", "WebSocket", "Windows", "Wireframe", "Write", "XML", "XMLHttpRequest", "Xamarin", "YAML", "a", "abs", "abstract", "abstraction", "acceleration", "access", "accumulate", "accumulator", "acos", "adapter", "addEventListener", "address", "adjacent_difference", "aggregate", "aggregator", "agile", "alert", "algorithm", "alias", "aliasing", "alignas", "alignof", "alloc", "allocate", "allocation", "analog", "and", "annotation", "appendChild", "applicative", "architecture", "argument", "arithmetic", "array", "arrow_function", "as", "asin", "assembler", "assembly", "assert", "assert_eq", "assert_ne", "async", "async_function", "asynchronous", "atan", "atomic", "attribute", "authentication", "authorization", "auto", "automation", "await", "back", "backbone", "backend", "background", "bandwidth", "base64", "begin", "bench", "bench!", "binary", "binary_search", "binding", "bitmap", "bitset", "body", "bool", "boolean", "bootstrap", "bootstrapping", "border", "boundary", "box", "break", "buffer", "bug", "byte", "bytecode", "cache", "callback", "canonical", "capacity", "cascade", "case", "casting", "catch", "cctype", "cfg", "cfg!", "cfg_attr", "cfg_attr!", "chan", "char", "character", "checksum", "chrono", "chrono_literals", "circuit", "clamp", "class", "classList", "classical", "clearInterval", "clearTimeout", "client", "clock", "closure", "cloud", "cluster", "cmath", "code", "coercion", "cohesion", "cold", "collaboration", "collation", "collection", "color", "compiler", "composition", "compression", "concatenation", "concurrency", "concurrent", "condition_variable", "conditional", "configuration", "confirm", "console", "const", "const_cast", "constexpr", "constraint", "construct", "constructor", "container", "context", "continue", "conversion", "cookie", "copy", "core", "coroutine", "cos", "count", "crash", "crate", "createElement", "createTextNode", "creational", "cstdio", "cstring", "cursor", "cwctype", "cybersecurity", "database", "dbg", "deadlock", "debugging", "declaration", "declare", "decltype", "decomposition", "deduplication", "def", "default", "default_constructor", "defer", "deferred", "deinit", "delete", "dependency", "deployment", "deprecated", "deque", "dereference", "derive", "derive!", "descriptor", "design", "destruct", "directive", "disassembler", "dispatch", "display", "distributed", "div", "do", "document", "domain", "double", "duration", "dyn", "dynamic", "dynamic_cast", "echo", "efficiency", "element", "elif", "else", "elseif", "elsif", "emplace", "emplace_back", "empty", "emulator", "encapsulation", "encoding", "encryption", "end", "endpoint", "ensure", "entity", "enum", "equal_range", "equivalence", "erase", "error", "escape_sequence", "event", "except", "exception", "exception_handling", "execution", "exp", "expect", "explicit", "exponential", "export", "export_name", "extends", "extension", "extern", "extern crate", "f32", "f64", "fabs", "factory", "failthrough", "fallback", "false", "fetch", "file", "filesystem", "filter", "final", "finally", "find", "firewall", "flex", "float", "float_point", "fn", "font-size", "for", "forEach", "foreach", "format", "forward_list", "framework", "friend", "from", "front", "front-end", "frontend", "fstream", "fun", "func", "function", "functional", "future", "garbage", "garbage_collection", "gateway", "generic", "get", "getAttribute", "getElementById", "getter", "go", "goto", "grid", "guard", "handler", "hashing", "head", "header", "heap", "heuristic", "hexadecimal", "hierarchical", "high_resolution_clock", "hoisting", "host", "hotfix", "html", "i128", "i16", "i32", "i64", "i8", "iOS", "icon", "identifier", "if", "img", "immutable", "impl", "implementation", "implements", "implicit", "import", "in", "incremental", "index", "inference", "infinite", "inheritance", "init", "initializer_list", "injection", "inline", "innerHTML", "innerTextabstract", "inner_product", "input", "insert", "instance", "instanceof", "instantiation", "int", "integer", "interceptor", "interface", "internal", "interpolation", "interpreter", "invocation", "io", "iostream", "iota", "is", "isize", "isolate", "iteration", "iterator", "jQuery", "kernel", "keyword", "lambda", "latency", "legacy", "let", "li", "library", "lifecycle", "lifetime", "limits", "link", "link_name", "link_section", "linker", "list", "listener", "literal", "localStorage", "locale", "localization", "lock_guard", "locking", "log", "log10", "logarithmic", "logging", "long", "loop", "lower_bound", "macOS", "machine", "macro", "make_shared", "make_unique", "managed", "manifest", "map", "margin", "marshal", "match", "max", "max_size", "memory_order", "merge", "metadata", "method", "middleware", "migration", "min", "mod", "model", "module", "monitor", "monitoring", "move", "multiprocessing", "must_use", "mut", "mutable", "mutex", "namespace", "native", "nested", "network", "new", "next", "next_permutation", "nil", "no_link", "no_mangle", "node", "noexcept", "not", "null", "nullptr", "numeric", "object", "observer", "ol", "ontology", "opcode", "operand", "operating", "operator", "optimization", "or", "otherwise", "outerHTML", "overhead", "overload", "override", "p", "package", "packaged_task", "packet", "padding", "pagination", "pair", "panic", "paradigm", "parameter", "parse", "parser", "parsing", "part", "partial_sum", "partition", "pattern", "payload", "persistent", "pixel", "platform", "pointer", "polymorphism", "pop_back", "portability", "position", "pow", "pragma", "preprocessor", "prev_permutation", "primitive", "print", "println", "priority_queue", "priv", "private", "procedure", "process", "processing", "promise", "prompt", "protected", "protocol", "prototype", "proxy", "pub", "pub(crate)", "pub(in path)", "pub(self)", "pub(super)", "public", "push_back", "query", "querySelector", "querySelectorAll", "queue", "race", "raise", "rand", "random", "range", "range-based", "reactive", "read", "read_line", "read_to_string", "recursion", "recursive_lock", "recursive_mutex", "red-black", "redo", "reduce", "ref", "refactoring", "reflection", "regex", "register", "rehashing", "reinterpret_cast", "reject", "reliable", "removeChild", "removeEventListener", "rendering", "repeat", "repository", "repr", "request", "rescue", "reserve", "resolve", "resource", "responsive", "return", "return_type", "reusability", "reverse", "robust", "rollback", "rotate", "router", "routing", "runtime", "sandbox", "sandboxing", "scalability", "scalar", "schema", "scope", "script", "sealed", "security", "select", "self", "serialization", "server", "session", "sessionStorage", "set", "setAttribute", "setInterval", "setTimeout", "set_difference", "set_intersection", "set_symmetric_difference", "set_union", "setter", "shared_lock", "shared_ptr", "short", "shrink_to_fit", "shuffle", "side_effect", "signed", "sin", "singleton", "size", "sizeof", "sort", "source", "sqrt", "srand", "sstream", "stable_sort", "stack", "stack_frame", "stateful", "stateless", "statement", "static", "static_assert", "static_cast", "std", "std::io", "stdexcept", "steady_clock", "storage", "stream", "strictfp", "string", "string_literal", "stringify", "struct", "structural", "style", "subroutine", "subscript", "super", "switch", "sync", "synchronization", "synchronized", "syntax", "system", "system_clock", "table", "tan", "target_endian", "target_pointer_width", "td", "template", "template_specialization", "test", "test!", "testing", "textContent", "th", "then", "this", "this_thread", "thread", "thread_local", "thread_pool", "throw", "throws", "time", "time_point", "timeout", "todo", "todo!", "token", "topological", "tr", "trait", "transaction", "transformation", "transient", "transpiler", "true", "try", "try!", "tuple", "type", "type_info", "type_traits", "typedef", "typeid", "typename", "u128", "u16", "u32", "u64", "u8", "ul", "undefined", "unicode", "unimplemented", "union", "unique", "unique_lock", "unique_ptr", "unit", "unit_test", "unless", "unmanaged", "unordered_map", "unordered_set", "unreachable", "unreachable!()", "unsafe", "unsigned", "until", "unwrap", "upper_bound", "use", "using", "usize", "val", "validation", "var", "variable", "vector", "version", "versioning", "virtual", "virtual_function", "void", "volatile", "weak_ptr", "when", "where", "while", "wildcard", "window", "with", "workflow", "wrapper", "write", "writeln", "yield", "zero-day", "zero_initialized"};

void displayWord(const string &word, int index)
{
    cout << ' ' + TEXT_BOLD << word << ' ' + RESET_FORMATTING;
    cout << TEXT_BOLD + TEXT_COLOR_CYAN << index << RESET_FORMATTING << '\n';
    cout << ' ' + TEXT_BOLD + TEXT_COLOR_CYAN + TEXT_COLOR_GREEN;
    for (int i = 0; i < word.length(); i++)
        cout << "─";
}

void pauseAndDisplayWord(const string &word, int index, duration<int64_t, std::nano> &elapsedTime)
{
    high_resolution_clock::time_point startTime = high_resolution_clock::now();
    displayWord(word, index);
    cin.get();
    cout << CLEAR_SCREEN + RESET_FORMATTING;
    high_resolution_clock::time_point endTime = high_resolution_clock::now();
    elapsedTime -= endTime - startTime;
}

int main(int argc, char *argv[])
{
    int numberOfWords;
    if (argc == 2)
    {
        numberOfWords = stoi(argv[1]);

        if (numberOfWords <= 0 || numberOfWords > size(words))
        {
            cout << "Please enter a number between 1 and " << size(words) << ".\n";
            return 1;
        }
    }
    else
    {
        numberOfWords = size(words);
    }

    cout << HIDE_CURSOR;
    for (int i = 3; i > 0; i--)
    {
        cout << CLEAR_SCREEN;
        cout << i << '\n';
        sleep(1);
    }

    int typoCount = 0;
    int totalWordsTyped = 0;
    int totalCharactersTyped = 0;

    duration<int64_t, std::nano> elapsedTime;
    high_resolution_clock::time_point startTime = high_resolution_clock::now();

    cout << CLEAR_SCREEN;

    for (int i = numberOfWords - 1; i >= 0; i--)
    {
        string currentWord = words[i];

        while (true)
        {
            displayWord(currentWord, i + 1);
            cout << "\n:";

            string userInput;
            getline(cin, userInput);

            cout << CLEAR_SCREEN + RESET_FORMATTING;

            if (userInput == currentWord)
            {
                totalWordsTyped++;
                totalCharactersTyped += currentWord.length();
                break;
            }

            if (userInput.empty())
                pauseAndDisplayWord(currentWord, i + 1, elapsedTime);
            else
                typoCount++;
        }
    }

    high_resolution_clock::time_point endTime = high_resolution_clock::now();
    elapsedTime += endTime - startTime;
    duration<double> elapsedTimeSeconds = duration_cast<duration<double>>(elapsedTime);

    cout << CLEAR_SCREEN + RESET_FORMATTING;
    cout << "Typo Count: " << typoCount << '\n';
    cout << "Typo Rate: " << static_cast<double>(typoCount) / totalWordsTyped * 100 << "%\n";
    cout << "Total Characters Typed: " << totalCharactersTyped << '\n';
    cout << "Time Elapsed: " << elapsedTimeSeconds.count() << " seconds\n";
    cout << "Characters Per Minute (CPM): " << (totalCharactersTyped / elapsedTimeSeconds.count()) * 60 << '\n';
    cout << "Words Per Minute (WPM): " << (totalWordsTyped / elapsedTimeSeconds.count()) * 60 << '\n';

    return 0;
}