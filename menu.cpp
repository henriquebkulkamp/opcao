#ifdef _WIN32
#define WINDOWS_SYSTEM
#include <Windows.h>
#endif

#include <iostream>
#include <string>
#include <vector>

using namespace std;


void printter(vector<string> opcoes, int n) {
    cout << "\r";
    for (int i=0; i<n; i++) {
        cout << opcoes[i] << "    ";
    }
    
    cout << "\033[34m" << opcoes[n] << "\033[m";
    
    for (int i=n+1; i<opcoes.size(); i++) {
        cout << "    " << opcoes[i];
    }
}


int menu(vector<string> opcoes) {
    int n = 0;
    int size = opcoes.size();
    cout << "\033[?25l";        // APAGA O CURSOR
    printter(opcoes, n);

#ifdef WINDOWS_SYSTEM
    while (true) {
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {    // SETA PARA ESQUERDA
            n = (n == 0) ? size-1 : n-1;
            printter(opcoes, n);
        }
        
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {   // SETA PARA DIREITA  
            n = (n == size-1) ? 0 : n+1;
            printter(opcoes, n);
        }
        
        if (GetAsyncKeyState(VK_RETURN) & 0x8000 || GetAsyncKeyState(VK_SPACE) & 0x8000) {
            cout << endl;
            cout << "\033[?25h" << endl;  // MOSTRA CURSOR NOVAMENTE
            return n;
        }
        
        Sleep(100);
    }
#endif
    return 0; // CASO NAO SEJA USUARIO DE WINDOWS
}

int main() {
    vector<string> opcoes = {"opcao0", "opcao1", "opcao2", "opcao3"};

    int n = menu(opcoes);
    
    // EXIBE A OPCAO ESCOLHIDA (ESPACO || ENTER)
    cout << "> Option Selected: " << n << endl; 
    return 0;
}
