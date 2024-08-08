#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
	int i, j, k, state = 0, check1 = 0 ;
	bool check2 ;
	int nump, numr ;
	printf( "Banker's Algorithm\n" ) ;
	printf( "Enter number of process : " ) ;
	scanf( "%d", &nump ) ; //รับค่าจำนวนกระบวนการ
	printf( "Enter number of resource : " ) ;
	scanf( "%d", &numr ) ; //รับค่าจำนวนรีซอช
	int process[ nump ][ numr * 4 + 1 ], avail[ numr ], unit[ numr ] ;
	for( i = 0 ; i < nump ; i++ ) { //กำหนดค่าตัวแปรทั้งหมดให้เป็น 0
		for( j = 0 ; j <= nump * 4 ; j++ ) {
			process[ i ][ j ] = 0 ;
		}
	}
	printf( "Enter all unit of resource :\n" ) ;
	for( i = 0 ; i < nump ; i++ ) { //รับค่ารีซอชทั้งหมดที่มีอยู่
		printf( "resource %d : ", i + 1 ) ;
		scanf( "%d", &unit[ i ] ) ;
	}
	for( i = 0 ; i < nump ; i++ ) { //รับค่า allocation ของ process
		printf( "Enter allocation of process : %d\n", i + 1 ) ;
		for( j = 0 ; j < numr ; j++ ) {
			printf( "resource %d : ", j + 1 ) ;
			scanf( "%d", &process[ i ][ j ] ) ;
		}
	}
	printf( "----------------------------------------\n" ) ;
	for( i = 0 ; i < nump ; i++ ) { //รับค่า max of process
		printf( "Enter max of process : %d\n", i + 1 ) ;
		for( j = 0 ; j < numr ; j++ ) {
			printf( "resource %d : ", j + 1 ) ;
			scanf( "%d", &process[ i ][ numr + j ] ) ;
		}
	}
	printf( "\n----------------------------------------" ) ;
	for( i = 0 ; i < numr ; i++ ) { //คัดลอก resaurch จาก unit มาไว้ใน avail
		avail[ i ] = unit[ i ] ;
	}
	for( i = 0 ; i < nump ; i++ ) {
		for( j = 0 ; j < numr ; j++ ) {
			if( process[ i ][ j ] > process[ i ][ numr + j ] ) { //ตรวจสอบความถูกต้อง allocation เทียบกับ maxprocess 
				printf( "\nYour input invalid!!!" ) ;
				exit( 0 ) ;
			}
			process[ i ][ numr * 2 + j ] = process[ i ][ numr + j ] - process[ i ][ j ] ;
			avail[ j ] -= process[ i ][ j ] ; //ประมวลผล avail ที่เหลืออยู่
			if( avail[ j ] < 0 ) { //ตรวจสอบค่า avail
				printf( "\nYour input invalid!!!" ) ;
				exit( 0 ) ;
			}
		}
	}
	printf( "\nAll resource is " ) ;
	for( i = 0 ; i < numr ; i++ ) { //แสดง resaurch ที่เหลืออยู่
		if( i > 0 ) {
			printf( "," ) ;
		}
		printf( "%d ( %d instant )", i + 1, unit[ i ] ) ;
	}
	i = 0 ;
	while( state < nump && check1 < nump ) { //ประมวลผล
		check2 = true ;
		for( j = 0 ; j < numr ; j++ ) {
			if( process[ i ][ numr * 2 + j ] > avail[ j ] ) { //ตรวจสอบว่า resaurch ที่มีอยู่เพียงพอต่อการประมวลผลหรือไม่
				check2 = false ; //ระบุค่าว่าพอไหม
				break ;
			}
		}
		check1++ ; //ใช้ในการตรวจสอบว่าหากซ้ำหากว่าวนครบหนึ่งรอบแล้วแต่ resaurch ยังไม่พอสัก process ก็จะออกจาก loop
		if( check2 && process[ i ][ numr * 4 ] <= 0 ) { //หาก resaurch พอ state ณ ตำแหน่งที่ i state เท่ากับ 0 หรือเปล่า
			state++ ;
			process[ i ][ numr * 4 ] = state ; //เก็บค่า state ไว้
			check1 = 0 ; //หากกระบวนการทำงานพอสำหรับประมวลผล ก็จะดกำหนดให้ check1 เริ่มนับใหม่
			for( j = 0 ; j < numr ; j++ ) { //เอาค่า allocation มาไว้ให้ avail อีกครั้ง
				process[ i ][ numr * 3 + j ] = avail[ j ] ;
				avail[ j ] += process[ i ][ j ] ;
			}
		}
		if( i < nump - 1 ) { //วน loop คิวของ process
			i++ ;
		} else {
			i = 0 ;
		}
	}
	printf( "\n----------------------------------------" ) ;
	printf( "\n          Allocaion --> Max --> Need --> Available --> state" ) ; //แสดงหัวข้อ
	printf( "\nProcess     " ) ;
	for( i = 0 ; i < 4 ; i++) {
		for( j = 1 ; j <= numr ; j++ ) {
			printf( "%d ", j ) ;
			if( j % numr == 0 )  {
				printf( "          " ) ;
			}
		}
	}
	printf( "\n----------------------------------------\n" ) ; //แสดงลำดับการประมวลผล
	for( i = 0 ; i < nump ; i++ ) {
		printf( "P%d          ", i + 1 ) ;
		for( j = 0 ; j <= numr * 4 ; j++ ) {
			printf( "%d ", process[ i ][ j ] ) ;
			if( ( j + 1 ) % numr == 0 )  {
				printf( "          " ) ;
			}
		}
		printf( "\n" ) ;
	}
	printf( "            " ) ; //แสดง ค่าที่เหลือเป็นลำดับสุดท้าย
	for( i = 1 ; i <= numr * 3 ; i++ ) {
		printf( "  " ) ;
		if( i % numr == 0 )  {
			printf( "          " ) ;
		}
	}
	for( i = 0 ; i < numr ; i++ ) {
		printf( "%d ", avail[ i ] ) ;
	}
	if( check1 < nump ) {
		printf( "\nSafe State\n" ) ;
	} else {
		printf( "\nUnsafe State!!!\n" ) ;
	}
}