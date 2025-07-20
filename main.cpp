#include <bits/stdc++.h>
using namespace std;

class Game
{
private:
	vector<pair<int, int>> areas = {
		{10, 17}, 
		{10, 16}, 
		{9, 17}, 
		{10, 15}, 
		{9, 16}, 
		{10, 14}, 
		{8, 17}, 
		{9, 15}, 
		{10, 13}, 
		{8, 16}, 
		{9, 14}, 
		{8, 15}, {10, 12}, 
		{7, 17}, 
		{9, 13}, 
		{7, 16}, {8, 14}, 
		{10, 11}, 
		{9, 12}, 
		{7, 15}, 
		{8, 13}, 
		{6, 17}, 
		{10, 10}, 
		{9, 11}, 
		{7, 14}, 
		{6, 16}, {8, 12}, 
		{7, 13}, 
		{6, 15}, {9, 10}, {10, 9}, 
		{8, 11}, 
		{5, 17}, 
		{6, 14}, {7, 12}, 
		{9, 9}, 
		{5, 16}, {8, 10}, {10, 8}, 
		{6, 13}, 
		{7, 11}, 
		{5, 15}, 
		{6, 12}, {8, 9}, {9, 8}, 
		{5, 14}, {7, 10}, {10, 7}, 
		{4, 17}, 
		{6, 11}, 
		{5, 13}, 
		{4, 16}, {8, 8}, 
		{7, 9}, {9, 7}, 
		{4, 15}, {5, 12}, {6, 10}, {10, 6}, 
		{4, 14}, {7, 8}, {8, 7}, 
		{5, 11}, 
		{6, 9}, {9, 6}, 
		{4, 13}, 
		{3, 17}, 
		{5, 10}, {10, 5}, 
		{7, 7}, 
		{3, 16}, {4, 12}, {6, 8}, {8, 6}, 
		{3, 15}, {5, 9}, {9, 5}, 
		{4, 11}, 
		{3, 14}, {6, 7}, {7, 6}, 
		{4, 10}, {5, 8}, {8, 5}, {10, 4}, 
		{3, 13}, 
		{3, 12}, {4, 9}, {6, 6}, {9, 4}, 
		{5, 7}, {7, 5}, 
		{2, 17}, 
		{3, 11}, 
		{2, 16}, {4, 8}, {8, 4}, 
		{2, 15}, {3, 10}, {5, 6}, {6, 5}, {10, 3}, 
		{2, 14}, {4, 7}, {7, 4}, 
		{3, 9}, {9, 3}, 
		{2, 13}, 
		{5, 5}, 
		{2, 12}, {3, 8}, {4, 6}, {6, 4}, {8, 3}, 
		{2, 11}, 
		{3, 7}, {7, 3}, 
		{2, 10}, {4, 5}, {5, 4}, {10, 2}, 
		{2, 9}, {3, 6}, {6, 3}, {9, 2}, 
		{1, 17}, 
		{1, 16}, {2, 8}, {4, 4}, {8, 2}, 
		{1, 15}, {3, 5}, {5, 3}, 
		{1, 14}, {2, 7}, {7, 2}, 
		{1, 13}, 
		{1, 12}, {2, 6}, {3, 4}, {4, 3}, {6, 2}, 
		{1, 11}, 
		{1, 10}, {2, 5}, {5, 2}, {10, 1}, 
		{1, 9}, {3, 3}, {9, 1}, 
		{1, 8}, {2, 4}, {4, 2}, {8, 1}, 
		{1, 7}, {7, 1}, 
		{1, 6}, {2, 3}, {3, 2}, {6, 1}, 
		{1, 5}, {5, 1}, 
		{1, 4}, {2, 2}, {4, 1}, 
		{1, 3}, {3, 1}, 
		{1, 2}, {2, 1}
	};
	vector<vector<int>> board;
	vector<vector<int>> score;
	vector<vector<int>> tmp_board;
	vector<vector<int>> tmp_score;
	vector<vector<int>> tmp_enemy_board;
	vector<vector<int>> tmp_enemy_score;
	bool first;
	bool passed;

