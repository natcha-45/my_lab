#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define allprocess 5

struct info { //สร้างโครงสร้างข้อมูลเพื่อเก็บข้อมูลของโปรเซส
	char name[ 3 ] ;
	int burst ;
	int arrival ;
	int priority ;
};

struct info *process[ allprocess ], *cp[ allprocess ] ; //ทำการประกาศตัวแปร pointer แบบ array เพื่อเก็บที่อยู่ของข้อมูล
float wait[ allprocess ], turnaround[ allprocess ] ; //ทำการประกาศตัวแปร wait เพื่อเก็บ waittime และ turnaround เพื่อเก็บ

void create() { //ทำการจองพื้นที่ในหน่วยความจำ
	int i = 0 ;
	for( i = 0 ; i < allprocess ; i++ ) {
		process[ i ] = malloc( sizeof( struct info ) ) ; //จองและให้ process[ i ] ชี้
	}
}

void set() {  //กำหนดค่าให้ process
	strcpy( process[ 0 ]->name, "P1" ) ;
	process[ 0 ]->burst = 9 ;
	process[ 0 ]->arrival = 1 ;
	process[ 0 ]->priority = 3 ;
	strcpy( process[ 1 ]->name, "P2" ) ;
	process[ 1 ]->burst = 3 ;
	process[ 1 ]->arrival = 1 ;
	process[ 1 ]->priority = 5 ;
	strcpy( process[ 2 ]->name, "P3" ) ;
	process[ 2 ]->burst = 5 ;
	process[ 2 ]->arrival = 3 ;
	process[ 2 ]->priority = 1 ;
	strcpy( process[ 3 ]->name, "P4" ) ;
	process[ 3 ]->burst = 4 ;
	process[ 3 ]->arrival = 4 ;
	process[ 3 ]->priority = 4 ;
	strcpy( process[ 4 ]->name, "P5" ) ;
	process[ 4 ]->burst = 2 ;
	process[ 4 ]->arrival = 7 ;
	process[ 4 ]->priority = 2 ;
}

void reset() { //รีเซ็ตข้อมูล และทำการคัดลอกข้อมูลเ็นเหมือนการเริ่มกระบวนการใหม่
	int i = 0 ;
	for( i = 0 ; i < allprocess ; i++ ) {
		free( cp[ i ] ) ; //ทำการคืนพื้นที่ที่เคยจองให้หน่วยความจำ
		cp[ i ] = malloc( sizeof( struct info ) ) ; //ทำการจองพื้นที่
		strcpy( cp[ i ]->name, process[ i ]->name ) ; //คัดลอกข้อมูล
		cp[ i ]->burst = process[ i ]->burst ;
		cp[ i ]->arrival = process[ i ]->arrival ;
		cp[ i ]->priority = process[ i ]->priority ;
	}
}

bool haveprocess() { //ตรวจสอบว่ายังมี process ไหม
	bool result = false ;
	int i ;
	for( i = 0 ; i < allprocess ; i++ ) {
		if( cp[ i ]->burst > 0 ) {
			result = true ; //ถ้ายังมี burst time ที่มากกว่า 0 อยู่ก็จะส่งค่าจริงกลับไป
		}
	}
	return( result ) ; //ถ้า burst น้อยกว่าหรือเท่ากับ 0 ก็จะส่งค่าเท็จกลับไป
}

int lastp( int time ) { //ตรวจสอบว่า ณ เวลานั้นๆ มีกระบวนการกี่กระบวนการที่เข้ามาแล้ว
	int last = -1, i ;
	for( i = 0 ; i < allprocess ; i++ ) {
		if( cp[ i ]->arrival <= time ) { //ตรวจสอบว่า ตำแหน่งใดที่ arrival น้อยกว่าเท่ากับ time บ้าง
			last = i ;
		}
	}
	return( last ) ;  //ส่งตำแหน่งสุดท้ายที่ arrival น้อยกว่าเท่ากับ time กลับไป
}

