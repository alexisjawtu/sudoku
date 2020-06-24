#include <iostream>
#include <fstream>
using namespace std;

int m_dato[9][9];

void cargar_los_datos()
{
    ifstream sudoku_dato("./datos.txt");
    if (!sudoku_dato) {
        cout << "Error en la ruta del archivo?";
        exit(1);
    }
    sudoku_dato.get();
    char x = sudoku_dato.peek();
    int  i = 0;
    int  j = 0;
    while (x != ']')
    {
        if (i < 9)
        {
            if (j < 9)
            {
                int num = 0;
                sudoku_dato >> num;
                m_dato[i][j] = num;
                x = sudoku_dato.peek();
                j ++;
                if (x == ',') sudoku_dato.get();
            }
            else
            {
                i++;
                j = 0;
            }
        }
    }
    sudoku_dato.close();
}

pair <int,int> extremos_del_cuadrado2 (int numero_de_cuadrado)
{
    switch (numero_de_cuadrado)
    {
        case 1:
           return make_pair(0,0);
           break;
        case 2:
           return make_pair(0,3);
           break;
        case 3:
           return make_pair(0,6);
           break;
        case 4:
           return make_pair(3,0);
           break;
        case 5:
           return make_pair(3,3);
           break;
        case 6:
           return make_pair(3,6);
           break;
        case 7:
           return make_pair(6,0);
           break;
        case 8:
           return make_pair(6,3);
           break;
        default:
           return make_pair(6,6);
    }
}

int que_cuadrado2(int fila, int columna)
{
    if (fila<3)
    {
        if (columna < 3) return 1;
        else if (columna < 6) return 2;
        else return 3;
    }
    else if(fila < 6)
    {
        if (columna < 3) return 4;
        else if (columna < 6) return 5;
        else return 6;
    }
    else
    {
        if (columna < 3) return 7;
        else if (columna < 6) return 8;
        else return 9;
    }
}

bool chequear (int i, int j, int k)
{
    for (int l=0;l<9;l++)
    {
        if (l != i && m_dato[l][j]==k) return 0;
    }
    for (int t=0;t<9;t++)
    {
        if (t != j && m_dato[i][t]==k) return 0;
    }
    pair<int,int> par = extremos_del_cuadrado2 (que_cuadrado2(i,j));
    int n = par.first;
    int m = par.second;
    for (int u = n; u < n + 3; u ++)
    {
        for (int v = m; v < m + 3; v++)
        {
            if ((u != i || v != j) && m_dato[u][v] == k) return 0;
        }
    }
    return 1;
}

void f (int i, int j)
{
    if (j == 9)
    {
        f(i+1, 0);
        return;
    }
    if (i == 9)
    {
        cout << "Resultado: " << endl;
        for (int z = 0; z < 9; z++)
        {
            for (int y = 0; y < 9; y++)
            {
                cout << m_dato[z][y] << " | ";
            }
            cout << endl;
        }
        exit(1);
        return;
    }
    if (m_dato[i][j] > 0)
    {
        // cout << "(" << i << "," << j << ")"; // visualizar progreso
        f(i,j+1);
        return;
    }
    for (int k = 1; k < 10; k++)
    {
        m_dato[i][j] = k;
        if (chequear(i,j,k))
        {
            // cout << "(" << i << "," << j << ")"; // visualizar progreso
            f(i,j+1);
        }
    }
    m_dato[i][j] = 0;
}
