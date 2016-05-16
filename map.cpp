#include "map.h"

void Map::setup()
{
    for (int i = 0; i < size; i++)
    {
        std::vector<Tile> row;
        for (int ii = 0; ii < size; ii++)
        {
            Tile tile;

            if (i == 0)
            {
                tile.top = true;
                tile.topedge = true;
                tile.type = 1;
            }
            else if (i == size - 1)
            {
                tile.bot = true;
                tile.botedge = true;
                tile.type = 1;
            }
            if (ii == 0) {
                tile.left = true;
                tile.leftedge = true;
                tile.type = 1;
            }
            else if (ii == size - 1)
            {
                tile.right = true;
                tile.rightedge = true;
                tile.type = 1;
            }

            row.push_back(tile);
        }
        symBoardMain.push_back(row);
    }

    for (int s = 0; s < size; s++)
    { // adding wall values
        for (int ss = 0; ss < size; ss++)
        {
            std::cout << "the random number is:  " << rand() % 11 << "\n";
            if (rand() % 11 > frequency && ss < size-1)
            {
                symBoardMain[s][ss].right = true;
                symBoardMain[s][ss+1].left = true;
            }
            if (rand() % 11 > frequency && s < size-1)
            {
                symBoardMain[s][ss].bot = true;
                symBoardMain[s+1][ss].top = true;
            }
        }
    }

    for (int m = 0; m < size; m++) { // finding room sizes
        for (int mm = 0; mm < size; mm++) {
            if (!symBoardMain[m][mm].checked) {

                std::vector<Coordinates> visited;
                std::vector<Coordinates> comebacks;
                int xx = mm;
                int yy = m;
                while (true) {

                    symBoardMain[yy][xx].checked = true;
                    symBoardMain[yy][xx].timesChecked++;

                    Coordinates coords;
                    coords.x = xx;
                    coords.y = yy;
                    visited.push_back(coords);

                    int numberofspaces = 0;

                    if (!symBoardMain[yy][xx].top)
                    {
                        numberofspaces++;
                    }
                    if (!symBoardMain[yy][xx].bot)
                    {
                        numberofspaces++;
                    }
                    if (!symBoardMain[yy][xx].left)
                    {
                        numberofspaces++;
                    }
                    if (!symBoardMain[yy][xx].right)
                    {
                        numberofspaces++;
                    }

                    if (symBoardMain[yy][xx].timesChecked < numberofspaces)
                    {
                        comebacks.push_back(coords);
                    }

                    if (symBoardMain[yy][xx].topedge == false && symBoardMain[yy][xx].top == false && symBoardMain[yy-1][xx].checked == false)
                    {
                        yy--;
                    }
                    else if (symBoardMain[yy][xx].botedge == false && symBoardMain[yy][xx].bot == false && symBoardMain[yy+1][xx].checked == false)
                    {
                        yy++;
                    }
                    else if (symBoardMain[yy][xx].leftedge == false && symBoardMain[yy][xx].left == false && symBoardMain[yy][xx-1].checked == false)
                    {
                        xx--;
                    }
                    else if (symBoardMain[yy][xx].rightedge == false && symBoardMain[yy][xx].right == false && symBoardMain[yy][xx+1].checked == false)
                    {
                        xx++;
                    }
                    else
                    {
                        if (comebacks.size() == 0)
                        {
                            for (int u = 0; u < visited.size(); u++)
                            {
                                symBoardMain[visited[u].y][visited[u].x].magnitude = visited.size();
                            }
                            if (visited.size() > biggest)
                            {
                                biggest = visited.size();
                                std::cout << "setting bigest to: " << biggest << "\n";
//                                int rando1 = Random.Range(0,visitedx.size-1);
//                                player1.transform.position = new Vector3(visitedx[rando1] * increment, player1.transform.position.y, visitedy[rando1] * increment);
//                                int rando2 = Random.Range(0,visitedx.size-1);
//                                player2.transform.position = new Vector3(visitedx[rando2] * increment, player2.transform.position.y, visitedy[rando2] * increment);
                            }
                            break;
                        }
                        xx = comebacks[comebacks.size()-1].x;
                        yy = comebacks[comebacks.size()-1].y;
                        comebacks.erase(comebacks.begin() + comebacks.size()-1);
                    }
                }
            }
        }
    }

//    int row = 0;
//    for (int a = 0; a < size; a++)
//    {
//        for (int aa = 0; aa < size; aa++)
//        {
//            std::cout << "magnitude:  " << symBoardMain[a][aa].magnitude << "\n";
//            int h = 0;
//            std::cin >> h;
//            if (symBoardMain[a][aa].magnitude == biggest)
//            {
//                std::cout << "1\n";
//                int h = 0;
//                std::cin >> h;
//                if (symBoardMain[a][aa].botedge && symBoardMain[a][aa].rightedge)
//                {
//                    std::cout << "2\n";
//                    boardMain[row].push_back(2);
//                    boardMain[row].push_back(2);
//                    boardMain[row].push_back(2);
//                    boardMain[row+1].push_back(2);
//                    boardMain[row+1].push_back(0);
//                    boardMain[row+1].push_back(0);
//                    boardMain[row+2].push_back(2);
//                    boardMain[row+2].push_back(0);
//                    boardMain[row+2].push_back(0);
//                }
//                else if (symBoardMain[a][aa].topedge && symBoardMain[a][aa].leftedge)
//                {
//                    std::cout << "3\n";
//                    boardMain[row].push_back(0);
//                    boardMain[row].push_back(0);
//                    boardMain[row].push_back(2);
//                    boardMain[row+1].push_back(0);
//                    boardMain[row+1].push_back(0);
//                    boardMain[row+1].push_back(2);
//                    boardMain[row+2].push_back(2);
//                    boardMain[row+2].push_back(2);
//                    boardMain[row+2].push_back(2);
//                }
//                else if (symBoardMain[a][aa].topedge && symBoardMain[a][aa].rightedge)
//                {
//                    boardMain[row].push_back(2);
//                    boardMain[row].push_back(0);
//                    boardMain[row].push_back(0);
//                    boardMain[row+1].push_back(2);
//                    boardMain[row+1].push_back(0);
//                    boardMain[row+1].push_back(0);
//                    boardMain[row+2].push_back(2);
//                    boardMain[row+2].push_back(2);
//                    boardMain[row+2].push_back(2);
//                }
//                else if (symBoardMain[a][aa].botedge && symBoardMain[a][aa].leftedge)
//                {
//                    boardMain[row].push_back(2);
//                    boardMain[row].push_back(2);
//                    boardMain[row].push_back(2);
//                    boardMain[row+1].push_back(0);
//                    boardMain[row+1].push_back(0);
//                    boardMain[row+1].push_back(2);
//                    boardMain[row+2].push_back(0);
//                    boardMain[row+2].push_back(0);
//                    boardMain[row+2].push_back(2);
//                }
//                else if (symBoardMain[a][aa].topedge)
//                {
//                    boardMain[row].push_back(0);
//                    boardMain[row].push_back(0);
//                    boardMain[row].push_back(0);
//                    boardMain[row+1].push_back(0);
//                    boardMain[row+1].push_back(0);
//                    boardMain[row+1].push_back(0);
//                    boardMain[row+2].push_back(2);
//                    boardMain[row+2].push_back(2);
//                    boardMain[row+2].push_back(2);
//                }
//                else if (symBoardMain[a][aa].botedge)
//                {
//                    boardMain[row].push_back(2);
//                    boardMain[row].push_back(2);
//                    boardMain[row].push_back(2);
//                    boardMain[row+1].push_back(0);
//                    boardMain[row+1].push_back(0);
//                    boardMain[row+1].push_back(0);
//                    boardMain[row+2].push_back(0);
//                    boardMain[row+2].push_back(0);
//                    boardMain[row+2].push_back(0);
//                }
//                else if (symBoardMain[a][aa].leftedge)
//                {
//                    boardMain[row].push_back(0);
//                    boardMain[row].push_back(0);
//                    boardMain[row].push_back(2);
//                    boardMain[row+1].push_back(0);
//                    boardMain[row+1].push_back(0);
//                    boardMain[row+1].push_back(2);
//                    boardMain[row+2].push_back(0);
//                    boardMain[row+2].push_back(0);
//                    boardMain[row+2].push_back(2);
//                }
//                else if (symBoardMain[a][aa].rightedge)
//                {
//                    boardMain[row].push_back(2);
//                    boardMain[row].push_back(0);
//                    boardMain[row].push_back(0);
//                    boardMain[row+1].push_back(2);
//                    boardMain[row+1].push_back(0);
//                    boardMain[row+1].push_back(0);
//                    boardMain[row+2].push_back(2);
//                    boardMain[row+2].push_back(0);
//                    boardMain[row+2].push_back(0);
//                }
//                boardMain[row].push_back(1);
//                boardMain[row].push_back(1);
//                boardMain[row].push_back(1);
//                boardMain[row+1].push_back(1);
//                boardMain[row+1].push_back(1);
//                boardMain[row+1].push_back(1);
//                boardMain[row+2].push_back(1);
//                boardMain[row+2].push_back(1);
//                boardMain[row+2].push_back(1);
//            }
//            else
//            {
//                std::cout << "completely failing" << std::endl;
////                boardMain[row].push_back(0);
////                boardMain[row].push_back(0);
////                boardMain[row].push_back(0);
////                boardMain[row+1].push_back(0);
////                boardMain[row+1].push_back(0);
////                boardMain[row+1].push_back(0);
////                boardMain[row+2].push_back(0);
////                boardMain[row+2].push_back(0);
////                boardMain[row+2].push_back(0);
//            }
//        }
//        row += scale;
//    }
}

void Map::draw()
{
    std::cout << "biggest: " << biggest << "\n";
    for (int i = 0; i < size; i++)
    {
        for (int ii = 0; ii < size; ii++)
        {
            std::cout << symBoardMain[i][ii].magnitude << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << "\n\n\n";
    for (int i = 0; i < size; i++)
    {
        for (int ii = 0; ii < size; ii++)
        {
            int yupper = 0;
            if (symBoardMain[i][ii].left)
            {
                yupper++;
            }
            if (symBoardMain[i][ii].right)
            {
                yupper++;
            }
            if (symBoardMain[i][ii].top)
            {
                yupper++;
            }
            if (symBoardMain[i][ii].bot)
            {
                yupper++;
            }
            std::cout << yupper << "\t";
        }
        std::cout << std::endl;
    }
}
