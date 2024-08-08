#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define max 20

bool checkadmin() {
	printf( "\nLogin with admin mode" ) ;
	FILE *fp ;
	char name[ max ], pass[ max ], nametemp[ max ], passtemp[ max ], mode ;
	name[ 0 ]  = '0' ;
	fp = fopen( "Admin/admin.txt", "r" ) ;
	fscanf( fp, "%s", name ) ;
	fscanf( fp, "%s", name ) ;
	fscanf( fp, "%s", pass ) ;
	fscanf( fp, "%s", pass ) ;
	if( name[ 0 ] == '0' ) {
		fclose( fp ) ;
		fp = fopen( "Admin/admin.txt", "w" ) ;
		printf( "\nNot have admin please enter admin name and password" ) ;
		printf( "\nInput name : " ) ;
		fputs( "name ", fp ) ;
		scanf( "%s", &name ) ;
		fprintf( fp, "%s ", name ) ;
		printf( "Input password : " ) ;
		fputs( "passsword ", fp ) ;
		scanf( "%s", &pass ) ;
		fprintf( fp, "%s", pass ) ;
		fclose( fp ) ;
		printf( "Add admin success!!!" ) ;
		fclose( fp ) ;
		fp = fopen( "Admin/account.txt", "w" ) ;
		fputs( "1", fp ) ;
		fclose( fp ) ;
		printf( "\n-------------------------------------" ) ;
		return( true ) ;
	} else {
		printf( "\nname : " ) ;
		scanf( "%s", &nametemp ) ;
		printf( "password : " ) ;
		scanf( "%s", &passtemp ) ;
		if( ( strcmp( nametemp, name ) == 0 ) && ( strcmp( passtemp, pass ) == 0 ) ) {
			printf( "Login with admin success!!!" ) ;
			printf( "\n-------------------------------------" ) ;
			fclose( fp ) ;
			return( true ) ;
		} else {
			printf( "Your username or password wrong" ) ;
			printf( "\n-------------------------------------" ) ;
		}
		fclose( fp ) ;
	}
	return( false ) ;
}

void adduser() {
	printf( "\nAdd user mode\n" ) ;
	FILE *fp1, *fp2 ;
	char temp[ max ], tempinfo[ max ], account1[ max ], mode ;
	int account2 ;
	fp1 = fopen( "Admin/account.txt", "r" ) ;
	fscanf( fp1, "%s", account1 ) ;
	account2 = atoi( temp ) ;
	strcpy( temp, "User/" ) ;
	strcat( temp, account1 ) ;
	strcat( temp, ".txt" ) ;
	fp2 = fopen( temp, "w" ) ;
	account2 = atoi( account1 ) ;
	account2++ ;
	fclose( fp1 ) ;
	fp1 = fopen( "Admin/account.txt", "w+" ) ;
	fprintf( fp1, "%d", account2 ) ;
	printf( "Your account ID : %s", account1 ) ;
	fputs( "account ", fp2 ) ;
	fprintf( fp2, "%s ", account1 ) ;
	printf( "\npassword : " ) ;
	fputs( "password ", fp2 ) ;
	scanf( "%s", &tempinfo ) ;
	fprintf( fp2, "%s ", tempinfo ) ;
	printf( "name : " ) ;
	fputs( "name ", fp2 ) ;
	scanf( "%s", &tempinfo ) ;
	fprintf( fp2, "%s ", tempinfo ) ;
	printf( "surname : " ) ;
	fputs( "surname ", fp2 ) ;
	scanf( "%s", &tempinfo ) ;
	fprintf( fp2, "%s ", tempinfo ) ;
	while( mode != '1' && mode != '2' ) {
		printf( "type" ) ;
		fputs( "type ", fp2 ) ;
		printf( " : 1 Saving    2 fixed\n" ) ;
		mode = getch() ;
		switch( mode ) {
			case '1' :	fputs( "saving ", fp2 ) ;
						break ;
			case '2' :	fputs( "fixed ", fp2 ) ;
						break ;
		}
	}
	printf( "phone number : " ) ;
	fputs( "phonenumber ", fp2 ) ;
	scanf( "%s", &tempinfo ) ;
	fprintf( fp2, "%s", tempinfo ) ;
	printf( "Add user success" ) ;
	printf( "\n-------------------------------------" ) ;
	strcpy( temp, "User/" ) ;
	strcat( temp, account1 ) ;
	strcat( temp, "state.txt" ) ;
	fclose( fp2 ) ;
	fp2 = fopen( temp, "w+" ) ;
	fputs( "date ", fp2 ) ;
	fputs( "deposit ", fp2 ) ;
	fputs( "withdraw ", fp2 ) ;
	fputs( "balance\n", fp2 ) ;
	fclose( fp1 ) ;
	fclose( fp2 ) ;
}

