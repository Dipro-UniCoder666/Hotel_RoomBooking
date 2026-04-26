#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

struct Room {
    int num;
    string type;
    string gname;
    int nights;
    bool taken;
    float bill;
};

// single=1200 double=1500 suite=3500, simple
float rate(string t) {
    if (t == "single") return 1200;
    if (t == "double") return 1500;
    if (t == "suite") return 3500;
    return 0;
}

void header() {
    cout << "\n╔══════════════════════╗\n";
    cout << "║      Hotel Arena     ║\n";
    cout << "╚══════════════════════╝\n";
}

int main() {

    SetConsoleOutputCP(65001);  // force UTF-8

    vector<Room> h = {
        {101, "single", "", 0, false, 0},
        {102, "single", "", 0, false, 0},
        {103, "single", "", 0, false, 0},
        {201, "double", "", 0, false, 0},
        {202, "double", "", 0, false, 0},
        {301, "suite", "", 0, false, 0},
    };

    int ch;

    header();

    again:
    cout << "\n1. see rooms\n";
    cout << "2. book\n";
    cout << "3. checkout\n";
    cout << "4. all bookings\n";
    cout << "0. quit\n";
    cout << "\n>> ";
    cin >> ch;

    if (ch == 1) {
        cout << "\nfree rooms:\n";
        for (int i = 0; i < h.size(); i++) {
            if (!h[i].taken)
                cout << "  room " << h[i].num << " [" << h[i].type << "] - " << rate(h[i].type) << " tk/night\n";
        }
    }

    else if (ch == 2) {
        string nm, tp;
        int nt;

        cout << "name: ";
        cin.ignore();
        getline(cin, nm);  

        cout << "type (single/double/suite): ";
        cin >> tp;

        if (rate(tp) == 0) {
            cout << "wrong type bro\n";
            goto again;
        }

        cout << "how many nights: ";
        cin >> nt;

        bool found = false;
        for (int i = 0; i < h.size(); i++) {
            if (!h[i].taken && h[i].type == tp) {
                h[i].taken = true;
                h[i].gname = nm;
                h[i].nights = nt;
                h[i].bill = rate(tp) * nt;
                cout << "\nok! room " << h[i].num << " booked for " << nm << "\n";
                cout << "total = " << h[i].bill << " tk\n";
                found = true;
                break;
            }
        }

        if (!found) cout << "no " << tp << " room available rn\n";
    }

    else if (ch == 3) {
        int rn;
        cout << "room number: ";
        cin >> rn;

        bool ok = false;
        for (int i = 0; i < h.size(); i++) {
            if (h[i].num == rn && h[i].taken) {
                cout << "\nguest: " << h[i].gname << "\n";
                cout << "stayed: " << h[i].nights << " nights\n";
                cout << "bill: " << h[i].bill << " tk\n";
                cout << "thanks for staying!\n";

                h[i].taken = false;
                h[i].gname = "";
                h[i].nights = 0;
                h[i].bill = 0;
                ok = true;
                break;
            }
        }
        if (!ok) cout << "room not found or already empty\n";
    }

    else if (ch == 4) {
        cout << "\n--- bookings ---\n";
        bool any = false;
        for (int i = 0; i < h.size(); i++) {
            if (h[i].taken) {
                cout << "room " << h[i].num << " | " << h[i].type
                     << " | " << h[i].gname
                     << " | " << h[i].nights << "n"
                     << " | " << h[i].bill << "tk\n";
                any = true;
            }
        }
        if (!any) cout << "no bookings yet\n";
    }

    else if (ch == 0) {
        cout << "bye\n";
        return 0;
    }

    else {
        cout << "??\n";
    }

    goto again; 
}