	int myScore = 0;
	int enemyScore = 0;

	int myTime;
	int oppTime;

    bool isValid(int r1, int c1, int r2, int c2)
    {
        int sums = 0;
        bool r1fit = false, c1fit = false, r2fit = false, c2fit = false;

        for (int r = r1; r <= r2; r++)
            for (int c = c1; c <= c2; c++)
                if (board[r][c] != 0)
                {
                    sums += board[r][c];
                    if (r == r1)
                        r1fit = true;
                    if (r == r2)
                        r2fit = true;
                    if (c == c1)
                        c1fit = true;
                    if (c == c2)
                        c2fit = true;
                }
        return (sums == 10) && r1fit && r2fit && c1fit && c2fit;
    }

	int getScore(int r1, int c1, int r2, int c2, int myScore) {
        int sums = 0;

        for (int r = r1; r <= r2; r++)
            for (int c = c1; c <= c2; c++)
                if (score[r][c] != myScore)
				sums++;
        return sums;
	}

	void scan_area(pair<int, int> &area, vector<vector<int>> &targetAreas) {
		for (int row = 0; row + (area.first - 1) < 10; row++) {
			for (int col = 0; col + (area.second - 1) < 17; col++) {
				if (isValid(row, col, row + area.first - 1, col + area.second - 1)) {
					targetAreas.push_back({row, col, row + area.first - 1, col + area.second - 1});
				}
			}
		}
	}

	// 두 사각형이 겹치는지 확인하는 함수
	bool doRectanglesOverlap(int myR1, int myC1, int myR2, int myC2, int r1, int c1, int r2, int c2) {
		// X축(열)에서 겹치는지 확인
		bool overlapX = (myC1 <= c2) && (myC2 >= c1);
		// Y축(행)에서 겹치는지 확인
		bool overlapY = (myR1 <= r2) && (myR2 >= r1);
		
		// 두 축 모두에서 겹쳐야 실제로 겹치는 것
		return overlapX && overlapY;
	}

	bool isNextNextEnemyMoveStrong(int myR1, int myC1, int myR2, int myC2) {
		vector<int> targetArea;
		vector<vector<int>> targetAreas;
		int threeStepMyScore = 0;

		for (int row = myR1; row <= myR2; row++) {
			for (int col = myC1; col <= myC2; col++) {
				if (score[row][col] == 1) {
					threeStepMyScore++;
				}
			}
		}
		for (pair<int, int> &area: this->areas) {
			scan_area(area, targetAreas);
		}
		
		vector<int> selectedIdxs;
		vector<vector<int>> savedTwoStepBoard(10, vector<int>(17, 0));
		vector<vector<int>> savedTwoStepScore(10, vector<int>(17, 0));
		int savedTwoStepMyScore = 0, savedTwoStepEnemyScore = 0;

		// cout << '\t' << '\t' << '\t' << '\t' << "=== 내 수를 역역카운터 치는 수 ==="<< '\n';
		// cout << '\t' << '\t' << '\t' << '\t' << "내가 먹은 점수: " << threeStepMyScore << '\n';
		for (size_t idx = 0; idx < targetAreas.size(); idx++) {
			int r1, c1, r2, c2;
			r1 = targetAreas[idx][0];
			c1 = targetAreas[idx][1];
			r2 = targetAreas[idx][2];
			c2 = targetAreas[idx][3];
			if (doRectanglesOverlap(myR1, myC1, myR2, myC2, r1, c1, r2, c2)) {
				int threeStepEnemyScore = 0;
				int threeStepMinusMyScore = 0;
				for (int row = r1; row <= r2; row++) {
					for (int col = c1; col <= c2; col++) {
						if (score[row][col] == 0) {
							threeStepEnemyScore++;
						} else if (score[row][col] == 1) {
							threeStepEnemyScore++;
							threeStepMinusMyScore++;
						}
					}
				}
				if (threeStepEnemyScore >= threeStepMyScore - threeStepMinusMyScore) {
					// cout << '\t' << '\t' << '\t' << '\t' << "상대가 먹은 점수: " << threeStepEnemyScore << '\n';
					// cout << '\t' << '\t' << '\t' << '\t' << "상대가 역으로 먹은 내 점수: " << threeStepMinusMyScore << '\n';
					// cout << '\t' << '\t' << '\t' << '\t' << r1 << ' ' << c1 << ' ' << r2 << ' ' << c2 << '\n';
					selectedIdxs.push_back(idx);
				}
			}
		}
		if (selectedIdxs.empty()) {
			return false;
		}
		return true;
	}