int searchless( int last ) { //หาว่ากระบวนการใดที่มีเวลาในการประมวลผลน้อยที่สุด
	int i, less = 0, temp = 999 ;
	for( i = 0 ; i <= last ; i++ ) {
		if( cp[ i ]->burst < temp && cp[ i ]->burst > 0 ) { //หาตำแหน่งไหนน้อยที่สุด และ bursttime > 0 และในกรณีที่มาถึงพร้อมอันด้านหน้าจะได้ทำก่อน
			temp = cp[ i ]->burst ; //คัดลอกเวลาประมวลผล ณ ตำแหน่งนั้นมาไว้ใน temp
			less = i ; //เก็บตำแหน่งที่น้อยที่สุดไว้ตัวแปร less
		}
	}
	return( less ) ; //ส่งกลับค่า less
}

void cleanwaitturn() { //ทำการกำหนดค่า ตัวแปร wait และ turnaround เป็น 0 ทั้งหมด
	int i ;
    for( i = 0 ; i < allprocess ; i++ ) {
		wait[ i ] = 0 ;
		turnaround[ i ] = 0 ;
	}
}

void waitturn( int less, int last ) { //เป็นฟังก์ชั่นที่ทำหน้าที่เก็บ waittime และ turnaroundtime
	int i ;
    for( i = 0 ; i <= last ; i++ ) { //
		if( i != less && cp[ i ]->burst > 0 ) { //ทุกตัวที่ตำแหน่งน้อยกว่า last และไม่ใช่ตำแหน่ง less จะเพิ่มขึน 1 ค่า
			wait[ i ]++ ;
		}
		if( cp[ i ]->burst > 0 ) { //ทุกตัวที่ตำแหน่งน้อยกว่า last จะเพิ่มขึน 1 ค่า
			turnaround[ i ]++ ;
		}
	}
	
}

void average() { //ฟังก์ชั่นคิดค่า averrage waittime
	int i ;
	float result = 0 ;
	for( i = 0 ; i < allprocess ; i++ ) {  //รวมทุกค่าที่อยู่ในตัแปร wait
		result += wait[ i ] ;
	}
	printf( "\nAverage wait time is : %0.2f ms", result / allprocess ) ;
}

void disp() {
	int i ;
	printf( "\nWait time of process ( millisecond )" ) ;
	printf( "\n" ) ;
	for( i = 0 ; i < allprocess ; i++ ) { //แสดงชื่อ process
		printf( "| %-8s", cp[ i ]->name ) ;
	}
	printf( "\n" ) ;
	for( i = 0 ; i < allprocess ; i++ ) { //แสดง waittime
		printf( "| %-8.2f", wait[ i ] ) ;
	}
	average() ;
	printf( "\nTurnaround time : " ) ;
	for( i = 0 ; i < allprocess ; i++ ) { //แสดง turnaround time
		if( i > 0 ) {
			printf( " | " ) ;
		}
		printf( "%s = %0.2f ms", cp[ i ]->name, turnaround[ i ] ) ;
	}
}

void N_SJF() {
	char nametemp[ 3 ] = { 0, 0 } ;
	bool finish = true, arrow = false ;
	int less, last ;
	float time = 0 ;
	reset() ; //ล้างกระบวนการที่คัดลอก
	cleanwaitturn() ; //ล้างค่า waittime และ turnaroundtime
	printf( "## 1.Non preemptive SJF scheduling. ##\n" ) ;
	printf( "--------------------------------\n" ) ;
	printf( "\nSequence process is : " ) ;
	while( haveprocess() ) { //ส่วนประมวลผล ถ้ายังมี bursttime อยู่ก็ทำงานเรื่อยๆ
		last = lastp( time ) ; //หาตำแหน่งกระบวนการสุดท้ายที่เข้ามา
		if( last >= 0 ) {
			if( finish ) { //ตรวจว่ากระบวนการทำงานจนเสร็จหรือยังถ้าเสร็จให้หาค่าที่น้อยกว่าใหม่
				less = searchless( last ) ; //หาค่าว่ากระบวนการไหน ที่น้อยกว่า last มีค่า bursttime น้อยที่สุด
			}
			if( strcmp( nametemp, cp[ less ]->name ) ) { //ถ้าไม่ซ้ำกับตัวหน้าให้แสดงชื่อออกมา
				if( arrow ) {
					printf( "->" ) ;
				}
				printf( "%s", cp[ less ]->name ) ;
				strcpy( nametemp, cp[ less ]->name ) ;
				arrow = true ;
			}
			waitturn( less, last ) ; //เรียก waiturn เพื่อเก็บค่า waittime และ turnaround time
			cp[ less ]->burst-- ; //ลดค่าลง 1 ค่าเป็นเสมือนการทำงานเสร็จไป 1 quantum time
			if( cp[ less ]->burst <= 0 ) { //ถ้า burst time เป็น 0  ก็กำหนดค่าให้มีการหาค่าน้อยที่สุดใหม่ 
				finish = true ;
			} else {
				finish = false ;
			}
		}
		time++ ;
	}
	disp() ;
}

