#pragma once

//Tip: 对于构造类型需重载 < 运算符
template<typename TYPE> class KrxkSort
{
public:
	KrxkSort(TYPE*group, int len) { this->group = group; this->len = len; }
	TYPE* group;
	void bubble_sort(bool bAscending = true) {
		//冒泡排序
		for (int i = 0; i < len - 1; i++) {
			bool bContinue = false;

			for (int j = len - 1; j >i; j--) {
				if (bAscending) {
					if (group[j] < group[j - 1]) {
						swap(group[j], group[j - 1]);
						bContinue = true;
					}
				}
				else {
					if (group[j - 1] < group[j]) {
						swap(group[j], group[j - 1]);
						bContinue = true;
					}
				}
			}
			if (!bContinue) {
				break;
			}
		}
	}
	void insert_sort(bool bAscending = true) {
		for (int i = 1; i < len; i++) {
			for (int j = i; j>0; j--) {
				if (bAscending) {
					if (group[j] < group[j - 1]) {
						swap(group[j], group[j - 1]);
						continue;
					}
				}
				else {
					if (group[j - 1] < group[j]) {
						swap(group[j], group[j - 1]);
						continue;
					}
				}

				break;//无交换则退出循环
			}
		}
	}
	void select_sort(bool bAscending = true) {
		for (int i = 0; i < len - 1; i++) {
			int record_index = i;
			for (int j = len - 1; j>i; j--) {
				if (bAscending) {
					if (group[j] < group[record_index]) {
						record_index = j;
					}
				}
				else {
					if (group[record_index] < group[j]) {
						record_index = j;
					}
				}
			}
			swap(group[i], group[record_index]);
		}
	}
	void quick_sort(bool bAscending = true) {
		qsortHelp(0, len - 1, bAscending);
	}
protected: //quick_sort helper functions.
	void qsortHelp(int i, int j, bool bAscending) {
		if (j <= i) {
			return;
		}
		int pivotindex = findpivot(i, j);
		swap(group[j], group[pivotindex]);
		int k = partition(i - 1, j, group[j], bAscending);
		swap(group[k], group[j]);
		qsortHelp(i, k - 1, bAscending);
		qsortHelp(k + 1, j, bAscending);
	}
	inline int findpivot(int i, int j) {
		return (i + j) / 2;
	}
	int partition(int l, int r, TYPE& pivot, bool bAscending) {
		do {
			if (bAscending) {
				while (group[++l] < pivot) {
					;
				}
				while ((l < r) && (pivot < group[--r]))  {
					;
				}
			}
			else {
				while (pivot < group[++l]) {
					;
				}
				while ((l < r) && (group[--r] < pivot))  {
					;
				}
			}
			swap(group[l], group[r]);
		} while (l < r);
		return l;
	}
private:
	void swap(TYPE&a, TYPE&b)
	{
		TYPE temp;
		temp = a;
		a = b;
		b = temp;
	}
	int len;
};