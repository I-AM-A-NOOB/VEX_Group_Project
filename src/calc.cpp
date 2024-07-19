#include "calc.h"

float deg2rad(float _input) {
    return _input / 180 * M_PI;
}
float rad2deg(float _input) {
    return _input * 180 / M_PI;
}

int sign(float _input) {
    return (_input > 0) - (_input < 0);
}

int sign(double _input) {
    return (_input > 0) - (_input < 0);
}

/**
 * @brief 计算矢量大小
 * @param _x 矢量x分量
 * @param _y 矢量y分量
*/
float calMod(float _x, float _y) {
    return sqrtf(_x * _x + _y * _y);
}

/**
 * @brief 在笛卡尔坐标系计算矢量方向，x轴正方向为0度，顺时针为正，从0到360度
 * @param _x 矢量x分量
 * @param _y 矢量y分量
*/
float calDir(float _x, float _y) {
    return rad2deg(atan2(_y, _x));
}
