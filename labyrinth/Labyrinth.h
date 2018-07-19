//
// Created by 黄琛垚 on 2018/7/19.
//

#ifndef DATA_STRUCTURE_CELL_H
#define DATA_STRUCTURE_CELL_H

#include <cstdlib>
#include "../stack/Stack.h"

typedef enum {
    AVAILABLE, ROUTE, BACKTRACKED, WALL
} Status; //迷宫单元状态
//原始可用的、在当前路径上的、所有方向均尝试失败后回溯过的、不可使用的(墙)

typedef enum {
    UNKNOWN, EAST, SOUTH, WEST, NORTH, NO_WAY
} ESWN; //单元的相对邻接方向
//未定、东、南、西、北、无路可通

inline ESWN nextESWN(ESWN eswn) { return ESWN(eswn + 1); } //依次转至下一邻接方向

struct Cell { //迷宫格点
    int x, y; //x坐标、y坐标
    Status status; //类型
    ESWN incoming, outgoing; //进入、走出方向
};

#define LABY_MAX 24 //最大迷宫尺寸
Cell laby[LABY_MAX][LABY_MAX]; //迷宫

inline Cell *neighbor(Cell *cell) { //查询当前位置的相邻格点
    switch (cell->outgoing) {
        case EAST:
            return cell + LABY_MAX; //向东
        case SOUTH:
            return cell + 1; //向南
        case WEST:
            return cell - LABY_MAX; //向西
        case NORTH:
            return cell - 1; //向北
        default:
            exit(-1);
    }
}

inline Cell *advance(Cell *cell) { //从当前位置转入相邻格点
    Cell *next;
    switch (cell->outgoing) {
        case EAST: //向东
            next = cell + LABY_MAX;
            next->incoming = WEST;
            break;
        case SOUTH: //向南
            next = cell + 1;
            next->incoming = NORTH;
            break;
        case WEST: //向西
            next = cell - LABY_MAX;
            next->incoming = EAST;
            break;
        case NORTH: //向北
            next = cell - 1;
            next->incoming = SOUTH;
            break;
        default :
            exit(-1);
    }
    return next;
}

// 迷宫路径算法:在格单元s至t之间规划一条通路(如果的确存在)
bool labyrinth(Cell Laby[LABY_MAX][LABY_MAX], Cell *s, Cell *t) {
    if ((AVAILABLE != s->status) || (AVAILABLE != t->status)) { return false; } //退化情况
    Stack<Cell *> path; //用栈记录通路(Theseus的线绳)
    s->incoming = UNKNOWN;
    s->status = ROUTE;
    path.push(s); //起点
    do {
        Cell *c = path.top(); //检查当前位置(栈顶)
        if (c == t) { return true; } //若已抵达终点，则找到了一条通路;否则，(沿尚未试探的方向)向前试探
        while (NO_WAY > (c->outgoing = nextESWN(c->outgoing))) { //逐一检查所有方向
            if (AVAILABLE == neighbor(c)->status) { break; } //试图找到尚未试探的方向
        }
        if (NO_WAY <= c->outgoing) { //若所有方向都已尝试过
            c->status = BACKTRACKED;
            c = path.pop();
        } //则向后回溯一步
        else { //否则，向前试探一步
            path.push(c = advance(c));
            c->outgoing = UNKNOWN;
            c->status = ROUTE;
        }
    } while (!path.empty());
    return false;
}

#endif //DATA_STRUCTURE_CELL_H