void showuser() {
	FILE *fp1, *fp2 ;
	fp1 = fopen( "Admin/account.txt", "r" ) ;
	char temp[ max ], account[ max ], info[ max ] ;
	bool have = true;
	int last, i, j, k = 1 ;
	fscanf( fp1, "%s", temp ) ;
	last = atoi( temp ) ;
	for( i = 1 ; i < last ; i++ ) {
		strcpy( temp, "User/" ) ;
		itoa( i, account, 10 ) ;
		strcat( temp, account ) ;
		strcat( temp, ".txt" ) ;
		if( fp2 = fopen( temp, "r" ) ) {
			have = false ;
			printf( "\n%-2d: ", k++ ) ;
			for( j = 0 ; j < 12 ; j++ ) {
				fscanf( fp2, "%s", info ) ;
				if( j % 2 == 0 ) {
					printf( "%s : ", info ) ;
				} else {
					printf( "%-8s ", info ) ;
				}
			}
			fclose( fp2 ) ;
		}
	}
	if( have ) {
		printf( "Not have any user" ) ;
	}
	fclose( fp1 ) ;
	printf( "\n-------------------------------------" ) ;
}

void deleteuser( char tempname[ max ] ) {
	char name[ max ], temp[ max ] ;
	bool state ;
	strcpy( temp, "User/" ) ;
	strcat( temp, tempname ) ;
	strcat( temp, ".txt" ) ;
	state = remove( temp ) ;
	strcpy( temp, "User/" ) ;
	strcat( temp, tempname ) ;
	strcat( temp, "state.txt" ) ;
	remove( temp ) ;
	if( state == 0 ) {
		printf( "Delete success!!!" ) ;
	} else {
		printf( "Delete fail or don't have this account" ) ;
	}
	printf( "\n-------------------------------------" ) ;
}

void admin() {
	FILE *fp ;
	char name[ max ], temp[ max ] ;
	fp = fopen( "Admin/admin.txt", "w+" ) ;
	printf( "\nname : " ) ;
	scanf( "%s", &temp ) ;
	fputs( "name ", fp ) ;
	fprintf( fp, "%s ", temp ) ;
	printf( "password : " ) ;
	scanf( "%s", &temp ) ;
	fputs( "password ", fp ) ;
	fprintf( fp, "%s", temp ) ;
	fclose( fp ) ;
	printf( "Edit admin success!!!" ) ;
	printf( "\n-------------------------------------" ) ;
}

void userinfo( char temp[ max ] ) {
	FILE *fp ;
	char info[ max ] ;
	char par[ max ], mode ;
	strcpy( par, "User/" ) ;
	strcat( par, temp ) ;
	strcat( par, ".txt" ) ;
	fp = fopen( par, "r" ) ;
	if( fp == 0 ) {
		fclose( fp ) ;
		printf( "Do not have this account" ) ;
	} else {
		fclose( fp ) ;
		fp = fopen( par, "w+" ) ;
		fscanf( fp, "%s", info ) ;
		fscanf( fp, "%s", info ) ;
		fputs( "account ", fp ) ;
		fprintf( fp, "%s ", temp ) ;
		printf( "password : " ) ;
		fputs( "password ", fp ) ;
		scanf( "%s", &info ) ;
		fprintf( fp, "%s ", info ) ;
		printf( "name : " ) ;
		fputs( "name ", fp ) ;
		scanf( "%s", &info ) ;
		fprintf( fp, "%s ", info ) ;
		printf( "surname : " ) ;
		fputs( "surname ", fp ) ;
		scanf( "%s", &info ) ;
		fprintf( fp, "%s ", info ) ;
		while( mode != '1' && mode != '2' ) {
			printf( "type" ) ;
			fputs( "type\t", fp ) ;
			printf( " : 1 Saving    2 fixed" ) ;
			mode = getch() ;
			switch( mode ) {
				case '1' :	fputs( "saving ", fp ) ;
							break ;
				case '2' :	fputs( "fixed ", fp ) ;
							break ;
			}
		}
		printf( "\nphonenumber : " ) ;
		fputs( "phonenumber ", fp ) ;
		scanf( "%s", &info ) ;
		fprintf( fp, "%s", info ) ;
		printf( "Edit user success!!!" ) ;
		fclose( fp ) ;
	}
	printf( "\n-------------------------------------" ) ;
}