void SJF() {
	int last, less ;
	float time = 0 ;
	char nametemp[ 3 ] = { 0, 0 } ;
	bool arrow = false ;
	reset() ;
	cleanwaitturn() ;
	printf( "\n\n## 2.Preemptive SJF scheduling. ##\n" ) ;
	printf( "--------------------------------\n" ) ;
	printf( "\nSequence process is : " ) ;
	while( haveprocess() ) { //ส่วนประมวลผล ถ้ายังมี bursttime อยู่ก็ทำงานเรื่อยๆ
		last = lastp( time ) ; //หาตำแหน่งกระบวนการสุดท้ายที่เข้ามา
		if( last >= 0 ) {
			less = searchless( last ) ; //หาค่าว่ากระบวนการไหน ที่น้อยกว่า last มีค่า bursttime น้อยที่สุด
			if( strcmp( nametemp, cp[ less ]->name ) ) { //ถ้าไม่ซ้ำกับตัวแปรก่อนหน้าก็แสดงผลออกมาเลย
				if( arrow ) {
					printf( "->" ) ;
				}
				printf( "%s", cp[ less ]->name ) ;
				strcpy( nametemp, cp[ less ]->name ) ;
				arrow = true ;
			}
			waitturn( less, last ) ; //เรียก waiturn เพื่อเก็บค่า waittime และ turnaround time
			cp[ less ]->burst-- ; //ลดค่าลง 1 ค่าเป็นเสมือนการทำงานเสร็จไป 1 quantum time
		}
		time++ ;
	}
	disp() ;
}

int searchqueue( int queue, int last ) { //หาตำแหน่งว่ากระบวนการต่อไปที่จะประมวลผลคือกระบวนการใดโดยวนเป็นวงกลม
	int i ;
	for( i = 0 ; i <= last ; i++ ) {
		if( queue > last ) { //เมื่อเกินตำแหน่งสุดท้าให้เริ่ม 0 ใหม่
			queue = 0 ;
		}
		if( cp[ queue ]->burst > 0 ) { //หากเจอตัวที่ทำงานไม่เสร็จก็ส่งคืนตำแหน่งนั้น หากทำงานเสร็จจะเลื่อนไปตัวถัดไป
			return( queue ) ;
		} else {
			queue++ ;
		}
	}
	
}

