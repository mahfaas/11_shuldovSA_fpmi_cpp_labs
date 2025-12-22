#include <iostream>
#include <set>

using ll = long long;

void ReshetoEratosphena(int n) {

    std::set<int> candidates;
    for (int i = 2; i <= n; ++i) {
        candidates.insert(i);
    }

    while(!candidates.empty()) {
        int t = *candidates.begin();
        std::cout << t << " ";

        for (ll i = 1LL*t*2; i <= n; i += t) {
            candidates.erase(static_cast<int>(i));
        }

        candidates.erase(t);
    }
}

int main()
{
    int n;
    std::cin >> n;
    ReshetoEratosphena(n);
    return 0;
}
