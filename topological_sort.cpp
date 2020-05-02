#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

void DEL_msasiedztwa(int v, int A[][100])
{
    int stopien_wejsciowy[100] = { 0 };
    int odwiedzone_ms[100] = { 0 };
    vector <int> L;
    while (int(L.size()) < v)
    {
        for (int i = 0; i < v; i++)
        {
            stopien_wejsciowy[i] = 0;
            for (int j = 0; j < v; j++)
            {
                if (A[i][j] == -1)
                {
                    stopien_wejsciowy[i] += 1;
                }
            }
            if (odwiedzone_ms[i] == 0 && stopien_wejsciowy[i] == 0)
            {
                L.push_back(i);
                odwiedzone_ms[i] = 1;
                for (int j = 0; j < v; j++)
                {
                    A[i][j] = 0;
                    A[j][i] = 0;
                }
            }
        }
    }
    cout << endl << "Wierzcholki posortowane topologicznie: ";
    for (int i = 0; i < int(L.size()); i++)
    {
        cout << L[i] << " ";
    }
    cout << endl;
}


int DFS_start(int v, int A[][100])
{
    int res, i, j;
    int stopien_wejsciowy[100] = { 0 };
    for (i = 0; i < v; i++) //szukanie wierzchołków niezależnych
    {
        res = 0;
        for (j = 0; j < v; j++)
        {
            if (A[i][j] == 1 || A[i][j] == -1)
            {
                res += 1;
            }
        }
        if (res == 0)
        {
            return i;
        }
    }
    for (i = 0; i < v; i++) //szukanie wierzchołka o zerowym stopniu wejściowym
    {
        stopien_wejsciowy[i] = 0;
        for (j = 0; j < v; j++)
        {
            if (A[i][j] == -1)
            {
                stopien_wejsciowy[i] += 1;
            }
        }
        if (stopien_wejsciowy[i] == 0)
        {
            return i;
        }
    }
}

vector <int> L_ms;
int odwiedzone[100] = { 0 };

void DFS_msasiedztwa(int wierzcholek, int v, int A[][100])
{
    odwiedzone[wierzcholek] = 1;
    for (int i = 0; i < v; i++)
    {
        if (A[wierzcholek][i] == 1 && odwiedzone[i] == 0)
        {
            DFS_msasiedztwa(i, v, A);
        }
    }
    L_ms.insert(L_ms.begin(), wierzcholek);
}

int odwiedzone_mg[100] = { 0 };
int stopien_wejsciowy_mg[100] = { 0 };

void wejscie_mgrafu(int v, int A[][100])
{
    for (int i = 0; i < v; i++)
    {
        stopien_wejsciowy_mg[i] = 0;
    }

    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            if (A[i][j] > v && A[i][j] <= 2 * v)
            {
                stopien_wejsciowy_mg[i] += 1;
            }
        }
    }
}

vector <int> L_mg;

void DEL_mgrafu(int v, int A[][100])
{
    wejscie_mgrafu(v, A);
    for (int i = 0; i < v; i++)
    {
        if (odwiedzone_mg[i] == 0 && stopien_wejsciowy_mg[i] == 0)
        {
            L_mg.push_back(i);
            odwiedzone_mg[i] = 1;
            for (int j = 0; j < v; j++)
            {
                A[i][j] = 0;
                A[j][i] = 0;
            }
            DEL_mgrafu(v, A);
        }
    }
}

