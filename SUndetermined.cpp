
#include "SUndetermined.h"

SUndetermined::SUndetermined(SBarcode *bc, Drive *dri, Observer *obs, LineReturn *lr, LineTrace *lt)
{
    barCode = bc;
    drive = dri;
    observer = obs;
    lineReturn = lr;
    lineTrace = lt;

    phase = 0;
    run_on_board_pattern = 0;
    start_position = 0;
}


bool SUndetermined::run(){
    switch(phase)
    {
        case 0:
            drive->opeFRL(0, 2, 2);
			if(distance - observer->getDistance() > 3){
				changeScenario();
			}
            break;
        case 1:
            //段差検知
            //if(!段差検知)
            //drive(back);
            break;
        case 2:
            int tmp_distance = 21.5;
            if(start_position == 1) tmp_distance += 19;
            else if(start_position == 2) tmp_distance += 45;
            else if(start_position == 3) tmp_distance += 71;
            else if(start_position == 4) tmp_distance += 97;
            //start_positionまで移動
            if(observer->getDistance() > tmp_distance)
                drive->straight();
            break;
        case 3:
            drive->turn(90);
            break;
        case 4:
            if(!observer->isObstacle())
                drive->straight();
            break;
        case :
            //昇段
            break;
        case 4:
            //pattern_走行

        case

    }
        // switch pattern

    // {
    // int r = 1;
    // int l = -1;
    // case 1:

    //  Straight();
    //  Turn(90,r);
    //  Straight();
    //  Turn(90,l);
    //  Straight();
    //  break;
    // case 2:
    //  Straight();
    //  Turn(90,l);
    //  Straight();
    //  Turn(90,r);
    //  Straight();
    //  break;
    // case 3:
    //  Straight();
    //  Turn(45,l);
    //  Straight();
    //  Turn(45,r);
    //  Straight();
    //  break;
    // case 4:
    //  Straight();
    //  Turn(45,r);
    //  Straight();
    //  Turn(45,l);
    //  Straight();
    //  break;
    // case 5:
    //  Straight();
    //  Turn(90,r);
    //  Straight();
    //  Turn(90,l);
    //  Straight();
    //  break;
    // case 6:
    //  Straight();
    //  Turn(90,l);
    //  Straight();
    //  Turn(90,r);
    //  Straight();
    //  break;
    // }

	return false;
}


//getRunPattern
//これの関数にバーコードで取ってきた情報を入れると走行うパターンの１ー６のどれにするか帰ってくる
//unsigned char Barcode->getBarcode()みたいなメンバ関数があったらそれを引数にする感じ
int SUndetermined::getRunPattern(unsigned char c)
{
    int bit_array[8] = {(int)c>>7&1,(int)c>>6&1,(int)c>>5&1,(int)c>>4&1,(int)c>>3&1,(int)c>>2&1,(int)c>>1&1,(int)c&1};

    int bottles_pos[4] = {(4 - (2*bit_array[0] + bit_array[1])),
                            (4 - (2*bit_array[2] + bit_array[3])),
                            (4 - (2*bit_array[4] + bit_array[5])),
                            (4 - (2*bit_array[6] + bit_array[7]))};

    int diff_distance[3] ={0,0,0};
    int k = -1;
    int tmp_dist = -1;
    for(int i = 0; i < 4; ++i)
    {
        if(i!=0)
        {
            diff_distance[i-1] = calcManhattanDistance(bottles_pos[i-1],bottles_pos[i]);
        }
    }
    for(int i = 0; i < 3; ++i)
    {
        if(2 <= diff_distance[i] && tmp_dist <=diff_distance[i])
        {
            k = i+1;
            tmp_dist = diff_distance[i];
        }
    }

    //std::cout << "k " << k;
    if(bottles_pos[k-1] <= bottles_pos[k]) start_position = k+1;
    else                                   start_position = k;

//     return start_pos;
    //std::cout << max_n << std::endl;
    int pattern = checkRoutePattern(bottles_pos[k-1],bottles_pos[k]);
    return pattern;
}

// int SUndetermined::calcManhattanDistance(Point2 pos_1, Point2 pos_2)
// {
//     return abs(pos_1.x - pos_2.x) + abs(pos_1.y - pos_2.y);
// }

