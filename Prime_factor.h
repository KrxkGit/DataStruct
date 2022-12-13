#pragma once

class Prime_factor
{
public:
	Prime_factor(int x)
	{
		count = 0;
		tempcount = 0;
		m_result = NULL;
		Caculate(x);
		Save(x);
	}
	~Prime_factor() { if (m_result != NULL) delete m_result; }
	int* getResult() { return m_result; }
	int getCount() { return count; }
protected:
	void Caculate(int x) {
		for (int i = 2; i < x; i++) {
			if ((x%i) == 0) {
				if (m_result != NULL) {
					m_result[tempcount] = i;
					tempcount++;
				}
				else {
					count++;
				}

				x /= i;
				Caculate(x);
				return;
			}
		}
		if (m_result != NULL) {
			m_result[tempcount] = x;
		}
		else {
			count++;
		}
	}
	void Save(int x) {
		m_result = new int[count];
		Caculate(x);
	}
private:
	int count;
	int tempcount;
	int* m_result;
};