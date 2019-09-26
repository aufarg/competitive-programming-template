${-- /*
    Vexorian's c++ tester template for greed. Version 0.1
    - Colors using ANSI C codes.
    - Allow custom test cases with unknown result.
    - Allow "disabling" custom test cases by modifying the list of tests to run.
    - Timeout for individual cases, modify CASE_TIME_OUT below to customize
    (c) Victor Hugo Soliz Kuncar, ZLIB/LibPNG license
*/ }
bool check_answer(${Method.Params}, ${Method.ReturnType} expected, ${Method.ReturnType} result)
{
    return expected == result;
}

//------------------------------------------------------------------------------

char do_test(${foreach Method.Params p}${p.Type},${end}${Method.ReturnType},int,bool);
${<if RecordRuntime}
const double CASE_TIME_OUT = 2.0;
${<end}

char run_testcase(int __no) {
${<foreach Method.Params p}
 ${if p.Type.Array}vector<${p.Type.Primitive}>${else}${p.Type.Primitive}${end} ${p.Name};
${<end}
 ${if Method.ReturnType.Array}vector<${Method.ReturnType.Primitive}>${else}${Method.ReturnType.Primitive}${end} __expected;
 bool __unknownAnswer = false;

 switch (__no) {
${<foreach Examples e}
  case ${e.Num}: {
${<foreach e.Input in}
${<if !in.Param.Type.Array}
    ${in.Param.Name} = ${in};
${<else}
    ${in.Param.Name} = { ${foreach in.ValueList v ,}${v}${end} };
${<end}
${<end}

${<if !e.Output.Param.Type.Array}
    __expected = ${e.Output};
${<else}
    __expected = {${foreach e.Output.ValueList v ,} ${v}${end} };
${<end}
    break;
  }
${<end}
  /*case ${NumOfExamples}: {
    // Your custom testcase goes here (don't forget to add to num/runTests below)
${<foreach Method.Params p}
    ${p.Name} = ;
${<end}

    __unknownAnswer = true;
    break;
  }*/

  default: return 'm';
 }
 return do_test(${foreach Method.Params p , }${p.Name}${end}, __expected, __no, __unknownAnswer);
}

// Tests total:
int      numTests  = ${NumOfExamples};
// Tests to run when there are no arguments:
set<int> runTests = { ${foreach Examples e , }${e.Num}${end} };

//------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <ctime>
${-- /*Maybe template/final code doesn't #include those files*/ --}
template <typename T> string pretty_print(T t) { stringstream s; typeid(T) == typeid(string) ? s << "\\"" << t << "\\"" : s << t; return s.str(); }
${<if HasArray}
// Vector print
template <typename T> ostream &operator << (ostream &out, vector<T> arr) {
    out << "{";
    for (int i = 0; i < arr.size(); ++i) out << (i == 0 ? "" : ",") << pretty_print(arr[i]);
    out << "}";
    return out;
}
${<end}

${<if Method.ReturnType.RealNumber}
#include<cmath>
bool double_equal (const double &expected, const double &received) { return abs(expected - received) < 1e-9 || abs(received) > abs(expected) * (1.0 - 1e-9) && abs(received) < abs(expected) * (1.0 + 1e-9); }

${<if Method.ReturnType.Array}
bool double_vector_equal (const vector<double> &expected, const vector<double> &received) {
    if (expected.size() != received.size()) return false;
    int n = expected.size();
    for (int i = 0; i < n; ++i)
        if (!double_equal(expected[i], received[i])) return false;
    return true;
}
${<end}
${<end}

string colorString(string s, int q)
{
    if (q == 0) {
        //neutral
        return s;
    } else if (q < -1) {
        //bad (score)
        return "\\033[1;41m"+s+"\\033[0m";
    } else if (q < 0) {
        //bad (single result)
        return "\\033[1;31m"+s+"\\033[0m";
    } else {
        //good
        return "\\033[1;32m"+s+"\\033[0m";
    }
}

string colorTestResult(char r)
{
    string s = string(1, r);
    switch(r) {
        case '+' :
            return colorString(s, 1);
        case '?':
            return colorString(s, 0);
        default :
            return colorString(s, -1);
    }
    return "";
}

char do_test(${Method.Params}, ${Method.ReturnType} __expected, int __caseNo, bool __unknownAnswer) {
 cout << "\\033[1;36mTest " << __caseNo << "\\033[0m: [" ${<foreach Method.Params p << ","}<< ${if p.Type.Array}${p.Name}${else}pretty_print(${p.Name})${end} ${<end} << "]" << endl;


${<if RecordRuntime}
    time_t __startClock = clock();
${<end}
    ${ClassName} *__instance = new ${ClassName}();
    ${Method.ReturnType} __result = __instance->${Method.Name}(${foreach Method.Params par , }${par.Name}${end});
${<if RecordRuntime}
    double __elapsed = (double)(clock() - __startClock) / CLOCKS_PER_SEC;
    cout << "Time: "<<__elapsed<<" seconds." << endl;
${<end}
    delete __instance;

    bool __correct = __unknownAnswer || ${<if Method.ReturnType.RealNumber}
${<if Method.ReturnType.Array}${--
    --}double_vector_equal(__expected, __result);
${<else}${--
    --}double_equal(__expected, __result);
${<end}
${<else}${--
    --}check_answer(${foreach Method.Params p , }${p.Name}${end}, __expected, __result);
${<end}

    if (! __correct) {
        cout << "Desired answer:" << endl;
        cout << "\\t" << ${if Method.ReturnType.Array} __expected ${else} pretty_print(__expected) ${end} << endl;
    }
    cout << "Your answer:" << endl;
    cout << "\\t" << ${if Method.ReturnType.Array} __result ${else} pretty_print(__result) ${end} << endl;

    char __res = '-';
    if (! __correct) {
        __res = 'X';
${<if RecordRuntime}
    } else if (__elapsed > CASE_TIME_OUT ) {
        __res = 'T';
${<end}
    } else if (__unknownAnswer) {
        __res = '?';
    } else {
        __res = '+';
    }
    cout << " "<<colorTestResult(__res)<<endl;

    cout << "\\033[0;2m===============================================================\\033[0m" << endl;
    return __res;
}

int main(int argc, char *argv[]) {
    string result;
    if (argc > 1) {
        runTests.clear();
        for (int i = 1; i < argc; ++i) {
            runTests.insert(atoi(argv[i]));
        }
    }
    int j = 0;
    for (int i: runTests) {
        while (j < i) {
            result += 'd';
            j++;
        }
        result += run_testcase(i);
        j = i + 1;
    }
    result += string( std::max(0, numTests - j), 'd' );
    cout << "${Problem.Name}: ";
    bool good = true;
    for (char ch: result) {
        good &= ( ch == '?' || ch == '+' );
        cout << colorTestResult(ch);
    }

${<if RecordScore}
    int T = time(NULL) - ${CreateTime};
    double PT = T / 60.0, TT = 75.0, SS = ${Problem.Score} * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT));
    string SSS = std::to_string((int)SS) + "." + std::to_string((int)(SS*100) % 100);
    cout << " (" << colorString(SSS, good? 1 : -2) <<")." << endl;
${<else}
    cout << endl;
${<end}
    return 0;
}
