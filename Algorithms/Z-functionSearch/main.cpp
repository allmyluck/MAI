#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <vector>

void Lowercase(std::string& str) {
    for (size_t i = 0; i < str.size(); i++) {
        str[i] = std::tolower(str[i]);
    }
}

template <class T, class K>
struct TData {
    T data;
    K line;
    K number;
    K zk;
    TData(T& ndata, K& nline, K& nnumber) : data(ndata), line(nline), number(nnumber), zk(0)
    {}

    TData() : data(""), line(0), number(0), zk(0)
    {}
};

class TZBlocks {
private:
    std::vector<std::shared_ptr<TData<std::string, long long>>> fulltext;
    long long patternsize;
    long long textsize;
public:
    TZBlocks() : fulltext(0,0), patternsize(0), textsize(0)
    {}

    void Read() {
        long long i = 0;
        long long line = 0;
        long long number = 1;
        std::string input;
        while(std::getline(std::cin,input)) {
            std::string word;
            std::stringstream tempstr(input);
            while(tempstr >> word) {
                Lowercase(word);
                std::shared_ptr<TData<std::string, long long>> temp(new TData<std::string,long long>(word, line, number));
                fulltext.push_back(temp);
                if(line != 0) {
                    textsize++;
                } else {
                    patternsize++;
                }
                number++; 
                i++;
            }
            if(line == 0) {
                std::string unstr = "&";
                std::shared_ptr<TData<std::string, long long>> temp(new TData<std::string,long long>(unstr, line, number));
                fulltext.push_back(temp);
            }
            line++;
            number = 1;
        }
    }

    void Result() {
        BuildZBocks();
        SimpleSearch();
    }
private:
    void BuildZBocks() {
        long long r = 0;
        long long l = 0;
        for(long long i = 1; i < (long long)fulltext.size(); i++) {
            if(i <= r) {
                fulltext[i]->zk = std::min(r - i + 1, fulltext[i - l]->zk);
            }
            while(((i + fulltext[i]->zk) < (long long)fulltext.size()) && 
            (fulltext[fulltext[i]->zk]->data == fulltext[i + fulltext[i]->zk]->data)) {
                fulltext[i]->zk++;
            }
            if(i + fulltext[i]->zk - 1 > r) {
                l = i;
                r = i + fulltext[i]->zk - 1;
            }
        }
    }
       
    void SimpleSearch() {
        for(size_t i = patternsize + 1;i < fulltext.size();i++) {
            if(fulltext[i]->zk == patternsize) {
                std::cout << fulltext[i]->line << ", " << fulltext[i]->number << std::endl;
            }
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    TZBlocks gg;
    gg.Read();
    gg.Result();
    return 0;
}