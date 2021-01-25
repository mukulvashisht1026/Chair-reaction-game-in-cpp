/*
To run this file, Type these commands on terminal
g++ ChainReactionGame.cpp
./a.out
*/
#include<bits/stdc++.h>
using namespace std;

#define defaultIdOfEmptyCell -1
#define cornerCell 1
#define edgeCell 2
#define innerCell 3
#define tableRowCount 10
#define tableColCount 10
#define playerCount 2

string colorArray[] = {"Red" , "Green" , "Blue" , "Yellow" };

static int c =0;
class Cell{
    private:

        int playerIdOfTheCell, typeOfCell;// there are three types of cell : corner cell , edge cell, inner cell
        int weightOfTheCell;
        int rowNum, colNum;
        string colorOfTheCell;
        
        
    public:

        Cell(int rowNumber , int colNumber) {

            playerIdOfTheCell =-1;
            colorOfTheCell = "Black";
            weightOfTheCell = 0;
            rowNum = rowNumber;
            colNum = colNumber;

            bool isTopLeftCorner = (!rowNumber && !colNumber);
            bool isBottomRightCorner =  (rowNumber == tableRowCount-1 && colNumber == tableColCount-1);
            bool isTopRightCorner = (!rowNumber && colNumber == tableColCount-1);
            bool isBottomLeftCorner = (rowNumber == tableRowCount-1 && !colNumber);
            bool isCornerCell =  isTopLeftCorner || isTopRightCorner || isBottomLeftCorner || isBottomRightCorner;
            bool isEdgeCell = !isCornerCell && !(rowNumber && colNumber) ||  rowNumber == tableRowCount-1 || colNumber == tableColCount-1;

            typeOfCell = isCornerCell ? cornerCell : isEdgeCell ? edgeCell : innerCell;

        }
        
        pair<int,int> getIdOfCell() {
            return {rowNum , colNum};
        }

        int getTypeOfCell() {
            return typeOfCell;
        }

        int getWeightOfCell() {
            return weightOfTheCell;
        }

        void setPlayerIdOfTheCell(int playerId) {
            playerIdOfTheCell = playerId;
        }

        int getPlayerIdOfCell() {
            return playerIdOfTheCell;
        }

        void displayCell() {
            cout<<"["<<colorOfTheCell<<" "<<weightOfTheCell<<"] ";
        }

        bool canPlayTurn(int currPlayerId) {
            return (playerIdOfTheCell == defaultIdOfEmptyCell || playerIdOfTheCell == currPlayerId );   
        }

        void increaseWeight() {
            weightOfTheCell++;
        }

        void setColorOfTheCell(string color) {
            colorOfTheCell = color;
        }

        string getColorOfTheCell() {
            return colorOfTheCell; 
        }

        void setWeightOfTheCell(int weight) {
            weightOfTheCell = weight;
        }

};

class Board{

    private:    
        vector<vector<Cell*>> Grid;

    public :

        Board() {
            for(int i = 0 ; i < tableRowCount ; i++) {
                vector<Cell*> rowOfCells;
                for(int j = 0 ; j < tableColCount ; j++) {
                    Cell *cell = new Cell(i,j);
                    rowOfCells.push_back(cell);
                }
                Grid.push_back(rowOfCells);
            }
        }

    Cell* getCellFromBoard(int rowNum, int colNum) {
        return Grid[rowNum][colNum];
    } 
};


class Player{

    private:

        int playerId;
        int playerScore;
        string playerColor;

    public:

        Player(int Id,string color) {

            playerId = Id;
            playerColor = color;
            playerScore = 0;
        }

        int getPlayerId() {
            return playerId;
        }

        int getPlayerScore() {
            return playerScore;
        }

        string getPlayerColor() {
            return playerColor;
        }     
};

class ChainReactionGame {

    private:

        int winnerPlayerId;
        vector<Player*> arrayOfPlayers;
        Board* board;
        unordered_map<int, int> playerIdScoreMap;
    
    public:

        ChainReactionGame() {

            winnerPlayerId = -1;
            for(int i = 0 ; i < playerCount ; i++){
                Player *newPlayer = new Player(i, colorArray[i]);
                arrayOfPlayers.push_back(newPlayer);
                playerIdScoreMap[i] = 0; 
            }

            board = new Board();
        }

        vector<Player*> getPlayerArray() {
            return arrayOfPlayers;
        }

