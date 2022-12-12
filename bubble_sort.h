#pragma once

template<typename TYPE> class BXbubble_sort
{
public:
	BXbubble_sort(TYPE*group, int len) { this->group = group; this->len = len;  }
	TYPE* group;
	void bubble_sort(bool bAscending=true)
	{
		//冒泡排序
		for (int i = 0; i < len - 1; i++) {//遍历次数
			bool bContinue = false;

			for (int j = 0; j < len - i - 1; j++) {//两两交换
				if (bAscending) {
					if (group[j] >= group[j + 1]) {
						exchange(group[j], group[j + 1]);
						bContinue = true;
					}
				}
				else {
					if (group[j] <= group[j + 1]) {
						exchange(group[j], group[j + 1]);
						bContinue = true;
					}
				}
			}

			if (!bContinue) {
				break;
			}
		}
	}

private:
	void exchange(TYPE&a, TYPE&b)
	{
		TYPE temp;
		temp = a;
		a = b;
		b = temp;
	}
	int len;
};