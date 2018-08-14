#include <Windows.h>
#include <commctrl.h>					//needed for "visual style"
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <vector>
#include <fstream>
#include <string>
#include "Resources.h"
#pragma comment(lib, "Comctl32.lib")	//needed for "visual style"


HINSTANCE hInst;
const char* windowClass = "UP";
HWND field1, field2, button1, button2, textarea1, textarea2, static1, static2;
typedef std::vector<std::string> vector;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void RandomizeNewRotation(vector &all_maps, vector &old_maps);
void LoadMaps(std::string path, vector &maps);
void save(vector &v);


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = 0;
	icex.dwICC = ICC_ANIMATE_CLASS | ICC_USEREX_CLASSES;
	
	InitCommonControlsEx(&icex);

	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(UP_ICON));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName = 0;
	wc.lpszClassName = windowClass;
	wc.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(UP_ICON), IMAGE_ICON, 16, 16, 0);

	if (!RegisterClassEx(&wc)) {
		return 0;
	}

	HWND hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,
								windowClass,
								"*|UP|*Zombies Map Generator",
								WS_OVERLAPPEDWINDOW,
								CW_USEDEFAULT,
								CW_USEDEFAULT,
								800,
								600,
								NULL,
								NULL,
								hInst,
								NULL);
	if (!hwnd)
		return 0;

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG message;

	while (GetMessage(&message, NULL, 0, 0) > 0) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	
	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HFONT hf;
	HDC hdc;
	switch (msg)
	{
		case WM_CREATE:
		{
			//create a font
			long lfHeight;
			hdc = GetDC(NULL);
			lfHeight = -MulDiv(12, GetDeviceCaps(hdc, LOGPIXELSY), 72);
			ReleaseDC(NULL, hdc);
			hf = CreateFont(lfHeight, 0, 0, 0, 0, FALSE, 0, 0, 0, 0, 0, 0, 0, "Arial"); //5th parameter if = 700 then its bold

			//buttons
			field1 = CreateWindowEx(WS_EX_CLIENTEDGE, "Edit", "available_maps.txt", WS_CHILD | WS_VISIBLE, 10, 10, 150, 25, hWnd, NULL, hInst, (LPVOID)lParam);	//new rotation
			field2 = CreateWindowEx(WS_EX_CLIENTEDGE, "Edit", "old_rotation.txt", WS_CHILD | WS_VISIBLE, 10, 40, 150, 25, hWnd, NULL, hInst, (LPVOID)lParam);	//old rotation

			button1 = CreateWindowEx(NULL, "Button", "Load", WS_CHILD | WS_VISIBLE, 180, 10, 50, 20, hWnd, NULL, hInst, (LPVOID)lParam);	//load the txt files
			button2 = CreateWindowEx(NULL, "Button", "Save", WS_CHILD | WS_VISIBLE, 180, 40, 50, 20, hWnd, NULL, hInst, (LPVOID)lParam);	//write to file and save

			static1 = CreateWindowEx(NULL, "Static", "New", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 300, 10, 90, 20, hWnd, NULL, hInst, (LPVOID)lParam);	//new rotation
			static2 = CreateWindowEx(NULL, "Static", "Old", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 550, 10, 90, 20, hWnd, NULL, hInst, (LPVOID)lParam);	//old rotation

			textarea1 = CreateWindowEx(NULL, "Static", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 250, 40, 200, 400, hWnd, NULL, hInst, (LPVOID)lParam);	//new rotation
			textarea2 = CreateWindowEx(NULL, "Static", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 500, 40, 200, 400, hWnd, NULL, hInst, (LPVOID)lParam);	//old rotation

			//set font for every window created
			SendMessage(field1, WM_SETFONT, (WPARAM)hf, TRUE);
			SendMessage(field2, WM_SETFONT, (WPARAM)hf, TRUE);
			SendMessage(button1, WM_SETFONT, (WPARAM)hf, TRUE);
			SendMessage(button2, WM_SETFONT, (WPARAM)hf, TRUE);
			SendMessage(static1, WM_SETFONT, (WPARAM)hf, TRUE);
			SendMessage(static2, WM_SETFONT, (WPARAM)hf, TRUE);
			SendMessage(textarea1, WM_SETFONT, (WPARAM)hf, TRUE);
			SendMessage(textarea2, WM_SETFONT, (WPARAM)hf, TRUE);


		}
		break;
		case WM_COMMAND:
			{
				//arrays to get the filenames
				char all[100];
				char old[100];
				ZeroMemory(all, 100);
				ZeroMemory(old, 100);

				if (msg == WM_COMMAND && (HWND)lParam == button1) {
					//create temporary files
					//so we can easily access 
					//them and display them 
					//in thetext fields
					std::ifstream file1("holder1.txt");
					std::ifstream file2("holder2.txt");

					GetWindowTextA(field1, all, _countof(all));
					GetWindowTextA(field2, old, _countof(old));

					vector all_maps, old_maps;

					//fill the vectors with their respective maps
					LoadMaps(all, all_maps);
					LoadMaps(old, old_maps);

					//randomize a new rotation
					RandomizeNewRotation(all_maps, old_maps);

					//load the newly generated rotation into strings
					//as well as the old rotation
					std::string tmp1, tmp2;
					if (file1.is_open() && file2.is_open()) {
						std::getline(file1, tmp1);
						std::getline(file2, tmp2);
					}

					//set the window text and display the old
					//and the new rotation
					SetWindowTextA(textarea1, tmp1.c_str());
					SetWindowTextA(textarea2, tmp2.c_str());

				}
				if (msg == WM_COMMAND && (HWND)lParam == button2) {
					vector new_rotation;
					
					std::ifstream file;
					
					//read the rotation from the temporary file
					file.open("holder1.txt");
					
					//fill the vector like usual
					std::string tmp;
					while (std::getline(file, tmp))
						new_rotation.push_back(tmp);

					//call the save function to save the rotation
					save(new_rotation);
					MessageBox(hWnd, "Successfully saved the rotation to 'New Rotation.txt'", "Success!", MB_ICONINFORMATION);
				}
			}
			break;
		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			//remove holders used for temp storage
			std::remove("holder1.txt");
			std::remove("holder2.txt");
			break;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}

