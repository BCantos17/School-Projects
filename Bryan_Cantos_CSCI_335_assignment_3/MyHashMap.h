/** 
 * Created and modified by Bryan Cantos 2015
 * CSCI 335
 **/

#ifndef MY_HASH_MAP_H
#define MY_HASH_MAP_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;

template<typename KeyType, typename ObjectType>
class MyHashMap 
{
  public:
	enum EntryType { ACTIVE, EMPTY, DELETED };

  private:
	struct HashEntry
    {
		KeyType		element;
		ObjectType	mapped;
		EntryType	info;

		HashEntry( 	const KeyType & e = KeyType{ }, 
					const ObjectType & m = ObjectType{ }, 
					EntryType i = EMPTY )
					: element{ e }, mapped{ m }, info{ i } { }
        
		HashEntry( 	KeyType && e, 
					ObjectType && m, 
					EntryType i = EMPTY )
				: element{ std::move( e ) }, mapped{ std::move( m ) }, info{ i } { }
	};
	vector<HashEntry> array;
	int currentSize;

  public:
	/****************OUTER FUNCTIONS******************/
	explicit MyHashMap 			( int size );
	void makeEmpty				();
	bool insert					( const KeyType & key, const ObjectType & obj );
	bool insert					( const KeyType && key, const ObjectType && obj );
	bool remove					( const KeyType & key );
	bool contains				(const KeyType & key ) const;
	ObjectType find				( const KeyType & key ) const;
	ObjectType & operator[]		( const KeyType & key );
	ObjectType & operator[]		( const KeyType && key );

  	/*****************ITERATOR FUNCTIONS****************/

	typedef typename std::vector<HashEntry>::iterator iterator;
	typedef typename std::vector<HashEntry>::const_iterator const_iterator;

	iterator 		begin() 		{ return array.begin(); }
	const_iterator 	begin() const 	{ return array.begin(); }
	iterator 		end() 			{ return array.end(); }
	const_iterator 	end() 	const 	{ return array.end(); }

  private:
    /****************INNER FUNCTIONS******************/

	bool	isActive	( int currentPos ) const;
	int 	findPos		( const KeyType & key ) const;
	void 	rehash		();
	size_t 	myhash 		( const KeyType & key ) const;
	bool 	insertKey	( const KeyType & key, const int currentPos );
	bool 	insertKey	( const KeyType && key, const int currentPos );
	bool	isPrime		( int n );
	int 	nextPrime	( int n );
};

#include "MyHashMap.cpp"
#endif