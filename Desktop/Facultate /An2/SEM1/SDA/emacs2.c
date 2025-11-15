#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define COMMANDS_FILE "operations.txt"
#define CONTENT_LIMIT 4096
#define FILENAME_LIMIT 128
#define COMMAND_LINE_LIMIT 5200

/*
* exemplu comenzi ( doar astea sunt )
OPEN file1.txt
PRINT file1.txt

OPEN file2.txt
PRINT file2.txt

WRITE file1.txt 5 12345
PRINT file1.txt

DELETE file1.txt 20 7
PRINT file1.txt

WRITE file1.txt 100 *******
PRINT file1.txt

SAVEAS file1.txt ceva.txt
PRINT file1.txt

PRINT file2.txt
SAVEAS file2.txt altceva.txt
PRINT file2.txt
*/

typedef enum
{
	OPEN = 1, // -1 si 0 rezervate pentru cazuri speciale
	WRITE, DELETE, PRINT, SAVEAS
} OPERATIE;

typedef struct node
{
	struct node *nxt;
	// FILE *file;
	char *filename;
	char *content; // il va contine si pe EOF
	unsigned int content_size; // il va contine si pe EOF
} NODE;

void eliberare ( NODE *node )
{
	if ( node == NULL ) return;

	NODE *nxt = node->nxt;

	// fclose ( node->file );
	free ( node->filename );
	free ( node->content );
	free ( node );

	eliberare ( nxt );
}

int potrivire_string ( const char *string1, const char *string2 )
{
	if ( strcmp ( string1, string2 ) == 0 )
		return 1;
	return 0;
}

unsigned int maxim ( unsigned int nr1, unsigned int nr2 )
{
	if ( nr1 >= nr2 ) return nr1;
	return nr2;
}

unsigned int minim ( unsigned int nr1, unsigned int nr2 )
{
	if ( nr1 <= nr2 ) return nr1;
	return nr2;
}
/*
int isalpha ( char ch )
{
	return '0' <= ch && ch <= '9';
	}*/

unsigned int strtou ( const char *str )
{
	unsigned int ret = 0, index = 0;

	while ( str[index] != '\0' && isalpha ( str[index] ) ) ret = ret * 10 + str[index++] - '0';

	return ret;
}

NODE *open ( const char *filename, NODE *list ) // ADAUGA FISIERELE LA INCEPUTUL LISTEI
{
	NODE *nod_nou = malloc ( sizeof ( NODE ) ); // nodul pe care il vom adauga la lista, la inceput

	if ( nod_nou == NULL )
	{
		perror ( "Eroare la alocare lista - nod_nou\n" );
		eliberare ( list );
		free ( nod_nou );
		exit ( -1 );
	}

	// alocari initiale

	nod_nou->filename = malloc ( sizeof ( char ) * FILENAME_LIMIT );

	if ( nod_nou->filename == NULL )
	{
		perror ( "Eroare la alocare lista - nod_nou - filename\n" );
		eliberare ( list );
		free ( nod_nou );
		exit ( -1 );
	}

	strcpy ( nod_nou->filename, filename );

	nod_nou->content = malloc ( sizeof ( char ) * CONTENT_LIMIT );

	nod_nou->content_size = 0;

	if ( nod_nou->filename == NULL || nod_nou->content == NULL )
	{
		perror ( "Eroare la alocare lista - nod_nou - strings\n" );
		eliberare ( list );
		eliberare ( nod_nou );
		exit ( -1 );
	}


	// citirea initiala ( daca fisierul e deja pe disc )

	FILE *file = NULL;
	file = fopen ( nod_nou->filename, "r" );

	if ( file != NULL )
	{
		char ch;
		do
		{
			ch = fgetc ( file );
			nod_nou->content[nod_nou->content_size++] = ch;
		} while ( ch != EOF && nod_nou->content_size < CONTENT_LIMIT - 2 ); // rezerva loc pentru EOF si '\0'

		if ( ch != EOF ) // ocupare loc EOF daca e nevoie
			nod_nou->content[nod_nou->content_size++] = EOF;
		nod_nou->content[nod_nou->content_size++] = '\0'; // incheiere string
	
		fclose ( file );
	}


	// cazul normal

	file = fopen ( nod_nou->filename, "a" );

	if ( file == NULL )
	{
		perror ( "Eroare la alocare lista - file\n" );
		eliberare ( list );
		eliberare ( nod_nou );
		exit ( -1 );
	}

	// nod_nou->file = file;
	nod_nou->nxt = list;

	return nod_nou;
}

void write ( const char *filename, const unsigned int index, const char *word, NODE *node )
{
	if ( node == NULL ) // filename not found in list case
	{
		printf ( "Fisierul nu a fost gasit!\n" );
		return;
	}

	// average case

	if ( potrivire_string ( filename, node->filename ) ) // filename found
	{
		/*
		// if ( node->content_size == 2 || index >= node->content_size ) // fisierul este gol SAU indexul este mai mare decat marimea reala ( content_size - 1 )
		if ( index >= node->content_size - 2 ) // indexul se suprapune peste continutul propriu-zis al fisierului ( exc. EOF si '\0' )
			start_index = node->content_size - 2;
		else
			start_index = index;
		*/

		// prepare index to write to

		unsigned int start_index = minim ( node->content_size - 2, index );

		char *str_tmp = malloc ( sizeof ( char ) * node->content_size );

		if ( str_tmp == NULL )
		{
			perror ( "Eroare alocare string - str_tmp");
			exit ( -1 );
		}

		strcpy ( str_tmp, node->content + start_index );
		strcpy ( node->content + start_index, word );
		strcpy ( node->content + start_index + strlen ( word ), str_tmp );

		free ( str_tmp );

		node->content_size += ( unsigned int ) strlen ( word );

		return;
	}

	else // try next node for filename
	{
		write ( filename, index, word, node->nxt );
	}
}

