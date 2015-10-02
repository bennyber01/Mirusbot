#ifndef NEXTIONGLOBALCALLBACKS_H
#define NEXTIONGLOBALCALLBACKS_H

// menu callbacks
void goBackCallback(void *ptr);
void menu1Callback(void *ptr);
void menu2Callback(void *ptr);
void menu3Callback(void *ptr);
void showNextMenuCallback(void *ptr);
void showPrevMenuCallback(void *ptr);

void showMainMenuCallback(void *ptr);
void showCameraArrowsCallback(void *ptr);

void cameraUpArrowPressedCallback(void *ptr);
void cameraUpArrowReleasedCallback(void *ptr);
void cameraDownArrowPressedCallback(void *ptr);
void cameraDownArrowReleasedCallback(void *ptr);
void cameraLeftArrowPressedCallback(void *ptr);
void cameraLeftArrowReleasedCallback(void *ptr);
void cameraRightArrowPressedCallback(void *ptr);
void cameraRightArrowReleasedCallback(void *ptr);
void cameraCenterCallback(void *ptr);
void toggleWanderingCallback(void *ptr);
void resetGaugeCallback(void *ptr);

#endif // NEXTIONGLOBALCALLBACKS_H