	bool isNextMyMoveStrong(int enemyR1, int enemyC1, int enemyR2, int enemyC2) {
		vector<int> targetArea;
		vector<vector<int>> targetAreas;
		int twoStepEnemyScore = 0;

		for (int row = enemyR1; row <= enemyR2; row++) {
			for (int col = enemyC1; col <= enemyC2; col++) {
				if (score[row][col] == 2) {
					twoStepEnemyScore++;
				}
			}
		}
		for (pair<int, int> &area: this->areas) {
			scan_area(area, targetAreas);
		}
		
		vector<int> selectedIdxs;
		vector<vector<int>> savedThreeStepBoard(10, vector<int>(17, 0));
		vector<vector<int>> savedThreeStepScore(10, vector<int>(17, 0));
		int savedThreeStepMyScore = 0, savedThreeStepEnemyScore = 0;
		// cout << '\t' << '\t' << '\t' << "=== 해당 수를 역카운터 치는 수 ==="<< '\n';
		// print_board();
		// cout << '\t' << '\t' << '\t' << "상대방이 먹은 점수: " << twoStepEnemyScore << '\n';
		
		for (size_t idx = 0; idx < targetAreas.size(); idx++) {
			int r1, c1, r2, c2;
			r1 = targetAreas[idx][0];
			c1 = targetAreas[idx][1];
			r2 = targetAreas[idx][2];
			c2 = targetAreas[idx][3];
			if (doRectanglesOverlap(enemyR1, enemyC1, enemyR2, enemyC2, r1, c1, r2, c2)) {
				int twoStepMyScore = 0;
				int twoStepMinusEnemyScore = 0;
				for (int row = r1; row <= r2; row++) {
					for (int col = c1; col <= c2; col++) {
						if (score[row][col] == 0) {
							twoStepMyScore++;
						} else if (score[row][col] == 2) {
							twoStepMyScore++;
							twoStepMinusEnemyScore++;
						}
					}
				}
				// cout << '\t' << '\t' << '\t' << "내가 먹은 점수: " << twoStepMyScore << '\n';
				// cout << '\t' << '\t' << '\t' << "내가 역으로 먹은 상대 점수: " << twoStepMinusEnemyScore << '\n';
				// cout << '\t' << '\t' << '\t' << r1 << ' ' << c1 << ' ' << r2 << ' ' << c2 << '\n';
				if (twoStepMyScore >= twoStepEnemyScore - twoStepMinusEnemyScore) {
					copyState(r1, c1, r2, c2, savedThreeStepBoard, savedThreeStepScore, savedThreeStepMyScore, savedThreeStepEnemyScore);
					updateMoveNonePrint(r1, c1, r2, c2, true);
					if (!isNextNextEnemyMoveStrong(r1, c1, r2, c2)) { 
						selectedIdxs.push_back(idx);
					}
					rewindState(r1, c1, r2, c2, savedThreeStepBoard, savedThreeStepScore, savedThreeStepMyScore, savedThreeStepEnemyScore);
				}
			}
		}
		if (selectedIdxs.empty()) {
			return false;
		}
		return true;
	}

