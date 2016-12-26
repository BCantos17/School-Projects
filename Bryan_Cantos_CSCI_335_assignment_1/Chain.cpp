// Created by Bryan Cantos
// Class CSCI 335

using namespace std;

Chain::Chain(): item_count(0), chain_arr(new int{CAPACITY})
{
}// End Default Constructor

Chain::Chain(int new_entry)
{
    item_count = 1;
    chain_arr = new int{CAPACITY};
    chain_arr[0] = new_entry;
}// End Copy Constructor

Chain::Chain(const Chain & right_hand_side)
{
    chain_arr = new int{CAPACITY};
    item_count = right_hand_side.item_count;
    //Copies contents from right hand side to the new Chain
    for(int i = 0; i < item_count;i++)
        chain_arr[i] = right_hand_side.chain_arr[i];
}// End Copy Constructor

Chain::~Chain()
{
    delete chain_arr;
}// End Destructor

Chain::Chain(Chain && right_hand_side): item_count(0), chain_arr(nullptr)
{
    item_count = right_hand_side.item_count;
    chain_arr = new int{CAPACITY};
    //Copies contents from right hand side to the new Chain
    for(int i = 0; i  < item_count; i++)
        chain_arr[i] = right_hand_side.chain_arr[i];
    right_hand_side.chain_arr = nullptr;
}// End Move Constructor

Chain & Chain::operator= (const Chain & right_hand_side)
{
    if(this != &right_hand_side)
    {
        Clear();
        CopyChainFrom(right_hand_side);
    }
    return *this;
}// End Copy Assignment

Chain & Chain::operator= (Chain && right_hand_side)
{
    Chain copy = right_hand_side;
    swap(*this, copy);
    return *this;
}// End Move Assignment

Chain Chain::operator+ (const Chain& right_hand_side) const
{
    Chain new_chain;
    new_chain.chain_arr= new int[CAPACITY];

   //Copies contents from left hand side to the new Chain
    for(int i = 0; i < item_count; i++)
    {
        new_chain.chain_arr[i] = chain_arr[i];
        new_chain.item_count++;
    }

    //Copies contents from right hand side to the new Chain
    for(int j = 0; j < right_hand_side.item_count; j++)
    {
        new_chain.chain_arr[item_count + j] = right_hand_side.chain_arr[j];
        new_chain.item_count++;
    }

    return new_chain;
}

Chain Chain::operator+ (int an_entry) const
{
    Chain new_chain;
    new_chain.chain_arr = new int[item_count + 1];

    //Copies contents from left hand side to the new Chain
    for(int i = 0; i < item_count; i++)
        new_chain.chain_arr[i] = chain_arr[i];

    //Add the new entry to the new chain
    new_chain.chain_arr[item_count] = an_entry;
    new_chain.item_count = item_count + 1;

    return new_chain;
}

int & Chain::operator[] (int chain_item)
{
    return chain_arr[chain_item];
}

ostream & operator<<(ostream & out_stream, const Chain & output_chain)
{
    out_stream << "[";

    //Outputs ever item in the array
    for(int i = 0;i < output_chain.item_count - 1; i++)
        out_stream << output_chain.chain_arr[i] << " ";

    out_stream << output_chain.chain_arr[ output_chain.item_count - 1 ]<< "]" << endl;

    return out_stream;
}

istream & operator>>(istream& in_stream, Chain& input_chain)
{
    string user_input; 

    cout << "Please enter numbers you want in the Chain. Type in stop to stop" << endl;
    //User inputs numbers and must type stop in order to stop
    while (in_stream >> user_input && user_input != "stop") 
    {
        int item = atoi(user_input.c_str());
        input_chain.Add(item);
    }
    return in_stream;
}

int Chain::Length()
{
    return item_count;
}

void Chain::Clear()
{
    chain_arr = nullptr;
    item_count = 0;
}

void Chain::CopyChainFrom(const Chain & a_chain)
{
    item_count = a_chain.item_count;
    chain_arr = new int{CAPACITY};
    for(int i = 0; i < item_count; i++)
        chain_arr[i] = a_chain.chain_arr[i];
}

void Chain::Add(int new_entry)
{
    chain_arr[item_count] = new_entry;
    item_count++;
}