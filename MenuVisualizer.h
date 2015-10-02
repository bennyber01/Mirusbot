#ifndef MENUVISUALIZER_H
#define MENUVISUALIZER_H

#include "NextionGlobalDefinitions.h"

class DisplayModule;

class MenuVisualizer
{
public:
    MenuVisualizer(DisplayModule * disp);
    virtual ~MenuVisualizer();

    void Init();
    void Update();

    void SetMenuTitles(const char ** arr, int arrSize, const char * title);
    void Show(int scr = -1);
    int GetLastScreenNum() { return screenToShow; }

    void ShowPrevMenu();
    void ShowNextMenu();

    void PressedMenu1();
    void PressedMenu2();
    void PressedMenu3();

private:
    DisplayModule * disp;

    char menuTile[20];
    char ** titles;
    int numOfTitles;

    int numOfScreens;
    int screenToShow;
    int lastMenusToShow;

    void ShowMenus(int i);
};

#endif // MENUVISUALIZER_H