	bool isNextEnemyMoveStrong(int myR1, int myC1, int myR2, int myC2, bool checkNextStep) {
		vector<int> targetArea;
		vector<vector<int>> targetAreas;
		int oneStepMyScore = 0;

		for (int row = myR1; row <= myR2; row++) {
			for (int col = myC1; col <= myC2; col++) {
				if (score[row][col] == 1) {
					oneStepMyScore++;
				}
			}
		}
		for (pair<int, int> &area: this->areas) {
			scan_area(area, targetAreas);
		}
		
		vector<int> selectedIdxs;
		vector<vector<int>> savedTwoStepBoard(10, vector<int>(17, 0));
		vector<vector<int>> savedTwoStepScore(10, vector<int>(17, 0));
		int savedTwoStepMyScore = 0, savedTwoStepEnemyScore = 0;

		for (size_t idx = 0; idx < targetAreas.size(); idx++) {
			int r1, c1, r2, c2;
			r1 = targetAreas[idx][0];
			c1 = targetAreas[idx][1];
			r2 = targetAreas[idx][2];
			c2 = targetAreas[idx][3];
			if (doRectanglesOverlap(myR1, myC1, myR2, myC2, r1, c1, r2, c2)) {
				int oneStepEnemyScore = 0;
				int oneStepMinusMyScore = 0;
				for (int row = r1; row <= r2; row++) {
					for (int col = c1; col <= c2; col++) {
						if (score[row][col] == 0) {
							oneStepEnemyScore++;
						} else if (score[row][col] == 1) {
							oneStepEnemyScore++;
							oneStepMinusMyScore++;
						}
					}
				}
				if (oneStepEnemyScore >= oneStepMyScore - oneStepMinusMyScore) {
					selectedIdxs.push_back(idx);
				}
			}
		}
		if (checkNextStep) {
			if (selectedIdxs.empty()) {
				return false;
			}
			// vector<int> bestSelectedIdxs = findBigestIdx(selectedIdxs, targetAreas, false);
			vector<int> bestSelectedIdxs = selectedIdxs;
			bool isCounter = false;
			for (size_t idx = 0; idx < bestSelectedIdxs.size(); idx++) {
				int r1, c1, r2, c2;
				r1 = targetAreas[bestSelectedIdxs[idx]][0];
				c1 = targetAreas[bestSelectedIdxs[idx]][1];
				r2 = targetAreas[bestSelectedIdxs[idx]][2];
				c2 = targetAreas[bestSelectedIdxs[idx]][3];
				// cout << '\t' << '\t' << "=== 상대가 할 수 있는 최선의 수 중 " << idx << "번쨰 ==="<< '\n';
				// cout << '\t' << '\t' << r1 << ' ' << c1 << ' ' << r2 << ' ' << c2 << '\n';
				copyState(r1, c1, r2, c2, savedTwoStepBoard, savedTwoStepScore, savedTwoStepMyScore, savedTwoStepEnemyScore);
				updateMoveNonePrint(r1, c1, r2, c2, false);
				isCounter |= !isNextMyMoveStrong(r1, c1, r2, c2);
				rewindState(r1, c1, r2, c2, savedTwoStepBoard, savedTwoStepScore, savedTwoStepMyScore, savedTwoStepEnemyScore);
			}
			return isCounter;
		}
		if (selectedIdxs.empty()) {
			return false;
		}
		return true;
	}

	vector<int> findBigestIdx(vector<int> &idxs, vector<vector<int>> &targetAreas, bool isMyTurn) {
		int max_score = 0;
		vector<int> maxIdxs;
		for (size_t idx = 0; idx < idxs.size(); idx++) {
			int r1, c1, r2, c2, cur_score = 0;
			r1 = targetAreas[idxs[idx]][0];
			c1 = targetAreas[idxs[idx]][1];
			r2 = targetAreas[idxs[idx]][2];
			c2 = targetAreas[idxs[idx]][3];
			for (int row = r1; row <= r2; row++) {
				for (int col = c1; col <= c2; col++) {
					if (isMyTurn) {
						if (score[row][col] != 1) {
							cur_score++;
						}
					} else {
						if (score[row][col] != 2) {
							cur_score++;
						}
					}
				}
			}
			if (cur_score > max_score) {
				max_score = cur_score;
			}
		}
		for (size_t idx = 0; idx < idxs.size(); idx++) {
			int r1, c1, r2, c2, cur_score = 0;
			r1 = targetAreas[idxs[idx]][0];
			c1 = targetAreas[idxs[idx]][1];
			r2 = targetAreas[idxs[idx]][2];
			c2 = targetAreas[idxs[idx]][3];
			for (int row = r1; row <= r2; row++) {
				for (int col = c1; col <= c2; col++) {
					if (isMyTurn) {
						if (score[row][col] != 1) {
							cur_score++;
						}
					} else {
						if (score[row][col] != 2) {
							cur_score++;
						}
					}
				}
			}
			if (cur_score == max_score) {
				maxIdxs.push_back(idxs[idx]);
			}
		}

		return maxIdxs;
	}

