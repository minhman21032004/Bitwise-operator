#include<iostream>
#include<string>
#include<math.h>
#define BIN_SIZE 8

//Binary size default is 8, therefore can be adjust to 4,16,32,64,...

using namespace std;

class Binary
{
private:
	string bin;	//string to store the bits, char '0' and '1'
	
	Binary binary_sum(Binary B, char& temp);	//variable temp help determine if a bit is overflow after sum operation
public:
	Binary();	//constructor

	Binary(int);	//Destructor

	void output();	//output binary

	int b10_value();	//get base 10 value

	char getLSB();	//get Least significant bit

	Binary _self();	//Get copy of self object

	Binary _abs();	//Get absoulute value

	//All operation is based on the string bin

	Binary operator~();	//operator NOT

	Binary operator&(Binary);	//operator AND

	Binary operator|(Binary);	//operator OR

	Binary operator^(Binary);	//operator XOR

	void operator=(Binary);	//operator =, A = B mean a gain value of B

	Binary operator<<(int);	//Shift left n bits

	Binary operator>>(int);	//Shift right n bits

	bool operator==(Binary B);	//operator == (compare equal)

	bool operator!=(Binary B);	//operator != (compare not equal)

	Binary operator+(Binary B);	//operator + (sum of 2 binary)

	Binary operator-(Binary B);	//operator - (subtract of 2 binary)

	Binary operator*(Binary B);	//operator * (multiplycation of 2 binary)

	Binary operator/(Binary B);	//operator / (division of 2 binary)

	Binary operator%(Binary B);	//operator %

	bool operator<(Binary B);	//operator < (compare less than)

	bool operator>(Binary B);	//operator < (compare more than)

	bool operator>=(Binary B);	//operator >= (compare more or equal than)

	bool operator<=(Binary B);	////operator >= (compare less or equal than)
	
};

char sum_process(char a, char b, char& temp);

int char_toInt(char c);

int main()
{
	int a, b;
	cout << "Nhap vao so nguyen a: ";
	cin >> a;
	cout << "Nhap vao so nguyen b: ";
	cin >> b;

	Binary binA(a);
	Binary binB(b);

	cout << "A binary: ";
	binA.output();

	cout << "B binary: ";
	binB.output();

	//operator +,-,*,/,% are overloaded

	cout << "\nA + B (binary) =  ";
	(binA + binB).output();
	cout << "A + B (decimal) = "<<(binA + binB).b10_value();

	cout << "\nA - B (binary) =  ";
	(binA - binB).output();
	cout << "A - B (decimal) = "<<(binA - binB).b10_value();

	cout << "\nA * B (binary) =  ";
	(binA * binB).output();
	cout << "A * B (decimal) = "<<(binA * binB).b10_value();

	cout << "\nA / B (binary) =  ";
	(binA / binB).output();
	cout << "A / B (decimal) = "<<(binA / binB).b10_value();

	cout << "\nA % B (binary) =  ";
	(binA % binB).output();
	cout << "A % B (decimal) = "<<(binA % binB).b10_value();
}



Binary Binary::binary_sum(Binary B, char& temp)
{
	Binary ret;
	for (int i = BIN_SIZE - 1; i >= 0; i -= 1)
	{
		ret.bin[i] = sum_process(bin[i], B.bin[i], temp);
	}
	return ret;
}

Binary::Binary()
{
	for (int i = 0; i < BIN_SIZE; i += 1)
	{
		bin += '0';
	}
}

Binary::Binary(int n)
{
	try
	{
		if (n < -pow(2,BIN_SIZE - 1) || n >= pow(2, BIN_SIZE - 1))
			throw std::runtime_error("out of convert range");

		int temp = abs(n);
		while (temp > 0)
		{
			int lsb = (temp & 1);
			if (lsb == 1)
				bin = '1' + bin;
			else
				bin = '0' + bin;
			temp = temp >> 1;
		}
		for (size_t i = bin.length(); i < BIN_SIZE; i += 1)
		{
			bin = '0' + bin;
		}

		if (n < 0)
		{
			for (int i = 0; i < BIN_SIZE; i += 1)
			{
				if (bin[i] == '1')
					bin[i] = '0';
				else
					bin[i] = '1';
			}
			for (int i = BIN_SIZE - 1; i >= 0; i -= 1)
			{
				if (bin[i] == '0')
				{
					bin[i] = '1';
					break;
				}
				else
					bin[i] = '0';
			}
		}
	}
	catch (const std::runtime_error& e)
	{
		std::cout << "Error: " << e.what() << endl;
		for (int i = 0; i < BIN_SIZE; i += 1)
		{
			bin += '0';
		}
	}
}

void Binary::output()
{
	cout << bin[0];
	for (int i = 1; i < BIN_SIZE; i += 1)
	{
		if (i % 4 == 0)
			cout << " ";
		cout << bin[i];
	}
	cout << endl;
}

int Binary::b10_value()
{
	int val = 0;
	val -= (char_toInt(bin[0]) << (BIN_SIZE - 1));
	for (int i = 1; i <BIN_SIZE; i += 1)
	{
		val += (char_toInt(bin[i]) << (BIN_SIZE - i - 1));
	}
	return val;
}

char Binary::getLSB()
{
	return bin[BIN_SIZE - 1];
}

Binary Binary::_self()
{
	Binary ret;
	ret.bin = bin;
	return ret;
}

Binary Binary::_abs()
{
	if (bin[0] == '1')
		return Binary(0) - _self();
	return _self();
}

