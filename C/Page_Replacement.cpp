#include <stdio.h>

#define page 19
//#define page 20
#define frame 4

int data[ page ] = { 2, 1, 2, 3, 7, 6, 2, 3, 4, 2, 1, 5, 6, 3, 2, 3, 6, 2, 1 } ;
//int data[ page ] = { 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1 } ;
int memory[ frame ][ page ], fault[ page ], tempmem[ frame ] ;

void clear() {
	int i, j ;
	for( i = 0 ; i < page ; i++ ) {
		for( j = 0 ; j < frame ; j++ ) {
			memory[ j ][ i ] = -1 ;
			tempmem[ j ] = -1 ;
		}
		fault[ i ] = 0 ;
	}
}

bool check( int i ) {
	int j ;
	for( j = 0 ; j < frame ; j++ ) {
		if( tempmem[ j ] == data[ i ] ) {
			return( false ) ;
		}
	}
	return( true ) ;
}

void disp() {
	int i, j, temp = 0 ;
	for( i = 0 ; i < page ; i++ ) {
		printf( "%2d ", data[ i ] ) ;
	}
	printf( "\n--------------------------------------------------------\n" ) ;
	printf( "\n" ) ;
	for( i = 0 ; i < frame ; i++ ) {
		for( j = 0 ; j < page ; j++ ) {
			if( memory[ i ][ j ] >= 0 ) {
				printf( "%2d ", memory[ i ][ j ] ) ;
			} else {
				printf( "   " ) ;
			}
		}
		printf( "\n" ) ;
	}
	printf( "--------------------------------------------------------\n" ) ;
	for( i = 0 ; i < page ; i++ ) {
		printf( "%2d ", fault[ i ] ) ;
	}
	for( i = 0 ; i < page ; i++ ) {
		temp += fault[ i ] ;
	}
	printf( "------>Page faults : %d\n", temp ) ;
}

void cp( int i ) {
	int j ;
	for( j = 0 ; j < frame ; j++ ) {
		memory[ j ][ i ] = tempmem[ j ] ;
	}
}

void FIFO() {
	int i, j = 0 ;
	printf( "\n1)Least Recently Used (FIFO) replacement\n" ) ;
	clear() ;
	for( i = 0 ; i < page ; i++ ) {
		if( check( i ) ) {
			tempmem[ j ] = data[ i ] ;
			cp( i ) ;
			fault[ i ] = 1 ;
			if( j >= frame - 1 ) {
				j = 0 ;
			} else {
				j++ ;
			}
		} else {
			fault[ i ] = 0 ;
		}
	}
	disp() ;
}

int past( int i ) {
	int j, k, temp, big = 0 ;
	int most[ frame ] ;
	for( j = 0 ; j < frame ; j++ ) {
		for( k = i ; k >= 0 ; k-- ) {
			if( tempmem[ j ] == data[ k ] ) {
				break ;
			}
		}
		most[ j ] = i - k ;
	}
	for( j = 0 ; j < frame ; j++ ) {
		if( big < most[ j ] ) {
			big = most[ j ] ;
			temp = j ;
		}
	}
	return( temp ) ;
}

void LRU() {
	int i, j ;
	printf( "\n2)Least Recently Used (LRU) replacement \n" ) ;
	clear() ;
	for( i = 0 ; i < page ; i++ ) {
		if( check( i ) ) {
			j = past( i ) ;
			tempmem[ j ] = data[ i ] ;
			cp( i ) ;
			fault[ i ] = 1 ;
		} else {
			fault[ i ] = 0 ;
		}
	}
	disp() ;
}

int future( int i ) {
	int j, k, temp, big = 0 ;
	int most[ frame ] ;
	for( j = 0 ; j < frame ; j++ ) {
		for( k = i ; k < page ; k++ ) {
			if( tempmem[ j ] == data[ k ] ) {
				break ;
			}
		}
		most[ j ] = k - i ;
	}
	for( j = 0 ; j < frame ; j++ ) {
		if( big < most[ j ] ) {
			big = most[ j ] ;
			temp = j ;
		}
	}
	return( temp ) ;
}

void OPTIMAL() {
	int i, j ;
	printf( "\n3)Optimal replacement\n" ) ;
	clear() ;
	for( i = 0 ; i < page ; i++ ) {
		if( check( i ) ) {
			j = future( i ) ;
			tempmem[ j ] = data[ i ] ;
			cp( i ) ;
			fault[ i ] = 1 ;
		} else {
			fault[ i ] = 0 ;
		}
	}
	disp() ;
}

int main() {
	printf( "Page replacement by Natchaphon Panasantikun 64543206012-9" ) ;
	FIFO() ;
	LRU() ;
	OPTIMAL() ;
}
