#ifndef NEXTIONGLOBALDEFINITIONS_H
#define NEXTIONGLOBALDEFINITIONS_H

#include "Nextion/Nextion.h"

// about dialog vars
static NexPage   page0(0, 0,  "page0");
static NexText    t0_0(0, 1,  "t0");        // version string

// menu vars
//static NexPage   page1(1, 0,  "page1");
static NexText    t1_0(1, 10, "t0");        // title
static NexText    t1_1(1, 4,  "t1");        // menu 1
static NexText    t1_2(1, 5,  "t2");        // menu 2
static NexText    t1_3(1, 6,  "t3");        // menu 3
static NexCrop    q1_5(1, 9,  "q5");        // title
static NexCrop    q1_0(1, 1,  "q0");        // menu 1
static NexCrop    q1_1(1, 2,  "q1");        // menu 2
static NexCrop    q1_2(1, 3,  "q2");        // menu 1
static NexCrop    q1_3(1, 7,  "q3");        // down button
static NexCrop    q1_4(1, 8,  "q4");        // up button

// text dialog
//static NexPage   page2(2, 0,  "page2");
static NexText    t2_0(2, 2,  "t0");        // title
static NexCrop    q2_0(2, 1,  "q0");        // title
//static NexText    t2_1(2, 3,  "t1");        // text 1
//static NexText    t2_2(2, 4,  "t2");        // text 2
//static NexText    t2_3(2, 5,  "t3");        // text 3
//static NexText    t2_4(2, 6,  "t4");        // text 4
//static NexText    t2_5(2, 7,  "t5");        // text 5

// camera arrows
//static NexPage   page3(3, 0,  "page3");
static NexText    t3_0(3, 2,  "t0");        // title
static NexCrop    q3_0(3, 1,  "q0");        // title
//static NexText    t3_1(3, 3,  "t1");        // azim text
//static NexText    t3_2(3, 4,  "t2");        // elev text
static NexHotspot m3_0(3, 5,  "m0");        // left button
static NexHotspot m3_1(3, 6,  "m1");        // up button
static NexHotspot m3_2(3, 7,  "m2");        // center button
static NexHotspot m3_3(3, 8,  "m3");        // down button
static NexHotspot m3_4(3, 9,  "m4");        // right button

// wandering buttons
//static NexPage   page4(4, 0,  "page4");
static NexText    t4_0(4, 2,  "t0");        // title
static NexCrop    q4_0(4, 1,  "q0");        // title
static NexPicture p4_0(4, 3,  "p0");        // picture

// robot angle dialog
static NexPage   page5(5, 0,  "page5");
static NexText    t5_0(5, 2,  "t0");        // title
static NexCrop    q5_0(5, 1,  "q0");        // title
static NexHotspot m5_0(5, 3,  "m0");        // reset button
//static NexGauge   z5_0(5, 4,  "z0");        // gauge

static NexTouch *nex_listen_list[] =
{
    &page0,
    &t0_0,

    &t1_0,
    &t1_1,
    &t1_2,
    &t1_3,
    &q1_0,
    &q1_1,
    &q1_2,
    &q1_3,
    &q1_4,
    &q1_5,

    &t2_0,
    &q2_0,

    &t3_0,
    &q3_0,
    &m3_0,
    &m3_1,
    &m3_2,
    &m3_3,
    &m3_4,

    &t4_0,
    &q4_0,
    &p4_0,

    &t5_0,
    &q5_0,
    &m5_0,

    NULL
};

#endif // NEXTIONGLOBALDEFINITIONS_H
