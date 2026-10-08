// Validador de cedula y RUC (Ecuador) - Modulo 10 y Modulo 11
// Solo usa estructuras repetitivas, switch y condicionales (sin arreglos, strings ni funciones).
#include <iostream>
using namespace std;

int main() {
    int opcion;
    do {
        cout << "\n=== VALIDADOR DE CEDULA / RUC ===\n";
        cout << "1. Cedula (persona natural)\n";
        cout << "2. RUC persona natural\n";
        cout << "3. RUC juridico / extranjeros sin cedula (3er digito 9)\n";
        cout << "4. RUC institucion publica (3er digito 6)\n";
        cout << "5. RUC automatico (detecta el tipo)\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Opcion invalida.\n";
            opcion = -1;
            continue;
        }
        if (opcion == 0) break;
        if (opcion < 1 || opcion > 5) {
            cout << "Opcion invalida.\n";
            continue;
        }

        // Leer caracter por caracter para conservar los ceros iniciales
        // (las provincias 01 a 09 empiezan con 0)
        long long n = 0;
        int len = 0;
        bool soloNumeros = true;
        char c;
        cout << "Ingrese el numero (solo digitos): ";
        cin.ignore(10000, '\n');
        cin.get(c);
        while (c != '\n' && cin) {
            if (c >= '0' && c <= '9') {
                if (len < 14) n = n * 10 + (c - '0');
                len++;
            } else if (c != ' ' && c != '\r') {
                soloNumeros = false;
            }
            cin.get(c);
        }
        if (!soloNumeros || len == 0) {
            cout << "-> NO VALIDO (solo se permiten numeros)\n";
            continue;
        }
        long long t;

        // Longitud correcta segun la opcion
        if ((opcion == 1 && len != 10) || (opcion != 1 && len != 13)) {
            cout << "-> NO VALIDO (longitud incorrecta)\n";
            continue;
        }

        // Separar los digitos a1..a13 (a1 = primer digito de la izquierda)
        int a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0, a6 = 0, a7 = 0;
        int a8 = 0, a9 = 0, a10 = 0, a11 = 0, a12 = 0, a13 = 0;
        t = n;
        for (int k = len; k >= 1; k--) {
            int d = (int)(t % 10);
            t /= 10;
            switch (k) {
                case 1: a1 = d; break;
                case 2: a2 = d; break;
                case 3: a3 = d; break;
                case 4: a4 = d; break;
                case 5: a5 = d; break;
                case 6: a6 = d; break;
                case 7: a7 = d; break;
                case 8: a8 = d; break;
                case 9: a9 = d; break;
                case 10: a10 = d; break;
                case 11: a11 = d; break;
                case 12: a12 = d; break;
                case 13: a13 = d; break;
            }
        }

        // Tipo: 1 cedula, 2 RUC natural, 3 RUC juridico, 4 RUC publico
        int tipo;
        switch (opcion) {
            case 1: tipo = 1; break;
            case 2: tipo = 2; break;
            case 3: tipo = 3; break;
            case 4: tipo = 4; break;
            default:
                if (a3 == 9) tipo = 3;
                else if (a3 == 6) tipo = 4;
                else tipo = 2;
                break;
        }

        bool ok = true;

        // Provincia entre 1 y 24
        int provincia = a1 * 10 + a2;
        if (provincia < 1 || provincia > 24) ok = false;

        // Tercer digito segun el tipo
        if ((tipo == 1 || tipo == 2) && a3 >= 6) ok = false;
        if (tipo == 3 && a3 != 9) ok = false;
        if (tipo == 4 && a3 != 6) ok = false;

        // Terminacion segun el tipo
        if (tipo == 2 && !(a11 == 0 && a12 == 0 && a13 == 1)) ok = false;
        if (tipo == 3 && a11 == 0 && a12 == 0 && a13 == 0) ok = false;
        if (tipo == 4 && a10 == 0 && a11 == 0 && a12 == 0 && a13 == 0) ok = false;

        // Digito verificador
        if (ok) {
            int suma = 0;
            int limite = (tipo == 4) ? 8 : 9;
            for (int i = 1; i <= limite; i++) {
                int x = 0;
                switch (i) {
                    case 1: x = a1; break;
                    case 2: x = a2; break;
                    case 3: x = a3; break;
                    case 4: x = a4; break;
                    case 5: x = a5; break;
                    case 6: x = a6; break;
                    case 7: x = a7; break;
                    case 8: x = a8; break;
                    case 9: x = a9; break;
                }

                int coef = 0;
                if (tipo == 1 || tipo == 2) {
                    // Modulo 10: 2,1,2,1,2,1,2,1,2
                    if (i % 2 == 1) coef = 2;
                    else coef = 1;
                } else if (tipo == 3) {
                    // Modulo 11: 4,3,2,7,6,5,4,3,2
                    switch (i) {
                        case 1: coef = 4; break;
                        case 2: coef = 3; break;
                        case 3: coef = 2; break;
                        case 4: coef = 7; break;
                        case 5: coef = 6; break;
                        case 6: coef = 5; break;
                        case 7: coef = 4; break;
                        case 8: coef = 3; break;
                        case 9: coef = 2; break;
                    }
                } else {
                    // Modulo 11: 3,2,7,6,5,4,3,2
                    switch (i) {
                        case 1: coef = 3; break;
                        case 2: coef = 2; break;
                        case 3: coef = 7; break;
                        case 4: coef = 6; break;
                        case 5: coef = 5; break;
                        case 6: coef = 4; break;
                        case 7: coef = 3; break;
                        case 8: coef = 2; break;
                    }
                }

                int producto = x * coef;
                if ((tipo == 1 || tipo == 2) && producto >= 10) producto -= 9;
                suma += producto;
            }

            int modulo = (tipo == 1 || tipo == 2) ? 10 : 11;
            int residuo = suma % modulo;
            int verificador;
            if (residuo == 0) verificador = 0;
            else verificador = modulo - residuo;

            int digitoReal = (tipo == 4) ? a9 : a10;
            if (verificador != digitoReal) ok = false;
        }

        if (ok) cout << "-> VALIDO\n";
        else cout << "-> NO VALIDO\n";
    } while (true);

    return 0;
}
