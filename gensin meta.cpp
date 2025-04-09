#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>

int main() {
    const char* genshinProcessName = "GenshinImpact.exe"; // Adjust this to match the Genshin executable name
    bool isBlinking = false;

    while (true) {
        // Check if Genshin is running
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnapshot == INVALID_HANDLE_VALUE) {
            return 1;
        }

        PROCESSENTRY32 pe;
        pe.dwSize = sizeof(PROCESSENTRY32);

        if (!Process32First(hSnapshot, &pe)) {
            CloseHandle(hSnapshot);
            return 1;
        }

        bool isGenshinRunning = false;
        do {
            if (strcmp(pe.szExeFile, genshinProcessName) == 0) {
                isGenshinRunning = true;
                break;
            }
        } while (Process32Next(hSnapshot, &pe));

        CloseHandle(hSnapshot);

        if (isGenshinRunning) {
            std::cout << "\r                                 "; // Clear the previous message
            std::cout << "\rEDAN BYPASS IS ACTIVATED." << std::endl;
            std::cout.flush();
            std::cout << "Press any key to exit..." << std::endl;
            system("pause > nul");
            return 0;
        }

        // Modify registry values
        system("reg add \"HKLM\\SYSTEM\\ControlSet001\\Services\\HoYoProtect\" /v \"ErrorControl\" /t REG_DWORD /d 0 /f > nul 2>&1");
        system("reg add \"HKLM\\SYSTEM\\ControlSet001\\Services\\HoYoProtect\" /v \"Start\" /t REG_DWORD /d 0 /f > nul 2>&1");
        system("reg add \"HKLM\\SYSTEM\\ControlSet001\\Services\\HoYoProtect\" /v \"Type\" /t REG_DWORD /d 0 /f > nul 2>&1");

        // Blink message
        const int LINE_WIDTH = 50;

        if (isBlinking) {
            std::cout << "\033[2J"; // Clear the screen
            std::cout << "\033[H"; // Move the cursor to the top left corner
            std::cout << "\033[38;5;94m"; // Brown color
            std::cout << "            __,__\n";
            std::cout << "   .--.  .-\"     \"-.  .--.\n";
            std::cout << "  / .. \\/  .-. .-.  \\/ .. \\\n";
            std::cout << " | |  '|  /   Y   \\  |'  | |\n";
            std::cout << " | \\   \\  \\ 0 | 0 /  /   / |\n";
            std::cout << "  \\ '- ,\\.-\"`` ``\"-./, -' /\n";
            std::cout << "   `'-' /_   ^ ^   _\\ '-'`\n";
            std::cout << "       |  \\._   _./  |\n";
            std::cout << "       \\   \\ `~` /   /\n";
            std::cout << "        '._ '-=-' _.'\n";
            std::cout << "           '~---~'\n";
            std::cout << "\033[0m"; // Reset color
            std::cout << "\033[92mEDAN BERJALAN\033[0m\n";
        }
        else {
            std::cout << "\033[2J"; // Clear the screen
            std::cout << "\033[H"; // Move the cursor to the top left corner
        }

        isBlinking = !isBlinking;
        std::cout.flush();

        // Wait for 100 milliseconds
        Sleep(100);
    }

    return 0;
}