void editadmin() {
	char name[ max ], pass[ max ], account1, info[ max ], mode ;
	int account2 ;
	while( mode != 'e' ) {
		printf( "\nPlease select mode to edit" ) ;
		printf( "\n1 Admin username and password" ) ;
		printf( "\n2 User information" ) ;
		printf( "\nE Exit" ) ;
		printf( "\n-------------------------------------" ) ;
		mode = getch() ;
		switch( mode ) {
			case '1' :	admin() ;
						break ;
			case '2' :	printf( "\naccount to edit : " ) ;
						scanf( "%s", &info ) ;
						userinfo( info ) ;
						break ;
		}
	}
}

void deposit( char account[ max ] ) {
	FILE *fp ;
	time_t rawtime ;
	struct tm *local ;
	time( &rawtime ) ;
	local = localtime( &rawtime ) ;
	char temp[ max ], monneyfile[ max ] ;
	int monney1, monney2, i ;
	strcpy( temp, "User/" ) ;
	strcat( temp, account ) ;
	strcat( temp, ".txt" ) ;
	fp = fopen( temp, "r" ) ;
	if( fp != 0 ) {
		for( i = 0 ; i < 12 ; i++ ) {
			fscanf( fp, "%s", temp ) ;
			if( i % 2 == 0 ) {
				printf( "%s : ", temp ) ;
			} else {
				printf( "%-8s", temp ) ;
			}
		}
		printf( "\n" ) ;
		fclose( fp ) ;
		strcpy( temp, "User/" ) ;
		strcat( temp, account ) ;
		strcat( temp, "state.txt" ) ;
		fp = fopen( temp, "r" ) ;
		fseek( fp, 0, SEEK_END ) ;
		long n = ftell( fp ) ;
		while( n >= 0 && fgetc( fp ) != ' ' ) {
			fseek( fp, n--, SEEK_SET ) ;
		}
		fscanf( fp, "%s", monneyfile ) ;
		fclose( fp ) ;
		fp = fopen( temp, "a" ) ;
		if( strchr( "1234567890", monneyfile[ 0 ] ) ) {
			monney2 = atoi( monneyfile ) ;
			printf( "amount : %s", monneyfile ) ;
			printf( "\nMonney : " ) ;
			scanf( "%d", &monney1 ) ;
			printf( "%d/%d/%d deposit : %d  amount : %d", local->tm_mday, local->tm_mon, local->tm_year + 1900, monney1, monney2 + monney1 ) ;
			fprintf( fp, "%d/%d/%d %d - %d\n", local->tm_mday, local->tm_mon, local->tm_year + 1900, monney1, monney2 + monney1 ) ;
		} else {
			printf( "amount : 0" ) ;
			printf( "\nMonney : " ) ;
			scanf( "%d", &monney1 ) ;
			printf( "%d/%d/%d deposit : %d  amount : %d", local->tm_mday, local->tm_mon, local->tm_year + 1900, monney1, monney1 ) ;
			fprintf( fp, "%d/%d/%d %d - %d\n", local->tm_mday, local->tm_mon, local->tm_year + 1900, monney1, monney1 ) ;
		}
		fclose( fp ) ;
	} else {
		printf( "Not have this account" ) ;
	}
	printf( "\n-------------------------------------" ) ;
}

void withdraw( char account[ max ] ) {
	FILE *fp ;
	time_t rawtime ;
	struct tm *local ;
	time( &rawtime ) ;
	local = localtime( &rawtime ) ;
	char temp[ max ], monneyfile[ max ] ;
	int monney1, monney2, i ;
	strcpy( temp, "User/" ) ;
	strcat( temp, account ) ;
	strcat( temp, ".txt" ) ;
	fp = fopen( temp, "r" ) ;
	if( fp != 0 ) {
		for( i = 0 ; i < 12 ; i++ ) {
			fscanf( fp, "%s", temp ) ;
			if( i % 2 == 0 ) {
				printf( "%s : ", temp ) ;
			} else {
				printf( "%-8s", temp ) ;
			}
		}
		printf( "\n" ) ;
		fclose( fp ) ;
		strcpy( temp, "User/" ) ;
		strcat( temp, account ) ;
		strcat( temp, "state.txt" ) ;
		fp = fopen( temp, "r" ) ;
		fseek( fp, 0, SEEK_END ) ;
		long n = ftell( fp ) ;
		while( n >= 0 && fgetc( fp ) != ' ' ) {
			fseek( fp, n--, SEEK_SET ) ;
		}
		fscanf( fp, "%s", monneyfile ) ;
		fclose( fp ) ;
		fp = fopen( temp, "a" ) ;
		if( strchr( "1234567890", monneyfile[ 0 ] ) ) {
			monney2 = atoi( monneyfile ) ;
			printf( "amount : %s", monneyfile ) ;
			printf( "\nMonney : " ) ;
			scanf( "%d", &monney1 ) ;
			if( monney2 - monney1 >= 0 ) {
				printf( "%d/%d/%d withdraw : %d  amount : %d", local->tm_mday, local->tm_mon, local->tm_year + 1900, monney1, monney2 - monney1 ) ;
				fprintf( fp, "%d/%d/%d - %d %d\n", local->tm_mday, local->tm_mon, local->tm_year + 1900, monney1, monney2 - monney1 ) ;
			} else {
				printf( "can't witdraw monney try again" ) ;
			}
		} else {
			printf( "amount : 0" ) ;
			printf( "\nNot have monney can't with draw" ) ;
		}
		fclose( fp ) ;
	} else {
		printf( "\nNot have this account" ) ;
	}
	printf( "\n-------------------------------------" ) ;
}

