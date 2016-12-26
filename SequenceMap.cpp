/* Bryan Cantos 2015
   CSCI 335 Assignment 2*/

SequenceMap::SequenceMap() {
}  /*end default constructor*/

SequenceMap::SequenceMap(const string & aKey) {
	key = aKey;
} /*end of one parameter constructor*/

SequenceMap::SequenceMap(const string & aKey, const string & anElement) {
	key = aKey;
	elements.insert(elements.begin(), anElement);
} /*end of two parameter constructor*/

bool SequenceMap::operator< (const SequenceMap & rightSide) const {
	return key < rightSide.key;
} /*end less than assignment*/

bool SequenceMap::operator== (const SequenceMap & rightSide) const {
	return key == rightSide.key;
}

void SequenceMap::Merge(const SequenceMap & other) {
	for(int i = 0; i < other.elements.size(); i++)
		elements.push_back(other.elements[i]);
} /*end Merge()*/

void SequenceMap::Replace(const string & aKey, const string & anElement) {
	vector<string> newElement;
	key = aKey;
	newElement.insert(newElement.begin(), anElement);
	elements = newElement;
} /*end Replace()*/

ostream& operator<<(ostream& output, const SequenceMap & rightSide){
    output <<rightSide.key << " = [ ";
    for(int i = 0; i < rightSide.elements.size();i++)
		output << rightSide.elements[i] << " ";
	output << "]";
    return output;
} /*end output operator overload*/