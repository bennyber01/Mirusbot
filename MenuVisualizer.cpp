#include "MenuVisualizer.h"
#include "DisplayModule.h"
#include "NextionGlobalCallbacks.h"
#include <stdarg.h>

char commandStr[30];

bool sendNextionCommand(const char * format, ...)
{
    va_list args;
    va_start(args, format);
    vsnprintf(commandStr, sizeof(commandStr) - 1, format, args);
    commandStr[sizeof(commandStr) - 1] = 0;
    va_end(args);
    dbSerialPrintln(commandStr);
    sendCommand(commandStr);
    return recvRetCommandFinished();
}

MenuVisualizer::MenuVisualizer(DisplayModule * disp)
{
    this -> disp = disp;
    titles = NULL;
    numOfTitles = 0;
    numOfScreens = 0;
    screenToShow = 0;
    lastMenusToShow = -1;
}

MenuVisualizer::~MenuVisualizer()
{
}

void MenuVisualizer::Init()
{
}

void MenuVisualizer::Update()
{
}

void MenuVisualizer::ShowPrevMenu()
{
    --screenToShow;
    if (screenToShow < 0)
        screenToShow = numOfScreens - 1;
    Show();
}
void MenuVisualizer::ShowNextMenu()
{
    ++screenToShow;
    if (screenToShow >= numOfScreens)
        screenToShow = 0;
    Show();
}

void MenuVisualizer::PressedMenu1()
{
    disp -> SetSelectedMenu(screenToShow * 3);
}

void MenuVisualizer::PressedMenu2()
{
    disp -> SetSelectedMenu(screenToShow * 3 + 1);
}

void MenuVisualizer::PressedMenu3()
{
    disp -> SetSelectedMenu(screenToShow * 3 + 2);
}

void MenuVisualizer::SetMenuTitles(const char ** arr, int arrSize, const char * title)
{
    strncpy(menuTile, title, sizeof(menuTile));
    titles = (char**) arr;
    numOfTitles = arrSize;
    numOfScreens = (int) ceil(double(arrSize) / 3.0);
    screenToShow = 0;
    lastMenusToShow = -1;
}

void MenuVisualizer::Show(int scr)
{
    if (scr != -1)
        screenToShow = scr;

    //page1.show();
    sendNextionCommand("page 1");

    int menusToShow = min(3, numOfTitles - screenToShow * 3);

    sendNextionCommand("t0.txt=\"%s (%d/%d) [%d:%d]\"", menuTile, screenToShow + 1, numOfScreens, menusToShow, numOfTitles);

    ShowMenus(menusToShow);

//    switch (menusToShow)
//    {
//        case 3:     t1_3.setText(titles[screenToShow * 3 + 2]);
//        case 2:     t1_2.setText(titles[screenToShow * 3 + 1]);
//        case 1:     t1_1.setText(titles[screenToShow * 3 + 0]);
//    }

    switch (menusToShow)
    {
        case 3:
            sendNextionCommand("t3.txt=\"%s\"", titles[screenToShow * 3 + 2]);
        case 2:
            sendNextionCommand("t2.txt=\"%s\"", titles[screenToShow * 3 + 1]);
        case 1:
            sendNextionCommand("t1.txt=\"%s\"", titles[screenToShow * 3 + 0]);
    }
}

void MenuVisualizer::ShowMenus(int i)
{
 //   if (lastMenusToShow == i)
 //       return;

    // menu 1
    int m1 = ((i>0)?3:4);
    sendNextionCommand("t1.picc=%d", m1);
    sendNextionCommand("q0.picc=%d", m1);
//        sendNextionCommand("tsw t1,0");   //component touch invalid
//        sendNextionCommand("tsw q0,0");   //component touch invalid

    // menu 2
    int m2 = ((i>1)?3:4);
    sendNextionCommand("t2.picc=%d", m2);
    sendNextionCommand("q1.picc=%d", m2);
//        sendNextionCommand("tsw t2,0");   //component touch invalid
//        sendNextionCommand("tsw q1,0");   //component touch invalid

    // menu 3
    int m3 = ((i>2)?3:4);
    sendNextionCommand("t3.picc=%d", m3);
    sendNextionCommand("q2.picc=%d", m3);
//        sendNextionCommand("tsw t3,0");   //component touch invalid
//        sendNextionCommand("tsw q2,0");   //component touch invalid

//    if (i == 0)
//    {
//        // menu 1
//        sendNextionCommand("t1.picc=4");
//        sendNextionCommand("q0.picc=4");
////        sendCommand("tsw t1,0");   //component touch invalid
////        sendCommand("tsw q0,0");   //component touch invalid
//
//        // menu 2
//        sendNextionCommand("t2.picc=4");
//        sendNextionCommand("q1.picc=4");
////        sendCommand("tsw t2,0");   //component touch invalid
////        sendCommand("tsw q1,0");   //component touch invalid
//
//        // menu 3
//        sendNextionCommand("t3.picc=4");
//        sendNextionCommand("q2.picc=4");
////        sendCommand("tsw t3,0");   //component touch invalid
////        sendCommand("tsw q2,0");   //component touch invalid
//    }
//    else if (i == 1)
//    {
//        // menu 1
//        sendNextionCommand("t1.picc=3");
//        sendNextionCommand("q0.picc=3");
////        sendCommand("tsw t1,1");
////        sendCommand("tsw q0,1");
//
//        // menu 2
//        sendNextionCommand("t2.picc=4");
//        sendNextionCommand("q1.picc=4");
////        sendCommand("tsw t2,0");   //component touch invalid
////        sendCommand("tsw q1,0");   //component touch invalid
//
//        // menu 3
//        sendNextionCommand("t3.picc=4");
//        sendNextionCommand("q2.picc=4");
////        sendCommand("tsw t3,0");   //component touch invalid
////        sendCommand("tsw q2,0");   //component touch invalid
//    }
//    else if (i == 2)
//    {
//        // menu 1
//        sendNextionCommand("t1.picc=3");
//        sendNextionCommand("q0.picc=3");
////        sendCommand("tsw t1,1");
////        sendCommand("tsw q0,1");
//
//        // menu 2
//        sendNextionCommand("t2.picc=3");
//        sendNextionCommand("q1.picc=3");
////        sendCommand("tsw t2,1");
////        sendCommand("tsw q1,1");
//
//        // menu 3
//        sendNextionCommand("t3.picc=4");
//        sendNextionCommand("q2.picc=4");
////        sendCommand("tsw t3,0");   //component touch invalid
////        sendCommand("tsw q2,0");   //component touch invalid
//    }
//    else if (i == 3)
//    {
//        // menu 1
//        sendNextionCommand("t1.picc=3");
//        sendNextionCommand("q0.picc=3");
////        sendCommand("tsw t1,1");
////        sendCommand("tsw q0,1");
//
//        // menu 2
//        sendNextionCommand("t2.picc=3");
//        sendNextionCommand("q1.picc=3");
////        sendCommand("tsw t2,1");
////        sendCommand("tsw q1,1");
//
//        // menu 3
//        sendNextionCommand("t3.picc=3");
//        sendNextionCommand("q2.picc=3");
////        sendCommand("tsw t3,1");
////        sendCommand("tsw q2,1");
//    }

    lastMenusToShow = i;
}
