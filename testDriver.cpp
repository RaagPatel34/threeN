//Raag Patel
//CECS 325-01
//Prog 7 - 3N + 1 (BigInt)
//May/3/2023
//I certify that this program is my own original work. I did not copy and part of this program from any other source. I further certify that I typed each and every line of code in this program
#include <iostream>
#include <vector>
#include <climits>
#include <string>
using namespace std;

class BigInt {
    private:
        vector<char> v;
    public:
        BigInt() {
            BigInt(0);
        }

        BigInt(int n) {
            if(n == 0) {
                v.push_back(0);
                return;
            }
            else {
                while(n != 0) {
                    int digit = n % 10;
                    v.push_back(digit);
                    n = n / 10;
                }
            }
        }

        BigInt(string n) {
            int len = n.length();
            char digit;
            for(int i = len - 1; i >= 0; i--) {
                digit = n[i];
                v.push_back(digit - '0');
            }
        }

        BigInt operator+(const BigInt &n) {
            BigInt answer;
            int carry = 0;
            int temp = 0;

            while(temp < v.size() or temp < n.v.size() or carry == 1) {
                int sum = carry;

                if(temp < v.size()) {
                    sum = sum + v[temp];
                }
                if(temp < n.v.size()) {
                    sum = sum + n.v[temp];
                }

                carry = sum / 10;
                int remainder = sum % 10;
                answer.v.push_back(remainder);
                temp++;
            }
            return(answer);
        }

        bool operator<(const BigInt &n) {
            int temp;

            if(v.size() < n.v.size()) {
                return(true);
            }
            else if(v.size() > n.v.size()) {
                return(false);
            }

            if(v.size() == n.v.size()) {
                for(temp = v.size() - 1; temp >= 0; temp--) {
                    if(v[temp] < n.v[temp]) {
                        return(true);
                    }
                    else if(v[temp] > n.v[temp]) {
                        return(false);
                    }
                }
                return(false);
            }
        }

        BigInt operator*(const BigInt &n) {
            BigInt answer;
            for(BigInt i(0); i < n; i = i + 1) {
                answer = answer + (*this);
            }
            return(answer);
        }

        BigInt half() {
            BigInt answer;
            int carryValue = 0;

            for (auto it = v.rbegin(); it != v.rend(); ++it) {
                int temp = (carryValue * 10) + *it;
                answer.v.insert(answer.v.begin(), temp / 2);
                carryValue = temp % 2;
            }

            while(answer.v.size() > 1 && answer.v.back() == 0) {
                answer.v.pop_back();
            }
            
            return(answer);
        }

        bool isEven() {
            if(v.front() % 2 == 0) {
                return(true);
            }
            else {
                return(false);
            }
        }

        bool operator==(const BigInt &n) {
            if(v.size() != n.v.size()) {
                return(false);
            }

            for(int i = 0; i < v.size(); i++) {
                if(v[i] != n.v[i]) {
                    return(false);
                }
            }
            return(true);
        }

        friend ostream & operator<<(ostream &out, const BigInt &n) {
            if (n.v.empty()) {
                out << 0;
                return out;
            }
      
            if (n.v.size() > 8) {
                int t1 = n.v.size() - 1;
                int t2 = n.v.size() - 2;
                int t3 = n.v.size() - 8;
                out << int(n.v[t1]) << ".";

                for (int i = t2; i >= t3; i--) {
                        cout << (int)n.v[i];
                }

                cout << "e" << n.v.size() - 1;
            }

            else {
                for(int i = n.v.size() - 1; i >= 0; i--)
                    cout << (int)n.v[i];
            }

            return out;
        }
};

//Different from program 6, uses BigInt's rather than regular ints
struct np1 {
    BigInt start;
    BigInt steps;
    BigInt max;
    BigInt odds;
    BigInt evens;
} threeNP1; //Global struct

void threeN1(BigInt x, bool print_step) {
    if(threeNP1.max < x) {
        threeNP1.max = x;
    }
    
    if(print_step == true) {
        cout << "-> (" << x << ") ";
    }
    
    if(x == BigInt(1)) {
        cout << endl << "Start: " << threeNP1.start << endl;
        cout << "Steps: " << threeNP1.steps << endl;
        cout << "Max: " << threeNP1.max << endl;
        cout << "Odds: " << threeNP1.odds << endl;
        cout << "Evens: " << threeNP1.evens << endl;
        return;
    } 
    else if(x.isEven()) {
        threeNP1.evens = threeNP1.evens + BigInt(1);
        threeNP1.steps = threeNP1.steps + BigInt(1);
        threeN1(x.half(), print_step);
    } 
    else {
        threeNP1.odds = threeNP1.odds + BigInt(1);
        threeNP1.steps = threeNP1.steps + BigInt(1);
        threeN1((x * BigInt(3)) + BigInt(1), print_step);
    }
}

int main() {
    BigInt MAX(INT_MAX);

	cout << "\nThe largest integer is " << MAX << endl;
	cout << "Twice the largest integer is "<< MAX + MAX << endl;

	BigInt start(INT_MAX);
	threeNP1.start = start;
	bool print_step = false;

	threeN1(start, print_step);

	cout << "\n";
	cout << endl;

	return 0;
}