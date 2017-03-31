#include "myheader.h"

using namespace std;

int main()
{
    //=======COMPLEX========
    /*
    vector<Complex> c;
    string filename = "asd.txt";
    fstream fin;
    fin.open(filename.c_str());
    fin >> c;
    */
    //==== VECTOR =====
    /*vector<int> v;
    string filename = "asd.txt";
    fstream fin;
    fin.open(filename.c_str());
    if(!fin.is_open())
    {
        cout << "Nem nyert!";
        return -1;
    }
    fin >> v;
    cout << "Minden elem negativ: ";
    int index = feltetelesMaximumKeresesVector(v);
    if(index != -1)
    {
        cout << "Igen " << v[index] << endl;
    }
    else
    {
        cout << "Nem" << endl;
    }

    cout << "DEBUG" << endl;
    for( int i = 0; i < v.size(); ++i )
    {
        cout << v.at(i) << endl;
    }*/
    //=== MÁTRIX ====
    vector<vector<int> > matrix;
    fstream fin("asd.txt");
    try {
        fin >> matrix;
        cout << "FMK: " << feltMaxKerOsszeg(matrix) << endl;
        cout << "DEBUG" << endl;
        for(int i = 0; i < matrix.size(); ++i) {
            for(int j = 0; j < matrix[i].size(); ++j) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    } catch(Exception exc) {
        switch(exc) {
        case URES_MATRIX:
            cout << "Ures volt a matrix!" << endl;
            break;
        case NEGATIVE_SIZE:
            cout << "Beolvasasnal negativ szamot adtal meg" << endl;
            break;
        default:
            cout << "Kerlek keresd a helpdesk-et!" << endl;
            break;
        }
    }

    return 0;
}