	void copyState(int r1, int c1, int r2, int c2, vector<vector<int>> &destBoard, vector<vector<int>> &destScore, int &destMyScore, int &destEnemyScore) {
		destMyScore = this->myScore;
		destEnemyScore = this->enemyScore;
		for (int row = r1; row <= r2; row++) {
			for (int col = c1; col <= c2; col++) {
				destBoard[row][col] = board[row][col];
				destScore[row][col] = score[row][col];
			}
		}
	}
	
	void rewindState(int r1, int c1, int r2, int c2, vector<vector<int>> &destBoard, vector<vector<int>> &destScore, int &destMyScore, int &destEnemyScore) {
		this->myScore = destMyScore;
		this->enemyScore = destEnemyScore;
		for (int row = r1; row <= r2; row++) {
			for (int col = c1; col <= c2; col++) {
				board[row][col] = destBoard[row][col];
				score[row][col] = destScore[row][col];
			}
		}
	}

public:
	Game() {}
	Game(const vector<vector<int>> &board, bool first)
		: board(board), first(first), passed(false) {
			tmp_board = vector<vector<int>>(10, vector<int>(17, 0));
			tmp_score = vector<vector<int>>(10, vector<int>(17, 0));
			tmp_enemy_board = vector<vector<int>>(10, vector<int>(17, 0));
			tmp_enemy_score = vector<vector<int>>(10, vector<int>(17, 0));
			score = vector<vector<int>>(10, vector<int>(17, 0));
			myTime = 10000;
			oppTime = 10000;
		}