int main()
{
    int v, e, input, reprezentacja; // v - l. wierzchołków, e - l. krawędzi, łuk z v1 do v2
    ifstream graf;

    cout << "Wybierz sposob wczytania grafu: \n" << "1. Z klawiatury \n" << "2. Z pliku \n" << "Wpisz nr 1 lub 2: ";
    cin >> input;
    while ((input != 1) && (input != 2))
    {
        cout << "Wpisz nr 1 lub 2: ";
        cin >> input;
    }

    cout << "\nWybierz sposob reprezentacji maszynowej grafu skierowanego: \n" << "1. Macierz sasiedztwa \n" << "2. Macierz grafu \n" << "3. Wyjscie\n" << "Wpisz nr 1, 2 lub 3: ";
    cin >> reprezentacja;
    while (reprezentacja != 3)
    { 
        while ((reprezentacja != 1) && (reprezentacja != 2))
        {
            cout << "Wpisz nr 1 lub 2: ";
            cin >> reprezentacja;
        }

        if (reprezentacja == 1)
        {
            int wybor;
            if (input == 1)
            {
                cout << "Podaj liczbe wierzcholkow i krawedzi oddzielone spacja: ";
                cin >> v >> e;
            }
            else
            {
                graf.open("Grafbc.txt");
                graf >> v >> e;
            }


            int i, j, v1, v2;
            char** A = new char* [v];  // Przydzielanie pamięci na wiersze o dł. v

            for (i = 0; i < v; i++)
            {
                A[i] = new char[v]; // Przydzielanie kolumn o dł. v do wierszy
            }

            for (i = 0; i < v; i++)
            {
                for (j = 0; j < v; j++)
                {
                    A[i][j] = 0;    // Macierz domyślnie wypełniona zerami
                }
            }

            // Odczytujemy kolejne definicje krawędzi
            if (input == 1)
            {
                cout << "Podaj liczbe liste krawedzi (wiercholki oddzielone spacja):\n";
                for (i = 0; i < e; i++)
                {
                    cin >> v1 >> v2;    // Wierzchołek startowy i końcowy krawędzi
                    A[v1][v2] = 1; // Krawędź v1->v2 w macierzy sasiedztwa
                    A[v2][v1] = -1;
                }
            }
            else
            {
                while (!graf.eof())
                {
                    graf >> v1 >> v2;
                    A[v1][v2] = 1; // Krawędź v1->v2 w macierzy sasiedztwa
                    A[v2][v1] = -1;
                }
            }

            int tab_pom1[100][100]; //skopiowanie macierzy sąsiedztwa do macierzy pomocniczej
            int tab_pom2[100][100];
            for (i = 0; i < v; i++)
            {
                for (j = 0; j < v; j++)
                {
                    tab_pom1[i][j] = A[i][j];
                    tab_pom2[i][j] = A[i][j];
                }
            }

            cout << endl << "Macierz sasiedztwa: " << endl;

            // Wypisywanie macierzy sąsiedztwa

            cout << "   ";
            for (i = 0; i < v; i++) cout << setw(3) << i;
            cout << endl;
            for (i = 0; i < v; i++)
            {
                cout << setw(3) << i;
                for (j = 0; j < v; j++) cout << setw(3) << (int)tab_pom1[i][j];
                cout << endl;
            }
            
            int count = 0;
            while (count < 2)
            {
                cout << endl << "Wybierz algorytm sortownania topologicznego:\n" << "1. Algorytm Kahna\n" << "2. Algorytm oparty na procedurze DFS\n";
                cout << "Podaj nr 1 lub 2: ";
                cin >> wybor;
                while (wybor != 1 && wybor != 2)
                {
                    cout << "Podaj nr 1 lub 2: ";
                    cin >> wybor;
                }

                if (wybor == 1)
                {
                    DEL_msasiedztwa(v, tab_pom1);
                    count += 1;
                }

                else if (wybor == 2)
                {
                    DFS_msasiedztwa(DFS_start(v, tab_pom2), v, tab_pom2);
                    cout << endl << "Wierzcholki posortowane topologicznie: ";
                    for (int i = 0; i < int(L_ms.size()); i++)
                    {
                        cout << L_ms[i] << " ";
                    }
                    cout << endl;
                    count += 1;
                }
            }
            

            for (i = 0; i < v; i++)
            {
                delete[] A[i];  //Zwalnianie pamięci
            }
            delete[] A;
            if (input == 2)
                graf.close();
            cout << endl;
        }

        else
        {
            if (input == 1)
            {
                cout << "Podaj liczbe wierzcholkow i krawedzi oddzielone spacja: ";
                cin >> v >> e;
            }
            else
            {
                graf.open("Grafbc.txt");
                graf >> v >> e;
            }

            int i, j, v1, v2;
            int MS[100][100];
            int MG[100][100];
            vector <int> nastepniki[100];
            vector <int> poprzedniki[100];
            vector <int> brak_incydencji[100];

            for (i = 0; i < v; i++)
            {
                for (j = 0; j < v; j++)
                {
                    MS[i][j] = 0;    // Macierz domyślnie wypełniona zerami
                }
            }

            for (i = 0; i < v; i++)
            {
                for (j = 0; j < v+3; j++)
                {
                    MG[i][j] = 0;    // Macierz domyślnie wypełniona zerami
                }
            }

            if (input == 1)
            {
                cout << "Podaj liczbe liste krawedzi (wierchołki oddzielone spacją):\n";
                for (i = 0; i < e; i++)
                {
                    cin >> v1 >> v2;    // Wierzchołek startowy i końcowy krawędzi
                    nastepniki[v1].push_back(v2);
                    poprzedniki[v2].push_back(v1);
                    MS[v1][v2] = 1; // Krawędź v1->v2 w macierzy sasiedztwa
                    MS[v2][v1] = -1;
                }
            }
            else
            {
                while (!graf.eof())
                {
                    graf >> v1 >> v2;
                    nastepniki[v1].push_back(v2);
                    poprzedniki[v2].push_back(v1);
                    MS[v1][v2] = 1; // Krawędź v1->v2 w macierzy sasiedztwa
                    MS[v2][v1] = -1;
                }
            }

            for (int i = 0; i < v; i++)
            {
                for (int j = 0; j < v; j++)
                {
                    if (MS[i][j] == 0)
                    {
                        brak_incydencji[i].push_back(j);
                    }
                }
            }

            for (int i = 0; i < v; i++)
            {
                for (int j = v; j < v+3; j++)
                {
                    if (j == (v) && !nastepniki[i].empty()) //krok 1 - wypełnienie kolumny pierwszymi następnikami
                    {
                        MG[i][j] = nastepniki[i].front();
                    }
                    if (j == (v+1) && !poprzedniki[i].empty()) //krok 2 - wypełnienie kolumny pierwszymi poprzednikami
                    {
                        MG[i][j] = poprzedniki[i].front();
                    }
                    if (j == (v+2) && !brak_incydencji[i].empty()) // krok 3 - wypełnienie kolumny pierwszymi wierzchołkami nieincydentymi
                    {
                        MG[i][j] = brak_incydencji[i].front();
                    }
                }
            }

            for (int i = 0; i < v; i++)
            {
                for (int j = 0; j < v; j++)
                {
                    if (MS[i][j] == 1 && !nastepniki[i].empty()) //do komórki wstawiamy numer ostatniego następnika i, jesli istnieje łuk i -> j
                    {
                        MG[i][j] = nastepniki[i].back();
                    }
                    if (MS[j][i] == 1 && !poprzedniki[i].empty()) //do komórki wstawiamy sumę ostatniego poprzednika + v, jeśli istnieje łuk z j -> i
                    {
                        MG[i][j] = v + poprzedniki[i].back();
                    }
                    if (MS[i][j] == 0 && MS[j][i] == 0 && !brak_incydencji[i].empty()) //do komórki wstawiamy ostatni nieincydentny wierzchołek z minusem, jeśli nie istnieje łuk i -> j
                    {
                        MG[i][j] = -brak_incydencji[i].back();
                    }
                }
            }

            cout << endl << "Macierz grafu: " << endl;

            // Wypisywanie macierzy grafu

            cout << "   ";
            for (i = 0; i < v+3; i++) cout << setw(3) << i;
            cout << endl;
            for (i = 0; i < v; i++)
            {
                cout << setw(3) << i;
                for (j = 0; j < v+3; j++) cout << setw(3) << (int)MG[i][j];
                cout << endl;
            }
            DEL_mgrafu(v, MG);

            cout << endl << "Wierzcholki posortowane topologicznie: ";
            for (int i = 0; i < int(L_mg.size()); i++)
            {
                cout << L_mg[i] << " ";
            }
            if (input == 2)
                graf.close();
            cout << endl << endl;

            cout << endl;
        }

        cout << "Wybierz sposob reprezentacji maszynowej grafu skierowanego: \n" << "1. Macierz sasiedztwa \n" << "2. Macierz grafu \n" << "3. Wyjscie\n" << "Wpisz nr 1, 2 lub 3: ";
        cin >> reprezentacja;
    }
    return 0;
}
