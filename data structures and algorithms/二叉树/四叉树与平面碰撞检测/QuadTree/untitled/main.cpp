#include <QApplication>
#include <QMainWindow>
#include <QTextCodec>
#include <QDebug>
#include <cmath>
#include <ctime>
#include <QLabel>
#include <cstdlib>
#include <QWidget>
#include "quadtree.h"

#define RECTANGLE_NUM 20
#define RANGE_MAX 500
#define RECTANGLE_MAX_WIDTH 100
#define RECTANGLE_MAX_HEIGHT 100
#define COLOR_INDEX (210 / RECTANGLE_NUM)

struct Rectangle;

typedef QuadTree<Rectangle> TreeType;
typedef TreeType::pos_type PosType;

static QString format(const char* str, ...)
{
    va_list arg_list;
    va_start(arg_list, str);
    char tmp[1024];
    int len = vsprintf(tmp, str, arg_list);
    tmp[len] = 0;
    va_end(arg_list);
    return QObject::tr(tmp);
}

struct Rectangle
{
    PositionType::PositionType operator()(const PosType& p) const
    {
        int quad = 0;
        bool left = minx < p.x;
        bool right = maxx > p.x;
        bool top = miny < p.y;
        bool bottom = maxy > p.y;
        if(left && top)
        {
            quad |= PositionType::LEFT_TOP;
        }
        if(left && bottom)
        {
            quad |= PositionType::LEFT_BOTTOM;
        }
        if(right && top)
        {
            quad |= PositionType::RIGHT_TOP;
        }
        if(right && bottom)
        {
            quad |= PositionType::RIGHT_BOTTOM;
        }
        return PositionType::PositionType(quad);
    }

    bool operator==(const Rectangle& p) const
    {
        return obj == p.obj;
    }

    bool operator()(const Rectangle& p) const
    {
        long long x1 = (minx + maxx) / 2, y1 = (miny + maxy) / 2;
        long long x2 = (p.minx + p.maxx) / 2, y2 = (p.miny + p.maxy) / 2;
        long long width1 = maxx - minx, height1 = maxy - miny;
        long long width2 = p.maxx - p.minx, height2 = p.maxy - p.miny;
        long long x = abs(x1 - x2), y = abs(y1 - y2);
        long long width = (width1 + width2) / 2, height = (height1 + height2) / 2;
        bool ret = x < width;
        ret = ret && y < height;
        return ret;
    }

    bool operator<(const Rectangle& p) const
    {
        return obj < p.obj;
    }

    friend QDebug& operator<<(QDebug& out, const Rectangle& p)
    {
        out << p.obj;
        return out;
    }

    long long minx;
    long long miny;
    long long maxx;
    long long maxy;
    long long obj;
};

static void collision(Rectangle& p1, Rectangle& p2)
{
//    if (p1.obj == 14)
//    {
    qDebug() << "collision: (" << p1.obj << ", " << p2.obj << ")";
//    }
}

struct CollisionManager
{
    void collision(const Rectangle& p1, const Rectangle& p2) const
    {
        qDebug() << "collision: (" << p1.obj << ", " << p2.obj << ")";
    }
};

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QTextCodec* codec = QTextCodec::codecForName("utf-8");//设置编码格式
    QTextCodec::setCodecForLocale(codec);
    /*
    - 4 右上：象限一
    - 8 左上：象限二
    - 2 左下：象限三
    - 1 右下：象限四

    */
    TreeType tree(8, PosType(0, 0), PosType(RANGE_MAX, RANGE_MAX));
    QMainWindow w;
    w.setWindowTitle(QObject::tr("QuadTree Test"));
    w.resize(RANGE_MAX + 100, RANGE_MAX + 100);
    QWidget* root = new QWidget(&w);
    root->setStyleSheet("background:rgb(255,255,255)");
    root->move(0, 0);
    root->resize(RANGE_MAX + 100, RANGE_MAX + 100);
//    srand(static_cast<unsigned int>(time(nullptr)));
    for(int i = 1; i <= RECTANGLE_NUM; ++i)
    {
        Rectangle p;
        p.minx = rand() % RANGE_MAX;
        p.miny = rand() % RANGE_MAX;
        p.maxx = rand() % RECTANGLE_MAX_WIDTH + p.minx + 10;
        p.maxy = rand() % RECTANGLE_MAX_HEIGHT + p.miny + 10;
        p.obj = i;
        QWidget* handle = new QWidget(root);
        handle->setStyleSheet(format("background:rgb(%d,%d,%d)", COLOR_INDEX * i, COLOR_INDEX * i, COLOR_INDEX * i));
        QLabel* label = new QLabel(handle);
        QFont ft;
        ft.setPointSize(12);
        label->setFont(ft);
        label->setStyleSheet(format("color:rgb(255,255,255)"));
        label->setText(QString::number(i));
        handle->move(static_cast<int>(p.minx), static_cast<int>(p.miny));
        handle->resize(static_cast<int>(p.maxx - p.minx), static_cast<int>(p.maxy - p.miny));
        qDebug() << "new obj:" << p.obj << " ---> min:(" << p.minx << ", " << p.miny << ") max:(" << p.maxx << ", " << p.maxy << ")";
        tree.insert(p);  // 所有节点插入到树中
    }
    tree.collision_detection(collision);  // 碰撞检测
    w.show();
    return a.exec();
}