	vector<int> getNextMove() {
		// 모든 경우의수를 탐색
		// 가능한 경우의 수를 targetAreas에 추가.
		vector<int> targetArea;
		vector<vector<int>> targetAreas;

		for (pair<int, int> &area: this->areas) {
			scan_area(area, targetAreas);
		}

		if (targetAreas.empty()) {
			return {-1, -1, -1, -1};
		}
		vector<int> noneCounterIdxs, counterIdxs;
		vector<vector<int>> savedOneStepBoard(10, vector<int>(17, 0));
		vector<vector<int>> savedOneStepScore(10, vector<int>(17, 0));
		int savedOneStepMyScore = 0, savedOneStepEnemyScore = 0;

		for (size_t idx = 0; idx < targetAreas.size(); idx++) {
			int r1, c1, r2, c2;
			r1 = targetAreas[idx][0];
			c1 = targetAreas[idx][1];
			r2 = targetAreas[idx][2];
			c2 = targetAreas[idx][3];

			copyState(r1, c1, r2, c2, savedOneStepBoard, savedOneStepScore, savedOneStepMyScore, savedOneStepEnemyScore);
			updateMoveNonePrint(r1, c1, r2, c2, true);
			if (!isNextEnemyMoveStrong(r1, c1, r2, c2, false)) { 
				noneCounterIdxs.push_back(idx);
			} else {
				// 상대방의 카운터 수를 적용하고 다음 내 수를 보는 코드
				counterIdxs.push_back(idx);
			}
			rewindState(r1, c1, r2, c2, savedOneStepBoard, savedOneStepScore, savedOneStepMyScore, savedOneStepEnemyScore);
		}
		if (noneCounterIdxs.empty()) {
			if (counterIdxs.empty()) {
				return {-1, -1, -1, -1};
			}
			vector<int> counterRevserseCounterIdxs;
			vector<vector<int>> savedOneStepBoard(10, vector<int>(17, 0));
			vector<vector<int>> savedOneStepScore(10, vector<int>(17, 0));
			int savedOneStepMyScore = 0, savedOneStepEnemyScore = 0;
			for (size_t idx = 0; idx < counterIdxs.size(); idx++) {
				int r1, c1, r2, c2;
				r1 = targetAreas[counterIdxs[idx]][0];
				c1 = targetAreas[counterIdxs[idx]][1];
				r2 = targetAreas[counterIdxs[idx]][2];
				c2 = targetAreas[counterIdxs[idx]][3];
				// cout << '\t' << "=== 두턴 뒤를 볼 때 내 행동 ===" << '\n';
				// cout << '\t' << r1 << ' ' << c1 << ' ' << r2 << ' ' << c2 << '\n';
				copyState(r1, c1, r2, c2, savedOneStepBoard, savedOneStepScore, savedOneStepMyScore, savedOneStepEnemyScore);
				updateMoveNonePrint(r1, c1, r2, c2, true);
				if (!isNextEnemyMoveStrong(r1, c1, r2, c2, true)) { 
					counterRevserseCounterIdxs.push_back(idx);
				}
				rewindState(r1, c1, r2, c2, savedOneStepBoard, savedOneStepScore, savedOneStepMyScore, savedOneStepEnemyScore);
			}
			if (counterRevserseCounterIdxs.empty()) {
				return {-1, -1, -1, -1};
			}
			
			vector<int> selectedIdxs = findBigestIdx(counterRevserseCounterIdxs, targetAreas, true);
			return targetAreas[selectedIdxs[0]];
		} else {
			vector<int> selectedIdxs = findBigestIdx(noneCounterIdxs, targetAreas, true);
			return targetAreas[selectedIdxs[0]];
		}
		return {-1, -1, -1, -1};
	}
	    // 상대방의 수를 받아 보드에 반영
    void updateOpponentAction(const vector<int> &action, int time)
    {
        updateMove(action[0], action[1], action[2], action[3], false);
    }

    // 주어진 수를 보드에 반영 (칸을 0으로 지움)
    void updateMoveNonePrint(int r1, int c1, int r2, int c2, bool isMyMove)
    {
        if (r1 == -1 && c1 == -1 && r2 == -1 && c2 == -1)
        {
            passed = true;
            return;
        }
        for (int r = r1; r <= r2; r++)
            for (int c = c1; c <= c2; c++) {
                board[r][c] = 0;
				if (isMyMove) {
					if (score[r][c] == 0) {
						myScore++;
					} else if (score[r][c] == 2) {
						myScore++;
						enemyScore--;
					}
					score[r][c] = 1;
				}
				else {
					if (score[r][c] == 0) {
						enemyScore++;
					} else if (score[r][c] == 1) {
						enemyScore++;
						myScore--;
					}
					score[r][c] = 2;
				}
			}
		if (myScore < 0) {
			cout << "!!! myScore 가 음수가 되는 이상한 경우 !!!" << '\n';
			print_board();
			exit(1);
		}
		if (enemyScore < 0) {
			cout << "!!! myScore 가 음수가 되는 이상한 경우 !!!" << '\n';
			print_board();
			exit(1);
		}
        passed = false;
    }

    // 주어진 수를 보드에 반영 (칸을 0으로 지움)
    void updateMove(int r1, int c1, int r2, int c2, bool isMyMove)
    {
        if (r1 == -1 && c1 == -1 && r2 == -1 && c2 == -1)
        {
            passed = true;
            return;
        }
        for (int r = r1; r <= r2; r++)
            for (int c = c1; c <= c2; c++) {
                board[r][c] = 0;
				if (isMyMove) {
					if (score[r][c] == 0) {
						myScore++;
					} else if (score[r][c] == 2) {
						myScore++;
						enemyScore--;
					}
					score[r][c] = 1;
				}
				else {
					if (score[r][c] == 0) {
						enemyScore++;
					} else if (score[r][c] == 1) {
						enemyScore++;
						myScore--;
					}
					score[r][c] = 2;
				}
			}
		// cout << "=== 해당 수를 진행 한 후 결과 ===" << '\n';
		// cout << r1 << ' ' << c1 << ' ' << r2 << ' ' << c2 << '\n';
		// print_board();
		if (myScore < 0) {
			cout << "!!! myScore 가 음수가 되는 이상한 경우 !!!" << '\n';
			exit(1);
		}
		if (enemyScore < 0) {
			cout << "!!! myScore 가 음수가 되는 이상한 경우 !!!" << '\n';
			exit(1);
		}
        passed = false;
    }

