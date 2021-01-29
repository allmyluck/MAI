#include <iostream>
#include <limits>
#include <vector>
#include <queue>

class TGraph {
public:
    TGraph(std::istream& in, const long long& count, const long long& lines) {
        matrix.resize(count);
        size = count;
        matrix.resize(size);
        long long from, to, weight;
        for(long long i = 0; i < lines; i++) {
            in >> from >> to >> weight;
            TData temp;
            temp.to = from - 1;
            temp.weight = weight;
            matrix[to - 1].push_back(temp);
            temp.to = to - 1;
            matrix[from - 1].push_back(temp);
        }
    }


    long long Find(long long& start, long long& finish) {
        std::vector<long long> distance(size, std::numeric_limits<long long int>::max());
        std::queue<TData> peaks;
        peaks.push(TData(start - 1, 0)); 
        distance[start - 1] = 0;
        while(!peaks.empty()) {
            long long v = peaks.front().to;
            peaks.pop();
            for(TData temp : matrix[v]) {
                if(distance[temp.to] > distance[v] + temp.weight) {
                    distance[temp.to] = distance[v] + temp.weight;
                    peaks.push(TData(temp.to,distance[temp.to]));
                }
            }
        }
        return distance[finish - 1];
    }

private:
    struct TData {
        long long to;
        long long weight;
        TData(long long nto, long long nweight): to(nto), weight(nweight)
        {}
        TData(): to(0), weight(0)
        {}
    };
    long long size;
    std::vector<std::vector<TData>> matrix;
};




int main() {
    long long max, count, start, finish;
    std::cin >> max >> count >> start >> finish;
    TGraph Our(std::cin, max, count);
    long long result;
    double startcl, end;
    startcl = clock();
    result = Our.Find(start,finish);
    end = clock();
    std::cout << "Time of working " << (end - startcl) / CLOCKS_PER_SEC << "sec" << std::endl;
    if(result == std::numeric_limits<long long int>::max()) {
        std::cout << "No solution" << std::endl;
    } else {
        std::cout << result << std::endl;
    }
    return 0;
}