void statement( char account[ max ] ) {
	FILE *fp ;
	char temp[ max ], info[ max ], show[ max ] ;
	int i = 0 ;
	strcpy( temp, "User/" ) ;
	strcat( temp, account ) ;
	strcat( temp, "state.txt" ) ;
	fp = fopen( temp, "r" ) ;
	if( fp != 0 ) {
		fscanf( fp, "%s", info ) ;
		while( strcmp( info, show ) != 0 ) {
			if( i > 3 && i % 4 == 0 ) {
				printf( "\n" ) ;
			}
			strcpy( show, info ) ;
			printf( "%-10s\t", show ) ;
			i++ ;
			fscanf( fp, "%s", info ) ;
		}
		fclose( fp ) ;
	} else {
		printf( "Not have this account" ) ;
	}
	printf( "\n-------------------------------------" ) ;
}

void reset() {
	FILE *fp ;
	char mode, temp[ max ], num[ max ] ;
	int last, i ;
	while ( mode != 'y' && mode != 'n' ) {
		printf( "\nAre you sure to reset please press 'Y' or 'N'" ) ;
		mode = getch() ;
		if( mode == 'y' ) {
			fp = fopen( "Admin/account.txt", "r" ) ;
			if( fp != 0 ) {
				fscanf( fp, "%s", temp ) ;
				last = atoi( temp ) ;
				for( i = 1 ; i <= last ; i++ ) {
					itoa( i, num, 10 ) ;
					strcpy( temp, "User/" ) ;
					strcat( temp, num ) ;
					strcat( temp, ".txt" ) ;
					remove( temp ) ;
					itoa( i, num, 10 ) ;
					strcpy( temp, "User/" ) ;
					strcat( temp, num ) ;
					strcat( temp, "state.txt" ) ;
					remove( temp ) ;
				}
				fclose( fp ) ;
				remove( "Admin/account.txt" ) ;
				remove( "Admin/admin.txt" ) ;
				printf( "\nReset this program success!!!" ) ;
				exit( 0 ) ;
			}
		}
		if( mode == 'n' ) {
			printf( "\nNot reset this program" ) ;
		}
	}
	printf( "\n-------------------------------------" ) ;
}

void loginadmin() {
	char mode, account[ max ] ;
	if( checkadmin() ) {
		while( mode != 'e' ) {
			printf( "\nPlease select admin mode" ) ;
			printf( "\n1 : Add user" ) ;
			printf( "\n2 : Delete user" ) ;
			printf( "\n3 : Edit admin" ) ;
			printf( "\n4 : Show user" ) ;
			printf( "\n5 : Deposit" ) ;
			printf( "\n6 : Withdraw" ) ;
			printf( "\n7 : Show statement" ) ;
			printf( "\n8 : reset program" ) ;
			printf( "\nE : Exit" ) ;
			printf( "\n-------------------------------------" ) ;
			mode = getch() ;
			switch( mode ) {
				case '1' :	adduser() ;
							break ;
				case '2' :	printf( "\naccount to delete : " ) ;
							scanf( "%s", &account ) ;
							deleteuser( account ) ;
							break ;
				case '3' :	editadmin() ;
							break ;
				case '4' :	showuser() ;
							break ;
				case '5' :	printf( "\naccount to deposit : " ) ;
							scanf( "%s", &account ) ;
							deposit( account ) ;
							break ;
				case '6' :	printf( "\naccount to withdraw : " ) ;
							scanf( "%s", &account ) ;
							withdraw( account ) ;
							break ;
				case '7' :	printf( "\naccount to statement : " ) ;
							scanf( "%s", &account ) ;
							statement( account ) ;
							break ;
				case '8' :	reset() ;
							break ;
			}
		}
	}
}

