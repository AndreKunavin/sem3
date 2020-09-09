#include <stdio.h>
#include <assert.h>

#define N 256

unsigned long long int mul(unsigned long long int a, int n)	/*raising value a to the power of n*/
{
	int i;
	unsigned long long int c = 0;

	if (n == 0)
		return 1;
	
	assert(n >= 0);

	c = a;
	for (i = 1; i < n; i++)
		a *= c;

	return a;
}

int read_num(char* arr, int n)	/*reading the char array[n]*/
{
	int i = 0;
	char a;

	while (((a = getchar()) != '\n') && (i < n))
	{
		*(arr + i) = a;
		i++;
	}
	return i;
}

void write_num(char* arr, int n)	/*printing the array*/
{
	int i;
	
	for (i = 0; i < n; i++)
		putchar(*(arr + i));
	putchar('\n');
}


unsigned long long int sys1_dec(char* arr, int n, int sys1)	/*transfer from current number system to decimal n.s.*/
{
	int i;
	int ch;
	unsigned long long int dec = 0;

	for (i = 0; i < n; i++)
	{
		
		ch = *(arr + i) - 48;

		if (ch > 9)
			ch -= 7;

		assert(ch < sys1);
		//printf("%d ", ch);

		dec += ch * mul(sys1, n - i - 1);
		//printf("%d: ", n - i - 1);
		//printf("%lld ", dec); 
	}
	//putchar('\n');
	return dec;
}

void dec_sys2(unsigned long long int dec, int sys2)	/*transfer fron decimal n.s. to target n.s.*/
{
	unsigned long long int j = 0;
	int n = 0;
	int i;

	j = dec;
	while ((j /= sys2) != 0)
                ++n;
	
	int ch = 0;

	for (i = n; i >= 0; i--)
        {
		ch = dec / mul(sys2, i);

		if (ch > 9)
			ch += 7;

		putchar(ch + '0');
                dec %= mul(sys2, i);
        }

	putchar('\n');
}


int main()
{
	char num[N] = {};				/*space for the number*/
	int i;
	int n = 0;	

	printf("Write down the number: ");
	n = read_num(num, N);
	assert(n <= 16);

	int sys1 = 0;					/*current n.s.*/
	int sys2 = 0;					/*target n.s.*/

	printf("Write down current and target number systems: ");
	scanf("%d %d", &sys1, &sys2);

	assert((sys1 <= 16) && (sys1 >= 2));
	assert((sys2 <= 16) && (sys2 >= 2));

	if (sys1 == sys2)
	{	
		write_num(num, n);
		return 0;
	}

	unsigned long long int dec = 0;
	dec = sys1_dec(num, n, sys1);
	if (sys2 == 10)
	{
		printf("%lld\n", dec);
		return 0;
	}
	
	printf("Result: ");
	dec_sys2(dec, sys2);
	
	return 0;
}

