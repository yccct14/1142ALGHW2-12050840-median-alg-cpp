#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

// 用來同時儲存數值與權重
struct Item {
    int x;
    double w;
};

// 印出排序後資料
void printSortedValues(const vector<Item>& items) {
    cout << "Sorted data (x, w):\n";
    for (const auto& item : items) {
        cout << "(" << item.x << ", " << fixed << setprecision(2) << item.w << ") ";
    }
    cout << "\n";
}

// ------------------------------
// 1. 求中位數
// ------------------------------
double findMedian(vector<int> values) {
    // TODO:
    sort(values.begin(), values.end());
    int n = values.size();
    if (n % 2 == 1) {
        return values[n / 2];
    }
    return (values[n / 2 - 1] + values[n / 2]) / 2.0;
}

// ------------------------------
// 2. 求加權中位數
// 定義：排序後，找到最小的 x_k，使得
// 左側權重總和 <= 0.5，且右側權重總和 <= 0.5
// 常用實作方式：找第一個累積權重 >= 0.5 的元素
// ------------------------------
int findWeightedMedian(vector<Item> items) {
    // TODO:
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.x < b.x;
    });
    printSortedValues(items);
    double cumulativeWeight = 0.0;
    for (const auto& item : items) {
        cumulativeWeight += item.w;

        cout << "x = " << item.x
             << ", w = " << fixed << setprecision(2) << item.w
             << ", cumulative = " << cumulativeWeight << "\n";

        if (cumulativeWeight >= 0.5) {
            return item.x;
        }
    }
    return -1;
}

int main() {
    // 題目資料
    vector<int> x = {4, 3, 8, 5, 7, 10, 0, 9, 2, 11};
    vector<double> w = {0.05, 0.12, 0.08, 0.15, 0.14, 0.09, 0.10, 0.10, 0.06, 0.11};

    // 組合成 (x, w)
    vector<Item> items;
    for (int i = 0; i < x.size(); i++) {
        items.push_back({x[i], w[i]});
    }

    cout << "Original x values:\n";
    for (int v : x) cout << v << " ";
    cout << "\n\n";

    // 計算中位數
    double median = findMedian(x);
    cout << "Median = " << fixed << setprecision(1) << median << "\n\n";

    // 計算加權中位數
    int weightedMedian = findWeightedMedian(items);
    cout << "\nWeighted Median = " << weightedMedian << "\n";

    return 0;
}