bool checkuser( char account[ max ] ) {
	FILE *fp ;
	int i ;
	char temp[ max ], pass[ max ] ;
	printf( "password : " ) ;
	scanf( "%s", &pass ) ;
	strcpy( temp, "User/" ) ;
	strcat( temp, account ) ;
	strcat( temp, ".txt" ) ;
	fp = fopen( temp, "r" ) ;
	if( fp != 0 ) {
		for( i = 0 ; i < 4 ; i++ ) {
			fscanf( fp, "%s", temp ) ;
		}
		fclose( fp ) ;
		if( !strcmp( pass, temp ) ) {
			printf( "login with user ID : %s success", account ) ;
			printf( "\n-------------------------------------" ) ;
			return( true ) ;
		}
	}
	printf( "Your ID or password wrong" ) ;
	printf( "\n-------------------------------------" ) ;
	return( false ) ;
}

void showself( char account[ max ] ) {
	FILE *fp ;
	char temp[ max ] ;
	int i ;
	strcpy( temp, "User/" ) ;
	strcat( temp, account ) ;
	strcat( temp, ".txt" ) ;
	fp = fopen( temp, "r" ) ;
	for( i = 0 ; i < 12 ; i++ ) {
		fscanf( fp, "%s", temp ) ;
		if( i % 2 == 0 ) {
			printf( "%s : ", temp ) ;
		} else {
			printf( "%-8s", temp ) ;
		}
	}
	fclose( fp ) ;
	printf( "\n-------------------------------------" ) ;
}

int loginuser() {
	char mode, account[ max ] ;
	printf( "\nUser ID : " ) ;
	scanf( "%s", &account ) ;
	if( checkuser( account ) ) {
		while( mode != 'e' ) {
			printf( "\nPlease select user mode" ) ;
			printf( "\n1 : Delete self" ) ;
			printf( "\n2 : Edit information" ) ;
			printf( "\n3 : Show Infomation" ) ;
			printf( "\n4 : Deposit" ) ;
			printf( "\n5 : Withdraw" ) ;
			printf( "\n6 : Show statement" ) ;
			printf( "\nE : Exit" ) ;
			printf( "\n-------------------------------------" ) ;
			mode = getch() ;
			switch( mode ) {
				case '1' :	printf( "\n" ) ;
							deleteuser( account ) ;
							return( 0 ) ;
				case '2' :	printf( "\n" ) ;
							userinfo( account ) ;
							break ;
				case '3' :	printf( "\n" ) ;
							showself( account ) ;
							break ;
				case '4' :	printf( "\n" ) ;
							deposit( account ) ;
							break ;
				case '5' :	printf( "\n" ) ;
							withdraw( account ) ;
							break ;
				case '6' :	printf( "\n" ) ;
							statement( account ) ;
							break ;
			}
		}
	}
}

void howto() {
	FILE *fp ;
	fp = fopen( "Admin/instruction.txt", "r" ) ;
	char temp1[ max ], temp2[ max ] ;
	int end ;
	fscanf( fp, "%s", temp1 ) ;
	while( strcmp( temp1, temp2 ) ) {
		strcpy( temp2, temp1 ) ;
		fscanf( fp, "%s", temp1 ) ;
		if( temp2[ 1 ] == '-' ) {
			printf( "\t" ) ;
		}
		printf( "%s ", temp2 ) ;
		end = strlen( temp2 ) ;
		if( temp2[ end - 1 ] == '.' ) {
			printf( "\n" ) ;
		}
	}
	fclose( fp ) ;
	printf( "\n-------------------------------------" ) ;
}

int main() {
	char mode ;
	while( mode != 'e' ) {
		printf( "select mode :" ) ;
		printf( "\n1 : Login with admin mode" ) ;
		printf( "\n2 : Login with user mode" ) ;
		printf( "\n3 : How to user this program" ) ;
		printf( "\nE : Exit" ) ;
		printf( "\n-------------------------------------" ) ;
		mode = getch() ;
		switch( mode ) {
			case '1' :	loginadmin() ;
						break ;
			case '2' :	loginuser() ;
						break ;
			case '3' :	howto() ;
		}
		printf( "\n" ) ;
	}
}
