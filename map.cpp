#include "map.h"

void Map::setup()
{
    srand ( time(NULL) );
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
    int row = 0;
    for (int y = 0; y < size*(scale+1)+1; y++)
    {
        std::vector<int> myVec (0);
        boardMain.push_back(myVec);
    }
    for (int a = 0; a < size; a++)
    {
        for (int aa = 0; aa < size; aa++)
        {
            if (symBoardMain[a][aa].magnitude == biggest)
            {
                if (symBoardMain[a][aa].topedge && symBoardMain[a][aa].leftedge)
                {
                    boardMain[row].push_back(2);
                }
                if (symBoardMain[a][aa].topedge)
                {
                    for (int t = 0; t < scale; t++)
                    {
                        boardMain[row].push_back(2);
                    }
                }
                if (symBoardMain[a][aa].leftedge)
                {
                    for (int t = 1; t <= scale+1; t++)
                    {
                        boardMain[row+t].push_back(2);
                    }
                }
                if (symBoardMain[a][aa].rightedge || symBoardMain[a][aa].topedge)
                {
                    boardMain[row].push_back(2);
                }

                for (int t = 1; t <= scale; t++)
                {
                    for (int tt = 0; tt < scale; tt++)
                    {
                        boardMain[row+t].push_back(1);
                    }
                }

                if (symBoardMain[a][aa].bot)
                {
                    for (int t = 0; t < scale; t++)
                    {
                        boardMain[row+scale+1].push_back(2);
                    }
                }
                else
                {
                    for (int t = 0; t < scale; t++)
                    {
                        boardMain[row+scale+1].push_back(1);
                    }
                }
                if (symBoardMain[a][aa].right)
                {
                    for (int t = 1; t <= scale; t++)
                    {
                        boardMain[row+t].push_back(2);
                    }
                }
                else
                {
                    for (int t = 1; t <= scale; t++)
                    {
                        boardMain[row+t].push_back(1);
                    }
                }
                if (symBoardMain[a][aa].bot || symBoardMain[a][aa].right || (!symBoardMain[a][aa].botedge && symBoardMain[a+1][aa].magnitude == biggest && symBoardMain[a+1][aa].right) || (!symBoardMain[a][aa].rightedge && symBoardMain[a][aa+1].magnitude == biggest && symBoardMain[a][aa+1].bot))
                {
                    boardMain[row+scale+1].push_back(2);
                }
                else
                {
                    boardMain[row+scale+1].push_back(1);
                }
            }
            else // if the current tile is not in the biggest room
            {
                if (symBoardMain[a][aa].topedge && symBoardMain[a][aa].leftedge)
                {
                    boardMain[row].push_back(0);
                }
                if (symBoardMain[a][aa].leftedge)
                {
                    for (int t = 1; t <= scale; t++)
                    {
                        boardMain[row+t].push_back(0);
                    }

                    if (!symBoardMain[a][aa].botedge && symBoardMain[a+1][aa].magnitude == biggest && symBoardMain[a][aa].bot){
                        boardMain[row+scale+1].push_back(2);
                    }
                    else
                    {
                        boardMain[row+scale+1].push_back(0);
                    }
                }
                if (symBoardMain[a][aa].topedge)
                {
                    for (int t = 0; t < scale; t++)
                    {
                        boardMain[row].push_back(0);
                    }
                }
                if (symBoardMain[a][aa].rightedge || symBoardMain[a][aa].topedge)
                {
                    if (!symBoardMain[a][aa].rightedge && symBoardMain[a][aa].right && symBoardMain[a][aa+1].magnitude == biggest)
                    {
                        boardMain[row].push_back(2);
                    }
                    else
                    {
                        boardMain[row].push_back(0);
                    }
                }

                for (int t = 1; t <= scale; t++)
                {
                    for (int tt = 0; tt < scale; tt++)
                    {
                        boardMain[row+t].push_back(0);
                    }
                }

                if (!symBoardMain[a][aa].rightedge && symBoardMain[a][aa+1].magnitude == biggest && symBoardMain[a][aa].right)
                {
                    for (int t = 1; t <= scale; t++)
                    {
                        boardMain[row+t].push_back(2);
                    }
                }
                else /*if (symBoardMain[a][aa].rightedge ||  (!symBoardMain[a][aa].rightedge && symBoardMain[a][aa+1].magnitude != biggest && symBoardMain[a][aa].right))*/
                {
                    for (int t = 1; t <= scale; t++)
                    {
                        boardMain[row+t].push_back(0);
                    }
                }
                if (!symBoardMain[a][aa].botedge && symBoardMain[a+1][aa].magnitude == biggest && symBoardMain[a][aa].bot)
                {
                    for (int t = 0; t < scale; t++)
                    {
                        boardMain[row+scale+1].push_back(2);
                    }
                }
                else /*if (!symBoardMain[a][aa].botedge && symBoardMain[a][aa].bot && symBoardMain[a+1][aa].magnitude != biggest)*/
                {
                    for (int t = 0; t < scale; t++)
                    {
                        boardMain[row+scale+1].push_back(0);
                    }
                }
                if ((!symBoardMain[a][aa].botedge && symBoardMain[a+1][aa].magnitude == biggest && symBoardMain[a][aa].bot) || (!symBoardMain[a][aa].rightedge && symBoardMain[a][aa+1].magnitude == biggest && symBoardMain[a][aa].right) || (!symBoardMain[a][aa].botedge && !symBoardMain[a][aa].rightedge && symBoardMain[a+1][aa+1].magnitude == biggest))
                {
                    boardMain[row+scale+1].push_back(2);
                }
                else/* if ((symBoardMain[a][aa].rightedge ||  (!symBoardMain[a][aa].rightedge && symBoardMain[a][aa+1].magnitude != biggest && symBoardMain[a][aa].right)) || (symBoardMain[a][aa].rightedge ||  (!symBoardMain[a][aa].botedge && symBoardMain[a+1][aa].magnitude != biggest && symBoardMain[a][aa].bot)))*/
                {
                    boardMain[row+scale+1].push_back(0);
                }
            }
        }
        row += scale+1;
    }
    for (int hard = 0; hard < boardMain.size(); hard++)
    {
        while (boardMain[hard].size() != (scale+1)*size+1)
        {
            boardMain[hard].erase(boardMain[hard].begin() + boardMain[hard].size()-1);
        }
    }
}

void Map::draw()
{
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
    std::cout << "\n\n\n";
    for (int i = 0; i < boardMain.size(); i++)
    {
        std::cout << "\t";
        for (int ii = 0; ii < boardMain[i].size(); ii++)
        {
            char output;
            if (boardMain[i][ii] == 1)
            {
                output = ' ';
            }
            else if (boardMain[i][ii] == 2)
            {
                output = '#';
            }
            else if (boardMain[i][ii] == 0)
            {
                output = '.';
            }
            else
            {
                output = '?';
            }
            std::cout << output << " ";
        }
        std::cout << std::endl;
    }
}