Binary Binary::operator~()
{
	Binary ret;
	for (int i = 0; i < BIN_SIZE; i += 1)
	{
		if (bin[i] == '1')
			ret.bin[i] = '0';
		else
			ret.bin[i] = '1';
	}
	return ret;
}

Binary Binary::operator&(Binary B)
{
	Binary ret;
	for (int i = 0; i < BIN_SIZE; i += 1)
	{
		if (bin[i] == '1' && B.bin[i] == '1')
			ret.bin[i] = '1';
		else
			ret.bin[i] = '0';
	}
	return ret;
}

Binary Binary::operator|(Binary B)
{
	Binary ret;
	for (int i = 0; i < BIN_SIZE; i += 1)
	{
		if (bin[i] == '1' || B.bin[i] == '1')
			ret.bin[i] = '1';
		else
			ret.bin[i] = '0';
	}
	return ret;
}

Binary Binary::operator^(Binary B)
{
	Binary ret;
	for (int i = 0; i < BIN_SIZE; i += 1)
	{
		if (bin[i] != B.bin[i])
			ret.bin[i] = '1';
		else
			ret.bin[i] = '0';
	}
	return ret;
}

void Binary::operator=(Binary B)
{
	for (int i = 0; i < BIN_SIZE; i += 1)
	{
		bin[i] = B.bin[i];
	}
}

Binary Binary::operator<<(int t)
{
	Binary ret;
	try
	{
		if (t < 0 || t > BIN_SIZE)
			throw std::runtime_error("Shift out of range");

		for (int i = 0; i < BIN_SIZE - t; i += 1)
		{
			ret.bin[i] = bin[i + t];
		}
		for (int i = BIN_SIZE - t; i < BIN_SIZE; i += 1)
		{
			ret.bin[i] = '0';
		}
		return ret;
	}
	catch (const std::runtime_error& e)
	{
		std::cout << "Error: " << e.what() << endl;
		return ret;
	}
}

Binary Binary::operator>>(int t)
{
	Binary ret;
	try
	{
		if (t < 0 || t > BIN_SIZE)
			throw std::runtime_error("Shift out of range");

		for (int i = BIN_SIZE - 1; i >= t; i -= 1)
		{
			ret.bin[i] = bin[i - t];
		}
		for (int i = t - 1; i >= 0; i -= 1)
		{
			ret.bin[i] = '0';
		}
		return ret;
	}
	catch (const std::runtime_error& e)
	{
		std::cout << "Error: " << e.what() << endl;
		return ret;
	}
}

bool Binary::operator==(Binary B)
{
	return (bin == B.bin);
}

bool Binary::operator!=(Binary B)
{
	return (bin != B.bin);
}

Binary Binary::operator+(Binary B)
{
	char temp = '0';
	return binary_sum(B, temp);
}

Binary Binary::operator-(Binary B)
{
	B = ((~B) + Binary(1));
	return operator+(B);
}

Binary Binary::operator*(Binary Q)
{
	int k = BIN_SIZE;
	Binary ret;
	char c = '0';
	Binary A;
	while (k > 0)
	{
		char lsb = Q.getLSB();
		if (lsb == '1')
		{
			A = binary_sum(A, c);
		}
		ret >> 1;
		ret.bin = A.bin[BIN_SIZE - 1] + ret.bin;
		A = A >> 1;
		A.bin[0] = c;
		c = '0';
		Q = Q >> 1;
		k -= 1;
	}
	return ret;
}

Binary Binary::operator/(Binary B)
{
	Binary ret;
	try
	{
		if (B == Binary(0))
			throw std::runtime_error("Devide by zero");

		Binary Self;
		bool flag = 1;
		if (bin[0] != B.bin[0])
			flag = 0;
		Self = _self()._abs();
		B = B._abs();

		while (Self - B >= Binary(0))
		{
			ret = ret + Binary(1);
			Self = Self - B;
		}
		if (flag == 0)
			ret = ret * Binary(-1);
		return ret;
	}
	catch (const std::runtime_error& e)
	{
		cout << "Error: " << e.what() << endl;
		return ret;
	}
	
}

Binary Binary::operator%(Binary B)
{

	return (_self() - B * (_self() / B))._abs();
}

bool Binary::operator<(Binary B)
{
	Binary Sub = _self() - B;
	if (Sub.bin[0] == '1')
		return true;
	return false;
}

bool Binary::operator>(Binary B)
{
	Binary sub = _self() - B;
	if (sub.bin[0] == '0' && sub != Binary(0))
		return true;
	return false;
}

bool Binary::operator>=(Binary B)
{
	return ((_self() > B) || (_self() == B));
}

bool Binary::operator<=(Binary B)
{
	return (_self() == B || _self() < B);
}

int char_toInt(char c)
{
	if (c == '1')
		return 1;
	return 0;
}

char sum_process(char a, char b, char& temp)
{
	if (temp == '0')
	{
		if (a == '0' && b == '0') { return '0'; }
		if ((a == '1' && b == '0') || (a == '0' && b == '1')) { return '1'; }
		if (a == '1' && b == '1') { temp = '1'; return '0'; }
	}
	else
	{
		if (a == '0' && b == '0') { temp = '0'; return '1'; }
		if ((a == '1' && b == '0') || (a == '0' && b == '1')) { temp = '1'; return '0'; }
		if (a == '1' && b == '1') { temp = '1'; return '1'; }
	}
	return '0';
}