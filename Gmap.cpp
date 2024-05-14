#include "stdafx.h"
#include "GMap.h"

int GMap::LD = 36;//障碍物半径
int GMap::PD = 5;//豆子半径
//敌我双方出现位置没有豆子出现
void GMap::InitOP()
{
    peaMapData[E_ROW][E_ARRAY] = false;
    peaMapData[P_ROW][P_ARRAY] = false;
}
void GMap::DrawMap(HDC &memDC)//绘制墙壁
{
    HBRUSH hBrush = CreateSolidBrush(color);
    for(int i = 0; i < MAPLENTH; i++) {
        for(int j = 0; j < MAPLENTH; j++) {
            
            if(!mapData[i][j]&&i) {
                RECT rect;
                rect.left = j * LD;
                rect.top = i * LD;
                rect.right = (j + 1) * LD;
                rect.bottom = (i + 1) * LD;
                FillRect(memDC, &rect, hBrush);
            }
        }
    }
    DeleteObject(hBrush);
}
void GMap::DrawPeas(HDC &hdc)//绘制豆子
{
    for(int i = 0; i < MAPLENTH; i++) {
        for(int j = 0; j < MAPLENTH; j++) {
            if(peaMapData[i][j]) {
                // 在绘图设备上创建一个画刷
                HBRUSH hBrush = CreateSolidBrush(RGB(255, 128, 0)); // 这里创建了一个橙色画刷

                // 选取画刷到设备上下文
                HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

                // 画圆
                Ellipse(hdc, (LD / 2 - PD) + j * LD, (LD / 2 - PD) + i * LD, (LD / 2 + PD) + j * LD, (LD / 2 + PD) + i * LD);

                // 恢复原来的画刷
                SelectObject(hdc, hOldBrush);

                // 删除创建的画刷
                DeleteObject(hBrush);
            }
        }
    }

    // 如果按下q，直接过关，把豆子都改为被吃状态，以实现直接通关
    if(GetAsyncKeyState('Q') & 0x8000) {
        MessageBoxA(NULL, "开了就是开了？", "提示", MB_OK);
        for(int i = 0; i < MAPLENTH; i++) {
            for(int j = 0; j < MAPLENTH; j++) {
                peaMapData[i][j] = false;
            }
        }
    }
}
GMap::~GMap()
{

}
//Stage_1成员定义:
#define A true // true:表示豆子
#define B false // false:表示墙壁
bool Stage_1::initData[MAPLENTH][MAPLENTH] = {
    B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, //0
    B, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, B, //1
    B, A, B, B, B, B, B, A, A, A, A, A, B, B, B, B, B, A, B, //2
    B, A, B, A, A, A, B, A, B, B, B, A, B, A, A, A, B, A, B, //3
    B, A, B, A, B, A, B, A, A, B, A, A, B, A, B, A, B, A, B, //4
    B, A, A, A, B, A, A, A, A, B, A, A, A, A, B, A, A, A, B, //5
    B, A, B, A, B, A, B, A, A, A, A, A, B, A, B, A, B, A, B, //6
    B, A, B, A, A, A, B, A, B, B, B, A, B, A, A, A, B, A, B, //7
    B, A, B, B, B, B, B, A, A, B, A, A, B, B, B, B, B, A, B, //8
    B, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, B, //9
    B, A, B, B, B, B, B, B, B, A, B, B, B, B, B, B, B, A, B, //10
    B, A, B, A, A, A, A, A, A, A, A, A, A, A, A, A, B, A, B, //11
    B, A, B, A, B, B, B, A, B, B, B, A, B, B, B, A, B, A, B, //12
    B, A, B, A, A, A, B, A, A, A, A, A, B, A, A, A, B, A, B, //13
    B, A, B, B, B, A, B, B, B, B, B, B, B, A, B, B, B, A, B, //14
    B, A, A, A, B, A, A, A, A, A, A, A, A, A, B, A, A, A, B, //15
    B, B, B, A, B, A, B, B, B, B, B, B, B, A, B, A, B, B, B, //16
    B, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, B, //17
    B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, //18
};
#undef A
#undef B
Stage_1::Stage_1()
{
    color = RGB(140, 240, 240);
    for(int i = 0; i < MAPLENTH; i++) {
        for(int j = 0; j < MAPLENTH; j++) {
            this->mapData[i][j] = this->initData[i][j];
            this->peaMapData[i][j] = this->initData[i][j];
        }
    }
    //敌我双方出现位置没有豆子出现
    this->InitOP();
}
//Stage_2成员定义
#define A true
#define B false
bool Stage_2::initData[MAPLENTH][MAPLENTH] = {
    B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, //0
    B, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, B, //1
    B, A, B, B, B, B, B, B, B, A, B, B, B, B, B, B, B, A, B, //2
    B, A, B, A, A, A, A, A, B, A, B, A, A, A, A, A, B, A, B, //3
    B, A, B, A, B, B, B, A, B, A, B, A, B, B, B, A, B, A, B, //4
    B, A, A, A, B, A, A, A, A, A, A, A, A, A, B, A, A, A, B, //5
    B, A, B, A, B, A, B, B, B, B, B, B, B, A, B, A, B, A, B, //6
    B, A, B, A, B, A, B, A, A, A, A, A, B, A, B, A, B, A, B, //7
    B, A, B, A, B, A, B, A, B, B, B, A, B, A, B, A, B, A, B, //8
    B, A, A, A, B, A, A, A, A, A, A, A, A, A, B, A, A, A, B, //9
    B, A, B, A, B, B, B, A, B, A, B, A, B, B, B, A, B, A, B, //10
    B, A, B, A, A, A, B, A, A, A, A, A, B, A, A, A, B, A, B, //11
    B, A, B, B, B, A, B, A, B, B, B, A, B, A, B, B, B, A, B, //12
    B, A, A, A, A, A, B, A, A, A, A, A, B, A, A, A, A, A, B, //13
    B, A, B, B, B, B, B, A, B, B, B, A, B, B, B, B, B, A, B, //14
    B, A, B, A, A, A, A, A, B, A, B, A, A, A, A, A, B, A, B, //15
    B, A, B, A, B, B, B, B, B, A, B, B, B, B, B, A, B, A, B, //16
    B, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, B, //17
    B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, //18
};
#undef A
#undef B
Stage_2::Stage_2()
{
    color = RGB(204, 102, 0);
    for(int i = 0; i < MAPLENTH; i++) {
        for(int j = 0; j < MAPLENTH; j++) {
            this->mapData[i][j] = this->initData[i][j];
            this->peaMapData[i][j] = this->initData[i][j];
        }
    }
    //敌我双方出现位置没有豆子出现
    this->InitOP();
}
//Stage_3成员定义
#define A true
#define B false
bool Stage_3::initData[MAPLENTH][MAPLENTH] = {
    B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, //0
    B, A, A, A, B, A, A, A, A, A, A, A, A, A, A, B, A, A, B, //1
    B, A, B, A, B, A, B, B, B, A, B, B, B, A, B, A, B, A, B, //2
    B, A, B, A, B, A, B, A, A, A, A, A, B, A, B, A, B, A, B, //3
    B, A, B, A, B, A, B, A, B, B, B, A, B, A, B, A, B, A, B, //4
    B, A, A, A, A, A, B, A, B, A, B, A, B, A, A, A, A, A, B, //5
    B, A, B, B, B, B, B, A, B, A, B, A, B, B, B, B, B, A, B, //6
    B, A, B, A, A, A, A, A, B, A, B, A, A, A, A, A, B, A, B, //7
    B, A, B, A, B, B, B, A, B, A, B, A, B, B, B, A, B, A, B, //8
    B, A, A, A, B, A, A, A, A, A, A, A, A, A, B, A, A, A, B, //9
    B, A, B, B, B, A, B, A, B, A, B, A, B, A, B, B, B, A, B, //10
    B, A, A, A, A, A, B, A, A, A, A, A, B, A, A, A, A, A, B, //11
    B, A, B, B, B, A, B, A, B, B, B, A, B, A, B, B, B, A, B, //12
    B, A, A, A, B, A, A, A, A, A, A, A, A, A, B, A, A, A, B, //13
    B, A, B, A, B, B, B, A, B, B, B, A, B, B, B, A, B, A, B, //14
    B, A, B, A, A, A, B, A, A, A, A, A, B, A, A, A, B, A, B, //15
    B, A, B, B, B, A, B, B, B, B, B, B, B, A, B, B, B, A, B, //16
    B, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, B, //17
    B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, //18
};
#undef A
#undef B
Stage_3::Stage_3()
{
    color = RGB(153, 0, 0);
    for(int i = 0; i < MAPLENTH; i++) {
        for(int j = 0; j < MAPLENTH; j++) {
            this->mapData[i][j] = this->initData[i][j];
            this->peaMapData[i][j] = this->initData[i][j];
        }
    }
    //敌我双方出现位置没有豆子出现
    this->InitOP();
}