        int checkWin() {

            int countOfNonZeroScorePlayer = 0;
            for(auto eachPlayer : playerIdScoreMap){
                if(eachPlayer.second){
                    countOfNonZeroScorePlayer++;
                    winnerPlayerId = eachPlayer.first;
                    if(countOfNonZeroScorePlayer > 1){
                        winnerPlayerId = -1;
                        return false;
                    }   
                }
            }

            return true;
        }

        int displayScoreMap() {

            int countOfNonZeroScorePlayer = 0;
            for(auto eachPlayer : playerIdScoreMap){
                cout<<"playerId : "<<eachPlayer.first<<"\t : score "<<eachPlayer.second<<endl;
            }
            return 0;
        }

        bool burstBFS(Cell* selectedCell) {   
            
            int currCellPlayerId = selectedCell->getPlayerIdOfCell();
            queue<Cell*> queueOfCellToBurst;
            queueOfCellToBurst.push(selectedCell);

            while(!queueOfCellToBurst.empty()) {

                Cell *currCellToBurst = queueOfCellToBurst.front();
                queueOfCellToBurst.pop();

                if(currCellToBurst->getWeightOfCell() <= currCellToBurst->getTypeOfCell()) {
                    continue;
                }

                currCellToBurst->setPlayerIdOfTheCell(-1);
                currCellToBurst->setWeightOfTheCell(0);
                currCellToBurst->setColorOfTheCell("Black");

                vector<Cell*> arrayOfSplitToCell;
                pair<int,int> selectedCellId = currCellToBurst->getIdOfCell(); 
                int currRow = selectedCellId.first ,currCol = selectedCellId.second;

                if(currCellToBurst->getTypeOfCell() == cornerCell) {

                    bool isTopLeftCorner = (!currRow && !currCol);
                    bool isBottomRightCorner =  (currRow == tableRowCount-1 && currCol == tableColCount-1);
                    bool isTopRightCorner = (!currRow && currCol == tableColCount-1);
                    bool isBottomLeftCorner = (currRow == tableRowCount-1 && !currCol);

                    if(isTopLeftCorner) {
                        arrayOfSplitToCell.push_back(board->getCellFromBoard(currRow+1, currCol));
                        arrayOfSplitToCell.push_back(board->getCellFromBoard(currRow,currCol+1));
                    
                    } else if(isBottomRightCorner) {
                        arrayOfSplitToCell.push_back(board->getCellFromBoard(currRow-1,currCol));
                        arrayOfSplitToCell.push_back(board->getCellFromBoard(currRow,currCol-1));

                    } else if(isTopRightCorner) {
                        arrayOfSplitToCell.push_back(board->getCellFromBoard(currRow+1,currCol));
                        arrayOfSplitToCell.push_back(board->getCellFromBoard(currRow,currCol-1 ));

                    } else {
                        arrayOfSplitToCell.push_back(board->getCellFromBoard(currRow-1, currCol));
                        arrayOfSplitToCell.push_back(board->getCellFromBoard(currRow, currCol+1));
                    }
                } else if(currCellToBurst->getTypeOfCell() == edgeCell) {

                    bool isOnTopEdge = !currRow && currCol && currCol != tableColCount-1;
                    bool isOnRightEdge = (currCol == tableColCount-1  && currRow && currRow != tableRowCount-1);
                    bool isOnBottomEdge = (currRow == tableRowCount-1 && currCol && currCol != tableColCount-1);
                    bool isOnLeftEdge = (!currCol && currRow && currRow != tableRowCount-1);;

                    if(isOnTopEdge) {
                        arrayOfSplitToCell.push_back(board->getCellFromBoard(currRow+1,currCol));
                        arrayOfSplitToCell.push_back(board->getCellFromBoard(currRow,currCol+1));
                        arrayOfSplitToCell.push_back(board->getCellFromBoard(currRow,currCol-1));
                        
                    } else if(isOnRightEdge) {
                        arrayOfSplitToCell.push_back(board->getCellFromBoard(currRow-1,currCol));
                        arrayOfSplitToCell.push_back(board->getCellFromBoard(currRow+1,currCol));
                        arrayOfSplitToCell.push_back(board->getCellFromBoard(currRow,currCol-1));
                        
                    }
                    else if(isOnBottomEdge) {
                        arrayOfSplitToCell.push_back(board->getCellFromBoard(currRow-1, currCol));
                        arrayOfSplitToCell.push_back(board->getCellFromBoard(currRow, currCol+1));
                        arrayOfSplitToCell.push_back(board->getCellFromBoard(currRow, currCol-1));
                        
                    } else {
                        arrayOfSplitToCell.push_back(board->getCellFromBoard(currRow+1, currCol));
                        arrayOfSplitToCell.push_back(board->getCellFromBoard(currRow-1,currCol));
                        arrayOfSplitToCell.push_back(board->getCellFromBoard(currRow, currCol+1));
                        
                    }
                } else {
                    arrayOfSplitToCell.push_back(board->getCellFromBoard(currRow+1,currCol));
                    arrayOfSplitToCell.push_back(board->getCellFromBoard(currRow-1,currCol));
                    arrayOfSplitToCell.push_back(board->getCellFromBoard(currRow, currCol+1));
                    arrayOfSplitToCell.push_back(board->getCellFromBoard(currRow, currCol-1));

                }

                for(int i = 0 ; i < arrayOfSplitToCell.size() ; i++) {
                    
                    int otherCellPlayerId = arrayOfSplitToCell[i]->getPlayerIdOfCell();

                    if(otherCellPlayerId != currCellPlayerId) {
                        if(otherCellPlayerId!=-1) {
                            playerIdScoreMap[otherCellPlayerId]--;                            
                        }

                        arrayOfSplitToCell[i]->setPlayerIdOfTheCell(currCellPlayerId);
                        playerIdScoreMap[currCellPlayerId]++;
                        arrayOfSplitToCell[i]->setColorOfTheCell(colorArray[currCellPlayerId]);

                    }

                    if(arrayOfSplitToCell[i]->getWeightOfCell() +1 > arrayOfSplitToCell[i]->getTypeOfCell()) {
                        queueOfCellToBurst.push(arrayOfSplitToCell[i]);
                    }

                    arrayOfSplitToCell[i]->increaseWeight();
                    
                }

                if(checkWin()) {
                    return true;
                }
                playerIdScoreMap[currCellPlayerId]--;
            }

            return false;
        }

