#include <stdio.h>
#include <stdlib.h>
int
main() 
{
	int a, b, c ;
	int match = 0 ;

	scanf("%d", &a) ; //CREST_int(a) ; fprintf(stderr, "%d\n", a) ;
	scanf("%d", &b) ; //CREST_int(b) ; fprintf(stderr, "%d\n", b) ;
	scanf("%d", &c) ; //CREST_int(c) ; fprintf(stderr, "%d\n", c) ;

	if(a <= 0 || b<= 0 || c<= 0) 
		exit(0);  

    // printf("%d %d %d", a, b, c) ;
    //0: Equilateral, 1:Isosceles, 
	// 2: Not a traiangle, 3:Scalene

	int result = -1 ;

	if(a == b) 
		match = match + 1 ;
	if(a == c) 
		match = match + 2 ;
	if(b == c) 
		match = match + 3 ;
	if(match == 0) {
		if(a + b <= c) 
			result = 2 ;
		else if (b + c <= a) 
			result = 2 ;
		else if (a + c <= b) 
			result = 2 ;
		else 
			result = 3 ;
	} 
	else {
		if(match == 1) {
			if(a + b <= c) 
				result = 2 ;
			else
				result = 1 ;
		} 
		else {
			if (match == 2) {
				if (a + c <= b) 
					result = 2 ;
				else 
					result = 1 ;
            } 
			else {
				if (match == 3) {
					if(b + c <= a) 
						result = 2 ;
					else 
						result = 1 ;
				} 
				else {
					result = 0;
				}
			}
		}
	}
	printf("result=%d\n",result);
}
