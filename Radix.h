#pragma once

class BXDecimal_Radix
{
public:
	BXDecimal_Radix(int radix) { result = NULL; len = 0; this->radix = radix; }
	~BXDecimal_Radix() { if (result != NULL) { delete result; } }
	void Decimal_Radix(int decimal)
	{
		getlen(decimal);
		result = new int[len];
		for (int i = len - 1; decimal > 0; i--) {
			result[i] = decimal%radix;

			decimal = decimal / radix;
		}
	}
	char NumToUpChar(int num) {
		return char(char(num - 10) + 'A');
	}
	char NumToLowChar(int num) {
		return char(char(num - 10) + 'a');
	}
	int getlen() { return len; }

protected:
	int pow(int a, int x) {
		int temp = 1;
		for (int i = 0; i < x; i++) {
			temp = temp*a;
		}
		return temp;
	}
	void getlen(int decimal) {
		int temp = radix;
		for (int i = 1; true; i++) {
			if (temp > decimal) {
				this->len = i;
				break;
			}
			temp = temp*radix;
		}
	}

public:
	int* result;
private:
	int radix;
	int len;
};