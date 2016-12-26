/** 
 * Created and modified by Bryan Cantos 2015
 * CSCI 335
 **/

/***************************************PUBLIC FUNCTIONS*************************************/

// void makeEmpty			() 				--> Lazy deletion of map
// bool insert				( key, obj )  	--> copys lvalue into map
// bool insert				( key, obj ) 	--> move rvalue into map
// bool remove				( key )			--> lazy deletion of key
// bool contains			( key ) 		--> returns true if found
// ObjectType find			( key ) 		--> returns object of key
// ObjectType & operator[]	( key ) 		--> returns object of key, inserts lvalue if not found
// ObjectType & operator[]	( key ) 		--> returns object of key, move rvalue if not found

/**
 *  Default Contructor
 */
template<class KeyType, class ObjectType>
MyHashMap<KeyType, ObjectType>::MyHashMap( int size ) : array( nextPrime( size ) )
{ makeEmpty(); }

/**
 *  Lazy Deletion of map
 */
template<class KeyType, class ObjectType>
void MyHashMap<KeyType, ObjectType>::makeEmpty( )
{
	currentSize = 0;
	for( auto & entry : array )
		entry.info = EMPTY;
}


/**
 *  Copy Key and object into the map
 */
template<class KeyType, class ObjectType>
bool MyHashMap<KeyType, ObjectType>::insert( const KeyType & key, const ObjectType & obj )
{
	// Find key hash value
	int currentPos = findPos( key );

	if( isActive( currentPos ) )
		return false;

	// Insert Items
	array[ currentPos ].element = key;
	array[ currentPos ].mapped = obj;
	array[ currentPos ].info = ACTIVE;

	if( ++currentSize > array.size( ) / 2 )
		rehash( );

	return true;
}

/**
 *  Move Key and Object into the map
 */
template<class KeyType, class ObjectType>
bool MyHashMap<KeyType, ObjectType>::insert( const KeyType && key, const ObjectType && obj )
{
	// Find key hash value
	int currentPos = findPos( key );
	if( isActive( currentPos ) )
		return false;

	// Move Items in array
	array[ currentPos ].element = std::move( key );
	array[ currentPos ].mapped = std::move( obj );
	array[ currentPos ].info = ACTIVE;

	if( ++currentSize > array.size( ) / 2 )
		rehash( );

	return true;
}

/**
 *  Lazy Deletion of Key
 */
template<class KeyType, class ObjectType>
bool MyHashMap<KeyType, ObjectType>::remove( const KeyType & key )
{
	int currentPos = findPos( key );
	if( !isActive( currentPos ) )
		return false;

	array[ currentPos ].info = DELETED;
	return true;
}

/**
 *  Returns true if found
 */
template<class KeyType, class ObjectType>
bool MyHashMap<KeyType, ObjectType>::contains( const KeyType & key ) const
{
	return isActive( findPos( key ) );
}

/**
 *  Finds a Key iand return object.
 */
template<class KeyType, class ObjectType>
ObjectType MyHashMap<KeyType, ObjectType>::find( const KeyType & key ) const
{
	int currentPos = findPos ( key );
	if( isActive( currentPos ) )
		return array[ currentPos ].mapped;
	else {
		ObjectType nothing;
		return nothing;
	}
}

/**
 *  Overload Bracket operator, insert if new element
 *  Return Mapped object
 */
template<class KeyType, class ObjectType>
ObjectType & MyHashMap<KeyType, ObjectType>::operator[]( const KeyType & key )
{	
	int currentPos = findPos( key );
	if( !isActive( currentPos ) ) {
		if(  array[ currentPos ].info == DELETED )
			array[ currentPos ].info == ACTIVE;
		else
			insertKey( key, currentPos );
	}
		return array[ currentPos ].mapped;
}

/**
 *  Overload Bracket operator, move into map if new element
 *  Return Mapped object
 */