int SUndetermined::calcManhattanDistance(int pos_1, int pos_2)
{
    return  abs(pos_1 - pos_2);
}


// int SUndetermined::decide_k(std::vector<Point2> bottles_pos)
// {
//     std::vector<int> diff_distance;
//     int max_n = -1;
//     int tmp_dist = -1;
//     for(int i = 0; i < bottles_pos.size(); ++i)
//     {
//         if(i!=0){
//             diff_distance.push_back(calcManhattanDistance(bottles_pos[i-1],bottles_pos[i]));
//         }
//     }
//     for(int i = 0; i < diff_distance.size(); ++i)
//     {
//         if(3 <= diff_distance[i] && tmp_dist <=diff_distance[i])
//         {
//             max_n = i+1;
//             tmp_dist = diff_distance[i];
//         }
//     }
//     //std::cout << max_n << std::endl;
//     return max_n;
// }

// int SUndetermined::checkRoutePattern(Point2 p1, Point2 p2)
// {
//     int pattern = 0;
//     //四角 何も置いていない P ペットボトル
//     //P□ □P □P P□ □□ □□
//     //□□ □□ □□ □□ P□ □P
//     //□P P□ □□ □□ □□ □□
//     //□□ □□ P□ □P □P P□
//     // 1  2  3  4  5  6
//     //1
//     if(p1.y == 4 && p2.y == 2) pattern = 1;
//     else if(p1.y == 2 && p2.y == 4) pattern = 2;
//     else if(p1.y == 1 && p2.y == 4) pattern = 3;
//     else if(p1.y == 4 && p2.y == 1) pattern = 4;
//     else if(p1.y == 3 && p2.y == 1) pattern = 5;
//     else if(p1.y == 1 && p2.y == 3) pattern = 6;
//     else                           pattern = 0;
//     return pattern;
// }

int SUndetermined::checkRoutePattern(int p1, int p2)
{
    int pattern = 0;
    //四角 何も置いていない P ペットボトル
    //P□ □P □P P□ □□ □□
    //□□ □□ □□ □□ P□ □P
    //□P P□ □□ □□ □□ □□
    //□□ □□ P□ □P □P P□   停止
    // 1  2  3  4  5  6   0
    //1
    if(p1 == 4 && p2 == 2) pattern = 1;
    else if(p1 == 2 && p2 == 4) pattern = 2;
    else if(p1 == 1 && p2 == 4) pattern = 3;
    else if(p1 == 4 && p2 == 1) pattern = 4;
    else if(p1 == 3 && p2 == 1) pattern = 5;
    else if(p1 == 1 && p2 == 3) pattern = 6;
    else                           pattern = 0;
    return pattern;
}

// Point2 SUndetermined::decideStartPosition(std::vector<Point2> p_vec)
// {
//     int start_x = 0;
//     int k = decide_k(p_vec);
//     //std::cout << "k " << k;
//     if(p_vec[k-1].y <= p_vec[k].y) start_x = k+1;
//     else                                      start_x = k;
//     Point2 start_pos = {start_x,0};

//     return start_pos;
// }

// std::vector<Point2> SUndetermined::bitary2BottlesPos(std::vector<int> bit_array)
// {
//     std::vector<Point2> p_vec;
//     Point2 p1 = {1,(4 - (2*bit_array[0] + bit_array[1]))};
//     p_vec.push_back(p1);
//     Point2 p2 = {2,(4 - (2*bit_array[2] + bit_array[3]))};
//     p_vec.push_back(p2);
//     Point2 p3 = {3,(4 - (2*bit_array[4] + bit_array[5]))};
//     p_vec.push_back(p3);
//     Point2 p4 = {4,(4 - (2*bit_array[6] + bit_array[7]))};
//     p_vec.push_back(p4);
//     return p_vec;
// }

// std::vector<int> SUndetermined::uchar2bitary(unsigned char c)
// {
//     std::vector<int> bit_array;
//     bit_array.push_back((int)c>>7&1);
//     bit_array.push_back((int)c>>6&1);
//     bit_array.push_back((int)c>>5&1);
//     bit_array.push_back((int)c>>4&1);
//     bit_array.push_back((int)c>>3&1);
//     bit_array.push_back((int)c>>2&1);
//     bit_array.push_back((int)c>>1&1);
//     bit_array.push_back((int)c&1);
//     return bit_array;
// }