void save(vector &v) {
	std::fstream file("New_Rotation.txt", std::fstream::app | std::fstream::out);
	//check if the file is empty or not
	//if it is we don't printf a \n
	//this is simply to make it look better
	if (file.is_open()) {
		file.seekg(0, std::ios::end);
		size_t size = file.tellg();
		if (size > 0)
			file << '\n';
	}

	//print this to initiate the list
	file << "gametype" << " " << "zom" << " " << "map" << " ";

	for (int i = 0; i < v.size(); i++)
	{
		//take reference because othwerise
		//we check if it's equal to the value
		//whats on that index
		if (&v[i] == &v.back()) {
			file << v[i];
		}
		else
			file << v[i] << " " << "map" << " "; //if we're not on the last index of the vector then print this to the file
	}
}

void LoadMaps(std::string path, vector &maps) {
	std::ifstream file(path);
	//check if the file given exists
	//if it doesn't return
	if (!file.is_open()) {
		MessageBox(NULL, "This file does not exist", "File Not Found", MB_ICONINFORMATION);
		return;
	}
	else if (file.is_open()) {	//if the file does exist we read all its content into a string and push it back into the vector
		std::string tmp;
		while (std::getline(file, tmp)) {
			maps.push_back(tmp);
		}
	}
}

void RandomizeNewRotation(vector &all_maps, vector &old_maps) {
	srand(time(NULL));
	//remove the old rotations map from all_maps
	for (int i = 0; i < old_maps.size(); i++) {
		for (int j = 0; j < all_maps.size(); j++) {
			if (old_maps[i] == all_maps[j]) {
				all_maps[j] = all_maps.back();
				all_maps.pop_back();
			}
		}
	}

	vector new_rotation;

	//randomize picks from all_maps
	//and delete the chosen maps
	//so we dont have to deal with
	//duplications
	for (int i = 0; i < 12; i++) {
		int length = all_maps.size();
		int pos = rand() % length;
		std::string tmp;

		tmp = all_maps[pos];
		new_rotation.push_back(tmp);
		all_maps[pos] = all_maps.back();
		all_maps.pop_back();
	}

	//open the temporary files created
	//in wndproc and write to them
	std::ofstream file1("holder1.txt");
	std::ofstream file2("holder2.txt");

	//the writing to the file
	for (int i = 0; i < new_rotation.size(); i++) {
		file1 << new_rotation[i] << ' ';
	}
	for (int i = 0; i < old_maps.size(); i++) {
		file2 << old_maps[i] << ' ';
	}
}
