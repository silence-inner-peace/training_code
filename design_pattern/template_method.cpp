#include <iostream>
using namespace std;

//传统的车牌识别算法分为以下四个步骤：预处理、车牌定位、车牌分割、字符识别。

//抽象类，定义算法的基本骨架
class AbstractPlateAlgClass
{
public:
    //预处理
    virtual void PreProcesser() = 0;

    //车牌定位
    virtual void PlateLocation() = 0;

    //车牌定位
    virtual void PlateSegmation() = 0;

    //车牌定位
    virtual void PlateRecognition() = 0;

    //车牌识别模板方法，定义算法的基本步骤
    void PlateAlgTemplateMethod()
    {
        PreProcesser();
        PlateLocation();
        PlateSegmation();
        PlateRecognition();
    }
};

//具体类,实现算法A
class ConcreateAlgA :public AbstractPlateAlgClass
{
public:
    //预处理
    void PreProcesser()
    {
        cout << "算法A，车牌预处理" << endl;
    }

    //车牌定位
    void PlateLocation()
    {
        cout << "算法A，车牌定位" << endl;
    }

    //车牌分割
    void PlateSegmation()
    {
        cout << "算法A，车牌分割" << endl;
    }

    //字符识别
    void PlateRecognition()
    {
        cout << "算法A，字符识别" << endl;
    }
};

//具体类,实现算法B
class ConcreateAlgB :public AbstractPlateAlgClass
{
public:
    //预处理
    void PreProcesser()
    {
        cout << "算法B，车牌预处理" << endl;
    }

    //车牌定位
    void PlateLocation()
    {
        cout << "算法B，车牌定位" << endl;
    }

    //车牌分割
    void PlateSegmation()
    {
        cout << "算法B，车牌分割" << endl;
    }

    //字符识别
    void PlateRecognition()
    {
        cout << "算法B，字符识别" << endl;
    }
};

int main()
{
    //利用算法A进行车牌识别
    AbstractPlateAlgClass *pAlgA = new ConcreateAlgA();
    if (pAlgA !=NULL)
    {
        pAlgA->PlateAlgTemplateMethod();
        delete pAlgA;
        pAlgA = NULL;
    }

    cout << "******************************************" << endl;

    //利用算法B进行车牌识别
    AbstractPlateAlgClass *pAlgB = new ConcreateAlgB();
    if (pAlgB != NULL)
    {
        pAlgB->PlateAlgTemplateMethod();
        delete pAlgB;
        pAlgB = NULL;
    }

//    getchar();
    return 0;
}