        void displayStateOfTheBoard() {

            for(int i = 0; i < tableRowCount; i++) {
                for(int j = 0; j < tableColCount; j++) {
                    board->getCellFromBoard(i,j)->displayCell();
                    cout<<" ";
                }
                cout<<endl;
            }
        }

        bool isMovePossibleInThisCell(int rowId , int colId,int playerId) {

            Cell* currCell = board->getCellFromBoard(rowId,colId);
            if(currCell->canPlayTurn(playerId)) {

                currCell->setPlayerIdOfTheCell(playerId);
                int weightOfTheCurrCell = currCell->getWeightOfCell();
                
                if(weightOfTheCurrCell == 0) {
                    playerIdScoreMap[playerId]++;
                    currCell->setColorOfTheCell(colorArray[playerId]);
                }
                if(currCell->getTypeOfCell() < currCell->getWeightOfCell()+1) {
                    currCell->setWeightOfTheCell(currCell->getWeightOfCell()+1);
                    burstBFS(currCell);
                } else {
                    currCell->increaseWeight();
                }                 
                return true;
            }
            return false;
        }
        

        int getWinnerId(){
            return winnerPlayerId;
        }
};


int main(){

    ChainReactionGame chainReactionGameObj;
    vector<Player*> arrayOfPlayers =  chainReactionGameObj.getPlayerArray();

    int winnerPlayerId = -1,inputRow, inputCol,countOfTurns = 0;
    bool isGameEnds = false;

    while(!isGameEnds) {
        int i = 0;

        while( i < arrayOfPlayers.size()) {
        
            cout<<"player "<<i<<" turn : enter the location \n";
            cin>>inputRow>>inputCol;
            if(inputRow <= 0 && inputRow >= tableRowCount-1 || inputCol <= 0 && inputCol >= tableColCount-1){
                cout<<"please enter a valid cell location \n";
                continue;
            }
        
            if(chainReactionGameObj.isMovePossibleInThisCell(inputRow,inputCol,arrayOfPlayers[i]->getPlayerId())) {
                 i++;
                 countOfTurns++;
                 
            } else {
                 cout<<"make move again please in different location\n";
            }

            cout<<"\n state of the board is \n"<<endl;
             
            chainReactionGameObj.displayStateOfTheBoard();
            chainReactionGameObj.displayScoreMap();
            cout<<endl;

            winnerPlayerId = chainReactionGameObj.getWinnerId();
            if(winnerPlayerId != -1 && countOfTurns > 2) {
                isGameEnds = true;
                break;
            }
        }
    }
    
    cout<<"Winner of the game is player with id = "<<winnerPlayerId<<endl;

    return 0;
}