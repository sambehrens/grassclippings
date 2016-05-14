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
            if (rand() % 11 > frequency && ss < size-1)
            {
                symBoardMain[s][ss].right = true;
                symBoardMain[s][ss].left = true;
            }
            if (rand() % 11 > frequency && s < size-1)
            {
                symBoardMain[s][ss].bot = true;
                symBoardMain[s][ss].top = true;
            }
        }
    }

    for (int m = 0; m < size; m++) { // finding room sizes
        for (int mm = 0; mm < size; mm++) {
            if (symBoardMain[m][mm].checked == false) {

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

                    if (symBoardMain[yy][xx].top == false)
                        {
                        numberofspaces++;
                    }
                    if (symBoardMain[yy][xx].bot == false)
                    {
                        numberofspaces++;
                    }
                    if (symBoardMain[yy][xx].left == false)
                    {
                        numberofspaces++;
                    }
                    if (symBoardMain[yy][xx].right == false)
                    {
                        numberofspaces++;
                    }

                    if (symBoardMain[yy][xx].timesChecked < numberofspaces)
                    {
                        comebacks.push_back(coords);
                    }

                    if (symBoardMain[yy][xx].topedge == false && symBoardMain[yy][xx].top == false && symBoardMain[yy-1][xx].checked == false)
                        {
                        yy -= 1;
                    }
                    else if (symBoardMain[yy][xx].botedge == false && symBoardMain[yy][xx].bot == false && symBoardMain[yy+1][xx].checked == false)
                    {
                        yy += 1;
                    }
                    else if (symBoardMain[yy][xx].leftedge == false && symBoardMain[yy][xx].left == false && symBoardMain[yy][xx-1].checked == false)
                    {
                        xx -= 1;
                    }
                    else if (symBoardMain[yy][xx].rightedge == false && symBoardMain[yy][xx].right == false && symBoardMain[yy][xx+1].checked == false)
                    {
                        xx += 1;
                    }
                    else
                    {
                        if (comebacks.size() == 0)
                        {
                            for (int u = 0; u < visited.size(); u += 1)
                            {
                                symBoardMain[visited[u].y][visited[u].x].magnitude = visited.size();
                            }
                            if (visited.size() > biggest)
                            {
                                biggest = visited.size();
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


}

void Map::draw()
{
    for (int i = 0; i < size * scale; i++)
    {
        for (int ii = 0; ii < size * scale; ii++)
        {
            std::cout << symBoardMain[i][ii].type;
        }
        std::cout << std::endl;
    }
}