	void print_board() {
		cout << "   " << ' ';
		for (int i = 0; i < 17; i++) {
			cout << ' ' << i % 10 << ' ' << ' ';
		}
		cout << '\n';
		for (int i = 0; i < 10; i++) {
			cout << ' ' << i << ' ' << ' ';
			for (int j = 0; j < 17; j++) {
				cout << "[" << board[i][j] << "] ";
			}
			cout << '\n';
		}
		cout << "\n";
		
		cout << "   " << ' ';
		for (int i = 0; i < 17; i++) {
			cout << ' ' << i % 10 << ' ' << ' ';
		}
		cout << '\n';
		for (int i = 0; i < 10; i++) {
			cout << ' ' << i << ' ' << ' ';
			for (int j = 0; j < 17; j++) {
				cout << "[" << score[i][j] << "] ";
			}
			cout << '\n';
		}
		cout << myScore << ' ' << enemyScore << '\n';
		cout << endl;
	}
};

int main(int argc, char *argv[]) {
    Game game;
    bool first = false;

    while (true)
    {
        string line;
        getline(cin, line);

        istringstream iss(line);
        string command;
        if (!(iss >> command))
            continue;

        if (command == "READY")
        {
            // 선공 여부 확인
            string turn;
            iss >> turn;
            first = (turn == "FIRST");
            cout << "OK" << endl;
            continue;
        }

        if (command == "INIT")
        {
            // 보드 초기화
            vector<vector<int>> board;
            string row;
            while (iss >> row)
            {
                vector<int> boardRow;
                for (char c : row)
                {
                    boardRow.push_back(c - '0'); // 문자 → 숫자 변환
                }
                board.push_back(boardRow);
            }
            game = Game(board, first);
            continue;
        }
		
        if (command == "TIME")
        {
			// 내 차례: 수 계산 및 출력
            int myTime, oppTime;
            iss >> myTime >> oppTime;
			
            vector<int> ret = game.getNextMove();
            game.updateMove(ret[0], ret[1], ret[2], ret[3], true);
			// if (first)
			// 	cout << "FIRST " << ret[0] << " " << ret[1] << " " << ret[2] << " " << ret[3] << " " << 0 << endl; // 내 행동 출력
			// else 
			// 	cout << "SECOND " << ret[0] << " " << ret[1] << " " << ret[2] << " " << ret[3] << " " << 0 << endl; // 내 행동 출력
			
			cout << ret[0] << " " << ret[1] << " " << ret[2] << " " << ret[3] << endl; // 내 행동 출력
			continue;
		}
		
		if (command == "OPP")
		{
			// 상대 행동 반영
			int r1, c1, r2, c2, time;
			iss >> r1 >> c1 >> r2 >> c2 >> time;
			// if (first)
			// 	cout << "SECOND " << r1 << " " << c1 << " " << r2 << " " << c2 << " " << 0 << endl; // 내 행동 출력
			// else 
			// 	cout << "FIRST " << r1 << " " << c1 << " " << r2 << " " << c2 << " " << 0 << endl; // 내 행동 출력
			game.updateOpponentAction({r1, c1, r2, c2}, time);
			continue;
		}
		if (command == "PRINT") {
			game.print_board();
			continue;
		}
		
		if (command == "FINISH")
		{
			// 게임 종료
			break;
		}
		
		// 알 수 없는 명령 처리
		cerr << "Invalid command: " << command << endl;
		return 1;
	}
	
	return 0;
}