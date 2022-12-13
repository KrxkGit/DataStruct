#pragma once
//pos must be transferred to array form,meaning that you should begin with 0

struct BXPoint
{
	int x;
	int y;
};

struct BXLine
{
	BXPoint beginpt;
	BXPoint endpt;
	double k;
	double b;
	bool bKExist;
};

template<typename T> class BXMatrix_mapping {
public:
	BXMatrix_mapping(int i, int j, T background) {
		result = new T*[i];
		for (int t = 0; t < i; t++) {
			result[t] = new T[j];
		}
		this->i = i - 1; //transfer to array form
		this->j = j - 1;
		setBackground(background);
	};
	BXMatrix_mapping(T**v) {
		result = v;
	}
	~BXMatrix_mapping() {
		for (int t = 0; t < i; t++) {
			delete[]result[t];
		}
		delete[]result;
	};
	T** result;
	void DrawLine(BXPoint& beginpt, BXPoint& endpt, T content) {
		generateLine(beginpt, endpt);
		int startX = min(beginpt.x, endpt.x);
		int endX = max(beginpt.x, endpt.x);
		int startY = min(beginpt.y, endpt.y);
		int endY = max(beginpt.y, endpt.y);
		int tempY = 0;
		if (!m_line.bKExist) {
			for (tempY = startY; tempY <= endY; tempY++) {
				if (InRange(startX, tempY)) {
					result[startX][tempY] = content;
				}
			}
		}
		else {
			for (int t = startX; t <= endX; t++) {
				tempY = int(m_line.k*t + m_line.b);
				if (InRange(t, tempY)) {
					result[t][tempY] = content;
				}
			}
		}
	}
	void fillInside(BXPoint& beginpt, BXPoint& endpt, T boundary, T content) { //the first position mustn't be boundary;beginpt/endpt must be the up/down point
		int startX = min(beginpt.x, endpt.x);
		int endX = max(beginpt.x, endpt.x);
		int startY = min(beginpt.y, endpt.y);
		int tempY = 0;
		for (int i = startX; i <= endX; i++) {
			for (tempY = startY; result[i][tempY] != boundary && InRange(i, tempY); tempY++) {//down
				result[i][tempY] = content;
			}
			for (tempY = startY; result[i][tempY] != boundary && InRange(i, tempY); tempY--) {//up
				result[i][tempY] = content;
			}
		}
	}
	void setTail(T sign, T tail, bool bFindLast = true, bool bReplacesign = false) {
		for (int t = 0; t <= j; t++) {
			int r = 0;
			if (bFindLast) {
				for (r = j; r >= 0 && result[t][r] != sign; r--) {
					;//void
				}
			}
			else {
				for (r = 0; r <= j && result[t][r] != sign; r++) {
					;//void
				}
			}
			if (!bReplacesign) {
				r += 1;
			}
			for (int z = r; z <= j; z++) {
				result[t][z] = tail;
			}
		}
	}
	void setBackground(T background) {
		for (int t1 = 0; t1 <= i; t1++) {
			for (int t2 = 0; t2 <= j; t2++) {
				result[t1][t2] = background;
			}
		}
	}
	int getRows() { return i; }//begin with 0
	int getCols() { return j; }
protected:
	int min(int a, int b) { return (a <= b) ? a : b; }
	int max(int a, int b) { return (a >= b) ? a : b; }
	bool InRange(int x, int y) {
		if (0 <= x && x <= i && 0 <= y &&y <= j) {
			return true;
		}
		return false;
	}
	void generateLine(BXPoint& beginpt, BXPoint& endpt) {
		m_line.beginpt = beginpt;
		m_line.endpt = endpt;

		if (beginpt.x == endpt.x && beginpt.y != endpt.y) {
			m_line.bKExist = false;
		}
		else {
			m_line.bKExist = true;
			m_line.k = double(endpt.y - beginpt.y) / double(endpt.x - beginpt.x);
			m_line.b = double(endpt.y - double(m_line.k*endpt.x));
		}
	};
private:
	//Matrix
	int i;//begin with 0
	int j;
	//LINE
	BXLine m_line;
};