void delete ( const char *filename, const unsigned int index, const unsigned int count, NODE *node )
{
	if ( node == NULL ) // filename not found in list case
	{
		printf ( "Fisierul nu a fost gasit!\n" );
		return;
	}

	// average case

	if ( potrivire_string ( filename, node->filename ) ) // filename found
	{
		// prepare index to delete from and actual delete size

		unsigned int start_index = minim ( node->content_size - 2, index );
		unsigned int count_real = minim ( node->content_size - 2 - start_index, count );

		char *str_tmp = malloc ( sizeof ( char ) * node->content_size );

		if ( str_tmp == NULL )
		{
			perror ( "Eroare alocare string - str_tmp" );
			exit ( -1 );
		}

		strcpy ( str_tmp, node->content + start_index + count_real );
		strcpy ( node->content + start_index, str_tmp );

		free ( str_tmp );

		node->content_size -= count_real;

		return;
	}

	else // try next node for filename
	{
		delete ( filename, index, count, node->nxt );
	}
}

void printare_string ( const char *string )
{
	unsigned int size = ( unsigned int ) strlen ( string );
	for ( unsigned int i = 0; i < size && string[i] != EOF; i++ )
		printf ( "%c", string[i] );

	printf ( "\n\n\n" );
}

void print ( const char *filename, NODE *node )
{
	if ( node == NULL ) // filename not found in list case
	{
		printf ( "Fisierul nu a fost gasit!\n" );
		return;
	}

	// average case

	if ( potrivire_string ( filename, node->filename ) ) // filename found
	{
		printf ( "_________________________________________________________\n" );
		printf ( "\t%s\n", node->filename );
		printf ( "_________________________________________________________\n" );
		// printf ( "%s\n\n\n", node->content );
		printare_string ( node->content );

		return;
	}

	else // try next node for filename
	{
		print ( filename, node->nxt );
	}
}

void scriere_fisier ( const char *filename, const char *string, NODE *list )
{
	FILE *file = fopen ( filename, "w" );

	if ( file == NULL )
	{
		perror ( "Eroare la alocare fisier\n" );
		eliberare ( list );
		exit ( -1 );
	}

	fprintf ( file, "%s", string );

	fclose ( file );
}

NODE *saveas ( const char *filename, const char *newfile, NODE *node, NODE *prev, NODE *list ) // 2 pointeri tip NODE pentru cazul in care se elimina primul nod
{
	if ( node == NULL ) // filename not found in list case
	{
		printf ( "Fisierul nu a fost gasit!\n" );
		return list;
	}

	// average case

	if ( potrivire_string ( filename, node->filename ) ) // filename found
	{
		scriere_fisier ( newfile, node->content, list );

		if ( node == list ) // primul nod trebuie sters
			list = node->nxt;
		else // trebuie sters un nod din mijloc / final
			prev->nxt = node->nxt;

		node->nxt = NULL;
		eliberare ( node );

		return list;
	}

	else // try next node for filename
	{
		return saveas ( filename, newfile, node->nxt, node, list );
	}
}

void procesare()
{
	FILE *file_commands = fopen ( COMMANDS_FILE, "r" );

	if ( file_commands == NULL )
	{
		perror ( "Eroare la alocare fisier - commands" );
		exit ( -1 );
	}

	char *comanda = malloc ( sizeof ( char ) * COMMAND_LINE_LIMIT );

	NODE *list = NULL;

	OPERATIE operatie = -1;

	char filename[FILENAME_LIMIT];
	char new_filename[FILENAME_LIMIT];
	char word[CONTENT_LIMIT];
	unsigned int index, count;

	while ( ( comanda = fgets ( comanda, COMMAND_LINE_LIMIT, file_commands ) ) != NULL )
	{
		if ( potrivire_string ( comanda, "\n" ) ) continue; // pentru a filtra liniile goale din fisierul de comenzi

		comanda[strlen ( comanda )] = '\0';
		char *p = strtok ( comanda, " \n" );

		if ( potrivire_string ( p, "OPEN" ) ) operatie = OPEN;
		if ( potrivire_string ( p, "WRITE" ) ) operatie = WRITE;
		if ( potrivire_string ( p, "DELETE" ) ) operatie = DELETE;
		if ( potrivire_string ( p, "PRINT" ) ) operatie = PRINT;
		if ( potrivire_string ( p, "SAVEAS" ) ) operatie = SAVEAS;

		p = strtok ( NULL, " \n" );
		strcpy ( filename, p );

		switch ( operatie )
		{

		case ( OPEN ):
			list = open ( filename, list );
			break;

		case ( WRITE ):
			p = strtok ( NULL, " \n" );
			index = strtou ( p );
			p = strtok ( NULL, " \n" );
			strcpy ( word, p );
			write ( filename, index, word, list );
			break;

		case ( DELETE ):
			p = strtok ( NULL, " \n" );
			index = strtou ( p );
			p = strtok ( NULL, " \n" );
			count = strtou ( p );
			delete ( filename, index, count, list );
			break;

		case ( PRINT ):
			print ( filename, list );
			break;

		case ( SAVEAS ):
			p = strtok ( NULL, " \n" );
			strcpy ( new_filename, p );
			list = saveas ( filename, new_filename, list, NULL, list );
			break;

		default:
			break;

		}
	}
}

int main ( void )
{
	procesare();

	return 0;
}