template<class KeyType, class ObjectType>
ObjectType & MyHashMap<KeyType, ObjectType>::operator[]( const KeyType && key )
{	
	int currentPos = findPos( key );
	if( !isActive( currentPos ) ) {
		if(  array[ currentPos ].info == DELETED )
			array[ currentPos ].info == ACTIVE;
		else
			insertKey( key , currentPos );
	}
	return array[ currentPos ].mapped;
}
					
/***************************************PRIVATE FUNCTIONS*************************************/

//	bool isActive	( currentPos ) 		--> Return true if active
//	int findPos		( key ) 			--> return hash value of key
//	void rehash		() 					--> rehash a map into a bigger one
//	size_t myhash 	( key ) 			--> returns hash % table size
//	bool insertKey	( key, currentPos ) --> inserts a key into map
//	bool insertKey	( key, currentPos ) --> moves a key into map
//	bool isPrime	( n ) 				--> determines if an int is prime
//	int nextPrime	( n ) 				--> if not a prime, gets next prime number of int

/**
 *  Return true if the current position in map is taken
 */
template<class KeyType, class ObjectType>
bool MyHashMap<KeyType, ObjectType>::isActive( int currentPos ) const
{ 
	return array[ currentPos ].info == ACTIVE; 
}

/**
 *  Uses quadratic probing to find the next position in hash map.
 */
template<class KeyType, class ObjectType>
int MyHashMap<KeyType, ObjectType>::findPos( const KeyType & key ) const
{
	int offset = 1;
	int currentPos = myhash( key );

	while( array[ currentPos ].info != EMPTY &&
		   array[ currentPos ].element != key )
	{
		currentPos += offset;  // Compute ith probe
		offset += 2;
		if( currentPos >= array.size( ) )
			currentPos -= array.size( );
		if( array[ currentPos ].element == key )
			break;
	}

	return currentPos;
}

/**
 *  Rehash current map to make it twice as big
 */
template<class KeyType, class ObjectType>
void MyHashMap<KeyType, ObjectType>::rehash( )
{
	vector<HashEntry> oldArray = array;

		// Create new double-sized, empty table
	array.clear();
	array.resize( nextPrime( 2 * oldArray.size( ) ) );

		// Copy table over
	currentSize = 0;
	for( auto & entry : oldArray )
		if( entry.info == ACTIVE )
			insert( std::move( entry.element ), std::move( entry.mapped ) );
}

/**
 *  Gets the hash value of a key
 */
template<class KeyType, class ObjectType>
size_t MyHashMap<KeyType, ObjectType>::myhash( const KeyType & key) const
{
	static hash<KeyType> hf;
	return hf( key ) % array.size();
}

/**
 *  Inserts key into map
 */
template<class KeyType, class ObjectType>
bool MyHashMap<KeyType, ObjectType>::insertKey( const KeyType & key, const int currentPos )
{
		// Insert key as active
	array[ currentPos ].element = key;
	array[ currentPos ].info = ACTIVE;

	if( ++currentSize > array.size( ) / 2 )
		rehash( );

	return true;
}

/**
 *  Inserts key into map
 */
template<class KeyType, class ObjectType>
bool MyHashMap<KeyType, ObjectType>::insertKey( const KeyType && key, const int currentPos )
{
		// Insert key as active
	array[ currentPos ].element = std::move( key );
	array[ currentPos ].info = ACTIVE;

	if( ++currentSize > array.size( ) / 2 )
		rehash( );

	return true;
}

/**
 *  Determines if a number is a Prime
 */
template<class KeyType, class ObjectType>
bool MyHashMap<KeyType, ObjectType>::isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}

/**
 *  If a number is not Prime, get next Prime
 */
template<class KeyType, class ObjectType>
int MyHashMap<KeyType, ObjectType>::nextPrime( int n ) 
{
    if( n % 2 == 0 )
        ++n;

    for( ; !isPrime( n ); n += 2 )
        ;
    return n;
}