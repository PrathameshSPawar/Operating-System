#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

int scan(vector<int>& req, int n, int size, int initial, int move)
{
    int seek = 0;

    // Bubble Sort (as requested, keeping the same format)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (req[j] > req[j + 1]) {
                swap(req[j], req[j + 1]);
            }
        }
    }

    // Finding the index where requests are greater than initial position
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (initial < req[i]) {
            index = i;
            break;
        }
    }

    if (move == 1) {  // Upward movement
        for (int i = index; i < n; i++) {
            seek += abs(req[i] - initial);
            cout << "\nHead moves to " << req[i];
            initial = req[i];
        }
        // Move to the end of the disk
        seek += abs(size - 1 - initial);
        initial = size - 1;
        cout << "\nHead moves to " << initial;

        for (int i = index - 1; i >= 0; i--) {
            seek += abs(req[i] - initial);
            initial = req[i];
            cout << "\nHead moves to " << initial;
        }
    } else {  // Downward movement
        for (int i = index - 1; i >= 0; i--) {
            seek += abs(req[i] - initial);
            initial = req[i];
            cout << "\nHead moves to " << initial;
        }
        // Move to the start of the disk
        seek += abs(initial);
        initial = 0;
        cout << "\nHead moves to " << initial;

        for (int i = index; i < n; i++) {
            seek += abs(req[i] - initial);
            initial = req[i];
            cout << "\nHead moves to " << initial;
        }
    }

    return seek;
}

int main()
{
    int n, size, move, initial;
    cout << "\nEnter the total requests: ";
    cin >> n;
    vector<int> req(n);
    cout << "\nEnter the Requests one by one: ";
    for (int i = 0; i < n; i++) {
        cin >> req[i];
    }

    cout << "\nEnter the total size of disk: ";
    cin >> size;

    cout << "\nEnter the movement of disk (1 for Upward / 0 for Downward): ";
    cin >> move;

    cout << "\nEnter the initial position of head: ";
    cin >> initial;

    int ans = scan(req, n, size, initial, move);

    cout << "\nSeek Time is: " << ans;
    cout << "\nAverage of seek is: " << static_cast<double>(ans) / n;
    return 0;
}
