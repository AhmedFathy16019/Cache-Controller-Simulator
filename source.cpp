#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>
using namespace std;

// Object to imitate structure of cache line
class line
{
public:
    bool valid;
    int tag;
};

// Function to convert Binary Addresses to Decimal Addresses
int binaryToDecimal(string n)
{
    string num = n;
    int dec_value = 0;
    int base = 1;
    int len = num.length();
    for (int i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }
    return dec_value;
}


int main()
{
    // Variables Declaration
    int size, line_size, cycles, dec_seq;
    vector<string> sequence_bits; //copy of the file
    vector<int> sequence_dec; //addresses of the file decimal
    vector<line> cache;
    float hits, miss, access;
    hits = 0;
    miss = 0;
    access = 0;
    // Taking Input Variables
    cout << "Enter Total Cache Size: ";
    cin >> size;
    cout << endl << "Enter cache line size: ";
    cin >> line_size;
    cout << endl << "Enter number of cycles to access cache: ";
    cin >> cycles;
    // Reading Sequence from Text File
    ifstream file;
    fstream data;
    string seq;
    data.open("Test 2.txt");
    if (!data.is_open())
        cout << "Error in opening data file";
    else
    {
        while (!data.eof())
        {
            getline(data, seq);
            sequence_bits.push_back(seq); // Addresses in Binary
            dec_seq = binaryToDecimal(seq); // Converting to Decimal
            sequence_dec.push_back(dec_seq); // Addresses in Decimal
        }
    }
    data.close();
    // Calculating Number of lines in cache
    int num_lines = size / line_size;
    // Initiallizing Empty Cache
    for (int i = 0; i < num_lines; i++)
    {
        // Temp object for initialization
        line temp;
        temp.valid = 0;
        temp.tag = -1; //No Address is Negative and Avoid Uninitiallization Errors
        cache.push_back(temp);
    }
    // Instance Variables
    int in_tag;
    int in;
    int tag;
    string status;
    // Miss/Hit Rate
    float hit_rate;
    float miss_rate;
    // Looping Sequence
    for (int i = 0; i < sequence_dec.size(); i++)
    {
        // Calculating Index and Tag of current address
        in_tag = sequence_dec[i] / line_size;
        in = in_tag % num_lines;
        tag = in_tag / num_lines;
        access++;
        status = "NULL"; // Avoid not updating status from previous access
        // Printing Info of current Iteration
        cout << endl << "Address in Binary: " << sequence_bits[i] << "  Address in Decimal: " << sequence_dec[i] << endl;
        cout << "Before Access: Valid is: " << cache[in].valid << "   Tag is: " << cache[in].tag << endl;
        if (cache[in].valid == true)
        {
            if (cache[in].tag == tag)
            {
                // Hit Case
                hits++;
                status = "Hit";
            }
            else
            {
                // Conflict or Capacity Miss Case
                miss++;
                cache[in].tag = tag;
                status = "Miss";
            }
        }
        else
        {
            // Cold Start Miss Case
            miss++;
            cache[in].tag = tag;
            cache[in].valid = true;
            status = "Miss";
        }
        hit_rate = (hits / access);
        miss_rate = (miss / access);
        cout << "After Access: Valid is: " << cache[in].valid << "   Tag is: " << cache[in].tag << endl;
        cout << "Hit / Miss: " << status << endl;
        cout << "Number of Accesses: " << access << endl;
        cout << "Hit Rate is: " << hit_rate << endl;
        cout << "Miss Rate is: " << miss_rate << endl;
    }
    // Calculating Results after all acesses
    hit_rate = (hits / access);
    miss_rate = (miss / access);
    float AMAT = (hit_rate * cycles) + (miss_rate * 100);
    cout << "Information of the whole program:" << endl;
    cout << "Total Number of Accesses: " << access << endl;
    cout << "Hit Rate is: " << hit_rate << endl;
    cout << "Miss Rate is: " << miss_rate << endl;
    cout << "Average Memory Access Time (AMAT) is: " << AMAT << endl;
    return 0;
}