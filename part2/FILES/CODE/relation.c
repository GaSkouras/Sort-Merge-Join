#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../HEADERS/relation.h"

relation_data *relation_data_create ( relation_data *this ) {
	this = malloc ( sizeof ( relation_data ) ) ;
	return this;
}

relation_data *relation_data_create_relations ( relation_data *this , uint64_t total_columns , uint64_t total_tuples ) {
	this->numColumns = total_columns;
	this->columns = malloc ( total_columns * sizeof ( relation * ) );
	for ( int i = 0 ; i < total_columns ; i++ ) {
		this->columns[i] = relation_create ( this->columns[i] );
		this->columns[i] = relation_createtuples ( this->columns[i] , total_tuples );
	}
	return this;
}



relation * relation_create ( relation *this ) {
	this = malloc ( sizeof ( relation ) ) ;
	return this;
}

relation * relation_createtuples ( relation *this , int num /* number of tuples */ ) {
	//
	this->num_tuples = num ;
	//
	this->tuples = malloc ( num * sizeof(tuple) ) ;

	return this;
}

relation_data *relation_copy ( relation_data *original , relation_data *copy ) {
	uint64_t total_columns = original->numColumns;
	uint64_t total_tuples = original->numTuples;

	printf("TOTAL COLUMNS ARE %ld and total_tuples ARE %ld\n",total_columns,total_tuples);
	copy = relation_data_create( copy );
	copy = relation_data_create_relations ( copy , total_columns , total_tuples );
	return copy;
}

void relation_setkey( relation *this , int tup /*position of tuple that we want to set*/ , uint64_t key /*key we want to set*/ ) {
	
	tuple_setkey ( &this->tuples[tup] , key );

}

uint64_t relation_getkey ( relation *this , int tup /*position of tuple that we want to get*/) {
	
	uint64_t key = tuple_getkey ( &this->tuples[tup] );
	return key;

}




void relation_setpayload ( relation *this , int tup /*position of tuple that we want to set*/ , uint64_t payl /*payload we want to set*/ ) {
	
	tuple_setpayload ( &this->tuples[tup] , payl );

}

uint64_t relation_getpayload ( relation *this , int tup /*position of tuple that we want to get*/) {
	
	uint64_t payl = tuple_getpayload ( &this->tuples[tup] );
	return payl;

}

int relation_getnumtuples ( relation * this ) {
	return this->num_tuples ;
}

int relation_checkifsorted ( relation * this ) {
	int flag = 0;
	int total_tuples = relation_getnumtuples ( this ) ;
	for (int i = 1; i <=total_tuples ; i++ ){
		if ( relation_getkey(this,i) <= relation_getkey(this,i-1)) {
			//printf("%llu is smaller than %llu \n",relation_getkey(this,i) , relation_getkey(this,i-1) );
			flag = 1;
		}
	}
	return flag ;
}

void relation_print ( relation *rel ) {

	for (int i = 0; i < rel->num_tuples ; i++ ) {
		printf ( "PAYLOAD IS %ld KEY IS %ld \n" , relation_getpayload ( rel , i ) ,  relation_getkey ( rel , i )  ) ;
	}
}

void relation_free ( relation *rel ) {
	free (rel->tuples);
}

int isEqual(relation *rel_left, relation *rel_right, uint64_t i, uint64_t k)
{
	return rel_left->tuples[i].payload == rel_right->tuples[k].payload;
}

int isGreater ( relation *rel_left, relation *rel_right, int i, int k ) {
	if ( rel_left->tuples[i].payload > rel_right->tuples[k].payload ) {
		return 1;
	}
	else {
		return 0;
	}
}

