#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>

#define N 256

struct number
{
	char* num;
	int len;
};

int read_num(char* arr, int n)
{
	int i = 0;
	char a;

	while (((a = getchar()) != '\n') && (i < n))
	{
		arr[i] = a;
		i++;
	}
	return i;
}

void write_num(struct number Origin)
{
	int i;
	
	for (i = 0; i < Origin.len; i++)
		putchar(Origin.num[i]);
	putchar('\n');
}

unsigned long long int sys1_dec(struct number Origin, int sys1)
{
	int i;
	int ch;
	unsigned long long int dec = 0;

	for (i = 0; i < Origin.len; i++)
	{
		ch = Origin.num[i] - '0';

		if (ch > 9)
			ch -= 'A' - '9' - 1;

		assert(ch < sys1);

		dec += ch * (unsigned long long int) pow(sys1, Origin.len - i - 1);
	}
	return dec;
}

struct number dec_sys2(unsigned long long int dec, int sys2)
{
	unsigned long long int j = 0;
	int i;

	struct number Target;
	Target.num = (char*)malloc(N * sizeof(char));
	
	j = dec;
	while ((j /= sys2) != 0)
		++Target.len;
	int ch = 0;

	for (i = Target.len; i >= 0; i--)
	{
		ch = dec / (unsigned long long int)pow(sys2, i);

		if (ch > 9)
			ch += 'A' - '9' - 1;

		Target.num[Target.len - i] = ch + '0';
		dec %= (unsigned long long int)pow(sys2, i);
        }
	++Target.len;
	return Target;
}

struct number transfer(struct number Origin, int sys1, int sys2)
{	
	if (sys1 == sys2)
		return Origin;

	unsigned long long int dec = sys1_dec(Origin, sys1);
	struct number Target = dec_sys2(dec, sys2);
	
	return Target;
}


int main()
{
	char* num = (char*)malloc(N);
	struct number Origin, Target;

	printf("Write down the number: ");
	Origin.len = read_num(num, N);
	assert(Origin.len <= 16);
	Origin.num = num;
	
	int orig_sys = 0;
	int tar_sys = 0;
	printf("Write down origin and target number systems: ");
	scanf("%d %d", &orig_sys, &tar_sys);
	
	assert((orig_sys <= 16) && (orig_sys >= 2));
	assert((tar_sys <= 16) && (tar_sys >= 2));
	
	Target = transfer(Origin, orig_sys, tar_sys);
	printf("Result: ");
	write_num(Target);
	
	free(Target.num);
	free(num);

	return 0;
}