void RR() {
	bool arrow = false, chang = false ;
	char nametemp[ 3 ] = { 0, 0 } ;
	int i = 0, qt = 4, last , queue = 0 ;
	float time = 0 ;
	reset() ;
	cleanwaitturn() ;
	printf( "\n\n## 4.Round Robin scheduling. (Time quantum = 4). ##\n" ) ;
	printf( "--------------------------------\n" ) ;
	printf( "\nSequence process is : " ) ;
	while( haveprocess() ) { //ส่วนประมวลผล ถ้ายังมี bursttime อยู่ก็ทำงานเรื่อยๆ
		last = lastp( time ) ; //หาตำแหน่งกระบวนการสุดท้ายที่เข้ามา
		if( last >= 0 ) {
			if( chang ) {
				queue = searchqueue( queue + 1, last ) ; //เรียกใช้ฟังก์ชั่นเพื่อค้นหากระบวนการถัดไป
			}
			if( strcmp( nametemp, cp[ queue ]->name ) ) { //ถ้าไม่ซ้ำกับตัวแสดงค่าก่อนหน้าก็แสดงค่าชื่อออกมา
				if( arrow ) {
					printf( "->" ) ;
				}
				printf( "%s", cp[ queue ]->name ) ;
				strcpy( nametemp, cp[ queue ]->name ) ;
				arrow = true ;
			}
			waitturn( queue, last ) ; //กำการเรียกใช้ฟังก์ชั่นเพื่อเก็บค่า waittime และ trunaround time
			cp[ queue ]->burst-- ; //ลดค่า burst time เพื่อเป็นเสมือนการทำงานไป 1 quantum time
			if( cp[ queue ]->burst <= 0 ) { //ถ้ากระบวนการทำงานเสร็จก่อน quantum time ก็ให้เปลี่ยนค่าให้เข้าเงื่อนไขการเปลี่ยนกระบวนการ
				i = qt - 1 ;
			}
			if( i < qt - 1 ) { //ถ้าทำงานเสร็จก็เปลี่ยนได้ และตั้งค่า i เพื่อเริ่มนับใหม่
				i++ ;
				chang = false ;
			} else {
				i = 0 ;
				chang = true ;
			}
		}
		time++ ;
	}
	disp() ;
}

int searchprio( int last ) { //ค้นหาค่านัยสำคัญ
	int i, temp = 999, prio ;
	for( i = 0 ; i <= last ; i++ ) {
		if( temp > cp[ i ]->priority && cp[ i ]->burst > 0 ) { //ค้นหาว่ากระบวนการใดที่มีค่านัยสำคัญมากที่สุด และยังทำงานไม่เสร็จ
			temp = cp[ i ]->priority ;
			prio = i ; //เก็บตำแหน่งค่าตำแหน่งที่มีค่านัยสำคัญน้อยที่สุดไว้
		}
	}
	return( prio ) ; //ส่งกลับตำแหน่ง
}

void priority() {
	int last, prio ;
	float time = 0 ;
	char nametemp[ 3 ] = { 0, 0 } ;
	bool arrow = false ;
	reset() ;
	cleanwaitturn() ;
	printf( "\n\n## 4.Priorityscheduling. ##\n" ) ;
	printf( "--------------------------------\n" ) ;
	printf( "\nSequence process is : " ) ;
	int i = 0 ; //-----------
	while( haveprocess() ) { //ถ้ายังมีการะบวนการก็ให้ทำงานไปเรื่อยๆ
		last = lastp( time ) ; //หาตำแหน่งสุดท้าย ณ เวลานั้นที่มีกระบวนการมาทำงาน
		if( last >= 0 ) {
			prio = searchprio( last ) ; //หาตำแหน่งที่มีค่านัยสำคัญมากที่สุด
			if( strcmp( nametemp, cp[ prio ]->name ) ) { //ถ้าไม่ซ้ำตัวหน้าให้แสดงผลออกมา
				if( arrow ) {
					printf( "->" ) ;
				}
				printf( "%s", cp[ prio ]->name ) ;
				strcpy( nametemp, cp[ prio ]->name ) ;
				arrow = true ;
			}
			waitturn( prio, last ) ; //เก็บค่า waittime และ turnaround time
			cp[ prio ]->burst-- ; //ลดค่าเพื่อเป็นเสมือนการทำงานไป 1 quantum time
		}
		time++ ;
		if( i >= 20 ) { //-----------
			break ; //-----------
		}
		i++ ; //-----------
	}
	disp() ;
}

int main() {
	create() ; //จองพื้นที่
	set() ; //กำหนดข้อมูล
	printf( "# Mr.Natchaphon Surname Panasantikun ID : 645423206012-9 Sec.01 #\n" ) ;
	printf( "# OUTPUT LAB 6 CPU  Scheduling                                  #\n" ) ;
	N_SJF() ;
	SJF() ;
	RR() ;
	priority() ;
	return( 0 ) ;
}
