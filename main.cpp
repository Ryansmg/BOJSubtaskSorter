#include <bits/stdc++.h>
using namespace std;

// Updated: 2025-08-03

#define cin // in 이랑 헷갈리지 않도록 제거
struct cifstream { // custom ifstream, 입력을 다 받고 더 받으려고 할 때 프로그램 종료
    ifstream& in;
    explicit cifstream(ifstream& stream) : in(stream) {}
    template <typename T> cifstream& operator>>(T& s) {
        if(in >> s) return *this;
        cerr << "cannot read more\n"; exit(1);
    }
};

/// 사용 방법
/// 0. 폴리곤에서 standard package를 만들어 다운받은 후 doall.bat을 실행해 테스트케이스들을 생성해놓는다.
/// 1. set_subtask 함수를 함수 위의 설명을 참고해 수정한다.
/// 2. 컴파일해 exe 파일을 만든다.
/// 3. 만든 exe 파일을 doall.bat과 같은 위치로 이동시킨 후, 실행한다.
///    이때 그냥 실행해도 되지만, cmd에서 실행하면 진행 상황 또는 에러 내용을 볼 수 있다.
/// 4. result 폴더가 생성되며, 안의 파일들을 모두 BOJ stack에 업로드하면 된다.


/// 이 함수를 수정하시면 됩니다. main 함수는 수정하지 마세요.
/// in을 통해 입력 파일을 입력받아야 합니다. cin과 같은 방식을 사용하시면 됩니다.
/// 반환하는 vector<int>에는 입력 파일이 해당되는 서브태스크 번호가 전부 담겨있어야 합니다.
/// 이때, 실수를 방지하기 위해 파일 끝까지 전부 입력받았는지 확인하므로 모든 입력을 받아야 합니다.
/// 또한, 파일을 모두 읽은 후 입력을 추가로 받으려고 하면 에러를 출력하고 분류를 종료합니다.
/// 입력 파일만으로 판단하기 어려운 서브태스크의 경우에는 num 인수를 활용해서 하드코딩하시면 됩니다.
vector<int> set_subtask(cifstream&& in, int num) {
    // Newspapers for Magicians 분류 예시
    int n, o, s, e, m, p, t1, t2, q;
    in >> n >> o >> s >> e >> m;
    bool subtask3 = m == n - 1;

    for(int i=1; i<=m; i++) {
        int a, b; in >> a >> b;
        if(a != i || b != i+1) subtask3 = false;
    }
    in >> p;
    for(int i=0; i<p; i++) in >> t1 >> t2;
    in >> q;
    for(int i=0; i<q; i++) in >> t1 >> t2;

    vector<int> ret;
    if(o == 1) ret.push_back(1);
    if(q == 1) ret.push_back(2);
    if(subtask3) ret.push_back(3);
    ret.push_back(4);
    return ret;
}

#undef cin

int main() {
    if(filesystem::exists("./result")) {
        for(const auto& entry : filesystem::directory_iterator("./result")) {
            if(!remove(entry)) {
                cerr << "file remove failed. check processes using ./result directory\n";
                return 1;
            }
        }
    }
    else filesystem::create_directories("./result");
    set<string> processed;
    for(const auto& entry : filesystem::directory_iterator("./tests")) {
        string num = entry.path().stem().string();
        if(processed.find(num) != processed.end()) continue;
        processed.insert(num);
        string inputFile = entry.path().parent_path().string() + "/" + num;
        cout << num << " -> "; bool first = true;
        ifstream in(inputFile); string test;
        auto subtask_list = set_subtask(cifstream(in), stoi(num));
        if(in >> test) { cerr << "input stream was not read completely!\nread string: " << test << '\n'; exit(1); }
        for(int i : subtask_list) {
            if(!first) cout << ", ";
            cout << i; first = false;
            filesystem::copy_file(inputFile, "./result/subtask" + to_string(i) + "-" + num, filesystem::copy_options::overwrite_existing);
            filesystem::copy_file(inputFile + ".a", "./result/subtask" + to_string(i) + "-" + num + ".a", filesystem::copy_options::overwrite_existing);
        }
        cout << endl;
    }
}
